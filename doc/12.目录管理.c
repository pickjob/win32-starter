/**
 * 目录基本操作:
 *      CreateDirectory(
 *          [in]           LPCTSTR               lpPathName,
 *          [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes
 *      ): BOOL 创建目录
 *      CreateDirectoryEx(
 *          [in]           LPTSTR                lpTemplateDirectory,
 *          [in]           LPTSTR                lpNewDirectory,
 *          [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes
 *      ): BOOL 创建目录
 *      MoveFileEx(
 *          [in]           LPTSTR lpExistingFileName,
 *          [in, optional] LPTSTR lpNewFileName,
 *          [in]           DWORD  dwFlags
 *      ): BOOL 移动目录
 *      MoveFileWithProgress(
 *          [in]           LPTSTR             lpExistingFileName,
 *          [in, optional] LPTSTR             lpNewFileName,
 *          [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
 *          [in, optional] LPVOID             lpData,
 *          [in]           DWORD              dwFlags
 *      ): BOOL 移动目录
 *          dwFlags:
 *              MOVEFILE_COPY_ALLOWED
 *              MOVEFILE_DELAY_UNTIL_REBOOT
 *              MOVEFILE_FAIL_IF_NOT_TRACKABLE
 *              MOVEFILE_REPLACE_EXISTING
 *              MOVEFILE_WRITE_THROUGH
 *      RemoveDirectory(
 *          [in] LPCTSTR lpPathName
 *      ): BOOL 删除目录
 *      SetCurrentDirectory(
 *          [in] LPCTSTR lpPathName
 *      ): BOOL 设置当前目录
 *      GetCurrentDirectory(
 *          [in]  DWORD  nBufferLength,
 *          [out] LPTSTR lpBuffer
 *      ): DWORD 获得当前目录
 *      UINT GetWindowsDirectory(
 *          [out] LPCTSTR lpBuffer,
 *          [in]  UINT  uSize
 *      ): UINT 获得Windows目录路径(C:\Windows)
 *      GetSystemDirectory(
 *          [out] LPCTSTR lpBuffer,
 *          [in]  UINT  uSize
 *      ): UINT 获得系统目录路径(C:\Windows\System32)
 **/
