#include "main.h"

#include "utils/common.h"

#include <stdlib.h>

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    EnumProcess();
    return EXIT_SUCCESS;
}

BOOL EnumProcess() {
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) {
        ShowLastError(_T("CreateToolhelp32Snapshot"));
        return EXIT_FAILURE;
    }
    PROCESSENTRY32 pe32 = {};
    pe32.dwSize         = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        ShowLastError(_T("Process32First")); // show cause of failure
        CloseHandle(hProcessSnap);           // clean the snapshot object
        return EXIT_FAILURE;
    }
    do {
        log_info(_T("====================================================="));
        log_info(_T("PROCESS NAME:  %s"), pe32.szExeFile);
        log_info(_T("-------------------------------------------------------"));
        log_info(_T("  Process ID        = 0x%08X"), pe32.th32ProcessID);
        log_info(_T("  Thread count      = %d"), pe32.cntThreads);
        log_info(_T("  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
        log_info(_T("  Priority base     = %d"), pe32.pcPriClassBase);
        EnumProcessModules(pe32.th32ProcessID);
        EnumProcessThreads(pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return EXIT_SUCCESS;
}

BOOL EnumProcessModules(DWORD dwPID) {
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (INVALID_HANDLE_VALUE == hModuleSnap) {
        ShowLastError(_T("CreateToolhelp32Snapshot"));
        return EXIT_FAILURE;
    }
    MODULEENTRY32 me32 = {};
    me32.dwSize        = sizeof(MODULEENTRY32);
    if (!Module32First(hModuleSnap, &me32)) {
        ShowLastError(_T("Module32First"));
        CloseHandle(hModuleSnap);
        return EXIT_FAILURE;
    }
    do {
        log_info(_T("     MODULE NAME:     %s"), me32.szModule);
        log_info(_T("     Executable     = %s"), me32.szExePath);
        log_info(_T("     Process ID     = 0x%08X"), me32.th32ProcessID);
        log_info(_T("     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
        log_info(_T("     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
        log_info(_T("     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        log_info(_T("     Base size      = %d"), me32.modBaseSize);
    } while (Module32Next(hModuleSnap, &me32));
    CloseHandle(hModuleSnap);
    return EXIT_SUCCESS;
}

BOOL EnumProcessThreads(DWORD dwOwnerPID) {
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        ShowLastError(_T("CreateToolhelp32Snapshot"));
        return EXIT_FAILURE;
    }
    THREADENTRY32 te32 = {};
    te32.dwSize        = sizeof(THREADENTRY32);
    if (!Thread32First(hThreadSnap, &te32)) {
        ShowLastError(_T("Thread32First"));
        CloseHandle(hThreadSnap);
        return EXIT_FAILURE;
    }
    do {
        if (te32.th32OwnerProcessID == dwOwnerPID) {
            log_info(_T("     THREAD ID      = 0x%08X"), te32.th32ThreadID);
            log_info(_T("     Base priority  = %d"), te32.tpBasePri);
            log_info(_T("     Delta priority = %d"), te32.tpDeltaPri);
        }
    } while (Thread32Next(hThreadSnap, &te32));
    CloseHandle(hThreadSnap);
    return EXIT_SUCCESS;
}