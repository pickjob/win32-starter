/**
 * 消息
 *      数值范围
 *          0 - WM_USER –1: 保留供系统使用的消息
 *          WM_USER - 0x7FFF: 专用窗口类使用的整数消息
 *          WM_APP(0x8000) - 0xBFFF: 可供应用程序使用的消息
 *          0xC000 - 0xFFFF: 供应用程序使用的字符串消息
 *          大于 0xFFFF: 由系统保留
 *      前缀
 *          WM_: 常规
 *              WM_CLOSE: 作为窗口或应用程序应终止的信号发送
 *              WM_DESTROY: 在窗口遭销毁时发送
 *              WM_QUIT: 指示终止应用程序的请求
 *          **_: 控件消息
 * 函数
 *      消息循环:
 *          GetMessage: 从调用线程的消息队列中检索消息(阻塞)
 *          PeekMessage: 从调用线程的消息队列中检索消息(立即返回)
 *          TranslateMessage: 将虚拟密钥消息转换为字符消息
 *          DispatchMessage: 将消息调度到窗口过程
 *
 *          DefWindowProc: 调用默认窗口过程
 *          DefDlgProc: 默认窗口过程
 *
 *     PostMessage: 在与创建指定窗口的线程关联的消息队列中发布消息, 并在不等待线程处理消息的情况下返回
 *     PostQuitMessage: 向系统指示线程已发出终止请求
 *     SendMessage:	将指定的消息发送到窗口或窗口(阻塞)
 *     SendNotifyMessage: 将指定的消息发送到窗口或窗口
 *     SendMessageCallback + SendAsyncProc: 将消息传递给目标窗口过程后，系统将消息传递给回调函数
 *     BroadcastSystemMessage / BroadcastSystemMessageEx: 向指定的收件人发送邮件
 *     ReplyMessage: 答复通过 SendMessage 函数发送的消息，而不返回对调用 SendMessage的函数的控制
 *     WaitMessage: 当线程在其消息队列中没有其他消息时, 生成对其他线程的控制
 **/