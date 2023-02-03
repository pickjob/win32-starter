/**
 * I/O完成端口(IOCP, I/O completion port):
 *      CreateIoCompletionPort(
 *          _In_     HANDLE    FileHandle,
 *          _In_opt_ HANDLE    ExistingCompletionPort,
 *          _In_     ULONG_PTR CompletionKey,
 *          _In_     DWORD     NumberOfConcurrentThreads
 *      ): HANDLE 创建、关联 IOCP
 *          FileHandle:
 *              CreateFile 创建时必须使用 FILE_FLAG_OVERLAPPED
 *          NumberOfConcurrentThreads:
 *              0: 与CPU个数一致
 *              ExistingCompletionPort非空忽略
 *          CompletionKey:
 *              预定义好的完成后得到的 CompletionKey
 *      GetQueuedCompletionStatus(
 *          [in]  HANDLE       CompletionPort,
 *                LPDWORD      lpNumberOfBytesTransferred,
 *          [out] PULONG_PTR   lpCompletionKey,
 *          [out] LPOVERLAPPED *lpOverlapped,
 *          [in]  DWORD        dwMilliseconds
 *      ): BOOL 检查IOCP 状态, 出队
 *          lpCompletionKey:
 *              获得IOCP关联的 CompletionKey
 *          dwMilliseconds:
 *              INFINITE
 *      PostQueuedCompletionStatus(
 *          _In_     HANDLE       CompletionPort,
 *          _In_     DWORD        dwNumberOfBytesTransferred,
 *          _In_     ULONG_PTR    dwCompletionKey,
 *          _In_opt_ LPOVERLAPPED lpOverlapped
 *      ): BOOL 发送预定义好的IOCP 状态, 入队
 *      BindIoCompletionCallback(
 *          [in] HANDLE                          FileHandle,
 *          [in] LPOVERLAPPED_COMPLETION_ROUTINE Function,
 *          [in] ULONG                           Flags
 *      ): BOOL
 *      LpoverlappedCompletionRoutine(
 *          [in]      DWORD dwErrorCode,
 *          [in]      DWORD dwNumberOfBytesTransfered,
 *          [in, out] LPOVERLAPPED lpOverlapped
 *      ): void
*/