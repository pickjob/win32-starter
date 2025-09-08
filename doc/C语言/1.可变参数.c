/**
 * 头文件
 *      <stdarg.h>
 * 类型
 *      va_list: 保有 va_start、va_arg、va_end 及 va_copy 所需的信息(typedef)
 * 宏
 *      va_start: 令函数得以访问可变实参
 *      va_arg: 访问下一个可变函数实参
 *      va_end: 结束对函数可变实参的遍历
 *      va_copy: 创造函数可变实参的副本
 **/
#include <stdarg.h>
#include <stdio.h>

int sumInt(int count, ...) {
    int     sum = 0;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, int);
    }
    va_end(args);
    return sum;
}

int main(void) {
    printf("%d\n", sumInt(2, 2, 3));
    return 0;
}