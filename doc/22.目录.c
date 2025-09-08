/**
 * 函数:
 *      遍历目录
 *          FindFirstFile / FindFirstFileEx + FindNextFile + FindClose
 *              WIN32_FIND_DATA
 *                  dwFileAttributes
 *                      FILE_ATTRIBUTE_DIRECTORY: 文件夹
 *                  cFileName: 文件名
 *      监视目录改动
 *          FindFirstChangeNotification: 创建更改通知句柄并设置初始更改通知筛选器条件
 *          FindNextChangeNotification: 作系统在下次检测到适当的更改时发出更改通知信号的请求处理
 *          FindCloseChangeNotification: 停止更改通知处理监视
 *
 *          ReadDirectoryChanges / ReadDirectoryChangesEx: 检索描述指定目录中更改的信息
 *      GetCurrentDirectory / SetCurrentDirectory: 检索当前进程的当前目录
 *      GetWindowsDirectory: 获得Windows目录路径(C:\Windows)
 *      GetSystemDirectory: UINT 获得系统目录路径(C:\Windows\System32)
 *      CreateDirectory / CreateDirectory2 / CreateDirectoryEx: 创建目录
 *      MoveFileEx: 移动目录
 *      MoveFileWithProgress: 移动目录
 *          dwFlags:
 *              MOVEFILE_COPY_ALLOWED
 *              MOVEFILE_DELAY_UNTIL_REBOOT
 *              MOVEFILE_FAIL_IF_NOT_TRACKABLE
 *              MOVEFILE_REPLACE_EXISTING
 *              MOVEFILE_WRITE_THROUGH
 *      RemoveDirectory / RemoveDirectory2: 删除现有空目录
 **/