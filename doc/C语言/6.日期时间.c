//
// 头文件
//      <time.h>
// 类型
//      tm: 日历时间类型
//          tm_sec: 秒数 [​0​, 61]
//          tm_min: 分钟数 [​0​, 59]
//          tm_hour: 小时数 [​0​, 23]
//          tm_mday: 日 [1, 31]
//          tm_mon: 月份 [​0​, 11]
//          tm_year: 从 1900 年经过的年数
//          tm_wday: 星期（从星期日开始计）[​0​, 6]
//          tm_yday: 从 1 月 1 日始经过的天数 [​0​, 365]
//          tm_isdst: 夏时令标签
//      time_t: 从纪元开始的日历时间类型
//      clock_t: 从时点开始的处理器时间类型
//      timespec: 单位为秒和纳秒的时间
// 函数
//      时间:
//          time_t      time            (time_t* arg);                      // 返回纪元开始经过的当前系统日历时间
//          clock_t     clock           (void);                             // 返回未加工的程序启动时开始经过的处理器时间
//          int         timespec_get    (struct timespec *ts, int base);    // 返回基于给定时间基底的日历时间
//          int         timespec_getres (struct timespec *ts, int base );   // 返回基于给定时间基底的日历时间的解析度
//          double      difftime        (time_t time_end, time_t time_beg); // 计算时间差, 返回秒数
//      时间转换:
//          struct tm*  gmtime          (time_t* timer);
//          struct tm*  gmtime_r        (time_t* timer, struct tm* buf);
//          struct tm*  gmtime_s        (time_t* timer, struct tm* buf);
//          struct tm*  localtime       (time_t* timer );
//          struct tm*  localtime_r     (time_t* timer, struct tm* buf);
//          struct tm*  localtime_s     (time_t* timer, struct tm* buf);
//          time_t      mktime          (struct tm *arg );
//      格式化:
//          size_t      strftime        (char* str, size_t count, char* format, struct tm* tp); // struct tm 对象转换成自定义文本表示
//              %Y: 年份（4 位数）
//              %m: 月份（01-12）
//              %d: 日（01-31）
//              %H: 小时（00-23）
//              %M: 分钟（00-59）
//              %S: 秒（00-60）