/**
 *  文件对象:
 *      File name: 文件名
 *      Current byte offset: 当前偏移
 *      Share mode: 共享模式
 *      I/O mode: IO模式
 *  文件基本操作:
 *      CreateFile(
 *          [in]           LPTSTR                lpFileName,
 *          [in]           DWORD                 dwDesiredAccess,
 *          [in]           DWORD                 dwShareMode,
 *          [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
 *          [in]           DWORD                 dwCreationDisposition,
 *          [in]           DWORD                 dwFlagsAndAttributes,
 *          [in, optional] HANDLE                hTemplateFile
 *      ): HANDLE 创建打开文件 INVALID_HANDLE_VALUE
 *          lpFileName: 文件路径
 *              文件: 文件路径
 *              目录: 路径
 *              逻辑磁盘: "\\.\x:"
 *              物理磁盘: "\\.\PHYSCIALDRIVE"
 *              串口: "COMx"
 *              并口: "LPTx"
 *          dwDesiredAccess:
 *              GENERIC_ALL: GENERIC_READ | GENERIC_WRITE | GENERIC_EXECUTE
 *              FILE_ALL_ACCESS: FILE_READ_DATA | FILE_WRITE_DATA | FILE_EXECUTE | FILE_APPEND_DATA
 *          dwShareMode:
 *              0
 *              FILE_SHARE_READ
 *              FILE_SHARE_WRITE
 *              FILE_SHARE_READ | FILE_SHARE_WRITE
 *              FILE_SHARE_DELETE
 *          dwCreationDisposition: 文件是否存在需求
 *              CREATE_NEW
 *              CREATE_ALWAYS
 *              OPEN_EXISTING: 只打开
 *              OPEN_ALWAYS: 打开或者新建
 *              TRUNCATE_EXISTING
 *          dwFlagsAndAttributes:
 *              flag:
 *                  缓存:
 *                      FILE_FLAG_NO_BUFFERING: 不使用缓存，慎用
 *                      FILE_FLAG_SEQUENTIAL_SCAN: 顺序读
 *                      FILE_FLAG_RANDOM_ACCESS: 随机读
 *                      FILE_FLAG_WRITE_THROUGH: 禁止写缓存
 *                  其他:
 *                      FILE_FLAG_DELETE_ON_CLOSE: 关闭句柄删除文件
 *                      FILE_FLAG_OVERLAPPED: 异步IO
 *              attribute
 *                  FILE_ATTRIBUTE_NORMAL
 *                  FILE_ATTRIBUTE_TEMPORARY
 *                  FILE_ATTRIBUTE_READONLY
 *                  FILE_ATTRIBUTE_HIDDEN
 *                  FILE_ATTRIBUTE_ARCHIVE
 *                  FILE_ATTRIBUTE_SYSTEM
 *                  FILE_ATTRIBUTE_ENCRYPTED
 *      MoveFile(
 *          [in] LPTSTR lpExistingFileName,
 *          [in] LPTSTR lpNewFileName
 *      ): BOOL 移动文件
 *      CopyFile(
 *          [in] LPCTSTR lpExistingFileName,
 *          [in] LPCTSTR lpNewFileName,
 *          [in] BOOL    bFailIfExists
 *      ): BOOL 复制文件
 *          bFailIfExists:
 *              TRUE: 文件已存在返回失败
 *              FALSE: 文件已存在覆盖
 *      CopyFileEx(...): BOOL 复制文件, 可追踪过程
 *      DeleteFile(
 *          [in] LPCSTR lpFileName
 *      ): BOOL 删除文件
 *      BOOL CloseHandle(
 *          [in] HANDLE hObject
 *      ): BOOL 关闭文件句柄
 * 文件信息:
 *      GetBinaryType(
 *          [in]  LPCSTR  lpApplicationName,
 *          [out] LPDWORD lpBinaryType
 *      ): BOOL 确定文件是否为可执行文件
 *          lpBinaryType:
 *              SCS_32BIT_BINARY: 基于 32 位 Windows 的应用程序
 *              SCS_64BIT_BINARY: 基于 64 位 Windows 的应用程序
 *              SCS_DOS_BINARY: 基于 MS-DOS 的应用程序
 *              SCS_OS216_BINARY: 基于 16 位 OS/2 的应用程序
 *              SCS_POSIX_BINARY: 基于 POSIX 的应用程序
 *              SCS_WOW_BINARY: 基于 16 位 Windows 的应用程序
 *      GetFileSize(
 *          [in]            HANDLE  hFile,
 *          [out, optional] LPDWORD lpFileSizeHigh
 *      ): DWORD 获得文件大小
 *      GetFileSizeEx(
 *          [in]  HANDLE         hFile,
 *          [out] PLARGE_INTEGER lpFileSize
 *      ): BOOL 获得文件大小
 * 
 *      GetTempFileName(
 *          [in]  LPCTSTR lpPathName,
 *          [in]  LPCTSTR lpPrefixString,
 *          [in]  UINT    uUnique,
 *          [out] LPTSTR  lpTempFileName
 *      ): UINT 创建临时文件名
 * 文件信息:
 *      GetFullPathName(
 *          [in]  LPCWSTR lpFileName,
 *          [in]  DWORD   nBufferLength,
 *          [out] LPWSTR  lpBuffer,
 *          [out] LPWSTR  *lpFilePart
 *      ): DWORD 获得文件完整路径和文件名
 *      GetFileSize(
 *          [in]            HANDLE  hFile,
 *          [out, optional] LPDWORD lpFileSizeHigh
 *      ): DWORD 获得文件大小
 *            
 *      GetFileTime(
 *          [in]            HANDLE     hFile,
 *          [out, optional] LPFILETIME lpCreationTime,
 *          [out, optional] LPFILETIME lpLastAccessTime,
 *          [out, optional] LPFILETIME lpLastWriteTime
 *      ): BOOL 获得文件最后修改时间
 *      GetFileType(
 *          [in] HANDLE hFile
 *      ): DWORD获得文件类型
 *          FILE_TYPE_CHAR: 字符文件
 *          FILE_TYPE_DISK: 磁盘文件
 *          FILE_TYPE_PIPE: 匿名通道
 *          FILE_TYPE_UNKNOWN: 未知
 * 文件备份:
 *      BackupRead(
 *          [in]  HANDLE  hFile,
 *          [out] LPBYTE  lpBuffer,
 *          [in]  DWORD   nNumberOfBytesToRead,
 *          [out] LPDWORD lpNumberOfBytesRead,
 *          [in]  BOOL    bAbort,
 *          [in]  BOOL    bProcessSecurity,
 *          [out] LPVOID  *lpContext
 *      ): BOOL 备份文件流
 *      BackupWrite(
 *          [in]  HANDLE  hFile,
 *          [in]  LPBYTE  lpBuffer,
 *          [in]  DWORD   nNumberOfBytesToWrite,
 *          [out] LPDWORD lpNumberOfBytesWritten,
 *          [in]  BOOL    bAbort,
 *          [in]  BOOL    bProcessSecurity,
 *          [out] LPVOID  *lpContext
 *      ): BOOL 备份文件流
 *      BackupSeek(
 *          [in]  HANDLE  hFile,
 *          [in]  DWORD   dwLowBytesToSeek,
 *          [in]  DWORD   dwHighBytesToSeek,
 *          [out] LPDWORD lpdwLowByteSeeked,
 *          [out] LPDWORD lpdwHighByteSeeked,
 *          [in]  LPVOID  *lpContext
 *      ): BOOL 备份数据流转发
 *      
 * 
 *      使用句柄:
 *          ReadFile(
 *              [in]                HANDLE       hFile,
 *              [out]               LPVOID       lpBuffer,
 *              [in]                DWORD        nNumberOfBytesToRead,
 *              [out, optional]     LPDWORD      lpNumberOfBytesRead,
 *              [in, out, optional] LPOVERLAPPED lpOverlapped
 *          ): BOOL 同步读文件
 *          WriteFile(
 *              [in]                HANDLE       hFile,
 *              [in]                LPCVOID      lpBuffer,
 *              [in]                DWORD        nNumberOfBytesToWrite,
 *              [out, optional]     LPDWORD      lpNumberOfBytesWritten,
 *              [in, out, optional] LPOVERLAPPED lpOverlapped
 *          ): BOOL 同步写文件
 *              nNumberOfBytesToRead、nNumberOfBytesToWrite: 读、写字数
 *              lpOverlapped: NULL, 否则异步读写
 *          ReadFileEx(
 *              [in]            HANDLE                          hFile,
 *              [out, optional] LPVOID                          lpBuffer,
 *              [in]            DWORD                           nNumberOfBytesToRead,
 *              [in, out]       LPOVERLAPPED                    lpOverlapped,
 *              [in]            LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
 *          ): BOOL 异步读文件
 *          WriteFileEx(
 *              [in]           HANDLE                          hFile,
 *              [in, optional] LPCVOID                         lpBuffer,
 *              [in]           DWORD                           nNumberOfBytesToWrite,
 *              [in, out]      LPOVERLAPPED                    lpOverlapped,
 *              [in]           LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
 *          ): BOOL 异步写文件
 *          ReadFileScatter(
 *              [in]      HANDLE                  hFile,
 *              [in]      FILE_SEGMENT_ELEMENT [] aSegmentArray,
 *              [in]      DWORD                   nNumberOfBytesToRead,
 *                        LPDWORD                 lpReserved,
 *              [in, out] LPOVERLAPPED            lpOverlapped
 *          ): BOOL 异步读
 *          WriteFileGather(
 *              [in]      HANDLE                  hFile,
 *              [in]      FILE_SEGMENT_ELEMENT [] aSegmentArray,
 *              [in]      DWORD                   nNumberOfBytesToWrite,
 *                        LPDWORD                 lpReserved,
 *              [in, out] LPOVERLAPPED            lpOverlapped
 *          ): BOOL 异步写
 *          SetFilePointer(
 *              [in]                HANDLE hFile,
 *              [in]                LONG   lDistanceToMove,
 *              [in, out, optional] PLONG  lpDistanceToMoveHigh,
 *              [in]                DWORD  dwMoveMethod
 *          ): DWORD 重置文件指针
 *          SetFilePointerEx(
 *              [in]            HANDLE         hFile,
 *              [in]            LARGE_INTEGER  liDistanceToMove,
 *              [out, optional] PLARGE_INTEGER lpNewFilePointer,
 *              [in]            DWORD          dwMoveMethod
 *          ): BOOL 重置文件指针
 *              dwMoveMethod:
 *                  FILE_BEGIN
 *                  FILE_CURRENT
 *                  FILE_END
 *          FlushFileBuffers([in] HANDLE hFile): BOOL 刷新缓冲区
 *          CloseHandle([in] HANDLE hObject): BOOL 关闭句柄
 **/
