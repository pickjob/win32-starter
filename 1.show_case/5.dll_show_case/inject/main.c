#include "main.h"

/**
 * WinMain: 程序入口函数
 */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpShowCase = _T("ShowCase Template");
    HANDLE hStdout    = GetStdHandle(STD_OUTPUT_HANDLE);
    if (INVALID_HANDLE_VALUE == hStdout) {
        ShowLastError(_T("GetStdHandle"), lpShowCase);
        return EXIT_FAILURE;
    }
    LPTSTR lpDllPath
        = _T("C:\\repository\\code\\personal\\win32-starter\\build\\1.show_case\\5.dll_show_case\\libdll_show_case.dll");
    DWORD  dwProcessId    = 20800;
    // 打开注入进程，获取进程句柄
    HANDLE hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION
                                            | PROCESS_VM_WRITE | PROCESS_VM_READ,
                                        FALSE,
                                        dwProcessId);
    if (NULL == hRemoteProcess) {
        ShowLastError(_T("OpenProcess"), lpShowCase);
        return EXIT_FAILURE;
    }
    SIZE_T  nDllPathLength = 0;
    HRESULT hResult        = StringCchLength(lpDllPath, STRSAFE_MAX_CCH, &nDllPathLength);
    LPVOID  lpRemoteAddr
        = VirtualAllocEx(hRemoteProcess, NULL, (nDllPathLength + 1) * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
    if (NULL == lpRemoteAddr) {
        ShowLastError(_T("VirtualAllocEx"), lpShowCase);
        return EXIT_FAILURE;
    }
    if (!WriteProcessMemory(hRemoteProcess, lpRemoteAddr, lpDllPath, (nDllPathLength + 1) * sizeof(TCHAR), NULL)) {
        ShowLastError(_T("WriteProcessMemory"), lpShowCase);
        return EXIT_FAILURE;
    }
    HMODULE hDllKernel = GetModuleHandle(_T("kernel32.dll"));
    if (NULL == hDllKernel) {
        ShowLastError(_T("GetModuleHandle"), lpShowCase);
        return EXIT_FAILURE;
    }
    FARPROC lpFunLoadLibraryAddr = GetProcAddress(hDllKernel, "LoadLibraryW");
    if (NULL == lpFunLoadLibraryAddr) {
        ShowLastError(_T("GetProcAddress"), lpShowCase);
        return EXIT_FAILURE;
    }
    MessageBox(NULL, _T("AA"), _T("BC"), MB_OK);
    HANDLE hRemoteThread = CreateRemoteThread(hRemoteProcess,
                                              NULL,
                                              0,
                                              (LPTHREAD_START_ROUTINE) lpFunLoadLibraryAddr,
                                              lpRemoteAddr,
                                              0,
                                              NULL);
    if (NULL == hRemoteThread) {
        ShowLastError(_T("CreateRemoteThread"), lpShowCase);
        return EXIT_FAILURE;
    }
    CloseHandle(hRemoteProcess);
    LPTSTR lpGreetings      = _T("Hello World\n");
    size_t nGreetingsLength = 0;
    hResult                 = StringCchLength(lpGreetings, STRSAFE_MAX_CCH, &nGreetingsLength);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return EXIT_FAILURE;
    }
    BOOL bWriteSuccess = WriteConsole(hStdout, lpGreetings, nGreetingsLength, 0, NULL);
    if (!bWriteSuccess) {
        ShowLastError(_T("WriteConsole"), lpShowCase);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
