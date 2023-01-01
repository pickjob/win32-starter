/**
 * C语言版本
 *    C90:
 *      基础
 *    C99:
 *      支持不定长的数组
 *      变量声明不必放在语句块的开头
 *    C11:
 *      对齐处理
 *      多线程支持
 *    C18
 **/
// Hello World两个版本
#include <stdio.h>
int main(void) {
    printf("Hello World\n");
    return 0;
}
#include <stdio.h>
int main(int argc, char* argv[]) {
    printf("Hello World\n");
    return 0;
}
// 变量声明:
//      datatype var [= initial_value];
// 变量修饰符:
//      const: 只读
//      static:
//          局部变量: 变量在函数每次执行后保留
//          全局变量: 只作用于当前文件, 其他源文件不可引用, 值必须是常量
//      auto: 编译器自主分配(默认)
//      extern: 变量在其他文件里声明
//      register: 变量值放进寄存器, 不能读取地址
//      volatile: 不要对变量优化, 每次查询最新值
//      restrict: 允许编译器优化某些代码
// 运算符:
//      算术运算符: + - * / %
//      自增运算符、自减运算符: ++ --
//      关系运算符: > < >= <= == !=
//      逻辑运算符: !(非) &&(与) ||(或)
//      位运算符: ~(取反) &(与) |(或) ^(异或) <<(左移) >>(右移)
//      sizeof: 返回类型大小(Bytes)
// 流程控制:
//      if:
//          if (expression) statement [else statement]
//      ?::
//          expression ? true_statement : false_statement;
//      for:
//          for (initialization; continuation; action)
//              statement;
//      switch:
//          switch (expression) {
//              case value1: statement
//              case value2: statement
//              default: statement
//          }
//      while:
//          while (expression)
//              statement
//      do ... while:
//          do statement
//          while (expression);
//      break、continue:
// 数据类型:
//      char(1 Byte)
//      int short long
//      float double
//      boolean: 1(true) 0(false)
//      void*: 可以指向任意类型的数据
// 指针:
//      数据类型  *指针名称 = &数据变量;
// 函数:
//      datatype func_name([arg_type [arg_name] [, arg_type [arg_name]]]) {
//          return exp;
//      }
//      extern datetype func_name(args); // 外部函数
// 函数指针:
//      声明:
//          void (*p_func)(int, int, float) = NULL;
//          typedef void (*p_func)(int, int, float);
//      调用:
//          int val1 = p_func(1,2,3.0);
//          int val2 = (*p_func)(1,2,3.0);
// 数组:
//      datatype array_name[array_length]
//      变长数组(VLA, variable-length array)
//      **数组名指向的地址是不能更改的**
//          int ints[100];
//          ints = NULL; // 报错
//          int a[5] = {1, 2, 3, 4, 5};
//          // 写法一
//          int b[5] = a; // 报错
//          // 写法二
//          int b[5];
//          b = a; // 报错
//      数组指针加减法:
//          a + 1, a - 1: 下一个、上一个成员
//          a[b] == *(a + b)
//
//          int a[] = {11, 22, 33, 44, 55, 999};
//          int* p = a;
//          while (*p != 999) {
//              printf("%d\n", *p);
//              p++;
//          }
// 字符串:
//      char string[]
//      \0 结尾
// 结构:
//      struct struct_name {
//          // field
//      };
//      struct struct_name var_name = {}
//      typedef struct {
//
//      } type_name;
//      type_name var_name = {};
// 联合体:
//      union union_name {
//          // feiled_name
//      }
// 枚举:
//      typedef enum {
//          true,
//          false
//      } BOOLEAN;
// 宏:
//      #define SQUARE(X) X*X
//      #define PRINT_NUMS_TO_PRODUCT(a, b) { \
//          int product = (a) * (b); \
//          for (int i = 0; i < product; i++) { \
//              printf("%d\n", i); \
//          } \
//      }
//      #: 宏值转为字符串
//      ##: 标识符连接
//      不定参数宏:
//          #define X(a, b, ...) (10*(a) + 20*(b)), __VA_ARGS__
// 预处理器:
//      #define
//      #include
//      #ifdef ... #endif
//      #ifndef...#endif
//      预定义宏:
//          __DATE__: 编译日期 Mmm dd yyyy
//          __TIME__: 编译时间 hh:mm:ss
//          __FILE__: 当前文件名
//          __LINE__: 当前行号
//          __func__: 当前正在执行的函数名
//          __STDC_VERSION__: C语言版本 yyyymmL
// 标准库:
//      C99:
//          <assert.h>: 包含断言，被用来在程序的调试版本中帮助检测逻辑错误以及其他类型的bug
//          <complex.h>: 一组操作复数的函数
//          <ctype.h>:
//          定义了一组函数，用来根据类型来给字符分类，或者进行大小写转换，而不关心所使用的字符集（通常是ASCII或其扩展字符集，也有EBCDIC）
//          <errno.h>: 用来测试由库函数报的错误代码
//          <fenv.h>: 定义了一组用来控制浮点数环境的函数
//          <float.h>: 定义了用于浮点数库特定实现的宏常量
//          <inttypes.h>: 定义精确的宽度整数类型
//          <iso646.h>: 定义几个等效于C中某些运算符的宏用于使用ISO 646变体字符集进行编程
//          <limits.h>: 定义了用于整数库特定实现属性的宏常量
//          <locale.h>: 定义C语言本地化函数
//          <math.h>: 定义C语言数学函数
//          <setjmp.h>: 定义了宏setjmp和longjmp，在非局部跳转的时候使用
//          <signal.h>: 定义C语言信号处理函数
//          <stdarg.h>: 可变参数处理
//          <stdbool.h>: 定义布尔数据类型
//          <stddef.h>: 定义了几个常见的类型与宏
//          <stdint.h>: 定义精确的宽度整数类型
//          <stdio.h>: 定义输入输出函数
//          <stdlib.h>: 定义数值转换函数，伪随机数生成函数，动态内存分配函数，过程控制函数
//          <string.h>: 定义C语言字符串处理函数
//          <tgmath.h>: Defines type-generic mathematical functions.
//          <time.h>: Defines date and time handling functions
//          <wchar.h>: Defines wide string handling functions.
//          <wctype.h>: Defines set of functions used to classify wide characters by their types or to convert between
//          upper and lower case
//      C11:
//          <stdalign.h>: 用于查询和指定对象的数据结构对齐方式
//          <stdatomic.h>: 原子操作共享数据
//          <stdnoreturn.h>: For specifying non-returning functions
//          <threads.h>: Defines functions for managing multiple threads as well as mutexes and condition variables.
//          <uchar.h>: Types and functions for manipulating Unicode characters.
