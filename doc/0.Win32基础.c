/**
 *  Win32重要函数
 *      程序入口
 *          WinMainCRTStartup
 *          wWimMainCRTStartup
 *          mainCRTStartup
 *          wmainCRTStartup
 *      WinMain
 *          int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
 *          int APIENTRY wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
 *      DllMain
 *          BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
 *              switch (fdwReason) {
 *                  case DLL_PROCESS_ATTACH:
 *                      break;
 *                  case DLL_THREAD_ATTACH:
 *                      break;
 *                  case DLL_THREAD_DETACH:
 *                      break;
 *                  case DLL_PROCESS_DETACH:
 *                      break;
 *              }
 *              return TRUE;
 *          }
 *      Handler
 *          INVALID_HANDLE_VALUE: 无效句柄
 *          函数
 *               GetHandleInformation / SetHandleInformation: 对象句柄的某些属性。
 *               CloseHandle: 关闭句柄
 *               DuplicateHandle: 复制对象句柄
 *               CompareObjectHandles: 比较两个对象句柄, 以确定它们是否引用同一个基础内核对象
 *      控制台
 *          GetStdHandle / SetStdHandle: 标准流 HANDLE
 *              nStdHandle:
 *                  STD_INPUT_HANDLE
 *                  STD_OUTPUT_HANDLE
 *                  STD_ERROR_HANDLE
 *          ReadConsole: 读取控制台
 *          WriteConsole: 写入控制台
 **/