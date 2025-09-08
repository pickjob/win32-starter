/**
 * 格式
 *      CF_TEXT: 文本格式(ANSI)
 *      CF_UNICODETEXT: Unicode 文本格式
 *      CF_BITMAP: 位图 (HBITMAP) 的句柄
 * 函数
 *      GetClipboardData / SetClipboardData: 剪贴板中数据
 *      EmptyClipboard: 清空剪贴板并释放剪贴板中的数据句柄
 *      OpenClipboard / CloseClipboard: 打开、关闭剪贴板
 * 消息
 *      WM_COPY: 复制
 *      WM_CUT: 剪切
 *      WM_PASTE: 黏贴
 *      WM_CLEAR: 清除
 * 通知
 *      WM_CLIPBOARDUPDATE: 当剪贴板的内容发生更改时发送
 *      WM_DESTROYCLIPBOARD: 在调用 EmptyClipboard 函数清空剪贴板时, 剪贴板所有者会被发送通知
 **/