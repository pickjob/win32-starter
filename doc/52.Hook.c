/**
 * 类型
 *      WH_CALLWNDPROC / WH_CALLWNDPROCRET: CallWndProc + CallWndRetProc
 *          发送到窗口过程的消息之前
 *          发送到窗口过程的消息之后
 *      WH_CBT: CBTProc
 *          激活、创建、销毁、最小化、最大化、移动或调整窗口大小之前
 *          完成系统命令之前
 *          消息队列中删除鼠标或键盘事件之前
 *          设置输入焦点之前
 *          与系统消息队列同步之前
 *      WH_DEBUG: DebugProc
 *          系统会先调用 WH_DEBUG 钩子过程, 然后再调用与系统中任何其他钩子关联的钩子过程
 *      WH_FOREGROUNDIDLE: ForegroundIdleProc
 *          在其前台线程处于空闲状态时执行低优先级任务
 *      WH_GETMESSAGE: GetMsgProc
 *         监视即将由 GetMessage 或 PeekMessage 函数返回的消息
 *      WH_KEYBOARD_LL: LowLevelKeyboardProc
 *          监视即将在线程输入队列中发布的键盘输入事件
 *      WH_KEYBOARD: KeyboardProc
 *          监视发布到消息队列的键盘输入
 *      WH_MOUSE_LL: LowLevelMouseProc
 *          监视即将在线程输入队列中发布的鼠标输入事件
 *      WH_MOUSE: MouseProc
 *          监视发送到消息队列的鼠标输入
 *      WH_MSGFILTER 和 WH_SYSMSGFILTER: MessageProc + SysMsgProc
 *          监视即将由菜单、滚动条、消息框或对话框处理的消息
 *      WH_SHELL: ShellProc
 *          用于接收对 shell 应用程序有用的通知
 * Hook过程示例
 *      LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
 *          // process event
 *          // ...
 *          return CallNextHookEx(NULL, nCode, wParam, lParam);
 *      }
 * 函数
 *      SetWindowsHookEx: 添加Hook
 *      UnhookWindowsHookEx: 删除Hook
 *      CallNextHookEx: 将挂钩信息传递到当前挂钩链中的下一个挂钩过程
 **/
