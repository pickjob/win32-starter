//
// 头文件
//      <stdatomic.h>
// 类型
//      memory_order: 定义内存顺序制约
//      atomic_flag: 免锁原子布尔标志
// 枚举
//      enum memory_order {
//          memory_order_relaxed,
//          memory_order_consume,
//          memory_order_acquire,
//          memory_order_release,
//          memory_order_acq_rel,
//          memory_order_seq_cstf
//      };
// 函数
//      atomic_fetch_add / atomic_fetch_add_explicit: 原子加法
//      atomic_fetch_sub / atomic_fetch_sub_explicit: 原子减法
//
//      atomic_fetch_and / atomic_fetch_and_explicit: 原子逐位与(AND)
//      atomic_fetch_or / atomic_fetch_or_explicit: 原子逐位或(OR)
//      atomic_fetch_xor / atomic_fetch_xor_explicit: 原子逐位异或(XOR)
//
//      atomic_store / atomic_store_explicit: 存储值到原子对象
//      atomic_load / atomic_load_explicit: 从原子对象读取值
//
//      atomic_exchange / atomic_exchange_explicit: 将原子对象的值与一个值交换, 返回旧值