#include "main.h"

/**
 * WinMain: 程序入口函数
 */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpShowCase = _T("IO ShowCase");
    // Write File
    LPTSTR lpData     = _T("Hello World!\n你好，世界！\n");
    HANDLE hFile      = CreateFile(_T("io_show_case.txt"),    // 文件名
                              GENERIC_WRITE,             // 读写模式
                              0,                         // 分享模式
                              NULL,                      // 安全
                              CREATE_NEW,                // 文件操作
                              FILE_ATTRIBUTE_NORMAL,     // 文件属性
                              NULL);                     // 其他

    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD dwErrorCode = GetLastError();
        if (ERROR_FILE_EXISTS == dwErrorCode) {
            hFile = CreateFile(_T("io_show_case.txt"),             // 文件名
                               GENERIC_WRITE,                      // 读写模式
                               0,                                  // 分享模式
                               NULL,                               // 安全
                               OPEN_ALWAYS | TRUNCATE_EXISTING,    // 文件操作
                               FILE_ATTRIBUTE_NORMAL,              // 文件属性
                               NULL);                              // 其他
            if (hFile == INVALID_HANDLE_VALUE) {
                ShowLastError(_T("CreateFile"), lpShowCase);
                return EXIT_FAILURE;
            }
        } else {
            ShowLastError(_T("CreateFile"), lpShowCase);
            return EXIT_FAILURE;
        }
    }
    int    nMultiBytes  = WideCharToMultiByte(CP_UTF8, 0, lpData, -1, NULL, 0, NULL, NULL);
    HANDLE hProcessHeap = GetProcessHeap();
    LPVOID cbMultiBytes = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, nMultiBytes);
    if (NULL == cbMultiBytes) {
        ShowLastError(_T("HeapAlloc"), lpShowCase);
        return EXIT_FAILURE;
    }
    WideCharToMultiByte(CP_UTF8, 0, lpData, -1, cbMultiBytes, nMultiBytes, NULL, NULL);
    DWORD dwByteWriten = 0;
    BOOL  bErrorFlag   = WriteFile(hFile, cbMultiBytes, nMultiBytes - 1, &dwByteWriten, NULL);
    if (!HeapFree(hProcessHeap, 0, cbMultiBytes)) {
        ShowLastError(_T("HeapFree"), lpShowCase);
        return EXIT_FAILURE;
    }
    CloseHandle(hFile);
    hFile = CreateFile(_T("io_show_case.txt"),    // 文件名
                       GENERIC_READ,              // 读写模式
                       0,                         // 分享模式
                       NULL,                      // 安全
                       OPEN_ALWAYS,               // 文件操作
                       FILE_ATTRIBUTE_NORMAL,     // 文件属性
                       NULL);                     // 其他
    if (hFile == INVALID_HANDLE_VALUE) {
        ShowLastError(_T("CreateFile"), lpShowCase);
        return EXIT_FAILURE;
    }
    DWORD dwFileSize = GetFileSize(hFile, NULL);
    if (INVALID_FILE_SIZE == dwByteWriten) {
        ShowLastError(_T("HeapFree"), lpShowCase);
        return EXIT_FAILURE;
    }
    cbMultiBytes = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, dwFileSize + 1);
    if (NULL == cbMultiBytes) {
        ShowLastError(_T("HeapAlloc"), lpShowCase);
        return EXIT_FAILURE;
    }
    DWORD dwByteReaded = 0;
    if (FALSE == ReadFile(hFile, cbMultiBytes, dwFileSize - 1, &dwByteReaded, NULL)) {
        ShowLastError(_T("HeapAlloc"), lpShowCase);
        return EXIT_FAILURE;
    }
    int    nWideChar   = MultiByteToWideChar(CP_UTF8, 0, cbMultiBytes, -1, NULL, 0);
    LPVOID cbWideChars = HeapAlloc(hProcessHeap, HEAP_ZERO_MEMORY, (nWideChar + 1) * 2);
    if (NULL == cbMultiBytes) {
        ShowLastError(_T("HeapAlloc"), lpShowCase);
        return EXIT_FAILURE;
    }
    MultiByteToWideChar(CP_UTF8, 0, cbMultiBytes, -1, cbWideChars, nWideChar);
    CloseHandle(hFile);
    HANDLE hStdout     = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) {
        ShowLastError(_T("GetStdHandle"), lpShowCase);
        return EXIT_FAILURE;
    };
    LPTSTR lpContent = (LPTSTR) cbWideChars;
    size_t  nGreetingsLength = 0;
    HRESULT hResult          = StringCchLength(lpContent, STRSAFE_MAX_CCH, &nGreetingsLength);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return EXIT_FAILURE;
    }
    BOOL bWriteSuccess = WriteConsole(hStdout, lpContent, nGreetingsLength, 0, NULL);
    if (!bWriteSuccess) {
        ShowLastError(_T("WriteConsole"), lpShowCase);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
