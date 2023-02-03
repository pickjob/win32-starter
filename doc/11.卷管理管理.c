/**
 * 基本信息:
 *      GetLogicalDrives(): DWORD 获得可用磁盘驱动器
 *          0: A
 *          1: B
 *          ...
 *      GetLogicalDriveStrings(
 *          [in]  DWORD  nBufferLength,
 *          [out] LPTSTR lpBuffer
 *      ): DWORD 获得逻辑驱动器名称
 *          lpBuffer:
 *              C:\nullD:\null
 *      GetVolumePathName(
 *          [in]  LPCWSTR lpszFileName,
 *          [out] LPWSTR  lpszVolumePathName,
 *          [in]  DWORD   cchBufferLength
 *      ): BOOL 获得l路径 卷名
 *      GetDriveType(
 *          [in, optional] LPCSTR lpRootPathName
 *      ): UINT 获得磁盘驱动器类型
 *          DRIVE_UNKNOWN
 *          DRIVE_REMOVABLE
 *          DRIVE_FIXED
 *          DRIVE_CDROM
 *          DRIVE_RAMDISK
 *      GetVolumeInformation(
 *          [in, optional]  LPCSTR  lpRootPathName,
 *          [out, optional] LPSTR   lpVolumeNameBuffer,
 *          [in]            DWORD   nVolumeNameSize,
 *          [out, optional] LPDWORD lpVolumeSerialNumber,
 *          [out, optional] LPDWORD lpMaximumComponentLength,
 *          [out, optional] LPDWORD lpFileSystemFlags,
 *          [out, optional] LPSTR   lpFileSystemNameBuffer,
 *          [in]            DWORD   nFileSystemNameSize
 *      ): BOOL 获得卷信息
 *      GetVolumeNameForVolumeMountPoint(
 *          [in]  LPCTSTR lpszVolumeMountPoint,
 *          [out] LPTSTR  lpszVolumeName,
 *          [in]  DWORD   cchBufferLength
 *      ): 获得指定卷关联的 GUID路径
 *          lpszVolumeMountPoint:
 *              X:\mountX\
 *              Y:\
 *      GetDiskFreeSpace(
 *          [in]  LPCTSTR lpRootPathName,
 *          [out] LPDWORD lpSectorsPerCluster,
 *          [out] LPDWORD lpBytesPerSector,
 *          [out] LPDWORD lpNumberOfFreeClusters,
 *          [out] LPDWORD lpTotalNumberOfClusters
 *      ): BOOL 获得磁盘空闲信息
 *      GetDiskFreeSpaceEx(
 *          [in, optional]  LPCTSTR         lpDirectoryName,
 *          [out, optional] PULARGE_INTEGER lpFreeBytesAvailableToCaller,
 *          [out, optional] PULARGE_INTEGER lpTotalNumberOfBytes,
 *          [out, optional] PULARGE_INTEGER lpTotalNumberOfFreeBytes
 *      ): BOOL 获得磁盘空闲信息
 * 其他:
 *      SetVolumeLabel(
 *          [in, optional] LPCTSTR lpRootPathName,
 *          [in, optional] LPCTSTR lpVolumeName
 *      ): BOOL 设置卷标
 **/
