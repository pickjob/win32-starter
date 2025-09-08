/**
 * 匿名管道
 * 命名管道
 *      \\ServerName\pipe\PipeName
 * 函数
 *      GetNamedPipeInfo: 检索有关指定命名管道的信息
 *      GetNamedPipeHandleState / SetNamedPipeHandleState: 命名管道的信息
 *      PeekNamedPipe: 将数据从命名管道或匿名管道复制到缓冲区中, 而无需将其从管道中删除
 *      WaitNamedPipe: 等待, 直到超时间隔过或指定命名管道的实例可用于连接
 *      CreateNamedPipe: 创建命名管道的实例，并返回后续管道作的句柄
 *          访问模式
 *              PIPE_ACCESS_INBOUND
 *              PIPE_ACCESS_OUTBOUND
 *              PIPE_ACCESS_DUPLEX
 *      CallNamedPipe: 连接到消息类型管道, 从管道中写入和读取, 然后关闭管道
 *      ConnectNamedPip: 使命名管道服务器进程能够等待客户端进程连接到命名管道的实例
 */