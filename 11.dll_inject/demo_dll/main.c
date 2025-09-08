#include "main.h"

/**
 * DllMain: 程序入口函数
 *      Date: 2025-08-01
 **/
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, _T("DLL_PROCESS_ATTACH"), _T("DLL Injection"), MB_OK);
        break;

    case DLL_THREAD_ATTACH:
        MessageBox(NULL, _T("DLL_THREAD_ATTACH"), _T("DLL Injection"), MB_OK);
        break;

    case DLL_THREAD_DETACH:
        MessageBox(NULL, _T("DLL_THREAD_DETACH"), _T("DLL Injection"), MB_OK);
        break;

    case DLL_PROCESS_DETACH:
        MessageBox(NULL, _T("DLL_PROCESS_DETACH"), _T("DLL Injection"), MB_OK);
        break;
    }
    return TRUE;
}