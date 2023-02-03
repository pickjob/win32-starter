#include "main.h"

/**
 * WinMain: 程序入口函数
 */
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    LPTSTR lpShowCase = _T("ShowCase Template");
    HANDLE hStdout    = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout == INVALID_HANDLE_VALUE) {
        ShowLastError(_T("GetStdHandle"), lpShowCase);
        return EXIT_FAILURE;
    }
    LPTSTR  lpGreetings      = _T("Hello World\n");
    size_t  nGreetingsLength = 0;
    HRESULT hResult          = StringCchLength(lpGreetings, STRSAFE_MAX_CCH, &nGreetingsLength);
    if (FAILED(hResult)) {
        ShowLastError(_T("StringCchLength"), lpShowCase);
        return EXIT_FAILURE;
    }
    BOOL  bWriteSuccess       = WriteConsole(hStdout, lpGreetings, nGreetingsLength, 0, NULL);
    if (!bWriteSuccess) {
        ShowLastError(_T("WriteConsole"), lpShowCase);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
