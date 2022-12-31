#include "main.h"

// 对话框事件回调函数
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

/**
 * WinMain: 程序入口函数
*/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
    return EXIT_SUCCESS;
}

// 对话框初始化函数
INT_PTR DlgOnInitDialog(HWND hwndDlg, WPARAM wParam, LPARAM lParam) { return TRUE; }

// 对话框事件回调函数
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            // 初始化对话框, 必须返回TRUE
            return DlgOnInitDialog(hwndDlg, wParam, lParam);
        case WM_CLOSE:
            // 模块对话框必须用 EndDialog关闭
            EndDialog(hwndDlg, wParam);
            return TRUE;
        // 处理其他消息
        default:
            return FALSE;
    }
}
