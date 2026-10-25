#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { LOG_LEVEL_DEBUG = 0, LOG_LEVEL_INFO, LOG_LEVEL_WARN, LOG_LEVEL_ERROR } log_level_t;

// 日志-初始化
int  log_init(void);

// 日志-核心写日志函数
void log_write(log_level_t level, const char *file, int line, const char *fmt, ...);

// 日志-GetLastError
void log_last_error_write(log_level_t level, const char *file, int line, char *tag);

// 日志-衍生宏
#define LOG_DEBUG(...)   log_write(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)    log_write(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)    log_write(LOG_LEVEL_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...)   log_write(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)

#define LOG_LAST_ERROR(tag) log_last_error_write(LOG_LEVEL_INFO, __FILE__, __LINE__, tag)

#ifdef __cplusplus
}
#endif

#endif /* LOG_H */