/**
 * 头文件
 *      tlhelp32.h
 * 函数
 *      CreateToolhelp32Snapshot: 拍摄指定进程的快照、线程、模块、堆
 *          TH32CS_SNAPPROCESS
 *              Process32First: 检索有关系统快照中遇到的第一个进程的信息
 *              Process32Next: 检索系统快照中记录的下一个进程的相关信息
 *          TH32CS_SNAPTHREAD
 *              Thread32First
 *              Thread32Next
 *          TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32
 *              Module32First
 *              Module32Next
 *          TH32CS_SNAPHEAPLIST
 *              Heap32ListFirst
 *              Heap32ListNext
 *          TH32CS_SNAPALL: TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE | TH32CS_SNAPHEAPLIST
 **/