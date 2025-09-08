#include "utils/common.h"

// 展示最后操作错误
BOOL ShowLastError(LPTSTR lpTag) {
    DWORD dwErrorCode = GetLastError();
    if (EXIT_SUCCESS == dwErrorCode) {
        return FALSE;
    }
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

    size_t  nLength       = 0;
    size_t  nTotalLength  = 0;
    HRESULT hResult       = StringCchLength(lpErrorText, STRSAFE_MAX_CCH, &nLength);
    nTotalLength         += nLength;
    TCHAR szErrorInfo[nTotalLength + 64];
    hResult = StringCchPrintf(szErrorInfo, _countof(szErrorInfo), _T("%d-%s"), dwErrorCode, lpErrorText);
    if (fOk) {
        LocalFree(lpErrorText);
    }

    MessageBox(NULL, szErrorInfo, lpTag, MB_OK);
    return TRUE;
}

static pthread_mutex_t lock = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;

void                   log_details(const wchar_t *source_file, int source_line, int log_level, const wchar_t *fmt, ...) {
    setlocale(LC_ALL, "zh_CN.UTF-8");

    time_t timeNow = {};
    time(&timeNow);
    struct tm tmNow = {};
    localtime_s(&tmNow, &timeNow);

    char szLogFileName[64];
    strftime(szLogFileName, sizeof(szLogFileName) - 1, "application-%Y%m%d.log", &tmNow);

    wchar_t szwNow[64];
    wcsftime(szwNow, sizeof(szwNow) - 1, L"%Y-%m-%d %H:%M:%S", &tmNow);

    int                   iLogMessage = 1024 + (sizeof(fmt) / 8) * 8;
    wchar_t               szwLogMessage[iLogMessage];

    static const wchar_t *level_strings[] = {L"DEBUG", L"INFO", L"ERROR"};

    swprintf(szwLogMessage, sizeof(szwLogMessage) - 1, L"%s [%s] %s:%d %s\n", &szwNow, level_strings[log_level], source_file, source_line, fmt);

    pthread_mutex_lock(&lock);

    static FILE *fileLog = NULL;

    static char  szRealLogFileName[64];
    int          iFileNameCmp = strcmp(szLogFileName, szRealLogFileName);
    if (iFileNameCmp != 0) {
        if (fileLog != NULL) {
            fclose(fileLog);
        }
        strncpy(szRealLogFileName, szLogFileName, sizeof(szRealLogFileName));
        fileLog = fopen(szLogFileName, "a+");
    }

    va_list args;
    va_start(args, fmt);
    vfwprintf_s(fileLog, szwLogMessage, args);
    va_end(args);
    fflush(fileLog);

    pthread_mutex_unlock(&lock);
}

char *WideCharToMultiByteC(const wchar_t *wideStr, UINT codePage) {
    if (NULL == wideStr) {
        return NULL;
    }
    // 第一步：获取所需的多字节缓冲区大小
    int bufferSize = WideCharToMultiByte(
        codePage, // 目标编码页
        0,        // 转换标志
        wideStr,  // 输入宽字符串
        -1,       // 自动计算长度（包含终止符）
        NULL,     // 输出缓冲区（先为NULL获取大小）
        0,        // 输出缓冲区大小（0表示获取所需大小）
        NULL,     // 无效字符替代符
        NULL      // 是否使用了替代符的标志
    );
    if (0 == bufferSize) {
        ShowLastError(_T("WideCharToMultiByte"));
        return NULL;
    }

    // 分配缓冲区
    char *multiStr = (char *)LocalAlloc(LPTR, bufferSize);
    if (multiStr == NULL) {
        ShowLastError(_T("LocalAlloc"));
        return NULL;
    }

    // 第二步：执行实际转换
    int result = WideCharToMultiByte(
        codePage,
        0,
        wideStr,
        -1,
        multiStr,   // 输出缓冲区
        bufferSize, // 缓冲区大小
        NULL,
        NULL
    );

    if (0 == result) {
        ShowLastError(_T("WideCharToMultiByte"));
        LocalFree(multiStr);
        return NULL;
    }
    return multiStr;
}