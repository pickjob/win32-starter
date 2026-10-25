//
// 头文件
//      <signal.h>
// 类型
//      sig_atomic_t: 原子类型, 用于信号处理函数中
// 宏
//      信号类型
//          SIGABRT: 异常终止
//          SIGFPE: 浮点异常
//          SIGILL: 非法指令
//          SIGINT: 中断
//          SIGSEGV: 无效内存引用
//          SIGTERM: 终止请求
//          SIGBREAK: Ctrl-Break
//          SIGKILL: 杀死进程
//          SIGUSR1: 用户自定义信号 1
//          SIGUSR2: 用户自定义信号 2
//          SIGCHLD: 子进程状态改变
//          SIGCONT: 继续执行
//          SIGSTOP: 停止执行
//          SIGTSTP: 终端停止信号
//          SIGTTIN: 后台进程尝试从终端读取
//          SIGTTOU: 后台进程尝试向终端写入
//      信号处理策略
//          SIG_DFL: 默认处理
//          SIG_IGN: 忽略信号
// 函数
//      void (*signal( int sig, void (*handler) (int))) (int);
//          handler:
//              void fun(int sig);
//      int raise( int sig );