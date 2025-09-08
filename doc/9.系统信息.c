/**
 * 系统信息:
 *      GetSystemInfo
 *          SYSTEM_INFO:
 *              内存信息:
 *                  dwPageSize: 页大小(4KB)
 *                  lpMinimumApplicationAddress: 最小可用地址 64KB
 *                  lpMaximumApplicationAddress: 最大可用地址
 *                  dwAllocationGranularity: 分配粒度 64KB
 *              其他信息:
 *                  dwNumberOfProcessors: CPU数量
 *                  DUMMYUNIONNAME.DUMMYSTRUCTNAME.wProcessorArchitecture: CPU架构
 *                      PROCESSOR_ARCHITECTURE_INTEL: x86
 *                      PROCESSOR_ARCHITECTURE_AMD64: x64
 *      GetUserName / GetUserNameEx: 检索当前线程的用户名
 *      GetSystemDirectory: 检索系统目录的路径
 *      GetComputerName / GetComputerNameEx: 检索本地计算机的 NetBIOS 名称
 *      GetComputerObjectName: 检索指定格式的本地计算机名称
 *      GetVersion / GetVersionEx: 检索当前作系统的版本号。
 *      GetWindowsDirectory: 检索 Windows 目录的路径
 **/