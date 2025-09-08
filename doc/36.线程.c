/**
 * 函数
 *      GetThreadId: 检索指定线程的线程标识符
 *      GetThreadTimes: 检索指定线程的计时信息
 *      GetCurrentThread: 检索当前线程的伪句柄
 *      GetCurrentThreadId: 检索调用线程的线程标识符
 *      GetThreadDescription / SetThreadDescription: 分配给线程的说明
 *      GetThreadInformation / SetThreadInformation: 有关指定线程的信息
 *      GetProcessIdOfThread: 检索与指定线程关联的进程的进程标识符
 *      GetThreadPriority / SetThreadPriority: 指定线程的优先级值
 *      GetThreadPriorityBoost / SetThreadPriorityBoost: 指定线程的优先级提升控制状态
 *      GetThreadIdealProcessorEx / SetThreadIdealProcessor / SetThreadIdealProcessorEx: 指定线程的理想处理器的处理器编号
 *      GetThreadIOPendingFlag: 确定指定线程是否有任何 I/O 请求挂起
 *      GetExitCodeThread: 检索指定线程的终止状态
 *      QueryIdleProcessorCycleTime: 检索系统中每个处理器的空闲线程的周期时间
 *      QueryThreadCycleTime: 检索指定线程的周期时间
 *      CreateThread: 创建在调用进程的虚拟地址空间内执行的线程
 *          DWORD WINAPI ThreadProc(
 *              _In_ LPVOID lpParameter
 *          );
 *      CreateRemoteThread: 创建在另一个进程的虚拟地址空间中运行的线程
 *      CreateRemoteThreadEx: 创建一个线程，该线程在另一个进程的虚拟地址空间中运行，并选择性地指定扩展属性
 *      OpenThread: 打开现有线程对象
 *      SuspendThread: 挂起指定的线程
 *      Sleep / SleepEx: 在指定的时间间隔内暂停当前线程的执行
 *      ResumeThread: 递减线程的挂起计数
 *      SwitchToThread: 导致调用线程执行准备好在当前处理器上运行的另一个线程
 *      ExitThread: 结束调用线程
 *      TerminateThread: 终止线程
 *
 *      Tls(Thread Local Storage): 线程本地存储
 *          TlsAlloc: (TLS) 索引分配线程本地存储
 *          TlsGetValue / TlsSetValue: 指定 TLS 索引的调用线程的 TLS 槽中的值
 *          TlsFree: 释放 TLS 索引
 **/