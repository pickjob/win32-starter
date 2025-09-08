/**
 * 区别
 *      Job: 作业对象, 将进程组作为一个单元进行管理
 *      Process: 进程, 提供执行程序所需的资源
 *      Thread: 线程, 进程内可计划执行的实体
 *          堆栈空间: 默认1MB
 *      ThreadPool: 线程池, 工作线程集合
 * 函数
 *      QueryInformationJobObject / SetInformationJobObject: 限制和作业状态信息
 *      CreateJobObject: 创建或打开作业对象
 *      OpenJobObject: 打开现有作业对象
 *      AssignProcessToJobObject: 将进程与现有作业对象相关联
 *      IsProcessInJob: 确定进程是否在指定的作业中运行
 *      TerminateJobObject: 终止当前与作业关联的所有进程
 **/