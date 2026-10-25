//
// 头文件
//      <stdio.h>
// 函数
//      int     printf      (char* format, ...);
//      int     printf_s    (char* format, ...);
//      int     fprintf     (FILE* stream, char* format, ... );
//      int     fprintf_s   (FILE* stream, char* format, ... );
//      int     sprintf     (char* buffer, char* format, ... );
//      int     sprintf_s   (char* buffer, size_t bufsz, char* format, ... );
//      int     snprintf    (char* buffer, size_t bufsz, char* format, ... );
//      int     snprintf_s  (char* buffer, rsize_t bufsz, const char* format, ... );
//
//      int     vprintf     (char* format, va_list vlist);
//      int     vprintf_s   (char* format, va_list vlist);
//      int     vfprintf    (FILE* stream, char* format, va_list vlist);
//      int     vfprintf_s  (FILE* stream, char* format, va_list vlist);
//      int     vsprintf    (char* buffer, char *format, va_list vlist);
//      int     vsprintf_s  (char* buffer, size_t bufsz, char* format, va_list vlist);
//      int     vsnprintf   (char* buffer, size_t bufsz, char* format, va_list vlist);
//      int     vsnprintf_s (char* buffer, size_t bufsz, char* format, va_list vlist);
//
//      函数说明:
//          fXX: 写入文件流
//          sXX: 写入内存缓冲区
//          vXX: 支持可变参数格式化
//          XX_s: 边界校验
//
//          stream: 文件流
//          buffer: 内存缓冲区
//          bufsz: 最多写入的字符数
//          format: 格式(%起始):
//              s: 字符串
//              d: 十进制数字整数
//              x / X： 小写 / 大写 十六进制整数
//          返回值:
//              成功: 写入的字节数(有bufsz, 则为实际应该写入的字节数)
//              失败: 负数