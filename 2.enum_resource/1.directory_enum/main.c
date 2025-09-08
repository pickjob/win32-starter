#include "main.h"

#include <stdlib.h>

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    TCHAR           szDirectoryName[] = _T("./*");
    WIN32_FIND_DATA ffd               = {};
    HANDLE          hFind             = FindFirstFile(szDirectoryName, &ffd);
    if (INVALID_HANDLE_VALUE == hFind) {
        ShowLastError(_T("FindFirstFile"));
        return EXIT_FAILURE;
    }
    do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            log_info(_T("目录: %s"), ffd.cFileName);
        } else {
            log_info(_T("文件: %s"), ffd.cFileName);
        }
    } while (FindNextFile(hFind, &ffd));
    if (ERROR_NO_MORE_FILES != GetLastError()) {
        ShowLastError(_T("FindNextFile"));
    }
    FindClose(hFind);
    return EXIT_SUCCESS;
}