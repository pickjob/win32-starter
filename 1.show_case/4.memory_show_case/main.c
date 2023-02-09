#include "main.h"

SIZE_T FindAllocationSize(HANDLE hProcess, LPVOID lpRegionStartAddress, LPTSTR lpShowCase);

/**
 * WinMain: 程序入口函数
 */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpShowCase = _T("Memory ShowCase");
    HANDLE hStdout    = GetStdHandle(STD_OUTPUT_HANDLE);
    if (INVALID_HANDLE_VALUE == hStdout) {
        ShowLastError(_T("GetStdHandle"), lpShowCase);
        return EXIT_FAILURE;
    }
    DWORD  dwProcessId = 9596;
    HANDLE hProcess    = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
    if (NULL == hProcess) {
        ShowLastError(_T("OpenProcess"), lpShowCase);
        return EXIT_FAILURE;
    }
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, dwProcessId);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        ShowLastError(_T("CreateToolhelp32Snapshot"), lpShowCase);
        CloseHandle(hProcess);
        return EXIT_FAILURE;
    }
    LPVOID                   lpAddress                = NULL;
    MEMORY_BASIC_INFORMATION stMemoryBasicInformation = {0};
    while (TRUE) {
        SIZE_T nSize = VirtualQueryEx(hProcess, lpAddress, &stMemoryBasicInformation, sizeof(stMemoryBasicInformation));
        if (0 == nSize || sizeof(stMemoryBasicInformation) != nSize) {
            // ShowLastError(_T("VirtualQueryEx"), lpShowCase);
            break;
        }
        LPTSTR  lpRegionInfoTemplate   = _T("%p\t%12u\t%s\t%s\n");
        TCHAR   lpRegionInfo[1024 * 2] = {0};
        LPVOID  lpRegionStartAddress;
        SIZE_T  nRegionSize;
        LPTSTR  lpRegionType;
        TCHAR   lpRegionExtraInfo[1024] = {0};
        BOOL    bReserverd              = TRUE;
        HRESULT hResult;
        switch (stMemoryBasicInformation.State) {
            case MEM_FREE:
                bReserverd           = FALSE;
                lpRegionType         = _T("MEM_FREE");
                lpRegionStartAddress = stMemoryBasicInformation.BaseAddress;
                nRegionSize          = stMemoryBasicInformation.RegionSize;
                break;
            case MEM_COMMIT:
                lpRegionType         = _T("MEM_COMMIT");
                lpRegionStartAddress = stMemoryBasicInformation.AllocationBase;
                nRegionSize          = FindAllocationSize(hProcess, lpRegionStartAddress, lpShowCase);
                break;
            case MEM_RESERVE:
                lpRegionType         = _T("MEM_RESERVE");
                lpRegionStartAddress = stMemoryBasicInformation.AllocationBase;
                nRegionSize          = FindAllocationSize(hProcess, lpRegionStartAddress, lpShowCase);
                break;
        }
        if (bReserverd) {
            switch (stMemoryBasicInformation.Type) {
                case MEM_IMAGE:
                    lpRegionType = _T("MEM_IMAGE");
                    break;
                case MEM_MAPPED:
                    lpRegionType = _T("MEM_MAPPED");
                    break;
                case MEM_PRIVATE:
                    lpRegionType = _T("MEM_PRIVATE");
                    break;
            }
            BOOL          bImage          = FALSE;
            MODULEENTRY32 stModuleEntry32 = {0};
            stModuleEntry32.dwSize        = sizeof(stModuleEntry32);
            if (!Module32First(hSnapshot, &stModuleEntry32)) {
                ShowLastError(_T("Module32First"), lpShowCase);
                break;
            }
            do {
                if (lpRegionStartAddress == stModuleEntry32.modBaseAddr) {
                    hResult = StringCchPrintf(lpRegionExtraInfo,
                                              _countof(lpRegionExtraInfo),
                                              _T("%s"),
                                              stModuleEntry32.szExePath);
                    if (FAILED(hResult)) {
                        ShowLastError(_T("StringCchPrintf"), lpShowCase);
                        break;
                    }
                    bImage = TRUE;
                    break;
                }
            } while (Module32Next(hSnapshot, &stModuleEntry32));
            if (!bImage) {
                DWORD dwLen = GetMappedFileName(hProcess, lpRegionStartAddress, lpRegionExtraInfo, _countof(lpRegionExtraInfo));
            }
        }
        hResult = StringCchPrintf(lpRegionInfo,
                                  _countof(lpRegionInfo),
                                  lpRegionInfoTemplate,
                                  lpRegionStartAddress,
                                  nRegionSize,
                                  lpRegionType,
                                  lpRegionExtraInfo);
        if (FAILED(hResult)) {
            ShowLastError(_T("StringCchPrintf"), lpShowCase);
            break;
        }
        SIZE_T nRegionInfoLength = 0;
        hResult                  = StringCchLength(lpRegionInfo, STRSAFE_MAX_CCH, &nRegionInfoLength);
        if (FAILED(hResult)) {
            ShowLastError(_T("StringCchLength"), lpShowCase);
            break;
        }
        BOOL bWriteSuccess = WriteConsole(hStdout, lpRegionInfo, nRegionInfoLength, 0, NULL);
        if (!bWriteSuccess) {
            ShowLastError(_T("WriteConsole"), lpShowCase);
            break;
        }
        lpAddress = ((PBYTE) lpRegionStartAddress + nRegionSize);
    }
    CloseHandle(hSnapshot);
    CloseHandle(hProcess);
    return EXIT_SUCCESS;
}

SIZE_T FindAllocationSize(HANDLE hProcess, LPVOID lpRegionStartAddress, LPTSTR lpShowCase) {
    MEMORY_BASIC_INFORMATION stMemoryBasicInformation = {0};
    LPVOID                   lpStartAddress           = lpRegionStartAddress;
    SIZE_T                   nRegionSize              = 0;
    while (TRUE) {
        SIZE_T nSize
            = VirtualQueryEx(hProcess, lpStartAddress, &stMemoryBasicInformation, sizeof(stMemoryBasicInformation));
        if (0 == nSize || sizeof(stMemoryBasicInformation) != nSize) {
            ShowLastError(_T("VirtualQueryEx"), lpShowCase);
            break;
        }
        if (lpRegionStartAddress != stMemoryBasicInformation.AllocationBase) {
            break;
        }
        nRegionSize += stMemoryBasicInformation.RegionSize;
        lpStartAddress = ((PBYTE) lpStartAddress + stMemoryBasicInformation.RegionSize);
    }
    return nRegionSize;
}
