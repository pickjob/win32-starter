#ifndef COMMON_HEADER
#define COMMON_HEADER

// 头文件: C
#include <locale.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

// 头文件: Windows
// clang-format off
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <strsafe.h>
// clang-format on

// 宏: 宽字符转换
#define _L(x)  __L(x)
#define __L(x) L##x

// 宏: 日志宏
#define log_info(...) log_details(_L(__FILE__), __LINE__, LOG_INFO, __VA_ARGS__)

BOOL ShowLastError(LPTSTR lpTag);

enum { LOG_DEBUG, LOG_INFO, LOG_ERROR };

void log_details(
    const wchar_t *source_file,
    int            source_line,
    int            log_level,
    const wchar_t *fmt,
    ...
);

char *WideCharToMultiByteC(const wchar_t *wideStr, UINT codePage);

#endif