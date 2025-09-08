/**
 * 基本知识
 *      一些默认大小
 *          分配粒度(allocation granularity): 64KB
 *          页面大小: 4KB
 *      地址控件划分
 *          32bit
 *              空指针:    0x0 - 0x0000FFFF
 *              用户模式:  0x10000 - 0x7FFFFFFF
 *              内核模式:  0x80000000 - 0xFFFFFFFF
 *          64bit
 *              空指针:    0x0 - 0x0000FFFF
 *              用户模式:  0x10000 - 0x7FFFFFFFFFF
 *              内核模式:  800FFFFFFFF - 0xFFFFFFFFFFFFFFFF
 *      页面状态
 *          Free: 该页既未提交也不保留
 *          Reserve: 该页已保留以供将来使用
 *          Committed: 该页已分配
 *      页面保护属性: 读、写、执行
 *          PAGE_EXECUTE: 启用执行, 禁止读、写
 *          PAGE_EXECUTE_READ: 启用执行、读, 禁止写
 *          PAGE_EXECUTE_READWRITE: 启用执行、读、写
 *          PAGE_READONLY: 启用读, 禁止写入、执行
 *          PAGE_READWRITE: 启用读、写, 禁止执行
 *          PAGE_NOACCESS: 禁止执行、读、写
 *          文件映射
 *              PAGE_WRITECOPY: 启用读, 写创建新副本, 禁止执行
 *              PAGE_EXECUTE_WRITECOPY: 启用执行、读、写, 写创建新副本
 *          其他
 *              PAGE_GUARD: 区域中的页面将成为保护页
 *              PAGE_NOCACHE: 将所有页面设置为不可缓存
 *              PAGE_WRITECOMBINE: 设置要写入组合的所有页面
 *      内存池
 *          非分页池
 *          分页池
 *      内存区域
 *          FREE: 闲置
 *          PRIVATE: 私有
 *          IMAGE: 镜像
 *          MAPPED: 已映射
 * 函数
 *      常规
 *          信息
 *              GetLargePageMinimum: 检索大页的最小大小
 *              GetPhysicallyInstalledSystemMemory: 检索计算机上物理安装的 RAM 量
 *              GetSystemFileCacheSize / SetSystemFileCacheSize: 系统缓存的工作集的当前大小限制
 *              GetWriteWatch: 检索已写入虚拟内存区域中的页面的地址
 *              ResetWriteWatch: 重置虚拟内存区域的写入跟踪状态
 *              GlobalMemoryStatusEx: 获取有关系统当前使用物理内存和虚拟内存的信息
 *              QueryMemoryResourceNotification: 检索指定内存资源对象的状态
 *          FillMemory: 用指定的值填充内存块
 *          ZeroMemory: 用零填充内存块
 *          SecureZeroMemory / SecureZeroMemory2: 用零填充内存块
 *          MoveMemory: 将内存块从一个位置移到另一个位置
 *          CopyMemory: 将内存块从一个位置复制到另一个位置
 *      工作集:
 *          GetProcessMemoryInfo: 若要获取或更改最小和最大工作集大小
 *              working set
 *              paged pool
 *              nonpaged pool
 *              pagefile
 *          GetProcessWorkingSetSizeEx / SetProcessWorkingSetSizeEx
 *          EmptyWorkingSet
 *      堆内存
 *          HeapWalk: 枚举指定堆中的内存块
 *          HeapQueryInformation / HeapSetInformation: 检索 / 设置有关指定堆的信息
 *          HeapCreate / HeapDestroy: 创建/销毁 堆对象
 *          GetProcessHeap: 获取调用进程的堆的句柄
 *          GetProcessHeaps: 获取对调用进程有效的所有堆的句柄
 *          HeapAlloc / HeapFree: 分配 / 释放从堆分配的内存块
 *          HeapReAlloc: 从堆重新分配内存块
 *          HeapCompact: 合并堆上的相邻可用内存块
 *          HeapLock / HeapUnlock: 获取 / 释放 与指定堆关联的锁
 *          HeapSize: 检索从堆分配的内存块的大小
 *          HeapValidate: 尝试验证指定的堆
 *      虚拟内存
 *          QueryVirtualMemoryInformation： 返回有关指定进程的虚拟地址空间中的页面或一组页面的信息
 *          VirtualQuery / VirtualQueryEx: 提供有关调用进程的虚拟地址空间中的一系列页面的信息
 *          VirtualAlloc / VirtualAlloc2 / VirtualAllocEx / VirtualAllocExNuma: 保留、提交或更改指定进程的虚拟地址空间中内存区域的状态
 *          VirtualFree / VirtualFreeEx : 释放或取消提交调用进程的虚拟地址空间中的页面区域
 *          VirtualLock / VirtualUnlock: 锁定/解锁进程的虚拟地址空间的指定区域到物理内存中
 *          VirtualProtect / VirtualProtectEx: 更改调用进程的虚拟地址空间中已提交的页面区域的访问保护
 *      全局、局部(废弃)
 *          GlobalAlloc / GlobalReAlloc / GlobalLock / GlobalUnlock / GlobalFree
 *          LocalAlloc / LocalReAlloc / LocalLock / LocalFreess
 **/