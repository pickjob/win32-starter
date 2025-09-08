/**
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