// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/common.h"
#include "utils/log.h"
// clang-format on

// 线程池和TLS示例
void         ShowThreadPoolAndTls();

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;
    if (log_init() != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    ShowThreadPoolAndTls();
    return EXIT_SUCCESS;
}

VOID CALLBACK SimpleCallback(PTP_CALLBACK_INSTANCE callbackInstance, PVOID context) {
    int *idx = (int *)context;
    LOG_INFO("当前次序是%d", *idx);
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
        if (!TrySubmitThreadpoolCallback(SimpleCallback, (PVOID)(intptr_t)i, &stThreadPoolCallbackEnvironment)) {
            return;
        }
    }

    Sleep(10000);

    // 等待任务结束并清理任务相关资源
    CloseThreadpoolCleanupGroupMembers(pThreadPloolCleanupGroup, FALSE, NULL);
    // 清理线程池Environment
    DestroyThreadpoolEnvironment(&stThreadPoolCallbackEnvironment);
}
