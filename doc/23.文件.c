/**
 *  文件对象:
 *      File name: 文件名
 *      Current byte offset: 当前偏移
 *      Share mode: 共享模式
 *      I/O mode: IO模式
 *  限制
 *      MAX_PATH: 260
 *      扩展长度路径: 32767
 *          \\?\D:\非常长的路径
 * 文件信息:
 *      GetShortPathName: 8.3 格式的长文件名
 *      GetLongPathName: 短名称的长文件名版本
 *      GetFullPathName: 文件的完整路径
 *      GetFileSize / GetFileSizeEx: 获得文件大小
 *      GetTempFileName: 创建临时文件名
 *      GetFileTime / SetFileTime: 获得 / 设置 文件最后修改时间
 *      GetFileType: 检索文件的类型
 *          FILE_TYPE_CHAR: 字符文件
 *          FILE_TYPE_DISK: 磁盘文件
 *          FILE_TYPE_PIPE: 匿名通道
 *          FILE_TYPE_UNKNOWN: 未知
 *      GetBinaryType: 确定文件是否为可执行文件
 *          lpBinaryType:
 *              SCS_32BIT_BINARY: 基于 32 位 Windows 的应用程序
 *              SCS_64BIT_BINARY: 基于 64 位 Windows 的应用程序
 *              SCS_DOS_BINARY: 基于 MS-DOS 的应用程序
 *              SCS_OS216_BINARY: 基于 16 位 OS/2 的应用程序
 *              SCS_POSIX_BINARY: 基于 POSIX 的应用程序
 *              SCS_WOW_BINARY: 基于 16 位 Windows 的应用程序
 *  文件基本操作:
 *      ReadFile / ReadFileEx: 读文件
 *      WriteFile / WriteFileEx: 写文件
 *          nNumberOfBytesToRead、nNumberOfBytesToWrite: 读、写字数
 *          lpOverlapped: NULL, 否则异步读写
 *      ReadFileScatter: 散点收集方案读
 *      WriteFileGather: 散点收集方案写
 *      SetFilePointer / SetFilePointerEx : 设置文件指针
 *          dwMoveMethod:
 *              FILE_BEGIN
 *              FILE_CURRENT
 *              FILE_END
 *      FlushFileBuffers: 刷新缓冲区
 *      SetEndOfFile: 截断或扩展文件
 *      MoveFile / MoveFileEx: 移动文件
 *      CopyFile / CopyFileEx: 复制文件
 *          bFailIfExists:
 *              TRUE: 文件已存在返回失败
 *              FALSE: 文件已存在覆盖
 *      LockFile / LockFileEx: 通过调用进程锁定指定文件以独占访问
 *      UnlockFile / UnlockFileEx: 解锁指定文件中的区域
 *      DeleteFile: 删除文件
 *      CreateFile: 创建打开文件
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
 **/