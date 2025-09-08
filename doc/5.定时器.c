/**
 * 回调函数
 *      void Timerproc(
 *           HWND unnamedParam1,
 *           UINT unnamedParam2,
 *           UINT_PTR unnamedParam3,
 *           DWORD unnamedParam4) {
 *               ...
 *      }
 * 函数
 *      SetTimer: 创建具有指定超时值的计时器
 *      KillTimer: 销毁指定的计时器
 * 消息
 *      WM_TIMER
 *          wParam: 计时器标识符
 *          lParam: 指向应用程序定义的回调函数的指针
 **/