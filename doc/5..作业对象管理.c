/**
 * 基础知识:
 *      Job Object: 作业对象, 限制进程资源使用的进程集合
 * 作业管理:
 *      CreateJobObject(
 *          [in, optional] LPSECURITY_ATTRIBUTES lpJobAttributes,
 *          [in, optional] LPTSTR                lpName
 *      ): HANDLE 创建Job对象
 *      AssignProcessToJobObject(
 *          [in] HANDLE hJob,
 *          [in] HANDLE hProcess
 *      ): BOOL 绑定 进程 和 Job
 *      OpenJobObject(
 *          [in] DWORD  dwDesiredAccess,
 *          [in] BOOL   bInheritHandle,
 *          [in] LPCSTR lpName
 *      ): HANDLE 打开 Job
 *      IsProcessInJob(
 *          [in]           HANDLE ProcessHandle,
 *          [in, optional] HANDLE JobHandle,
 *          [out]          PBOOL  Result
 *      ): BOOL 判断进程是否在 Job 中
 *      SetInformationJobObject(
 *          [in] HANDLE             hJob,
 *          [in] JOBOBJECTINFOCLASS JobObjectInformationClass,
 *          [in] LPVOID             lpJobObjectInformation,
 *          [in] DWORD              cbJobObjectInformationLength
 *      ): BOOL 限制Job资源
 *          JobObjectInformationClass
 *              JobObjectBasicLimitInformation: 基本资源: 内存、时间片段
 *              ...
 *      QueryInformationJobObject(
 *          [in, optional]  HANDLE             hJob,
 *          [in]            JOBOBJECTINFOCLASS JobObjectInformationClass,
 *          [out]           LPVOID             lpJobObjectInformation,
 *          [in]            DWORD              cbJobObjectInformationLength,
 *          [out, optional] LPDWORD            lpReturnLength
 *      ): BOOL 查询 Job 信息
 *      TerminateJobObject(
 *          [in] HANDLE hJob,
 *          [in] UINT   uExitCode
 *      ): BOOL 结束Job关联进程
 **/
