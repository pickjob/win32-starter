/**
 * 加载、释放:
 *      LoadLibrary(
 *          [in] LPTSTR lpLibFileName
 *      ): HMODULE
 *      LoadLibraryEx(
 *          [in] LPCSTR lpLibFileName,
 *               HANDLE hFile,
 *          [in] DWORD  dwFlags
 *      ): HMODULE
 *      GetModuleHandle(
 *          [in, optional] LPCTSTR lpModuleName
 *      ): HMODULE (不增加计数)
 *      GetModuleHandleEx(
 *          [in]           DWORD   dwFlags,
 *          [in, optional] LPCTSTR lpModuleName,
 *          [out]          HMODULE *phModule
 *      ): BOOL (增加计数)
 *      FreeLibrary(
 *          [in] HMODULE hLibModule
 *      ): BOOL
 *      FreeLibraryAndExitThread(
 *          [in] HMODULE hLibModule,
 *          [in] DWORD   dwExitCode
 *      ): void
 * 运行时动态调用:
 *      GetProcAddress(
 *          [in] HMODULE hModule,
 *          [in] LPCSTR  lpProcName
 *      ): FARPROC 获得模块函数地址
 *          hModule: LoadLibray、LoadLibraryEx、LoadModuleHandle 返回句柄
 * DLL注入:
 *      SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, hInstDll, 0)
 *      远端线程注入:
 *          OpenProcess: 获得目标进程句柄
 *          VirtualAllocEx: 在目标进程中申请内存
 *          WriteProcessMemory: 向目标进程的内存中写入数据(函数参数)
 *          GetProcAddress: 获取LoadLibraryW函数地址
 *          CreateRemoteThread: 在目标进程创建线程, 调用 LoadLibraryW
 *          CloseHandle: 关闭目标进程句柄
 **/
