// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

// 资源定义
#include "resource.h"
#include "utils/log.h"
// clang-format on

// 对话框事件回调函数
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;
    if (log_init() != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    LOG_INFO("%s", "Hello World, Win32 Dialog!");
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
    return EXIT_SUCCESS;
}

// 对话框事件回调函数
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        // 初始化对话框, 必须返回TRUE
        return TRUE;
    case WM_CLOSE:
        // 模态对话框必须用 EndDialog关闭
        EndDialog(hwndDlg, wParam);
        return TRUE;
    case WM_COMMAND:
        if (wParam == IDOK || wParam == IDCANCEL) {
            EndDialog(hwndDlg, TRUE);
            return TRUE;
        }
        break;
    // 处理其他消息
    // case ...:
    default:
        return FALSE;
    }
    return FALSE;
}