//
// 头文件
//      <threads.h>
// 线程
//      常量(指示线程错误状态):
//          thrd_success
//          thrd_timedout
//          thrd_busy
//          thrd_nomem
//          thrd_error
//      类型:
//          thrd_t: 实现定义的标识线程的完整对象类型
//          thrd_start_t: 函数指针类型 int(*)(void*) 的 typedef，为 thrd_create 所用
//      函数:
//          thrd_create: 创建线程
//          thrd_detach: 分离线程
//          thrd_join: 阻塞到线程终止为止
//          thrd_exit: 终止调用方线程
//          thrd_sleep: 在给定的时间段内挂起调用方线程的执行
//          thrd_yield: 让出当前时间片段
//
//          thrd_current: 获取当前线程标识符
//          thrd_equal: 检查两个标识符是否表示同一线程
// 线程局域存储
//      类型:
//          tss_dtor_t: 函数指针类型 void(*)(void*)，用作 TSS 析构器
//      函数:
//          tss_create: 以给定的析构器，创建线程特定存储指针
//          tss_set: 写入线程特定存储
//          tss_get: 从线程特定存储读取
//          tss_delete: 释放给定的线程特定存储指针所保有的资源
// 互斥体
//      类型:
//          mtx_t: 互斥体标识符
//      枚举:
//          mtx_plain
//          mtx_recursive
//          mtx_timed
//      函数:
//          mtx_init: 创建互斥体
//          mtx_lock: 阻塞到锁定互斥体为止
//          mtx_trylock: 锁定互斥体，若已锁定则返回而不阻塞
//          mtx_timedlock: 阻塞到锁定互斥体或超时为止
//          mtx_unlock: 解锁互斥体
//          mtx_destroy: 销毁互斥体