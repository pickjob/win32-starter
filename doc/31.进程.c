/**
 * 函数
 *      枚举进程
 *          EnumProcesses: 检索系统中每个进程对象的进程标识符
 *      GetCommandLine: 检索当前进程的命令行字符串
 *      GetCurrentProcess: 检索当前进程的伪句柄
 *      GetCurrentProcessId: 检索调用进程的进程标识符
 *      GetProcessId: 检索指定进程的进程标识符
 *      GetProcessImageFileName
 *      GetEnvironmentStrings: 检索当前进程的环境块
 *      FreeEnvironmentStrings: 释放环境字符串块
 *      GetEnvironmentVariable / SetEnvironmentVariable: 环境块中指定变量的值
 *      GetGuiResources: 检索图形用户界面 (GUI) 指定进程正在使用的对象的句柄计数
 *      GetLogicalProcessorInformation: 检索有关逻辑处理器和相关硬件的信息
 *      GetProcessGroupAffinity: 检索指定进程的处理器组相关性
 *      GetProcessHandleCount: 检索属于指定进程的打开句柄数
 *      GetProcessIoCounters: 检索指定进程执行的所有 I/O 操作的计帐信息
 *      GetProcessPriorityBoost / SetProcessPriorityBoost: 检索指定进程的优先级提升控制状态
 *      GetProcessShutdownParameters / SetProcessShutdownParameters: 检索当前调用进程的关闭参数
 *      GetProcessTimes: 检索指定进程的 计时信息
 *      GetProcessVersion: 检索预期运行指定进程的系统的主版本号和次版本号
 *      GetProcessWorkingSetSize / GetProcessWorkingSetSizeEx / SetProcessWorkingSetSize / SetProcessWorkingSetSizeEx: 指定进程的最小和最大工作集大小
 *      GetProcessorSystemCycleTime: 检索指定组中每个处理器执行延迟过程调用所用的周期时间， (DPC) 和中断服务例程 (ISR)
 *      GetStartupInfo: 检索创建调用进程时指定的 STARTUPINFO 结构的内容
 *      GetExitCodeProcess: 检索指定进程的终止状态
 *      GetPriorityClass / SetPriorityClass: 指定进程的优先级类
 *      GetProcessAffinityMask / SetProcessAffinityMask: 指定进程的进程关联掩码和系统的系统关联掩码
 *      IsImmersiveProcess: 确定进程是否属于 Windows 应用商店应用
 *      QueryFullProcessImageName: 检索指定进程的可执行映像的完整名称
 *      QueryProcessAffinityUpdateMode / SetProcessAffinityUpdateMode: 检索指定进程的相关性更新模式
 *      QueryProcessCycleTime: 检索指定进程的所有线程的周期时间之和
 *      SetProcessInformation: 设置指定进程的信息
 *      CreateProcess: 创建新进程及其主线程
 *      CreateProcessAsUser: 创建新进程及其主线程 新进程在指定令牌表示的用户的安全上下文中运行
 *      OpenProcess: 打开现有的本地进程对象
 *      FlushProcessWriteBuffers: 刷新运行当前进程的线程的每个处理器的写入队列
 *      ExitProcess: 结束调用进程及其所有线程
 *      TerminateProcess: 终止指定的进程及其所有线程
 *
 *      模块
 *          EnumProcessModules / EnumProcessModulesEx
 *      GetModuleFileNameEx
 *      GetModuleBaseName
 *      GetModuleInformation
 **/