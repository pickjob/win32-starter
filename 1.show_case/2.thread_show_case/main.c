#include "main.h"

// 启动新线程示例
void ShowCreateThread(HANDLE hStdout, LPTSTR lpShowCase);

// 线程池和TLS示例
void ShowThreadPoolAndTls(HANDLE hStdout, LPTSTR lpShowCase);

/**
 * WinMain: 程序入口函数
 */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpShowCase = _T("Thread ShowCase");
    HANDLE hStdout    = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, _T("GetStdHandle"), lpShowCase, MB_OK);
        return EXIT_FAILURE;
    }
    ShowCreateThread(hStdout, lpShowCase);
    ShowThreadPoolAndTls(hStdout, lpShowCase);
    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadProc(HANDLE hStdout) {
    LPTSTR  lpShowCase       = _T("New Thread ShowCase");
    LPTSTR  lpGreetings      = _T("Hello World By Another Thread\n");
    size_t  nGreetingsLength = 0;
    HRESULT hResult          = StringCchLength(lpGreetings, STRSAFE_MAX_CCH, &nGreetingsLength);
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

// 启动新线程示例
void ShowCreateThread(HANDLE hStdout, LPTSTR lpShowCase) {
    HANDLE hNewThread = CreateThread(NULL,          // 安全属性
                                     0,             // 默认栈大小
                                     ThreadProc,    // 函数地址
                                     hStdout,       // 参数
                                     0,             // 创建标志
                                     NULL);         // 线程ID
    // 线程结束
    WaitForSingleObject(hNewThread, INFINITE);
}

VOID CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE callbackInstance, PVOID context) {
    HANDLE hStdout            = (HANDLE) context;
    LPTSTR lpShowCase         = _T("ThreadPool ShowCase");

    DWORD   dwCurrentThreadId = GetCurrentThreadId();
    TCHAR   szThreadInfo[50];
    size_t  nTotal;
    HRESULT hResult = StringCchPrintf(szThreadInfo, _countof(szThreadInfo), _T("CurrentThreadId: %d\n"), dwCurrentThreadId);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchPrintf"), lpShowCase);
        return;
    }
    hResult = StringCchLength(szThreadInfo, STRSAFE_MAX_CCH, &nTotal);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return;
    }
    BOOL bWriteSuccess = WriteConsole(hStdout, szThreadInfo, nTotal, 0, NULL);
    if (!bWriteSuccess) {
        ShowLastError(_T("WriteConsole"), lpShowCase);
        return;
    }
}

// 线程池和TLS示例
void ShowThreadPoolAndTls(HANDLE hStdout, LPTSTR lpShowCase) {
    TP_CALLBACK_ENVIRON stThreadPoolCallbackEnvironment = {0};
    // 初始化线程池Environment
    InitializeThreadpoolEnvironment(&stThreadPoolCallbackEnvironment);

    // 创建线程池  && 初始化线程池
    PTP_POOL pThreadPool = CreateThreadpool(NULL);
    SetThreadpoolThreadMaximum(pThreadPool, 4);
    SetThreadpoolThreadMinimum(pThreadPool, 4);
    // 关联 线程池Environment 和 线程池
    SetThreadpoolCallbackPool(&stThreadPoolCallbackEnvironment, pThreadPool);

    // 创建线程池Cleanup Group
    PTP_CLEANUP_GROUP pThreadPloolCleanupGroup = CreateThreadpoolCleanupGroup();
    // 关联 线程池Environment 和 线程池 Cleanup Group
    SetThreadpoolCallbackCleanupGroup(&stThreadPoolCallbackEnvironment, pThreadPloolCleanupGroup, NULL);

    // 创建多线程任务
    for (int i = 0; i < 10000; i++) {
        if (!TrySubmitThreadpoolCallback(SimpleCallback, hStdout, &stThreadPoolCallbackEnvironment)) {
            ShowLastError(_T("TrySubmitThreadpoolCallback"), lpShowCase);
            return;
        }
    }

    // 等待任务结束并清理任务相关资源
    CloseThreadpoolCleanupGroupMembers(pThreadPloolCleanupGroup, FALSE, NULL);
    // 清理线程池Environment
    DestroyThreadpoolEnvironment(&stThreadPoolCallbackEnvironment);
}
