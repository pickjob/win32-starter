/**
 * 等待函数
 *      单对象等待函数
 *          SignalObjectAndWait: 向一个对象发出信号，并等待另一个对象作为单个作
 *          WaitForSingleObject / WaitForSingleObjectEx: 等待指定的对象处于信号状态或超时间隔过
 *              dwMilliseconds:
 *                  INFINITE
 *              bAlertable: 是否可提醒
 *              result:
 *                  WAIT_ABANDONED
 *                  WAIT_OBJECT_0
 *                  WAIT_TIMEOUT
 *                  WAIT_FAILED
 *      多对象等待函数
 *          WaitForMultipleObjects / WaitForMultipleObjectsEx: 等待一个或多个指定对象处于信号状态或超时间隔过
 *          MsgWaitForMultipleObjects / MsgWaitForMultipleObjectsEx: 等待一个或多个指定对象处于信号状态或超时间隔过
 *      已注册的等待函数
 *          RegisterWaitForSingleObject: 指示线程池中的等待线程等待对象
 *          UnregisterWait / UnregisterWaitEx: 取消已注册的等待作
 * 同步对象
 *      Evnet: 事件
 *          CreateEvent / CreateEventEx: 创建或打开命名或未命名的事件对象
 *          OpenEvent: 打开现有的命名事件对象
 *          PulseEvent: 将指定的事件对象设置为信号状态，然后在释放适当的等待线程数后将其重置为非对齐状态
 *          SetEvent: 将指定的事件对象设置为信号状态
 *          ResetEvent: 将指定的事件对象设置为非对齐状态
 *      Mutex: 互斥体
 *          CreateMutex / CreateMutexEx: 创建或打开命名或未命名的互斥体对象
 *          OpenMutex: 打开现有的命名互斥体对象
 *          ReleaseMutex: 释放指定互斥体对象的所有权
 *      Semaphore: 信号量
 *              当前资源计数大于0, 信号量处于触发状态
 *              当前资源计数等于0, 信号处于未触发状态
 *              当前计数不会负数
 *              当前计数不会大于最大资源数
 *          CreateSemaphore / CreateSemaphoreEx: 创建或打开命名或未命名的信号灯对象
 *          OpenSemaphore: 打开现有的命名信号灯对象
 *          ReleaseSemaphore: 将指定的信号量增加指定的信号量
 *      Barriers: 栅栏
 *          InitializeSynchronizationBarrier: 初始化新的同步屏障
 *          EnterSynchronizationBarrier: 输入同步屏障，并等待适当的线程数在屏障上交接
 *          DeleteSynchronizationBarrier: 删除同步屏障
 *      Waitable timer: 等待定时器
 *          CreateWaitableTimer / CreateWaitableTimerEx: 创建或打开可等待的计时器对象
 *          OpenWaitableTimer: 打开现有的命名可等待计时器对象
 *          SetWaitableTimer / SetWaitableTimerEx: 激活指定的可等待计时器
 *          TimerAPCProc: 与 SetWaitableTimer 函数一起使用的应用程序定义的计时器完成例程
 *          CancelWaitableTimer: 将指定的可等待计时器设置为非活动状态
 *      Critical Section: 关键代码段
 *          InitializeCriticalSection / InitializeCriticalSectionEx: 初始化关键节对象
 *          InitializeCriticalSectionAndSpinCount: 初始化关键节对象并设置关键节的旋转计数
 *          TryEnterCriticalSection: 尝试在不阻止的情况下输入关键节
 *          EnterCriticalSection: 等待指定关键节对象的所有权
 *          SetCriticalSectionSpinCount: 设置指定关键节的旋转计数
 *          LeaveCriticalSection: 释放指定关键节对象的所有权
 *          DeleteCriticalSection: 释放未拥有的关键节对象使用的所有资源
 *      Slim Reader/Writer Lock:
 *          InitializeSRWLock: 初始化精简的读取器/编写器（SRW）锁
 *          AcquireSRWLockExclusive: 以独占模式获取精简的读取器/编写器（SRW）锁
 *          TryAcquiresRWLockExclusive: 尝试以独占模式获取精简的读取器/编写器（SRW）锁
 *          ReleaseSRWLockExclusive: 释放以独占模式获取的精简读取器/编写器（SRW）锁
 *          AcquireSRWLockShared: 在共享模式下获取精简的读取器/编写器（SRW）锁
 *          TryAcquireSRWLockShared: 尝试在共享模式下获取精简的读取器/编写器（SRW）锁
 *          ReleaseSRWLockShared: 释放在共享模式下获取的精简读取器/编写器（SRW）锁
 *
 *          InitializeConditionVariable: 初始化条件变量
 *          SleepConditionVariableCS: 在指定的条件变量上睡眠，并将指定的关键节作为原子作释放
 *          SleepConditionVariableSRW: 在指定的条件变量上休眠，并将指定的锁释放为原子作
 *          WakeAllConditionVariable: 唤醒所有等待指定条件变量的线程
 *          WakeConditionVariable: 唤醒等待指定条件变量的单个线程
 *      One-Time Initialization: 一次性初始化
 *          InitOnceInitialize: 初始化一次性初始化结构
 *          InitOnceExecuteOnce: 一次成功执行指定的函数
 *          InitOnceBeginInitialize: 开始一次性初始化
 *          InitOnceComplete: 完成一次性初始化
 *              dwFlags:
 *                  INIT_ONCE_ASYNC
 *                  INIT_ONCE_CHECK_ONLY
 * 原子操作: InterlockedXXX
 * 计时器函数
 *      CreateTimerQueue: 为计时器创建队列
 *      DeleteTimerQueue / DeleteTimerQueueEx: 删除计时器队列
 *      CreateTimerQueueTimer: 创建计时器队列计时器
 *      ChangeTimerQueueTimer: 更新计时器队列计时器
 *      DeleteTimerQueueTimer: 取消计时器队列计时器
 **/