// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <tchar.h>

#include "utils/common.h"
#include "utils/log.h"
// clang-format on

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;
    if (log_init() != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    TCHAR           szDirectoryName[] = _T("./*");
    WIN32_FIND_DATA ffd               = {0};
    HANDLE          hFind             = FindFirstFile(szDirectoryName, &ffd);
    if (INVALID_HANDLE_VALUE == hFind) {
        LOG_LAST_ERROR("FindFirstFile");
        return EXIT_FAILURE;
    }
    do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            LOG_INFO("目录: %s", utf16_to_utf8(ffd.cFileName));
        } else {
            LOG_INFO("文件: %s", utf16_to_utf8(ffd.cFileName));
        }
    } while (FindNextFile(hFind, &ffd));
    if (ERROR_NO_MORE_FILES != GetLastError()) {
        LOG_LAST_ERROR("FindNextFile");
    }
    FindClose(hFind);
    return EXIT_SUCCESS;
}