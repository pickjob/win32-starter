/**
 * DLLMain
 *      BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved ) {
 *          switch(fdwReason) {
 *              case DLL_PROCESS_ATTACH: // 进程加载 DLL
 *                  // Initialize once for each new process.
 *                  // Return FALSE to fail DLL load.
 *                  break;
 *              case DLL_THREAD_ATTACH: // 当前进程创建新的线程
 *                  // Do thread-specific initialization.
 *                  break;
 *              case DLL_THREAD_DETACH: // 线程正常退出
 *                  // Do thread-specific cleanup.
 *                  break;
 *              case DLL_PROCESS_DETACH: // 进程卸载 DLL
 *                  if (lpvReserved != nullptr) {
 *                      break; // do not do cleanup if process termination scenario
 *                  }
 *                  // Perform any necessary cleanup.
 *                  break;
 *          }
 *          return TRUE;  // Successful DLL_PROCESS_ATTACH.
 *      }
 * 函数
 *      LoadLibrary / LoadLibraryEx: 将指定的可执行模块映射到调用进程的地址空间
 *      GetModuleHandle / GetModuleHandleEx: 检索指定模块的模块句柄
 *      GetModuleFileName / GetModuleFileNameEx: 检索包含指定模块的文件的完全限定路径
 *      GetProcAddress: 从指定的 DLL 检索导出的函数或变量的地址
 *      FreeLibrary: 递减已加载 DLL 的引用计数
 *      FreeLibraryAndExitThread: 递减加载 DLL 的引用计数一个, 然后调用 ExitThread 终止调用线程
 * 搜索顺序
 *      应用程序目录
 *      系统目录
 *      Windows 目录
 *      当前工作目录
 *      PATH 环境变量中列出的目录
 *
 *      已知 DLL(HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\KnownDLLs)
 *      进程的包依赖项关系图
 *      从中加载应用程序的文件夹
 *      系统文件夹
 *      Windows 文件夹
 *      当前文件夹
 **/