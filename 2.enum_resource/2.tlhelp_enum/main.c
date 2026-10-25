// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <tlhelp32.h>

#include "utils/common.h"
#include "utils/log.h"
// clang-format on

// 线程池和TLS示例
BOOL         EnumProcess();
BOOL         EnumProcessModules(DWORD dwPID);
BOOL         EnumProcessThreads(DWORD dwOwnerPID);

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
    EnumProcess();
    return EXIT_SUCCESS;
}

BOOL EnumProcess() {
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    if (INVALID_HANDLE_VALUE == hProcessSnap) {
        LOG_LAST_ERROR("CreateToolhelp32Snapshot");
        return EXIT_FAILURE;
    }
    PROCESSENTRY32 pe32 = {};
    pe32.dwSize         = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        LOG_LAST_ERROR("Process32First"); // show cause of failure
        CloseHandle(hProcessSnap);        // clean the snapshot object
        return EXIT_FAILURE;
    }
    do {
        LOG_INFO("=====================================================");
        LOG_INFO("PROCESS NAME:  %s", utf16_to_utf8(pe32.szExeFile));
        LOG_INFO("-------------------------------------------------------");
        LOG_INFO("  Process ID        = 0x%08X", pe32.th32ProcessID);
        LOG_INFO("  Thread count      = %d", pe32.cntThreads);
        LOG_INFO("  Parent process ID = 0x%08X", pe32.th32ParentProcessID);
        LOG_INFO("  Priority base     = %d", pe32.pcPriClassBase);
        EnumProcessModules(pe32.th32ProcessID);
        EnumProcessThreads(pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return EXIT_SUCCESS;
}

BOOL EnumProcessModules(DWORD dwPID) {
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (INVALID_HANDLE_VALUE == hModuleSnap) {
        LOG_LAST_ERROR("CreateToolhelp32Snapshot");
        return EXIT_FAILURE;
    }
    MODULEENTRY32 me32 = {};
    me32.dwSize        = sizeof(MODULEENTRY32);
    if (!Module32First(hModuleSnap, &me32)) {
        LOG_LAST_ERROR("Module32First");
        CloseHandle(hModuleSnap);
        return EXIT_FAILURE;
    }
    do {
        LOG_INFO("     MODULE NAME:     %s", utf16_to_utf8(me32.szModule));
        LOG_INFO("     Executable     = %s", utf16_to_utf8(me32.szExePath));
        LOG_INFO("     Process ID     = 0x%08X", me32.th32ProcessID);
        LOG_INFO("     Ref count (g)  = 0x%04X", me32.GlblcntUsage);
        LOG_INFO("     Ref count (p)  = 0x%04X", me32.ProccntUsage);
        LOG_INFO("     Base address   = %p", (void *)me32.modBaseAddr);
        LOG_INFO("     Base size      = %u", (unsigned)me32.modBaseSize);
    } while (Module32Next(hModuleSnap, &me32));
    CloseHandle(hModuleSnap);
    return EXIT_SUCCESS;
}

BOOL EnumProcessThreads(DWORD dwOwnerPID) {
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        LOG_LAST_ERROR("CreateToolhelp32Snapshot");
        return EXIT_FAILURE;
    }
    THREADENTRY32 te32 = {};
    te32.dwSize        = sizeof(THREADENTRY32);
    if (!Thread32First(hThreadSnap, &te32)) {
        LOG_LAST_ERROR("Thread32First");
        CloseHandle(hThreadSnap);
        return EXIT_FAILURE;
    }
    do {
        if (te32.th32OwnerProcessID == dwOwnerPID) {
            LOG_INFO("     THREAD ID      = 0x%08X", te32.th32ThreadID);
            LOG_INFO("     Base priority  = %d", te32.tpBasePri);
            LOG_INFO("     Delta priority = %d", te32.tpDeltaPri);
        }
    } while (Thread32Next(hThreadSnap, &te32));
    CloseHandle(hThreadSnap);
    return EXIT_SUCCESS;
}