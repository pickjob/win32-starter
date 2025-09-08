/**
 * 函数
 *      遍历
 *          FindFirstVolume + FindNextVolume + FindVolumeClose: 检索计算机上的卷的名称
 *          FindFirstVolumeMountPoint + FindNextVolumeMountPoint + FindVolumeMountPointClose: 检索指定卷上装载的文件夹的名称
 *      GetLogicalDrives: 检索表示当前可用磁盘驱动器的位掩码
 *          0: A
 *          1: B
 *          ...
 *      GetLogicalDriveStrings: 使用指定系统中有效驱动器的字符串填充缓冲区
 *          C:\nullD:\null
 *      GetVolumePathName: 检索装载指定路径的卷装入点
 *      GetVolumePathNamesForVolumeName: 检索指定卷的驱动器号和装载的文件夹路径的列表
 *      GetDiskFreeSpace / GetDiskFreeSpaceEx: 检索有关指定磁盘的信息
 *      GetDriveType: 确定磁盘驱动器是可移动的、固定的、CD-ROM、RAM 磁盘还是网络驱动器
 *          DRIVE_UNKNOWN
 *          DRIVE_REMOVABLE
 *          DRIVE_FIXED
 *          DRIVE_CDROM
 *          DRIVE_RAMDISK
 *      GetVolumeInformation: 检索与指定根目录关联的文件系统和卷的相关信息
 *      GetVolumeInformationByHandleW: 检索与指定文件关联的文件系统和卷的相关信息
 *      GetVolumeNameForVolumeMountPoint: 检索与指定卷装入点关联的卷 GUID 路径（驱动器号、卷 GUID 路径或装载文件夹）
 *          lpszVolumeMountPoint:
 *              X:\mountX\
 *              Y:\
 *      SetVolumeLabel: 设置文件系统卷的标签
 *      SetVolumeMountPoint: 将卷与其他卷上的驱动器号或目录相关联
 **/