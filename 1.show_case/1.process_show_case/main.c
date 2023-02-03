#include "main.h"

// 进程环境变量示例
void ShowEnvironment(HANDLE hStdout, LPTSTR lpShowCase);
// 进程当前目录示例
void ShowCurrentDirectory(HANDLE hStdout, LPTSTR lpShowCase);
// 启动进程示例
void ShowCreateProcess(LPTSTR lpShowCase);

/**
 * WinMain: 程序入口函数
 */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpShowCase = _T("Process ShowCase");
    HANDLE hStdout    = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) {
        ShowLastError(_T("GetStdHandle"), lpShowCase);
        return EXIT_FAILURE;
    }
    // 进程环境变量
    ShowEnvironment(hStdout, lpShowCase);
    // 进程当前目录
    ShowCurrentDirectory(hStdout, lpShowCase);
    // 启动进程
    ShowCreateProcess(lpShowCase);
    return EXIT_SUCCESS;
}

// 进程环境变量示例
void ShowEnvironment(HANDLE hStdout, LPTSTR lpShowCase) {
    LPTSTR lpVariableKey   = _T("UserName");
    LPTSTR lpVariableValue = NULL;
    DWORD  nVariableLength = GetEnvironmentVariable(lpVariableKey, lpVariableValue, 0);
    if (ERROR_ENVVAR_NOT_FOUND == GetLastError()) {
        ShowLastError(_T("GetEnvironmentVariable"), lpShowCase);
        return;
    }
    HANDLE hProcessHeap = GetProcessHeap();
    lpVariableValue     = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, (nVariableLength + 1) * sizeof(TCHAR));
    if (NULL == lpVariableValue) {
        ShowLastError(_T("HeapAlloc"), lpShowCase);
        return;
    }
    nVariableLength = GetEnvironmentVariable(lpVariableKey, lpVariableValue, (nVariableLength + 1));
    size_t  nTotal  = 0;
    HRESULT hResult = StringCchLength(lpVariableKey, STRSAFE_MAX_CCH, &nTotal);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return;
    }
    nTotal += nVariableLength;
    TCHAR szVariableInfo[nTotal + 5];
    hResult = StringCchPrintf(szVariableInfo, _countof(szVariableInfo), _T("%s: %s\n"), lpVariableKey, lpVariableValue);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchPrintf"), lpShowCase);
        return;
    }
    hResult = StringCchLength(szVariableInfo, STRSAFE_MAX_CCH, &nTotal);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return;
    }
    BOOL bWriteSuccess = WriteConsole(hStdout, szVariableInfo, nTotal, 0, NULL);
    if (!bWriteSuccess) {
        ShowLastError(_T("WriteConsole"), lpShowCase);
        return;
    }
    if (!HeapFree(hProcessHeap, 0, lpVariableValue)) {
        ShowLastError(_T("HeapFree"), lpShowCase);
        return;
    }
}

// 进程当前目录示例
void ShowCurrentDirectory(HANDLE hStdout, LPTSTR lpShowCase) {
    LPTSTR lpCurrentDirectory = NULL;
    DWORD  nDirectoryLength   = GetCurrentDirectory(0, lpCurrentDirectory);
    if (nDirectoryLength == 0) {
        ShowLastError(_T("GetCurrentDirectory"), lpShowCase);
        return;
    }
    HANDLE hProcessHeap = GetProcessHeap();
    lpCurrentDirectory  = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, (nDirectoryLength + 1) * sizeof(TCHAR));
    if (NULL == lpCurrentDirectory) {
        ShowLastError(_T("HeapAlloc"), lpShowCase);
        return;
    }
    nDirectoryLength = GetCurrentDirectory((nDirectoryLength + 1), lpCurrentDirectory);
    size_t  nTotal   = 0;
    HRESULT hResult  = StringCchLength(lpCurrentDirectory, STRSAFE_MAX_CCH, &nTotal);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return;
    }
    TCHAR szVariableInfo[nTotal + 50];
    hResult
        = StringCchPrintf(szVariableInfo, _countof(szVariableInfo), _T("CurrentDirectory: %s\n"), lpCurrentDirectory);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchPrintf"), lpShowCase);
        return;
    }
    hResult = StringCchLength(szVariableInfo, STRSAFE_MAX_CCH, &nTotal);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return;
    }
    BOOL bWriteSuccess = WriteConsole(hStdout, szVariableInfo, nTotal, 0, NULL);
    if (!bWriteSuccess) {
        ShowLastError(_T("WriteConsole"), lpShowCase);
        return;
    }
    if (!HeapFree(hProcessHeap, 0, lpCurrentDirectory)) {
        ShowLastError(_T("HeapFree"), lpShowCase);
        return;
    }
}

// 启动进程示例
void ShowCreateProcess(LPTSTR lpShowCase) {
    STARTUPINFO stStartupInfo                = {0};
    stStartupInfo.cb                         = sizeof(stStartupInfo);
    PROCESS_INFORMATION stProcessInformation = {0};
    if (!CreateProcess(_T("C:\\Windows\\System32\\notepad.exe"),    // 程序名
                       NULL,                                        // 命令行参数
                       NULL,                                        // 进程安全属性
                       NULL,                                        // 线程安全属性
                       FALSE,                                       // HANDLE是否继承
                       0,                                           // 创建标志
                       NULL,                                        // 子进程环境字符串
                       NULL,                                        // 子进程当前目录
                       &stStartupInfo,                              // 结构 STARTUPINFO
                       &stProcessInformation)                       // 结构 PROCESS_INFORMATION
    ) {
        ShowLastError(_T("CreateProcess"), lpShowCase);
        return;
    }

    // 等待进程结束
    WaitForSingleObject(stProcessInformation.hProcess, INFINITE);
}
