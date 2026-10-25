//
// VA: 虚拟内存地址(Virtual Address), 进程基地址 + 相对虚拟内存地址
// RVA: 相对虚拟内存地址(Relative Virtual Address)
// FOA: 文件偏移地址(File Offset Address)
//      给定RVA计算FOA
//          FOA = SECTION_FILE_BASE + (RVA - SECTION_RVA)
//      对齐
//          节内存对齐: 32bit: 4KB(1000H) 64bit: 8KB(2000H)
//          节文件对齐: 512B(200H)
//          资源数据对齐: 4B
// PE文件结构
//      DOS MZ Header
//          IMAGE_DOS_HEADER
//              e_magic（0x0 WORD): "MZ" (0x4D 0x5A)
//              e_lfanew(0x3C DWORD): PE头相对于文件的偏移地址
//          DOS Stub
//              This program cannot be run in DOS mode.
//      PE Header(IMAGE_NT_HEADERS)
//          Signature: "PE\0\0" (0x50 0x45 0x00 0x00): 4字节
//          IMAGE_FILE_HEADER: COFF Heaer, 20字节
//              Machine: PE文件支持平台
//                  IMAGE_FILE_MACHINE_I386: x86 (0x4c 0x01)
//                  IMAGE_FILE_MACHINE_AMD64: x64 (0x64 0x86)
//              Characteristics: 文件属性
//                  IMAGE_FILE_RELOCS_STRIPPED: 文件中不存在定位信息 0x0001
//                  IMAGE_FILE_EXECUTABLE_IMAGE: 文件可执行 0x0002
//                  IMAGE_FILE_LARGE_ADDRESS_AWARE: 应用程序可处理大于2GB地址 0x0020
//                  IMAGE_FILE_32BIT_MACHINE: 只在32bit上运行 0x0100
//                  IMAGE_FILE_DLL: DLL文件 0x2000
//              NumberOfSections: PE中节数量, Windows限制最大96
//              TimeDateStamp: time_t, 秒数低32位
//          IMAGE_OPTIONAL_HEADER32 / IMAGE_OPTIONAL_HEADER64
//              Magic
//                  PE32: 0x0B 0x01
//                  PE32+: 0x0B 0x02
//              ImageBase: 程序的建议装载地址, 64K的倍数
//                  DLL-0x10000000
//                  EXE-0x400000(32) 0x40000000(64)
//              SizeOfImage: 内存中整个PE镜像尺寸
//              AddressOfEntryPoint: 程序执行入口 RVA
//              BaseOfCode: 代码的区块的起始RVA
//              SizeOfCode: 所有代码节的大小
//              SizeOfHeaders: 所有头 + 节表大小
//              SizeOfStackReserve: 初始化时栈大小, 默认0x100000(1MB)
//              SizeOfStackCommit: 初始化时栈提交大小, 默认0x1000(4KB)
//              SizeOfHeapReserve: 初始化时保留队大小, 默认0x100000(1MB)
//              SizeOfHeapCommit: 初始化时堆提交大小, 默认0x1000(4KB)
//              Subsystem: 子系统类型
//                  IMAGE_SUBSYSTEM_UNKNOWN: 未知子系统 0
//                  IMAGE_SUBSYSTEM_NATIVE: 设备驱动 1
//                  IMAGE_SUBSYSTEM_WINDOWS_GUI: GUI 2
//                  IMAGE_SUBSYSTEM_WINDOWS_CUI: CUI 3
//              DllCharacteristics: DLL文件特征
//                  IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE: 加载时重定位 0x0040
//                  IMAGE_DLLCHARACTERISTICS_NO_SEH: 不使用用SEH 0x0400
//              SectionAlignment(0x38 DWORD): 内存中节对齐粒度
//                  32bit: 0x1000 (4 KB)
//                  64bit: 0x2000 (8 KB)
//              FileAlignment(0x3C DWORD): 文件中节对齐粒度
//                  0x200(512 B)
//
//              NumberOfRvaAndSizes: DataDirectory数量, 16
//              IMAGE_DATA_DIRECTORY * 16 DataDirectory: 数据目录
//                  VirtualAddress: 数据起始RVA
//                  isize: 数据块大小
//                      00 Export Table: .edata 导出表的地址和大小
//                      01 Import Table: .idata 导入目录表的地址和大小
//                      02 Resource Table: .rsrc  资源表的地址和大小
//                      03 Exception Table: .pdata 异常表的地址和大小
//                      04 Certificate Table: 属性证书表的地址和大小
//                      05 Base Relocation Table: .reloc 基址重定位表的地址和大小
//                      06 Debug Information: .debug 调试数据起始地址和大小
//                      07 Architecture
//                      08 Global Ptr: 全局指针寄存器中的一个值的RVA, Size 0
//                      09 TLS Table: 线程局部存储(TLS)表的地址和大小
//                      10 Load Config Table: 加载配置表的地址和大小
//                      11 Bound Import Table: 绑定导入查找表的地址和大小
//                      12 Import Address Table: IAT, 导入函数地址表的地址和大小
//                          PE未加载: 与 INT 指向相同 IMAGE_IMPORT_BY_NAME
//                          PE加载: 函数实际位置数组
//                      13 Delay Import Descriptor: 延迟导入描述符的地址和大小
//                      14 CLR Runtime Header: .cormeta CLR运行时头部的地址和大小
//                      15 Reserved
//          Section Table
//              IMAGE_SECTION_HEADER
//                  Name: 节区名, \0结尾, 8 Byte ASCII字符
//                      .rdata: 只读的运行时数据
//                      .bass: 未经初始化数据
//                      .data: 已初始化数据
//                      .text: 代码
//                      .rsrc: 资源
//                      .tls: 线程本地存储(Thead-local storage)
//                      .reloc: 重定位表信
//                      .edata: 导出名字表(exported names table)
//                      .idata: 导入名字表(imported names tables)
//                      .didata: 延迟导入的名字表(Delay imported names table)
//                  VirtualAddress: 节区虚拟内存RVA
//                  VirtualSize: 节区虚拟内存尺寸
//                  PointerToRawData: 节区文件FOA
//                  SizeOfRawData: 节区文件尺寸
//                  Characteristics: 节区属性
//                      IMAGE_SCN_CNT_INITIALIZED_DATA: 包含初始化数据
//                      IMAGE_SCN_CNT_UNINITIALIZED_DATA： 包含未初始化数据
//                      IMAGE_SCN_CNT_CODE: 包含代码
//                      IMAGE_SCN_MEM_DISCARDABLE: 可被丢弃
//                      IMAGE_SCN_MEM_NOT_CACHED: 节中数据不缓存
//                      IMAGE_SCN_MEM_NOT_PAGED: 节中数据不交换到磁盘中
//                      IMAGE_SCN_MEM_SHARED: 内存中可共享
//                      IMAGE_SCN_MEM_EXECUTE: 可执行
//                      IMAGE_SCN_MEM_READ: 可读
//                      IMAGE_SCN_MEM_WRITE: 可写