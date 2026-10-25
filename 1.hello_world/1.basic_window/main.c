// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/log.h"
// clang-format on

// 窗口消息循环
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY     WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;
    if (log_init() != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    LOG_INFO("%s", "Hello World, Win32!");

    // Register the window class
    const TCHAR CLASS_NAME[] = _T("HelloWin32");
    // 必须零初始化：WNDCLASSEX 中 lpszMenuName / hIconSm 若不置 0 会是栈垃圾，传给 RegisterClassEx 会导致其内部卡死、窗口无法创建
    WNDCLASSEX  wcx          = {0};
    wcx.cbSize               = sizeof(wcx);                     // size of structure
    wcx.style                = CS_HREDRAW | CS_VREDRAW;         // redraw if size changes
    wcx.lpfnWndProc          = WindowProc;                      // points to window procedure
    wcx.cbClsExtra           = 0;                               // no extra class memory
    wcx.cbWndExtra           = 0;                               // no extra window memory
    wcx.hInstance            = hInstance;                       // handle to instance
    wcx.hIcon                = LoadIcon(NULL, IDI_APPLICATION); // predefined app. icon
    wcx.hCursor              = LoadCursor(NULL, IDC_ARROW);     // predefined arrow
    wcx.hbrBackground        = GetStockObject(WHITE_BRUSH);     // white background brush
    wcx.lpszClassName        = CLASS_NAME;                      // name of window class
    RegisterClassEx(&wcx);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                   // Optional window styles.
        CLASS_NAME,          // Class name
        L"HelloWin32",       // Caption name
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,

        NULL,      // Parent window
        NULL,      // Menu
        hInstance, // Instance handle
        NULL       // Additional application data
    );
    if (!hwnd) {
        return EXIT_FAILURE;
    }
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC         hdc = BeginPaint(hwnd, &ps);
        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
        break;
    }
    // 关闭流程: WM_CLOSE: DestroyWindow -> WM_DESTROY: PostQuitMessage -> WM_QUIT
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return EXIT_SUCCESS;
    case WM_DESTROY:
        PostQuitMessage(EXIT_SUCCESS);
        return EXIT_SUCCESS;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}