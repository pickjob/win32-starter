// 标准 头文件
#include <stdio.h>

// Windows 头文件
// clang-format off
#include <windows.h>
#include <windowsx.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <strsafe.h>
// clang-format on

// 自定义库 头文件
#include "utils/common.h"

// 线程池和TLS示例
BOOL EnumProcess();
BOOL EnumProcessModules(DWORD dwPID);
BOOL EnumProcessThreads(DWORD dwOwnerPID);