// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/common.h"
#include "utils/log.h"
// clang-format on

/**
 * DllMain: 程序入口函数
 *      Date: 2025-08-01
 **/
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    (void)hinstDLL;
    (void)lpReserved;
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        // 仅在进程加载本 DLL 时提示一次
        MessageBox(NULL, _T("DLL_PROCESS_ATTACH"), _T("DLL Injection"), MB_OK);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    default:
        break;
    }
    return TRUE;
}