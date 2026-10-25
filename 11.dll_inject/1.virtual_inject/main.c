// clang-format off
#include <stdlib.h>

#include <windows.h>
#include <windowsx.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/common.h"
#include "utils/log.h"
// clang-format on

// 目标进程内调用的加载函数：须与写入的内存字符串编码一致（TCHAR => UNICODE 用 W）
#ifdef UNICODE
#define LOADLIBRARY_NAME "LoadLibraryW"
#else
#define LOADLIBRARY_NAME "LoadLibraryA"
#endif

// 按进程名查找进程 ID（未找到返回 0）
DWORD        FindProcessIdByName(LPCTSTR lpName);

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
    // 查询 notepad.exe 的进程 ID
    DWORD dwProcessId = FindProcessIdByName(_T("notepad.exe"));
    if (0 == dwProcessId) {
        LOG_ERROR("未找到 notepad.exe 进程");
        return EXIT_FAILURE;
    }
    LOG_INFO("notepad.exe PID = %lu", (unsigned long)dwProcessId);

    // 取与本模块同目录下的 demo_dll.dll 的绝对路径。
    // LoadLibraryW 在目标进程中执行，相对路径会按"目标进程"的目录解析，
    // 因此必须写入绝对路径，否则加载失败（错误码 126）。
    TCHAR  szDllPath[MAX_PATH] = {0};
    DWORD  dwPathLen           = GetModuleFileName(NULL, szDllPath, MAX_PATH);
    if (0 == dwPathLen || dwPathLen >= MAX_PATH) {
        LOG_LAST_ERROR("GetModuleFileName");
        return EXIT_FAILURE;
    }
    PTCHAR pLastSlash = _tcsrchr(szDllPath, _T('\\'));
    if (NULL == pLastSlash) {
        LOG_ERROR("解析可执行文件路径失败");
        return EXIT_FAILURE;
    }
    *(pLastSlash + 1) = _T('\0');
    if (FAILED(StringCchCat(szDllPath, MAX_PATH, _T("demo_dll.dll")))) {
        LOG_ERROR("拼接 DLL 路径失败");
        return EXIT_FAILURE;
    }

    // 打开注入进程，获取进程句柄
    HANDLE hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwProcessId);
    if (NULL == hRemoteProcess) {
        LOG_LAST_ERROR("OpenProcess");
        return EXIT_FAILURE;
    }

    SIZE_T  nDllPathLength = 0;
    LPTSTR  lpDllPath      = szDllPath;
    HRESULT hResult        = StringCchLength(lpDllPath, STRSAFE_MAX_CCH, &nDllPathLength);
    if (FAILED(hResult)) {
        CloseHandle(hRemoteProcess);
        return EXIT_FAILURE;
    }
    // 提交一段新内存需要同时声明 MEM_COMMIT | MEM_RESERVE
    LPVOID lpRemoteAddr = VirtualAllocEx(hRemoteProcess, NULL, (nDllPathLength + 1) * sizeof(TCHAR), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (NULL == lpRemoteAddr) {
        LOG_LAST_ERROR("VirtualAllocEx");
        CloseHandle(hRemoteProcess);
        return EXIT_FAILURE;
    }
    if (!WriteProcessMemory(hRemoteProcess, lpRemoteAddr, lpDllPath, (nDllPathLength + 1) * sizeof(TCHAR), NULL)) {
        LOG_LAST_ERROR("WriteProcessMemory");
        CloseHandle(hRemoteProcess);
        return EXIT_FAILURE;
    }
    HMODULE hDllKernel = GetModuleHandle(_T("kernel32.dll"));
    if (NULL == hDllKernel) {
        LOG_LAST_ERROR("GetModuleHandle");
        CloseHandle(hRemoteProcess);
        return EXIT_FAILURE;
    }
    FARPROC lpFunLoadLibraryAddr = GetProcAddress(hDllKernel, LOADLIBRARY_NAME);
    if (NULL == lpFunLoadLibraryAddr) {
        LOG_LAST_ERROR("GetProcAddress");
        CloseHandle(hRemoteProcess);
        return EXIT_FAILURE;
    }
    HANDLE hRemoteThread = CreateRemoteThread(hRemoteProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpFunLoadLibraryAddr, lpRemoteAddr, 0, NULL);
    if (NULL == hRemoteThread) {
        LOG_LAST_ERROR("CreateRemoteThread");
        CloseHandle(hRemoteProcess);
        return EXIT_FAILURE;
    }
    LOG_INFO("已向 PID=%lu 注入: %ls", (unsigned long)dwProcessId, szDllPath);

    // 等待远端线程结束后回收资源（此处的内存将在目标进程退出时自动释放）
    WaitForSingleObject(hRemoteThread, INFINITE);
    CloseHandle(hRemoteThread);
    CloseHandle(hRemoteProcess);
    return EXIT_SUCCESS;
}

// 按进程名查找进程 ID（未找到返回 0）
DWORD FindProcessIdByName(LPCTSTR lpName) {
    DWORD  dwPid = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnap) {
        return 0;
    }
    PROCESSENTRY32 pe32 = {0};
    pe32.dwSize         = sizeof(pe32);
    if (Process32First(hSnap, &pe32)) {
        do {
            if (0 == _tcsicmp(pe32.szExeFile, lpName)) {
                dwPid = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hSnap, &pe32));
    }
    CloseHandle(hSnap);
    return dwPid;
}