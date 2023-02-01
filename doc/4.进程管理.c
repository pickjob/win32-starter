/**
 * 基础知识:
 *      Process: 进程, 资源容器
 * 进程管理:
 *      启动进程:
 *          CreateProcess(
 *              [in, optional]      LPTSTR                lpApplicationName,
 *              [in, out, optional] LPTSTR                lpCommandLine,
 *              [in, optional]      LPSECURITY_ATTRIBUTES lpProcessAttributes,
 *              [in, optional]      LPSECURITY_ATTRIBUTES lpThreadAttributes,
 *              [in]                BOOL                  bInheritHandles,
 *              [in]                DWORD                 dwCreationFlags,
 *              [in, optional]      LPVOID                lpEnvironment,
 *              [in, optional]      LPTSTR                lpCurrentDirectory,
 *              [in]                LPSTARTUPINFOW        lpStartupInfo,
 *              [out]               LPPROCESS_INFORMATION lpProcessInformation
 *          ): BOOL
 *          ShellExecute(
 *              [in, optional] HWND   hwnd,
 *              [in, optional] LPTSTR lpOperation,
 *              [in]           LPTSTR lpFile,
 *              [in, optional] LPTSTR lpParameters,
 *              [in, optional] LPTSTR lpDirectory,
 *              [in]           INT    nShowCmd
 *          ): HINSTANCE
 *              lpOperation:
 *                  explore
 *                  open
 *                  runas: UAC 运行
 *              nShowCmd:
 *                  SW_SHOWNORMAL
 *          ShellExecuteEx(
 *              [in, out] SHELLEXECUTEINFO *pExecInfo
 *          ): BOOL
 *      进程获得:
 *          OpenProcess(
 *              [in] DWORD dwDesiredAccess,
 *              [in] BOOL  bInheritHandle,
 *              [in] DWORD dwProcessId
 *          ): HANDLE 打开进程
 *              dwDesiredAccess:
 *                  PROCESS_ALL_ACCESS
 *                  PROCESS_QUERY_INFORMATION: 查询进程信息
 *                  PROCESS_VM_OPERATION PROCESS_VM_READ PROCESS_VM_WRITE: 进程内存管理
 *                  PROCESS_TERMINATE PROCESS_CREATE_PROCESS、PROCESS_CREATE_THREAD: 进程管理
 *      进程基本信息:
 *          当前进程ID、句柄:
 *              GetCurrentProcess(): HANDLE
 *              GetProcessId(
 *                  [in] HANDLE Process
 *              ): DWORD
 *              GetCurrentProcessId(): DWORD              
 *          环境变量:
 *              GetEnvironmentVariable(
 *                  [in, optional]  LPCTSTR lpName,
 *                  [out, optional] LPWSTR  lpBuffer,
 *                  [in]            DWORD   nSize
 *              ): DWORD
 *                  nSize: 缓冲区字符数, 包括NULL
 *                  返回: 成功返回字符数, 不包括NULL, 失败返回0
 *              SetEnvironmentVariable(
 *                  [in]           LPCTSTR lpName,
 *                  [in, optional] LPCTSTR lpValue
 *              ): BOOL
 *          当前目录:
 *              GetCurrentDirectory(
 *                  [in]  DWORD  nBufferLength,
 *                  [out] LPTSTR lpBuffer
 *              ): DWORD
 *                  nBufferLength: 缓冲区字符数, 包括NULL
 *                  返回: 成功返回字符数, 不包括NULL, 失败返回0
 *              SetCurrentDirectory(
 *                  [in] LPCTSTR lpPathName
 *              ): BOOL
 *          镜像路径:
 *              QueryFullProcessImageName(
 *                  [in]      HANDLE hProcess,
 *                  [in]      DWORD  dwFlags,
 *                  [out]     LPTSTR  lpExeName,
 *                  [in, out] PDWORD lpdwSize
 *              ): BOOL
 *          退出代码:
 *              GetExitCodeProcess(
 *                  [in]  HANDLE  hProcess,
 *                  [out] LPDWORD lpExitCode
 *              ): BOOL
 *      进程结束: 
 *          ExitProcess(
 *              [in] UINT uExitCode
 *          ): void
 *          TerminateProcess(
 *              [in] HANDLE hProcess,
 *              [in] UINT   uExitCode
 *          ): BOOL
 **/
