/**
 * 类型
 *      WNDCLASSEX: 窗口类
 *          cbSize: sizeof(WNDCLASSEX) 结构的大小
 *          lpszClassName: lpszClassName
 *              系统
 *                   Button
 *                   Static
 *                   Edit
 *                   ListBox
 *                   ScrollBar
 *                   Combox
 *                   ComboLBox
 *          style: 类样式
 *              CS_DBLCLKS: 双击鼠标, 将双击消息发送到 WndProc
 *          hInstance: 类窗口句柄
 *          lpfnWndProc: 窗口过程指针
 *          cbClsExtra: 按照窗口类结构分配的额外字节数
 *          cbWndExtra: 窗口实例之后分配的额外字节数
 *
 *          hCursor / hbrBackground / hIcon / hIconSm
 *          lpszMenuName: MAKEINTRESOURCE
 *      窗口样式 / 扩展窗口样式
 *          WS_VISIBLE: 可见
 *          WS_BORDER: 边界线
 *          WS_CAPTION: 标题
 *          WS_DISABLED: 不可操作
 *          WS_SYSMENU: 标题栏带菜单
 *          WS_SIZEBOX / WS_THICKFRAME: 大小调节边框
 *          WS_HSCROLL / WS_VSCROLL: 有垂直、水平滚动条
 *          WS_MINIMIZE / WS_MAXIMIZE: 启动最小、最大化
 *          WS_MINIMIZEBOX / WS_MAXIMIZEBOX: 最小、最大按钮
 *
 *          WS_OVERLAPPED / WS_TILED: 重叠的
 *          WS_OVERLAPPEDWINDOW / WS_TILEDWINDOW: WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
 *
 *          WS_POPUP: 弹出窗口
 *          WS_POPUPWINDOW: WS_POPUP | WS_BORDER | WS_SYSMENU
 *
 *          WS_EX_ACCEPTFILES: 拖放文件
 * 消息过程
 *      LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
 *          switch (uMsg) {
 *          case WM_PAINT: {
 *              PAINTSTRUCT ps;
 *              HDC         hdc = BeginPaint(hwnd, &ps);
 *              // All painting occurs here, between BeginPaint and EndPaint.
 *              FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
 *              EndPaint(hwnd, &ps);
 *          }
 *          // 关闭流程: WM_CLOSE: DestroyWindow -> WM_DESTROY: PostQuitMessage -> WM_QUIT
 *          case WM_CLOSE:
 *              DestroyWindow(hwnd);
 *              return EXIT_SUCCESS;
 *          case WM_DESTROY:
 *              PostQuitMessage(EXIT_SUCCESS);
 *              return EXIT_SUCCESS;
 *          }
 *          return DefWindowProc(hwnd, uMsg, wParam, lParam);
 *      }
 * 函数
 *      遍历窗口
 *          EnumWindows + EnumWindowsProc
 *          EnumChildWindows + EnumChildProc
 *      窗口属性
 *          RegisterClass / RegisterClassEx: 注册一个窗口类
 *          UnregisterClass: 取消注册窗口类，释放类所需的内存
 *          GetClassName / GetClassInfoEx / GetClassLongPtr: 检索指定窗口所属的类的名
 *          GetWindowText / SetWindowText: 将指定窗口的标题栏（如果有）的文本复制到缓冲区中
 *          GetWindowTextLength
 *      GetWindowInfo: 窗口信息
 *      GetWindowModuleFileName: 窗口关联模块文件信息
 *      GetWindowLongPtr / SetWindowLongPtr: 更改指定窗口的属性
 *      GetDesktopWindow: 获得桌面窗口
 *      GetTopWindow: 检查与指定父窗口关联的子窗口的 Z 顺序
 *      GetNextWindow: 检索 Z 顺序中下一个或上一个窗口的句柄
 *      IsWindow: 确定指定的窗口句柄是否标识现有窗口
 *      IsWindowUnicode: 确定指定的窗口是否为本机 Unicode 窗口
 *      CreateWindow / CreateWindowEx: 创建窗口
 *      FindWindow / FindWindowEx: 检索其类名和窗口名与指定字符串匹配的顶级窗口的句柄
 *      位置
 *          MoveWindow: 更改指定窗口的位置和维度
 *          BringWindowToTop: 将指定的窗口带到 Z 顺序的顶部
 *          SetWindowPos: 更改子窗口、弹出窗口或顶级窗口的大小、位置和 Z 顺序
 *      显示/ 可用
 *          ShowWindow / ShowWindowAsync: 设置指定窗口的显示状态
 *          IsWindowVisible: 检索指定窗口的可见性状态
 *          EnableWindow
 *          IsWindowEnabled
 *      CloseWindow: 最小化窗口
 *      DestroyWindow: 摧毁窗口
 *      AnimateWindow: 允许在显示或隐藏窗口时产生特殊效果
 *      附加数据
 *          EnumProps / EnumPropsEx + PropEnumProc / PropEnumProcEx: 通过将窗口的属性列表中的所有条目（一个一个）传递给指定的回调函数来枚举这些条目
 *          GetProp / SetProp: 从指定窗口的属性列表中检索数据句柄。 字符串标识要检索的句柄。 之前对 setProp 函数的调用必须将字符串和句柄添加到属性列表中。
 *          RemoveProp: 从指定窗口的属性列表中删除一个条目
 * 消息&通知
 *      WM_GETTEXT / WM_SETTEXT: 将与窗口相对应的文本复制到调用方提供的缓冲区中
 *      WM_GETTEXTLENGTH: 确定与窗口关联的文本的长度（以字符为单位）
 *      WM_GETFONT / WM_SETFONT: 检索控件当前绘制文本时使用的字体
 *      WM_GETICON / WM_SETICON: 将新的大图标或小图标与窗口相关联
 *
 *      WM_NULL: 不执行任何操作
 *      WM_SIZE: 在窗口大小发生更改后发送到窗口
 *      WM_SIZING: 发送到用户正在调整大小的窗口
 *      WM_MOVE: 在移动窗口后发送
 *      WM_MOVING: 发送到用户正在移动的窗口
 *      WM_SHOWWINDOW: 在窗口即将隐藏或显示时发送到该窗口
 *      WM_ENABLE: 当应用程序更改窗口的启用状态时发送
 *      WM_CREATE: 当应用程序请求通过调用 CreateWindowEx 或 CreateWindow 函数创建窗口时发送
 *      WM_CLOSE: 作为窗口或应用程序应终止的信号发送
 *      WM_DESTROY: 在窗口遭销毁时发送
 *      WM_QUIT: 指示终止应用程序的请求
 **/