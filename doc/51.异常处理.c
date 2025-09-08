/**
 * 异常处理一些函数:
 *      ErrorCode:
 *          GetLastError / SetLastError: 当前线程的最后错误码(TLS)
 *          FormatMessage: 错误码格式化
 *              dwFlags:
 *                  FORMAT_MESSAGE_ALLOCATE_BUFFER: 函数申请足够内存存放信息, 调用者最后调用LocalFree释放
 *                  FORMAT_MESSAGE_FROM_HMODULE: 模块查找错误描述
 *                  FORMAT_MESSAGE_FROM_SYSTEM: 系统查找错误描述
 *                  FORMAT_MESSAGE_IGNORE_INSERTS: 忽略message中%1占位符
 *              dwLanguageId:
 *                  MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)
 *      SetUnhandledExceptionFilter: LPTOP_LEVEL_EXCEPTION_FILTER
 *          LPTOP_LEVEL_EXCEPTION_FILTER: 异常处理函数
 *              LONG WINAPI EXCEPTION_HANDLER([in] _EXCEPTION_POINTERS *ExceptionInfo)
 *              错误信息:
 *                  GetExceptionInformation(void): LPEXCEPTION_POINTERS
 *                      EXCEPTION_RECORD: 异常描述结构
 *                      CONTEXT: 执行上下文
 *              返回:
 *                  EXCEPTION_EXECUTE_HANDLER: 异常处理结束
 *                  EXCEPTION_CONTINUE_EXECUTION: 异常处理继续
 *                  EXCEPTION_CONTINUE_SEARCH: 异常处理继续，错误对话框
 * SEH(Structured Exception Handling): 线程相关
 *      // 清理资源, 发生异常, 先执行外部异常过滤, 再执行清理, 最后执行外部异常处理代码
 *      // 控制代码大小
 *      __try {
 *          // 受保护执行的代码
 *      } __finally {
 *          // 清理用途的代码
 *      }
 *      // 异常过滤, 优先执行受保护代码, 异常发生, 执行过滤表达式, 根据执行结果决定后续过程
 *      __try {
 *          // 受保护执行的代码
 *      } __except (过滤表达式) {
 *          // 异常处理代码
 *      }
 *          过滤表达式:
 *              EXCEPTIION_EXECUTE_HANDLER: 执行异常处理代码
 *              EXECEPTION_CONTINUE_SEARCH: 操作系统查找其他异常处理代码
 *              EXCEEPTION_CONTINUE_EXECUTION: 不处理, 受保护代码继续执行
 *              辅助判断函数:
 *                  GetExceptionCode(): DWORD 获得异常码
 *                  GetExceptionInformation(): LPEXCEPTION_POINTERS
 *                      EXCEPTION_RECORD: 异常描述结构
 *                      CONTEXT: 执行上下文
 *      __leave
 **/