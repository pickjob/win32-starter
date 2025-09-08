/**
 * 样式
 *      模态(Modal): WS_POPUP, WS_CAPTION, WS_VISIBLE, DS_MODALFRAME
 *      非模态(Modalless): WS_POPUP, WS_CAPTION, WS_VISIBLE
 * 对话框过程函数
 *      BOOL CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
 *          switch (message) {
 *          case WM_XX:
 *              // 处理过消息, 返回TRUE
 *              // 未处理, 返回FALSE
 *          case WM_NOTIFY:
 *              // 控件发给父窗口通知事件
 *          case WM_INITDIALOG:
 *              // 初始化对话框, 必须返回TRUE
 *              return TRUE;
 *          case WM_CLOSE:
 *              // 模块对话框必须用 EndDialog关闭
 *              EndDialog(hwndDlg, wParam);
 *              return TRUE;
 *          default:
 *              return FALSE;
 *          }
 *      }
 *      DefDlgProc: 默认消息处理函数
 * 函数:
 *      MessageBox / MessageBoxEx: 消息框
 *      模态
 *          DialogBox / DialogBoxParam
 *          EndDialog: 关闭模态对话框
 *      非模态
 *          CreateDialog / CreateDialogParam
 *          DestroyWindow: 关闭非模态对话框
 *      通用对话框
 *      控件操作
 *          GetDlgItem: 对话框中控件的句柄
 *          GetDlgCtrlID: 对话框控件的标识符
 *          GetDlgItemText / SetDlgItemText: 对话框中的控件关联的标题或文本
 *          GetDlgItemInt / SetDlgItemInt: 对话框中指定控件的文本转换为整数值
 *          SendDlgItemMessage: 将消息发送到对话框中的指定控件
 * 消息&通知
 *      DM_GETDEFID / DM_SETDEFID: 对话框的默认按下按钮控件的标识符
 *
 *      WM_INITDIALOG: 在显示对话框之前立即发送到对话框过程
 *      WM_CTLCOLORDLG: 在系统绘制对话框之前发送到对话框
 **/