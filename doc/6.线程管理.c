/**
 * 基础知识:
 *      Thread: 线程, 可执行基本单元
 *      ThreadPool: 线程池, 工作线程集合
 *      堆栈空间: 默认1MB
 * 线程管理:
 *      创建线程:
 *          CreateThread(
 *              [in, optional]  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
 *              [in]            SIZE_T                  dwStackSize,
 *              [in]            LPTHREAD_START_ROUTINE  lpStartAddress,
 *              [in, optional]  __drv_aliasesMem LPVOID lpParameter,
 *              [in]            DWORD                   dwCreationFlags,
 *              [out, optional] LPDWORD                 lpThreadId
 *          ): HANDLE
 *          CreateRemoteThread(
 *              [in]  HANDLE                 hProcess,
 *              [in]  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
 *              [in]  SIZE_T                 dwStackSize,
 *              [in]  LPTHREAD_START_ROUTINE lpStartAddress,
 *              [in]  LPVOID                 lpParameter,
 *              [in]  DWORD                  dwCreationFlags,
 *              [out] LPDWORD                lpThreadId
 *          ): HANDLE 创建远端线程, 其他进程内存中
 *          CreateRemoteThreadEx(
 *              [in]            HANDLE                       hProcess,
 *              [in, optional]  LPSECURITY_ATTRIBUTES        lpThreadAttributes,
 *              [in]            SIZE_T                       dwStackSize,
 *              [in]            LPTHREAD_START_ROUTINE       lpStartAddress,
 *              [in, optional]  LPVOID                       lpParameter,
 *              [in]            DWORD                        dwCreationFlags,
 *              [in, optional]  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList,
 *              [out, optional] LPDWORD                      lpThreadId
 *          ): HANDLE
 *              StartAddress:
 *                  DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
 *              dwCreationFlags:
 *                  CREATE_SUSPENDED
 *                  STACK_SIZE_PARAM_IS_A_RESERVATION
 *      获得线程:
 *          OpenThread(
 *              [in] DWORD dwDesiredAccess,
 *              [in] BOOL  bInheritHandle,
 *              [in] DWORD dwThreadId
 *          ): HANDLE 打开线程, 获得句柄
 *              dwDesiredAccess:
 *                  THREAD_ALL_ACCESS
 *                  THREAD_DIRECT_IMPERSONATION
 *                  THREAD_GET_CONTEXT 
 *                  THREAD_IMPERSONATE
 *                  THREAD_QUERY_INFORMATION
 *                  THREAD_QUERY_LIMITED_INFORMATION
 *                  THREAD_SET_CONTEXT
 *                  THREAD_SET_INFORMATION
 *                  THREAD_SET_LIMITED_INFORMATION
 *                  THREAD_SET_THREAD_TOKEN
 *                  THREAD_SUSPEND_RESUME
 *                  THREAD_TERMINATE
 *      线程控制:
 *          线程休眠
 *              Sleep(
 *                  [in] DWORD dwMilliseconds
 *              ): void
 *              SleepEx(
 *                  [in] DWORD dwMilliseconds,
 *                  [in] BOOL  bAlertable
 *              ): DWORD
 * 
 *              SuspendThread(
 *                  [in] HANDLE hThread
 *              ): DWORD 暂停线程
 *              ResumeThread(
 *                  [in] HANDLE hThread
 *              ): DWORD 恢复线程
 *          线程切换:
 *              SwitchToThread(): BOOL
 *      线程基本信息:
 *          GetCurrentThread(): HANDLE 获得当前线程句柄
 *          GetThreadId(
 *              [in] HANDLE Thread
 *          ): DWORD
 *          GetCurrentThreadId(): DWORD 获得当前线程ID
 *          GetThreadContext / SetThreadContext: 线程上下文
 *          GetThreadDescription / SetThreadDescription: 线程描述
 *          GetThreadInformation / SetThreadInformation: 线程信息
 *      结束线程:
 *          ExitThread(
 *              [in] DWORD dwExitCode
 *          ): void
 *          TerminateThread(
 *              [in, out] HANDLE hThread,
 *              [in]      DWORD  dwExitCode
 *          ): BOOL
 *      CRT相关函数优先使用: C函数初始化
 *          _beginthreadex / _endthreadex
 * Tls(Thread Local Storage): 线程本地存储
 *      TlsAlloc(): DWORD 获得tls solt
 *      TlsGetValue([in] DWORD dwTlsIndex): LPVOID
 *      TlsSetValue([in] DWORD dwTlsIndex, [in, optional] LPVOID lpTlsValue): BOOL
 *      TlsFree([in] DWORD dwTlsIndex): BOOL 释放tls solt
 * Thread Pool: 线程池
 *      回调环境: 绑定线程池相关资源
 *          InitializeThreadpoolEnvironment(
 *              [out] PTP_CALLBACK_ENVIRON pcbe
 *          ): void 初始化线程池回调环境
 *          SetThreadpoolCallbackRunsLong(
 *              [in, out] PTP_CALLBACK_ENVIRON pcbe
 *          ): void 回调可能会长时间运行
 *          DestroyThreadpoolEnvironment(
 *              [in, out] PTP_CALLBACK_ENVIRON pcbe
 *          ): void 销毁资源
 *      基础线程池:
 *          CreateThreadpool(
 *              PVOID reserved
 *          ): PTP_POOL 创建线程池
 *          SetThreadpoolThreadMaximum(
 *              [in, out] PTP_POOL ptpp,
 *              [in]      DWORD    cthrdMost
 *          ): void 设置线程池最大数
 *          SetThreadpoolThreadMinimum(
 *              [in, out] PTP_POOL ptpp,
 *              [in]      DWORD    cthrdMic
 *          ): BOOL 设置线程池最小数
 *          SetThreadpoolCallbackPool(
 *              [in, out] PTP_CALLBACK_ENVIRON pcbe,
 *              [in]      PTP_POOL             ptpp
 *          ): void 绑定Thread Poll 和线程池回调环境
 *          CloseThreadpool(
 *              [in, out] PTP_POOL ptpp
 *          ): void 释放线程池
 *      Cleanup Group清理组: 自动关闭
 *          CreateThreadpoolCleanupGroup(): PTP_CLEANUP_GROUP 清理组
 *          SetThreadpoolCallbackCleanupGroup(
 *              [in, out]      PTP_CALLBACK_ENVIRON              pcbe,
 *              [in]           PTP_CLEANUP_GROUP                 ptpcg,
 *              [in, optional] PTP_CLEANUP_GROUP_CANCEL_CALLBACK pfng
 *          ): void 绑定Cleanup 和 PTP_CALLBACK_ENVIRON
 *          CloseThreadpoolCleanupGroupMembers(
 *              [in, out]           PTP_CLEANUP_GROUP ptpcg,
 *              [in]                BOOL              fCancelPendingCallbacks,
 *              [in, out, optional] PVOID             pvCleanupContext
 *          ): void 等待任务完成，清理相关任务对象
 *          CloseThreadpoolCleanupGroup(
 *              [in, out] PTP_CLEANUP_GROUP ptpcg
 *          ): void
 *      Work: 多线程任务
 *          CreateThreadpoolWork(
 *              [in]                PTP_WORK_CALLBACK    pfnwk,
 *              [in, out, optional] PVOID                pv,
 *              [in, optional]      PTP_CALLBACK_ENVIRON pcbe
 *          ): PTP_WORK 绑定Work 和 PTP_CALLBACK_ENVIRON
 *              VOID CALLBACK WorkCallback(
 *                  _Inout_     PTP_CALLBACK_INSTANCE Instance,
 *                  _Inout_opt_ PVOID                 Context,
 *                  _Inout_     PTP_WORK              Work
 *              ): Work签名 
 *          SubmitThreadpoolWork(
 *              [in, out] PTP_WORK pwk
 *          ): void 提交Work
 *          TrySubmitThreadpoolCallback(
 *              [in]                PTP_SIMPLE_CALLBACK  pfns,
 *              [in, out, optional] PVOID                pv,
 *              [in, optional]      PTP_CALLBACK_ENVIRON pcbe
 *          ): BOOL
 *          CloseThreadpoolWork(
 *              [in, out] PTP_WORK pwk
 *          ): void 释放Work
 *      IO 相关:
 *          CreateThreadpoolIo(
 *              [in]                HANDLE                fl,
 *              [in]                PTP_WIN32_IO_CALLBACK pfnio,
 *              [in, out, optional] PVOID                 pv,
 *              [in, optional]      PTP_CALLBACK_ENVIRON  pcbe
 *          ): PTP_IO 绑定 IO 和 PTP_CALLBACK_ENVIRON
 *              VOID CALLBACK IoCompletionCallback(
 *                  _Inout_     PTP_CALLBACK_INSTANCE Instance,
 *                  _Inout_opt_ PVOID                 Context,
 *                  _Inout_opt_ PVOID                 Overlapped,
 *                  _In_        ULONG                 IoResult,
 *                  _In_        ULONG_PTR             NumberOfBytesTransferred,
 *                  _Inout_     PTP_IO                Io
 *              ): IO签名
 *          StartThreadpoolIo(
 *              [in, out] PTP_IO pio
 *          ): void
 *          CloseThreadpoolIo(
 *              [in, out] PTP_IO pio
 *          ): void
 *      Timer 相关:
 *          CreateThreadpoolTimer(
 *              [in]                PTP_TIMER_CALLBACK   pfnti,
 *              [in, out, optional] PVOID                pv,
 *              [in, optional]      PTP_CALLBACK_ENVIRON pcbe
 *          ): PTP_TIMER  绑定Timer 和 PTP_CALLBACK_ENVIRON
 *              VOID CALLBACK TimerCallback(
 *                  _Inout_     PTP_CALLBACK_INSTANCE Instance,
 *                  _Inout_opt_ PVOID                 Context,
 *                  _Inout_     PTP_TIMER             Timer
 *              ): Timer签名
 *          SetThreadpoolTimer(
 *              [in, out]      PTP_TIMER pti,
 *              [in, optional] PFILETIME pftDueTime,
 *              [in]           DWORD     msPeriod,
 *              [in, optional] DWORD     msWindowLength
 *          ): void 
 *          CloseThreadpoolTimer(
 *              [in, out] PTP_TIMER pti
 *          ): void
 *      TP_CALLBACK_INSTANCE 可用函数:
 *          FreeLibraryWhenCallbackReturns(
 *              [in, out] PTP_CALLBACK_INSTANCE pci,
 *              [in]      HMODULE               mod
 *          ): void 退出释放 DLL 模块
 *          LeaveCriticalSectionWhenCallbackReturns(
 *              [in, out] PTP_CALLBACK_INSTANCE pci,
 *              [in, out] PCRITICAL_SECTION     pcs
 *          ): void 退出离开 CriticalSection
 *          ReleaseMutexWhenCallbackReturns(
 *              [in, out] PTP_CALLBACK_INSTANCE pci,
 *              [in]      HANDLE                mut
 *          ): void 退出释放 Mutex
 *          ReleaseSemaphoreWhenCallbackReturns(
 *              [in, out] PTP_CALLBACK_INSTANCE pci,
 *              [in]      HANDLE                sem,
 *              [in]      DWORD                 crel
 *          ): void 退出释放Semaphore
 *          SetEventWhenCallbackReturns(
 *              [in, out] PTP_CALLBACK_INSTANCE pci,
 *              [in]      HANDLE                evt
 *          ): void 退出设置 Event
 **/
