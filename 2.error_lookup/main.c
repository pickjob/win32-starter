#include "main.h"

// 对话框事件回调函数
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
    return EXIT_SUCCESS;
}

// 对话框点击事件回调
INT_PTR DlgOnCommand(HWND hwndDlg, WPARAM wParam, LPARAM lParam) {
    LPTSTR lpErrorLoopup = _T("ErrorLoopup");
    // 0-菜单   1-快捷键    其他-控件通知码
    WORD   nCommandType  = HIWORD(wParam);
    WORD   nCommandId    = LOWORD(wParam);
    if (nCommandType > 1) {
        // 控件通知消息响应
        HWND hwndCommand = (HWND) lParam;
    } else {
        // 命令消息响应
        switch (nCommandId) {
            case IDC_BUTTON_ERROR_LOOKUP: {
                UINT   nErrorCode  = GetDlgItemInt(hwndDlg, IDC_EDIT_ERROR_CODE, NULL, FALSE);
                LPTSTR lpErrorText = NULL;
                BOOL   fOk         = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER
                                             | FORMAT_MESSAGE_IGNORE_INSERTS,
                                         NULL,
                                         nErrorCode,
                                         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                         (LPTSTR) &lpErrorText,
                                         0,
                                         NULL);
                if (!fOk) {
                    HMODULE hLibrary = LoadLibraryEx(_T("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
                    if (NULL != hLibrary) {
                        fOk = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS
                                                | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                            hLibrary,
                                            nErrorCode,
                                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                            lpErrorText,
                                            0,
                                            NULL);
                        if (!fOk) {
                            lpErrorText = NULL;
                        }
                        FreeLibrary(hLibrary);
                    }
                }
                if (!fOk) {
                    lpErrorText = _T("未知错误!");
                }
                size_t  nTotalLength      = 0;
                size_t  nLength           = 0;
                HRESULT hResult           = StringCchLength(lpErrorText, STRSAFE_MAX_CCH, &nLength);
                if (FAILED(hResult)) {
                    ShowLastError(_T("StringCchLength"), lpErrorLoopup);
                    break;
                }
                nTotalLength += nLength;
                TCHAR szErrorInfo[nTotalLength + 100];
                hResult = StringCchPrintf(szErrorInfo, _countof(szErrorInfo), _T("%d-%s"), nErrorCode, lpErrorText);
                if (FAILED(hResult)) {
                    ShowLastError(_T("StringCchPrintf"), lpErrorLoopup);
                    break;
                }
                if (fOk) {
                    LocalFree(lpErrorText);
                }

                HWND hwndEdit = GetDlgItem(hwndDlg, IDC_EDIT_ERROR_MESSAGE);
                Edit_SetText(hwndEdit, szErrorInfo);
                break;
            }
            default:
                break;
        }
    }
    return FALSE;
}

// 对话框初始化函数
INT_PTR DlgOnInitDialog(HWND hwndDlg, WPARAM wParam, LPARAM lParam) {
    INITCOMMONCONTROLSEX stInitCommonControlsEx = {};
    stInitCommonControlsEx.dwSize               = sizeof(stInitCommonControlsEx);
    stInitCommonControlsEx.dwICC = ICC_TREEVIEW_CLASSES | ICC_ANIMATE_CLASS | ICC_BAR_CLASSES | ICC_COOL_CLASSES
                                   | ICC_DATE_CLASSES | ICC_INTERNET_CLASSES | ICC_LINK_CLASS | ICC_LISTVIEW_CLASSES
                                   | ICC_PAGESCROLLER_CLASS | ICC_PROGRESS_CLASS | ICC_STANDARD_CLASSES
                                   | ICC_TAB_CLASSES | ICC_UPDOWN_CLASS | ICC_USEREX_CLASSES;
    InitCommonControlsEx(&stInitCommonControlsEx);
    return TRUE;
}

// 对话框事件回调函数
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            return DlgOnCommand(hwndDlg, wParam, lParam);
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
