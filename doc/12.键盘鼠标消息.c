/**
 * 消息&通知
 *      键盘
 *          WM_KEYDOWN
 *          WM_KEYUP
 *
 *          WM_CHAR: 按下的键的字符代码
 *          WM_UNICHAR: 按下的键的字符代码
 *      鼠标
 *          WM_MOUSEHOVER: 当光标将鼠标悬停在窗口的工作区上
 *          WM_MOUSEMOVE: 光标移动时发布到窗口
 *          WM_LBUTTONDOWN: 按下了鼠标左键
 *          WM_LBUTTONUP: 释放了鼠标左键
 *          WM_LBUTTONDBLCLK: 双击鼠标左键
 *          WM_MBUTTONDOWN: 按下了鼠标中键
 *          WM_MBUTTONUP: 释放了鼠标中键
 *          WM_MBUTTONDBLCLK: 双击鼠标中键
 *          WM_RBUTTONDOWN: 按下了鼠标右键
 *          WM_RBUTTONUP: 释放了鼠标右键
 *          WM_RBUTTONDBLCLK: 双击鼠标右键
 *
 *          通用:
 *              wParam:
 *                  组合:
 *                      MK_CONTROL: 按下了 CTRL 键
 *                      MK_SHIFT: 按下了 SHIFT 键
 *                      MK_LBUTTON: 按下了鼠标左键
 *                      MK_MBUTTON: 按下了鼠标中键
 *                      MK_RBUTTON: 按下了鼠标右键
 *              lParam: 鼠标坐标轴
 *                  int xPos = GET_X_LPARAM(lParam);
 *                  int yPos = GET_Y_LPARAM(lParam);
 **/