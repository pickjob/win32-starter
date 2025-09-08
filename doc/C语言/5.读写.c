//
// 头文件
//      <stdio.h> <wchar.h>
// 类型(stdio.h)
//      FILE: 对象类型，能够保存控制 C I/O 流所需的全部信息
//      fpos_t: 非数组完整对象类型，足以唯一指定文件的位置和多字节解析状态
// 预定义标准流(stdio.h)
//      stdin: 与标准输入流关联的 FILE* 类型表达式
//      stdout: 与标准输出流关联的 FILE* 类型表达式
//      stderr: 与标准错误输出流关联的 FILE* 类型表达式
// 宏(stdio.h)
//      EOF: int 类型的负数整数常量表达式
//      FOPEN_MAX: 能同时打开的最大文件数
//      FILENAME_MAX: 保有最长受支持文件名所需的 char 数组大小
//      BUFSIZ: setbuf 所用的缓冲区大小
//      SEEK_SET / SEEK_CUR / SEEK_END: 指示从文件首开始 / 当前 / 文件尾 寻位的 fseek 参数
// 函数
//      文件访问(stdio.h)
//          fopen / fopen_s: 打开文件
//          fflush: 将输出流与实际文件同步
//          fclose: 关闭文件
//          setbuf / setvbuf: 为文件流设置缓冲区
//          fwide(<wchar.h>): 将文件流在宽字符 I/O 和窄字符 I/O 间切换
//      直接输入/输出(stdio.h)
//          fread: 从文件读取
//          fwrite: 写入到文件
//      文件定位(stdio.h)
//          fgetpos: 获取文件位置指示器
//          fsetpos: 将文件位置指示器移动到文件中的指定位置
//          fseek: 将文件位置指示符移动到文件中的指定位置
//          rewind: 将文件位置指示器移动到文件首
//      错误处理(stdio.h):
//          clearerr: 清除错误
//          feof: 检查文件结尾
//          ferror: 检查文件错误
//          perror: 显示对应当前错误的字符串到 stderr
//      对文件的操作(stdio.h)
//          remove: 删除文件
//          rename: 重命名文件
//          tmpfile tmpfile_s: 返回指向临时文件的指针
//          tmpnam tmpnam_s: 返回唯一的文件名
//      有格式输入/输出:
//          窄字符(stdio.h)
//              scanf_s / fscanf_s: 从stdin、文件流或缓冲区读取格式化输入
//              printf_s / fprintf_s: 打印格式化输出到 stdout、文件流或缓冲区
//          宽字符(wchar.h)
//              wscanf_s / fwscanf_s: 从stdin、文件流或缓冲区读取格式化输入
//              wprintf_s / fwprintf_s: 打印格式化输出到 stdout、文件流或缓冲区
//          格式(%起始):
//              s: 字符串
//              d: 十进制数字整数
//              x / X： 小写 / 大写 十六进制整数