/**
 *  Win32重要函数:
 *      程序入口:
 *          WinMainCRTStartup
 *          wWimMainCRTStartup
 *          mainCRTStartup
 *          wmainCRTStartup
 *      WinMain:
 *          int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
 *              return MessageBox(NULL, "hello, world", "caption", 0);
 *          }
 *      DllMain:
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
 **/
