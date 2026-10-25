#include "utils/log.h"

#include "utils/common.h"

// clang-format off
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
// clang-format on

#define LOG_BUF_SIZE 4096

static const char *const g_filepath    = "app.log";
static const char       *g_level_str[] = {"DEBUG", "INFO", "WARN", "ERROR"};

static FILE             *g_file        = NULL;
static CRITICAL_SECTION  g_lock;

static INIT_ONCE         g_once = INIT_ONCE_STATIC_INIT;
static BOOL CALLBACK     lock_init_once(PINIT_ONCE o, PVOID p, PVOID *ctx) {
    (void)o;
    (void)p;
    (void)ctx;
    InitializeCriticalSection(&g_lock);
    // 设置控制台输出代码页为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    return TRUE;
}
int log_init(void) {
    InitOnceExecuteOnce(&g_once, lock_init_once, NULL, NULL);

    if (g_filepath && g_filepath[0]) {
        wchar_t *u16FilePath = utf8_to_utf16(g_filepath);
        if (!u16FilePath) {
            return EXIT_FAILURE;
        }

        EnterCriticalSection(&g_lock);
        FILE *f = NULL;
        if (g_file) {
            fclose(g_file);
            g_file = NULL;
        }
        errno_t err = _wfopen_s(&f, u16FilePath, L"ab");
        if (u16FilePath) {
            free(u16FilePath);
        }
        g_file = (err == 0) ? f : NULL;
        if (!g_file) {
            LeaveCriticalSection(&g_lock);
            return EXIT_FAILURE;
        } else {
            LeaveCriticalSection(&g_lock);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

void log_write(log_level_t level, const char *file, int line, const char *fmt, ...) {
    InitOnceExecuteOnce(&g_once, lock_init_once, NULL, NULL);
    if (level < 0 || level > LOG_LEVEL_ERROR) {
        level = LOG_LEVEL_INFO;
    }

    // 时间
    SYSTEMTIME st;
    GetLocalTime(&st);

    // 源文件只展示名称
    const char *fname = file ? file : "";
    const char *p     = strrchr(fname, '\\');
    if (p) {
        fname = p + 1;
    }
    p = strrchr(fname, '/');
    if (p) {
        fname = p + 1;
    }

    // 内容最多到 cap-2，给结尾的 '\n' 与 '\0' 预留位置
    char   szLineBuf[LOG_BUF_SIZE];
    size_t cap = sizeof(szLineBuf);
    size_t off = 0;

    int    n   = snprintf(
        szLineBuf,
        cap,
        "[%04d-%02d-%02d %02d:%02d:%02d.%03d] [%s] %s:%d | ",
        st.wYear,
        st.wMonth,
        st.wDay,
        st.wHour,
        st.wMinute,
        st.wSecond,
        st.wMilliseconds,
        g_level_str[level],
        fname,
        line
    );
    if (n < 0) {
        return;
    }
    off = ((size_t)n < cap - 1) ? (size_t)n : cap - 2;

    if (off < cap - 1) {
        va_list ap;
        va_start(ap, fmt);
        int m = vsnprintf(szLineBuf + off, cap - off, fmt, ap);
        va_end(ap);
        if (m > 0) {
            off += (size_t)m;
            if (off > cap - 2) {
                off = cap - 2;
            }
        }
    }

    // 去掉消息尾部的换行/回车（如 FormatMessage 自带 "\r\n"），再补一个换行
    while (off > 0 && (szLineBuf[off - 1] == '\r' || szLineBuf[off - 1] == '\n')) {
        off--;
    }
    szLineBuf[off++]  = '\n';
    szLineBuf[off]    = '\0';

    HANDLE hStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdHandle != NULL && hStdHandle != INVALID_HANDLE_VALUE) {
        wchar_t *u16LineBuf = utf8_to_utf16(szLineBuf);
        if (u16LineBuf) {
            DWORD   written = 0;
            size_t  nLen    = 0;
            HRESULT hResult = StringCchLength(u16LineBuf, STRSAFE_MAX_CCH, &nLen);
            if (SUCCEEDED(hResult)) {
                WriteConsoleW(hStdHandle, u16LineBuf, (DWORD)nLen, &written, NULL);
            }
            free(u16LineBuf);
        }
    }

    EnterCriticalSection(&g_lock);
    if (g_file) {
        fwrite(szLineBuf, 1, strlen(szLineBuf), g_file);
        fflush(g_file);
    }
    LeaveCriticalSection(&g_lock);
}

void log_last_error_write(log_level_t level, const char *file, int line, char *tag) {
    DWORD  dwErrorCode = GetLastError();
    LPTSTR lpErrorText = NULL;
    BOOL   fOk         = FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwErrorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpErrorText,
        0,
        NULL
    );
    if (!fOk) {
        HMODULE hLibrary = LoadLibraryEx(_T("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
        if (NULL != hLibrary) {
            fOk = FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
                hLibrary,
                dwErrorCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpErrorText,
                0,
                NULL
            );
            FreeLibrary(hLibrary);
        }
    }
    if (!fOk) {
        lpErrorText = _T("未知错误!");
    }

    char *u8ErrorInfo = utf16_to_utf8(lpErrorText);
    if (u8ErrorInfo) {
        log_write(level, file, line, "Tag: %s, LastCode:%d, Explain: %s", tag, dwErrorCode, u8ErrorInfo);
        free(u8ErrorInfo);
    }

    if (fOk) {
        LocalFree(lpErrorText);
    }
}