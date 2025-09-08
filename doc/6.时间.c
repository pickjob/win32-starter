/**
 * 不同时间
 *      系统时间: UTC
 *      文件时间: UTC, 1601 年 1 月 1 日凌晨 12：00 A.M. 起经过的 100 纳秒间隔数
 *      Windows 时间: 自上次启动系统以来的毫秒数
 * 结构
 *      FILETIME: 自 1601 年 1 月 1 日 (UTC) 以来的 100 纳秒间隔数
 *      SYSTEMTIME: 指定日期和时间，使用月份、日、年、工作日、小时、分钟、秒和毫秒的单个成员
 * 函数
 *      系统时间
 *          GetSystemTime / SetSystemTime: UTC 格式的当前系统日期和时间
 *          GetTimeFormat: 将系统时间格式化为指定区域设置的时间字符串
 *          NtQuerySystemTime: 返回系统时间
 *          GetSystemTimeAdjustment: 确定系统是否对其时间时钟应用定期时间调整
 *          SetSystemTimeAdjustment: 启用或禁用对系统时间时钟的定期时间调整
 *          RtlTimeToSecondsSince1970: 将指定的系统时间转换为自 1970 年 1 月 1 日的第一秒以来的秒数
 *      本地时间
 *          GetLocalTime / SetLocalTime: 当前本地日期和时间
 *          GetTimeZoneInformation / SetTimeZoneInformation: 当前时区设置
 *      文件时间
 *          GetFileTime / SetFileTime: 检索 / 设置指定文件或目录的创建、上次访问和上次修改的日期和时间
 *          CompareFileTime: 比较两个文件时间
 *          GetSystemTimeAsFileTime: 检索 UTC 格式的当前系统日期和时间
 *      转换
 *          SystemTimeToFileTime: 将系统时间转换为文件时间
 *          LocalFileTimeToFileTime: 根据 UTC 将本地文件时间转换为文件时间
 *          FileTimeToSystemTime: 将文件时间转换为系统时间格式
 *          FileTimeToLocalFileTime: 将 UTC 文件时间转换为本地文件时间
 *          RtlLocalTimeToSystemTime: 将指定的本地时间转换为系统时间
 *          SystemTimeToTzSpecificLocalTime: 将 UTC 时间转换为指定时区的相应本地时间
 *          SystemTimeToTzSpecificLocalTimeEx: 将具有动态夏令时设置的 UTC 时间转换为指定时区的相应本地时间
 *          TzSpecificLocalTimeToSystemTime: 将本地时间转换为 UTC 时间
 *          TzSpecificLocalTimeToSystemTimeEx: 将具有动态夏令时设置的本地时间转换为 UTC 时间
 *      Windows 时间
 *          GetSystemTimes: 检索系统计时信息
 *          GetTickCount: 检索自系统启动以来经过的毫秒数，最长为 49.7 天
 *          GetTickCount64: 检索自系统启动以来经过的毫秒数
 **/