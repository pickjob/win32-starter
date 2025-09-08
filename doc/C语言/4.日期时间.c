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
//      时间操纵:
//          time: struct time_t 返回纪元开始经过的当前系统日历时间
//          clock: struct clock_t 返回未加工的程序启动时开始经过的处理器时间
//          timespec_get: 返回基于给定时间基底的日历时间
//          timespec_getres: 返回基于给定时间基底的日历时间的解析度
//          difftime: 计算时间差, 返回秒数 s
//      格式转换:
//          gmtime / gmtime_r / gmtime_s: struct time_t => struct tm (UTC)
//          localtime / localtime_r / localtime_s: struct time_t => struct tm (本地时间)
//          mktime: struct tm => time time_t
//          strftime(wchar.h): struct tm 对象转换成自定义文本表示
//          wcsftime: 将 struct tm 对象转换成自定义宽字符文本表示
//              %Y-%m-%d %H:%M:%S
#include <stdio.h>
#include <time.h>
#include <wchar.h>

int main(void) {
    time_t timeNow = {0};
    time(&timeNow);
    struct tm tmNow = {0};
    localtime_s(&tmNow, &timeNow);

    char szNow[64];
    strftime(szNow, sizeof(szNow) - 1, "NOW(): %Y-%m-%d %H:%M", &tmNow);
    printf("%s\n", szNow);

    wchar_t szwNow[64];
    wcsftime(szwNow, sizeof(szwNow) - 1, L"NOW(): %Y-%m-%d %H:%M", &tmNow);
    wprintf(L"%s\n", szwNow);
}