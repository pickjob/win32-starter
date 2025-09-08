#include "main.h"

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpDllPath      = _T("Z:\\Personal\\win32-starter\\build\\11.dll_inject\\demo_dll\\libdemo_dll.dll");
    DWORD  dwProcessId    = 21620;
    // 打开注入进程，获取进程句柄
    HANDLE hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwProcessId);
    if (NULL == hRemoteProcess) {
        ShowLastError(_T("OpenProcess"));
        return EXIT_FAILURE;
    }
    SIZE_T  nDllPathLength = 0;
    HRESULT hResult        = StringCchLength(lpDllPath, STRSAFE_MAX_CCH, &nDllPathLength);
    LPVOID  lpRemoteAddr   = VirtualAllocEx(hRemoteProcess, NULL, (nDllPathLength + 1) * sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
    if (NULL == lpRemoteAddr) {
        ShowLastError(_T("VirtualAllocEx"));
        return EXIT_FAILURE;
    }
    if (!WriteProcessMemory(hRemoteProcess, lpRemoteAddr, lpDllPath, (nDllPathLength + 1) * sizeof(TCHAR), NULL)) {
        ShowLastError(_T("WriteProcessMemory"));
        return EXIT_FAILURE;
    }
    HMODULE hDllKernel = GetModuleHandle(_T("kernel32.dll"));
    if (NULL == hDllKernel) {
        ShowLastError(_T("GetModuleHandle"));
        return EXIT_FAILURE;
    }
    FARPROC lpFunLoadLibraryAddr = GetProcAddress(hDllKernel, "LoadLibraryW");
    if (NULL == lpFunLoadLibraryAddr) {
        ShowLastError(_T("GetProcAddress"));
        return EXIT_FAILURE;
    }
    HANDLE hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpFunLoadLibraryAddr, lpRemoteAddr, 0, NULL);
    if (NULL == hRemoteThread) {
        ShowLastError(_T("CreateRemoteThread"));
        return EXIT_FAILURE;
    }
    CloseHandle(hRemoteProcess);
    return EXIT_SUCCESS;
}