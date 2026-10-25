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
//          生命周期:
//              int     thrd_create     (thrd_t *thr, thrd_start_t func, void *arg);
//              void    thrd_yield      (void);
//              int     thrd_sleep      (struct timespec* duration, struct timespec* remaining);
//              int     thrd_detach     (thrd_t thr);
//              int     thrd_join       (thrd_t thr, int *res );
//              void    thrd_exit       (int res);
//          标识:
//              thrd_t  thrd_current    (void);
//              int     thrd_equal      (thrd_t lhs, thrd_t rhs);
// 线程局域存储
//      类型:
//          tss_dtor_t: 函数指针类型 void(*)(void*)，用作 TSS 析构器
//      函数:
//          int tss_create(tss_t* tss_key, tss_dtor_t destructor);
//          int tss_set(tss_t tss_key, void *val);
//          void* tss_get(tss_t tss_key);
//          int tss_delete(tss_t tss_key);
// 互斥体
//      类型:
//          mtx_t: 互斥体标识符
//      枚举:
//          mtx_plain
//          mtx_recursive
//          mtx_timed
//      函数:
//          int mtx_init(mtx_t* mutex, int type);
//          int mtx_lock(mtx_t* mutex);
//          int mtx_trylock(mtx_t* mutex);
//          int mtx_timedlock( mtx_t* mutex, struct timespec* time_point);
//          int mtx_unlock(mtx_t* mutex);
//          void mtx_destroy(mtx_t* mutex);
// 条件变量
//      类型:
//          cnd_t: 条件变量标识符
//      函数:
//          int cnd_init(cnd_t* cond);
//          int cnd_signal(cnd_t* cond);
//          int cnd_broadcast(cnd_t* cond);
//          int cnd_wait(cnd_t* cond, mtx_t* mutex);
//          int cnd_timedwait(cnd_t* cond, mtx_t* mutex, struct timespec* time_point);
//          void cnd_destroy(cnd_t* cond);