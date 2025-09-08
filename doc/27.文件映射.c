/**
 * 函数
 *      CreateFileMapping / CreateFileMapping2 / CreateFileMappingNuma: 为指定文件创建或打开命名或未命名的文件映射对象
 *      FlushViewOfFile: 在文件的映射视图中写入磁盘字节范围
 *      GetMappedFileName: 检查指定地址是否位于指定进程的地址空间中的内存映射文件中
 *      MapViewOfFile / MapViewOfFile2 / MapViewOfFile3 / MapViewOfFileEx / MapViewOfFileExNuma / MapViewOfFileNuma2: 将文件映射的视图映射到调用进程的地址空间
 *      OpenFileMapping: 打开命名的文件映射对象
 *      UnmapViewOfFile / UnmapViewOfFile2 / UnmapViewOfFileEx: 从调用进程的地址空间取消映射文件的映射视图
 *
 *      跨进程共享:
 *          对象名称: Global\ 开头
 **/