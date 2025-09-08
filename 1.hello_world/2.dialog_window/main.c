#include "main.h"

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    log_info(L"%s", L"Hello World Dialog");
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
        if (wParam == IDOK) {
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