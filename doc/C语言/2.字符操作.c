//
// 头文件
//      <string.h> <wchar.h> <stdlib.h>
// 函数
//      strcpy_s / wcscpy_s: 复制字符串给另一个
//      strncpy_s / wcsncpy_s: 从字符串复制一定数量的字符到另一个
//      strcat_s / wcscat_s: 连接两个字符串
//      strncat_s / wcsncat_s: 连接两个字符串的一定数量字符
//      strnlen_s / wcsnlen_s: 返回给定字符串的长度
//      strcmp / wcscmp: 比较两个字符串
//      strncmp / wcsncmp: 比较两个字符串的一定数量字符
//      sprintf_s / swprintf_s: 格式化字符串
//
//      memset_s: 以字符填充缓冲区
//      memcpy_s: 复制缓冲区到另一个
//      memccpy: 复制缓冲区到另一个，在指定的分隔符后停止
//      memmove_s: 移动缓冲区到另一个
//
//      wctomb_s: 转换宽字符为多字节表示
//      wcstombs_s: 转换宽字符串为窄多字节字符串
//      mbstowcs_s: 转换窄多字节字符串为宽字符串