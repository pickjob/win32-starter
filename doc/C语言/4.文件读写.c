//
// 头文件
//      <stdio.h>
// 类型
//      FILE: 对象类型，能够保存控制 C I/O 流所需的全部信息
// 预定义标准流
//      stdin: 与标准输入流关联的 FILE* 类型表达式
//      stdout: 与标准输出流关联的 FILE* 类型表达式
//      stderr: 与标准错误输出流关联的 FILE* 类型表达式
// 宏
//      EOF: int 类型的负数整数常量表达式
//      FOPEN_MAX: 能同时打开的最大文件数
//      FILENAME_MAX: 保有最长受支持文件名所需的 char 数组大小
//      BUFSIZ: setbuf 所用的缓冲区大小
//      SEEK_SET / SEEK_CUR / SEEK_END: 指示从文件首开始 / 当前 / 文件尾 寻位的 fseek 参数
// 函数
//      打开:
//          FILE*       fopen       (char* filename, char *mode);
//          errno_t     fopen_s     (FILE* streamptr, char* filename, char *mode);
//      刷新:
//          int         fflush      (FILE* stream);
//      定位:
//          long        ftell       (FILE* stream);
//          int         fseek       (FILE* stream, long offset, int origin);
//          int         fgetpos     (FILE* stream, fpos_t* pos);
//          int         fsetpos     (FILE *stream, fpos_t* pos);
//          void        rewind      (FILE* stream);
//      读写:
//          size_t      fread       (void* buffer, size_t size, size_t count, FILE* stream);
//          size_t      fwrite      (void* buffer, size_t size, size_t count, FILE* stream);
//      错误处理:
//      关闭:
//          int         fclose      (FILE* stream);
//      文件操作:
//          int         remove      (char* pathname);
//          int         rename      (char* old_filename, char* new_filename);
//          FILE*       tmpfile     (void);
//          errno_t     tmpfile_s   (FILE* streamptr);
//      函数说明
//          filename: 文件名
//          mode: 文件访问模式
//              "r": 以只读方式打开文件，该文件必须存在
//              "w": 以只写方式打开文件，若该文件已存在，则将其长度截为 0，即该文件内容会被删除；若该文件不存在，则创建该文件
//              "a": 以追加方式打开文件，若该文件已存在，则写入的数据会被加到该文件的末尾，即该文件原有内容不会被覆盖；若该文件不存在，则创建该文件
//              "r+": 以读写方式打开文件，该文件必须存在
//              "w+": 以读写方式打开文件，若该文件已存在，则将其长度截为 0，即该文件内容会被删除；若该文件不存在，则创建该文件
//              "a+": 以读写方式打开文件，若该文件已存在，则写入的数据会被加到该文件的末尾，即该文件原有内容不会被覆盖；若该文件不存在，则创建该文件
//              "b": 以二进制方式打开文件
//              "t": 以文本方式打开文件
//          streamptr: 输出参数
//          origin: SEEK_SET / SEEK_CUR / SEEK_END
//          返回值:
//              int:
//                  成功, 返回零
//                  失败, 返回 EOF 并设置文件流的错误指示器
//              errno_t:
//                  成功, 返回零, 文件流指针写入 *streamptr
//                  错误, 返回非零 错误码