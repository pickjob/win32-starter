/*
 * 原子操作: InterlockedXXX
 *      InterlockedIncrement(
 *          [in, out] LONG volatile *Addend
 *      ): LONG 原子加一, 32位数值, 64结尾64位数值
 *      InterlockedDecrement(
 *          [in, out] LONG volatile *Addend
 *      ): LONG 原子减一, 32位数值, 64结尾64位数值
 *      InterlockedAdd(
 *          [in, out] LONG volatile *Addend,
 *          [in]      LONG          Value
 *      ): LONG 原子加法
 *      InterlockedExchange(
 *          [in, out] LONG volatile *Target,
 *          [in]      LONG          Value
 *      ): LONG 原子交换, 32位数值, 64结尾64位数值 
 *      InterlockedExchangePointer(
 *          [in, out] PVOID volatile *Target,
 *          [in]      PVOID          Value
 *      ): PVOID 原子交换(指针)
 *      InterlockedExchangeAdd(
 *          [in, out] LONG volatile *Addend,
 *          [in]      LONG          Value
 *      ): LONG 原子加法
 *      InterlockedCompareExchange(
 *          [in, out] LONG volatile *Destination,
 *          [in]      LONG          ExChange,
 *          [in]      LONG          Comperand
 *      ): LONG 原子比较交换， CAS, 32位数值, 64结尾64位数值 
 *      InterlockedCompareExchangePointer(
 *          [in, out] PVOID volatile *Destination,
 *          [in]      PVOID          Exchange,
 *          [in]      PVOID          Comperand
 *      ): PVOID 原子比较交换(指针) CAS
 *      InterlockedAnd(
 *          [in, out] LONG volatile *Destination,
 *          [in]      LONG          Value
 *      ): LONG 原子逻辑 与
 *      InterlockedOr(
 *          [in, out] LONG volatile *Destination,
 *          [in]      LONG          Value
 *      ): LONG 原子逻辑 或
 *      InterlockedXor(
 *          [in, out] LONG volatile *Destination,
 *          [in]      LONG          Value
 *      ): LONG 原子逻辑 异或
 * 等待函数:
 *      WaitForSingleObject(
 *          [in] HANDLE hHandle,
 *          [in] DWORD  dwMilliseconds
 *      ): DWORD 等待对象某种条件达成
 *      WaitForSingleObjectEx(
 *          [in] HANDLE hHandle,
 *          [in] DWORD  dwMilliseconds,
 *          [in] BOOL   bAlertable
 *      ): DWORD 等待对象某种条件达成
 *          dwMilliseconds:
 *              INFINITE
 *          bAlertable: 是否可提醒              
 *          result:
 *              WAIT_ABANDONED
 *              WAIT_OBJECT_0
 *              WAIT_TIMEOUT
 *              WAIT_FAILED
 *      SignalObjectAndWait(
 *          [in] HANDLE hObjectToSignal,
 *          [in] HANDLE hObjectToWaitOn,
 *          [in] DWORD  dwMilliseconds,
 *          [in] BOOL   bAlertable
 *      ): DWORD 通知一个对象, 等待另一个对象
 *      WaitForMultipleObjects(
 *          [in] DWORD        nCount,
 *          [in] const HANDLE *lpHandles,
 *          [in] BOOL         bWaitAll,
 *          [in] DWORD        dwMilliseconds
 *      ): DWORD 等待多个对象
 *      WaitForMultipleObjectsEx(
 *          [in] DWORD        nCount,
 *          [in] const HANDLE *lpHandles,
 *          [in] BOOL         bWaitAll,
 *          [in] DWORD        dwMilliseconds,
 *          [in] BOOL         bAlertable
 *      ): DWORD
 * 同步对象:
 *      Evnet: 事件
 *          CreateEvent(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpEventAttributes,
 *              [in]           BOOL                  bManualReset,
 *              [in]           BOOL                  bInitialState,
 *              [in, optional] LPTSTR                lpName
 *          ): HANDLE 创建 Event, 失败返回 NULL
 *          CreateEventExA(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpEventAttributes,
 *              [in, optional] LPCSTR                lpName,
 *              [in]           DWORD                 dwFlags,
 *              [in]           DWORD                 dwDesiredAccess
 *          ): HANDLE
 *              bManualReset: TRUE ResetEvent First
 *              bInitialState: TRUE singaled
 *          OpenEvent(
 *              [in] DWORD  dwDesiredAccess,
 *              [in] BOOL   bInheritHandle,
 *              [in] LPTSTR lpName
 *          ): HANDLE
 *          SetEvent(
 *              [in] HANDLE hEvent
 *          ): BOOL 触发 Event
 *          ResetEvent(
 *              [in] HANDLE hEvent
 *          ): BOOL 重置 Event
 *      Mutex: 互斥体
 *          CreateMutex(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpMutexAttributes,
 *              [in]           BOOL                  bInitialOwner,
 *              [in, optional] LPTSTR                lpName
 *          ): HANDLE 创建Mutex, 失败返回 NULL
 *              bInitialOwner: 是否立刻拥有
 *          CreateMutexEx(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpMutexAttributes,
 *              [in, optional] LPTSTR                lpName,
 *              [in]           DWORD                 dwFlags,
 *              [in]           DWORD                 dwDesiredAccess
 *          ): HANDLE
 *              dwFlags:
 *                  CREATE_MUTEX_INITIAL_OWNER
 *          OpenMutex(
 *              [in] DWORD   dwDesiredAccess,
 *              [in] BOOL    bInheritHandle,
 *              [in] LPTSTR lpName
 *          ): HANDLE
 *          ReleaseMutex(
 *              [in] HANDLE hMutex
 *          ): BOOL 释放Mutex
 *      Semaphore: 信号量
 *          规则:
 *              当前资源计数大于0, 信号量处于出发状态
 *              当前资源计数等于0, 信号处于未触发状态
 *              当前计数不会负数
 *              当前计数不会大于最大资源数
 *          CreateSemaphore(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
 *              [in]           LONG                  lInitialCount,
 *              [in]           LONG                  lMaximumCount,
 *              [in, optional] LPTSTR                lpName
 *          ): HANDLE
 *          CreateSemaphoreEx(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
 *              [in]           LONG                  lInitialCount,
 *              [in]           LONG                  lMaximumCount,
 *              [in, optional] LPCSTR                lpName,
 *                             DWORD                 dwFlags,
 *              [in]           DWORD                 dwDesiredAccess
 *          ): HANDLE
 *              lInitialCount: 初始化数量
 *              lMaximumCount: 最大数量
 *          OpenSemaphore(
 *              [in] DWORD   dwDesiredAccess,
 *              [in] BOOL    bInheritHandle,
 *              [in] LPTWSTR lpName
 *          ): HANDLE
 *          ReleaseSemaphore(
 *              [in]            HANDLE hSemaphore,
 *              [in]            LONG   lReleaseCount,
 *              [out, optional] LPLONG lpPreviousCount
 *          ): HANDLE
 *      Waitable timer: 等待定时器
 *          CreateWaitableTimer(
 *              [in, optional] LPSECURITY_ATTRIBUTES lpTimerAttributes,
 *              [in]           BOOL                  bManualReset,
 *              [in, optional] LPCWSTR               lpTimerName
 *          ): HANDLE 创建定时器
 *          OpenWaitableTimer(
 *              [in] DWORD   dwDesiredAccess,
 *              [in] BOOL    bInheritHandle,
 *              [in] LPTWSTR lpTimerName
 *          ): HANDLE
 *          SetWaitableTimer(
 *              [in]           HANDLE              hTimer,
 *              [in]           const LARGE_INTEGER *lpDueTime,
 *              [in]           LONG                lPeriod,
 *              [in, optional] PTIMERAPCROUTINE    pfnCompletionRoutine,
 *              [in, optional] LPVOID              lpArgToCompletionRoutine,
 *              [in]           BOOL                fResume
 *          ): BOOL 设置定时器
 *          CancelWaitableTimer([in] HANDLE hTimer): BOOL 取消定时器
 *      Critical Section: 关键代码段
 *          InitializeCriticalSection(
 *              [out] LPCRITICAL_SECTION lpCriticalSection
 *          ): void 初始化
 *          InitializeCriticalSectionEx(
 *              [out] LPCRITICAL_SECTION lpCriticalSection,
 *              [in]  DWORD              dwSpinCount,
 *              [in]  DWORD              Flags
 *          ): BOOL
 *          InitializeCriticalSectionAndSpinCount(
 *              [out] LPCRITICAL_SECTION lpCriticalSection,
 *              [in]  DWORD              dwSpinCount
 *          ): BOOL
 *          SetCriticalSectionSpinCount(
 *              [in, out] LPCRITICAL_SECTION lpCriticalSection,
 *              [in]      DWORD              dwSpinCount
 *          ): DWORD
 *          EnterCriticalSection(
 *              [in, out] LPCRITICAL_SECTION lpCriticalSection
 *          ): void 进入 Critical Section, 等待进入
 *          TryEnterCriticalSection(
 *              [in, out] LPCRITICAL_SECTION lpCriticalSection
 *          ): void 进入 Critical Section, 能进则进
 *          LeaveCriticalSection(
 *              [in, out] LPCRITICAL_SECTION lpCriticalSection
 *          ): void 离开 Critical Section
 *          DeleteCriticalSection[
 *              in, out] LPCRITICAL_SECTION lpCriticalSection
 *          ): void
 *      Slim Reader/Writer Lock:
 *          InitializeSRWLock(
 *              [out] PSRWLOCK SRWLock
 *          ): void 初始化 SRW 锁
 *          AcquireSRWLockShared(
 *              [in, out] PSRWLOCK SRWLock
 *          ): void 获得共享锁
 *          AcquireSRWLockExclusive(
 *              [in, out] PSRWLOCK SRWLock
 *          ): void 获得排他锁
 *          TryAcquireSRWLockShared(
 *              [in, out] PSRWLOCK SRWLock
 *          )： BOOL
 *          TryAcquireSRWLockExclusive(
 *              [in, out] PSRWLOCK SRWLock
 *          ): BOOL
 *          ReleaseSRWLockShared(
 *              [in, out] PSRWLOCK SRWLock
 *          ): void 释放共享锁
 *          ReleaseSRWLockExclusive(
 *              [in, out] PSRWLOCK SRWLock
 *          ): void 释放排他锁
 *      One-Time Initialization:
 *          InitOnceInitialize([out] PINIT_ONCE InitOnce): void 初始化
 *          InitOnceBeginInitialize(
 *              [in, out]       LPINIT_ONCE lpInitOnce,
 *              [in]            DWORD       dwFlags,
 *              [out]           PBOOL       fPending,
 *              [out, optional] LPVOID      *lpContext
 *          ): BOOL 开始初始化
 *          InitOnceComplete(
 *              [in, out]      LPINIT_ONCE lpInitOnce,
 *              [in]           DWORD       dwFlags,
 *              [in, optional] LPVOID      lpContext
 *          ): BOOL
 *              dwFlags:
 *                  INIT_ONCE_ASYNC
 *                  INIT_ONCE_CHECK_ONLY
 *          InitOnceExecuteOnce(
 *              [in, out]           PINIT_ONCE    InitOnce,
 *              [in]                PINIT_ONCE_FN InitFn,
 *              [in, optional]      PVOID         Parameter,
 *              [in, out, optional] LPVOID        *Context
 *          ): BOOL 执行任务一次
 *              PINIT_ONCE:
 *                  BOOL PinitOnceFn(
 *                      [in, out]           PINIT_ONCE InitOnce,
 *                      [in, out, optional] PVOID Parameter,
 *                      [out, optional]     PVOID *Context
 *                  ): lpInitOnce 签名
 *      Barriers: 栅栏
 *          InitializeSynchronizationBarrier(
 *              [out] LPSYNCHRONIZATION_BARRIER lpBarrier,
 *              [in]  LONG                      lTotalThreads,
 *              [in]  LONG                      lSpinCount
 *          ): BOOL
 *          EnterSynchronizationBarrier(
 *              [in, out] LPSYNCHRONIZATION_BARRIER lpBarrier,
 *              [in]      DWORD                     dwFlags
 *          ): BOOL
 *              dwFlags:
 *                  SYNCHRONIZATION_BARRIER_FLAGS_BLOCK_ONLY
 *                  SYNCHRONIZATION_BARRIER_FLAGS_SPIN_ONLY
 *                  SYNCHRONIZATION_BARRIER_FLAGS_NO_DELETE
 *          DeleteSynchronizationBarrier(
 *              [in, out] LPSYNCHRONIZATION_BARRIER lpBarrier
 *          ): BOOL
 **/
