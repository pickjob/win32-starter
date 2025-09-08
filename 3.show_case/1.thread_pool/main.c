#include "main.h"

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    ShowThreadPoolAndTls();
    return EXIT_SUCCESS;
}

VOID CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE callbackInstance, PVOID context) {
    int *idx = (int *)context;
    log_info(L"当前次序是%d", *idx);
}

// 线程池和TLS示例
void ShowThreadPoolAndTls() {
    TP_CALLBACK_ENVIRON stThreadPoolCallbackEnvironment = {};
    // 初始化 ThreadpoolEnvironment
    InitializeThreadpoolEnvironment(&stThreadPoolCallbackEnvironment);

    // 创建 Threadpool
    PTP_POOL pThreadPool = CreateThreadpool(NULL);
    SetThreadpoolThreadMinimum(pThreadPool, 4);
    SetThreadpoolThreadMaximum(pThreadPool, 4);
    // 关联 ThreadpoolEnvironment 和 Threadpool
    SetThreadpoolCallbackPool(&stThreadPoolCallbackEnvironment, pThreadPool);

    // 创建 ThreadPloolCleanupGroup
    PTP_CLEANUP_GROUP pThreadPloolCleanupGroup = CreateThreadpoolCleanupGroup();
    // 关联 ThreadpoolEnvironment 和 线程池 ThreadPloolCleanupGroup
    SetThreadpoolCallbackCleanupGroup(&stThreadPoolCallbackEnvironment, pThreadPloolCleanupGroup, NULL);

    // 创建多线程任务
    for (int i = 0; i < 10000; i++) {
        if (!TrySubmitThreadpoolCallback(SimpleCallback, &i, &stThreadPoolCallbackEnvironment)) {
            return;
        }
    }

    Sleep(10000);

    // 等待任务结束并清理任务相关资源
    CloseThreadpoolCleanupGroupMembers(pThreadPloolCleanupGroup, FALSE, NULL);
    // 清理线程池Environment
    DestroyThreadpoolEnvironment(&stThreadPoolCallbackEnvironment);
}
