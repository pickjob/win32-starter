/**
 * 基本知识:
 *      地址控件划分:
 *          32bit:
 *              空指针:    0x0 - 0x0000FFFF
 *              用户模式:  0x10000 - 0x7FFFFFFF
 *              内核模式:  0x80000000 - 0xFFFFFFFF
 *          64bit:
 *              空指针:    0x0 - 0x0000FFFF
 *              用户模式:  0x10000 - 0x7FFFFFFFFFF
 *              内核模式:  800FFFFFFFF - 0xFFFFFFFFFFFFFFFF
 *      一些默认大小:
 *          分配粒度(allocation granularity): 64KB
 *          页面大小: 4KB
 *      页面状态:
 *          Free: VirtualFree 、VirtualFreeEx
 *          Reserve:  VirtualAlloc 、 VirtualAllocEx
 *          Committed
 *      页面保护属性: 读取、写入、执行
 *          PAGE_NOACCESS: 禁止读取、写入、执行
 *          PAGE_READONLY: 禁止写入、执行
 *          PAGE_READWRITE: 禁止执行
 *          PAGE_EXECUTE: 禁止读取、写入
 *          PAGE_EXECUTE_READ: 禁止写入
 *          PAGE_EXECUTE_READWRITE: 允许任何操作
 *          PAGE_WRITECOPY: 禁止执行, 读私有副本
 *          PAGE_EXECUTE_WRITECOPY: 允许任何操作, 读私有副本
 *          PAGE_GUARD: 写入通知
 *          PAGE_NOCACHE: 无缓存
 *          PAGE_WRITECOMBINE: 操作合并
 *      内存区域类型:
 *          FREE: 闲置
 *          PRIVATE: 私有
 *          IMAGE: 镜像
 *          MAPPED: 已映射
 * Heap Memory:
 *      基本:
 *          GetProcessHeap(): HANDLE 获得程序默认堆 Handle
 *          HeapAlloc(
 *              [in] HANDLE hHeap,
 *              [in] DWORD  dwFlags,
 *              [in] SIZE_T dwBytes
 *          ): LVOID
 *              dwFlags:
 *                  HEAP_ZERO_MEMORY
 *                  HEAP_GENERATE_EXCEPTION
 *                  HEAAP_NO_SERIALIZER
 *          HeapReAlloc(
 *              [in] HANDLE                 hHeap,
 *              [in] DWORD                  dwFlags,
 *              [in] _Frees_ptr_opt_ LPVOID lpMem,
 *              [in] SIZE_T                 dwBytes
 *          ): LVOID
 *              dwFlags:
 *                  HEAP_GENERATE_EXCEPTIONS
 *                  HEAP_NO_SERIALIZE
 *                  HEAP_ZERO_MEMORY
 *          HeapFree(
 *              [in] HANDLE                 hHeap,
 *              [in] DWORD                  dwFlags,
 *              [in] _Frees_ptr_opt_ LPVOID lpMem
 *          ): BOOL
 *      其他:
 *          GetProcessHeaps(
 *              [in]  DWORD   NumberOfHeaps,
 *              [out] PHANDLE ProcessHeaps
 *          ): DWORD 获得活动堆
 *          HeapCreate(
 *              [in] DWORD  flOptions,
 *              [in] SIZE_T dwInitialSize,
 *              [in] SIZE_T dwMaximumSize
 *          ): HANDLE 创建私有堆
 *              flOptions:
 *                  HEAP_CREATE_ENABLE_EXECUTE
 *                  HEAP_GENERATE_EXCEPTIONS
 *                  HEAP_NO_SERIALIZE
 *          HeapLock([in] HANDLE hHeap): BOOL
 *          HeapUnlock([in] HANDLE hHeap): BOOL
 *          HeapDestroy([in] HANDLE hHeap): 销毁私有堆
 *          HeapSize(
 *              [in] HANDLE  hHeap,
 *              [in] DWORD   dwFlags,
 *              [in] LPCVOID lpMem
 *          ): SIZE_T 查看堆大小
 *          HeapValidate(
 *              [in]           HANDLE  hHeap,
 *              [in]           DWORD   dwFlags,
 *              [in, optional] LPCVOID lpMem
 *          ): BOOL 校验堆
 *          HeapWalk(
 *              [in]      HANDLE               hHeap,
 *              [in, out] LPPROCESS_HEAP_ENTRY lpEntry
 *          ): BOOL 堆内存枚举
 *              PPROCESS_HEAP_ENTRY:
 *                  wFlags: Region BUSY
 *                  lpData: 开始地址
 *                  cbData: 区域大小
 *                  cbOverhead: 超过大小
 *                  iRegionIndex: 索引
 *      全局、局部(废弃):
 *          GlobalAlloc / GlobalReAlloc / GlobalLock / GlobalUnlock / GlobalFree
 *          LocalAlloc / LocalReAlloc / LocalLock / LocalFreess
 * Virtual Memory:
 *      基本:
 *          VirtualAlloc(
 *              [in, optional] LPVOID lpAddress,
 *              [in]           SIZE_T dwSize,
 *              [in]           DWORD  flAllocationType,
 *              [in]           DWORD  flProtect
 *          ): LPVOID
 *          VirtualAllocEx(
 *              [in]           HANDLE hProcess,
 *              [in, optional] LPVOID lpAddress,
 *              [in]           SIZE_T dwSize,
 *              [in]           DWORD  flAllocationType,
 *              [in]           DWORD  flProtect
 *          ): LPVOID
 *              flAllocationType:
 *                  MEM_COMMIT
 *                  MEM_RESERVE
 *                  MEM_RESET
 *                  MEM_RESET_UNDO
 *              flProtect: 页面保护属性
 *          VirtualFree(
 *              [in] LPVOID lpAddress,
 *              [in] SIZE_T dwSize,
 *              [in] DWORD  dwFreeType
 *          ): BOOL
 *          VirtualFreeEx(
 *              [in] HANDLE hProcess,
 *              [in] LPVOID lpAddress,
 *              [in] SIZE_T dwSize,
 *              [in] DWORD  dwFreeType
 *          ): BOOL
 *      其他:
 *          VirtualQuery(
 *             [in, optional] LPCVOID                   lpAddress,
 *             [out]          PMEMORY_BASIC_INFORMATION lpBuffer,
 *             [in]           SIZE_T                    dwLength
 *          ): 查询本进程内存信息
 *             lpBuffer:
 *                BaseAddress: 基本地址
 *                AllocationBase:
 *                AllocationProtect:
 *                RegionSize:
 *                State: MEM_COMMIT / MEM_FREE / MEM_RESERVE
 *                Type: MEM_IMAGE / MEM_MAPPED / MEM_PRIVATE
 *          VirtualQueryEx(
 *             [in]           HANDLE                    hProcess,
 *             [in, optional] LPCVOID                   lpAddress,
 *             [out]          PMEMORY_BASIC_INFORMATION lpBuffer,
 *             [in]           SIZE_T                    dwLength
 *          ): 查询其他进程内存信息
 *              MEMORY_BASIC_INFORMATION:
 *                  BaseAddress: lpAddress向下取到整个页面大小
 *                  AllocationBase
 *                  AllocationProtect: 保护属性
 *                  RegionSize: 区域大小
 *                  State:
 *                      MEM_FREE、MEM_RESERVE、MEM_COMMIT
 *                  Protect
 *                  Type
 *          VirtualLock(
 *              [in] LPVOID lpAddress,
 *              [in] SIZE_T dwSize
 *          ): BOOL 锁进物理内存
 *          VirtualUnlock(
 *              [in] LPVOID lpAddress,
 *              [in] SIZE_T dwSize
 *          ): BOOL 解锁物理内存
 *          VirtualProtect(
 *              [in]  LPVOID lpAddress,
 *              [in]  SIZE_T dwSize,
 *              [in]  DWORD  flNewProtect,
 *              [out] PDWORD lpflOldProtect
 *          ): BOOL 改变内存属性
 *          VirtualProtectEx(
 *              [in]  HANDLE hProcess,
 *              [in]  LPVOID lpAddress,
 *              [in]  SIZE_T dwSize,
 *              [in]  DWORD  flNewProtect,
 *              [out] PDWORD lpflOldProtect
 *          ): BOOL
 *          GlobalMemoryStatus(
 *              [out] LPMEMORYSTATUS lpBuffer
 *          ): void
 *              MEMORYSTATUS:
 *                  dwMemoryLoad: 正在使用内存百分比
 *                  dwTotalPhys: 实际物理内存(byte)
 *                  dwTotalPageFile: 提交内存限制当前大小(byte)
 *                  dwAvailPageFile: 当前进程可以提交最大内存(byte)
 *                  dwTotalVirtual: 虚拟内存用户模式大小(byte)
 *                  dwAvailVirtual: 用户模式未保留和未提交内存量(byte)
 * 其他内存函数:
 *      ZeroMemory([in] PVOID  Destination, [in] SIZE_T Length): void 内存置零
 *      SecureZeroMemory(_In_ PVOID  ptr, _In_ SIZE_T cnt): PVOID 内存置零
 *      FillMemory([out] PVOID  Destination, [in]  SIZE_T Length, [in]  BYTE   Fill): void 内存置数
 *      MoveMemory(_In_ PVOID  Destination, _In_ const VOID *Source, _In_       SIZE_T Length): void 移动内存
 *      CopyMemory(_In_ PVOID  Destination, _In_ const VOID *Source, _In_ SIZE_T Length): void 复制内存
 * 内存文件映射: (https://docs.microsoft.com/en-us/windows/win32/memory/file-mapping)
 *      打开文件: CreateFile
 *      创建文件映射内核对象: CreateFileMapping
 *      将文件数据映射到进程空间: MapViewOfFile MapViewOfFileEx
 *      从进程空间撤销对文件数据的映射: UnmapViewOfFile
 *      关闭文件映射对象和文件对象: CloseHandle
 **/
