//
// 头文件
//      <string.h>
// 函数
//      memset_s: 以字符填充缓冲区
//      memcpy_s: 复制缓冲区到另一个
//      memccpy: 复制缓冲区到另一个，在指定的分隔符后停止
//      memmove_s: 移动缓冲区到另一个
//
//      wctomb_s: 转换宽字符为多字节表示
//      wcstombs_s: 转换宽字符串为窄多字节字符串
//      mbstowcs_s: 转换窄多字节字符串为宽字符串
//
//      复制:
//          char*   strcpy   (char* dest, const char* src);
//          errno_t strcpy_s (char* dest, size_t destsz, const char* src);
//
//          char*   strncpy  (char* dest, const char* src, size_t count);
//          errno_t strncpy_s(char* dest, size_t destsz, const char* src, size_t count);
//      连接:
//          char*   strcat   (char* dest, const char* src);
//          errno_t strcat_s (char* dest, size_t destsz, const char* src);
//
//          char*   strncat  (char* dest, const char* src, size_t count);
//          errno_t strncat_s(char* dest, size_t destsz, const char* src, size_t count);
//      比较:
//          int     strcmp   (char* lhs, char* rhs);
//          int     strncmp  (char* lhs, char* rhs, size_t count);
//      字符位置(第一次/最后一次):
//          char*   strchr   (char* str, int ch);
//          char*   strrchr  (char* str, int ch);
//      字符串位置:
//          char*   strstr   (char* str, char* substr);
//      长度:
//          size_t  strlen   (char* str);
//          size_t  strnlen  (char* str, size_t maxsize);
//      内存操作:
//          void*   memset   (void* dest, int ch, size_t count);
//          errno_t memset_s (void *dest, size_t destsz, int ch, size_t count);
//          void*   memcpy   (void* dest, const void* src, size_t count);
//          errno_t memcpy_s (void* dest, size_t destsz, const void* src, size_t count);
//          int     memcmp   (void* lhs, void* rhs, size_t count);
//          void*   memchr   (void* ptr, int ch, size_t count);
//          void*   memmove  (void* dest, const void* src, size_t count);
//          errno_t memmove_s(void* dest, size_t destsz, void* src, size_t count);
//
//      函数说明:
//          strnXX, 指定操作长度
//          strXX_s, 指定目标缓冲区大小
//
//          dest: 目标缓冲区
//          src:  源缓冲区
//          ch:   操作字符
//          destsz: 写入的最大字节数
//          errno_t:
//              成功时返回零
//              失败时返回非零