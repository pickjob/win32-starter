/**
 * 同步
 *      CreateThreadpoolWait: 创建新的等待对象
 *      SetThreadpoolWait / SetThreadpoolWaitEx: 设置 wait 对象
 *      WaitForThreadpoolWaitCallbacks: 等待未完成的等待回调完成, 并选择性地取消尚未开始执行的挂起回调
 *      CloseThreadpoolWait: 释放指定的等待对象
 * 回调环境
 *      InitializeThreadpoolEnvironment: 初始化回调环境
 *      SetThreadpoolCallbackPool: 设置生成回调时要使用的线程池
 *      SetThreadpoolCallbackCleanupGroup: 将指定的清理组与指定的回调环境相关联
 *      SetThreadpoolCallbackLibrary: 确保只要有未完成的回调, 指定的 DLL 就保持加载状态
 *      SetThreadpoolCallbackPriority: 指定回调函数相对于同一线程池中其他工作项的优先级
 *      SetThreadpoolCallbackRunsLong: 指示与此回调环境关联的回调可能不会快速返回
 *      DestroyThreadpoolEnvironment: 删除指定的回调环境
 * 池
 *      CreateThreadpool: 分配要执行回调的新线程池
 *      SetThreadpoolThreadMaximum: 设置指定线程池可以分配给进程回调的最大线程数
 *      SetThreadpoolThreadMinimum: 设置指定线程池必须提供给进程回调的最小线程数
 *      CloseThreadpool: 关闭指定的线程
 * 清理组
 *      CreateThreadpoolCleanupGroup: 创建应用程序可用于跟踪一个或多个线程池回调的清理组
 *      CloseThreadpoolCleanupGroup: 关闭指定的清理组
 *      CloseThreadpoolCleanupGroupMembers: 释放指定清理组的成员, 等待所有回调函数完成, 并选择性地取消任何未完成的回调函数
 * 工作
 *      CreateThreadpoolWork: 创建新的工作对象
 *      SubmitThreadpoolWork: 将工作对象发布到线程池
 *      TrySubmitThreadpoolCallback: 请求线程池工作线程调用指定的回调函数
 *      WaitForThreadpoolWorkCallbacks: 等待未完成的工作回调完成, 并选择性地取消尚未开始执行的挂起回调。
 *      CloseThreadpoolWork: 释放指定的工作对象
 * 定时器
 *      CreateThreadpoolTimer: 创建新的计时器对象
 *      IsThreadpoolTimerSet: 确定当前是否设置了指定的计时器对象
 *      SetThreadpoolTimer / SetThreadpoolTimerEx: 设置计时器对象
 *      WaitForThreadpoolTimerCallbacks: 等待未完成的计时器回调完成, 并选择性地取消尚未开始执行的挂起回调
 *      CloseThreadpoolTimer: 释放指定的计时器对象
 * IO
 *      CreateThreadpoolIo: 创建新的 I/O 完成对象
 *      StartThreadpoolIo： 通知线程池 I/O 操作可能针对指定的 I/O 完成对象开始
 *      CancelThreadpoolIo: 从 StartThreadpoolIo 函数取消通知
 *      CloseThreadpoolIo: 释放指定的 I/O 完成对象
 *      WaitForThreadpoolIoCallbacks: 等待未完成的 I/O 完成回调完成, 并选择性地取消尚未开始执行的挂起回调
 * 回调
 *      CallbackMayRunLong: 指示回调可能不会快速返回
 * 回调清理
 *      ReleaseMutexWhenCallbackReturns: 指定在当前回调完成时线程池将释放的互斥体
 *      ReleaseSemaphoreWhenCallbackReturns: 指定在当前回调完成时线程池将释放的信号灯
 *      LeaveCriticalSectionWhenCallbackReturns: 指定当前回调完成时线程池将释放的关键部分
 *      FreeLibraryWhenCallbackReturns: 指定在当前回调完成时线程池将卸载的 DLL
 *      SetEventWhenCallbackReturns: 指定当前回调完成时线程池将设置的事件
 *      DisassociateCurrentThreadFromCallback: 删除当前正在执行的回调函数与启动回调的对象之间的关联
 * 其他
 *      QueryThreadpoolStackInformation / SetThreadpoolStackInformation: 线程池中线程的堆栈保留和提交大小
 *      SetThreadpoolCallbackPersistent: 指定回调应在持久线程上运行
 */
