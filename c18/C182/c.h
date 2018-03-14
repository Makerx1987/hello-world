 /* c.h (程序名)单纯的C语言包含标准头文件，其应用的头文件更多 */
 #include<string.h>/* 字符串处理 */
 #include<ctype.h>/* 字符处理 */
 #include<malloc.h> 
 /* malloc()等，非标准头文件，malloc.h，动态存储分配函数头文件,当对内存区进行操作时,调用相关函数.
  ANSI标准建议使用stdlib.h头文件,但许多C编译要求用malloc.h,使用时应查阅有关手册。 */
 #include<limits.h> /* 定义各种数据类型最值常量，INT_MAX等 */
 #include<stdio.h> /* 定义输入/输出函数，EOF(=^Z或F6),NULL */
 #include<stdlib.h> /* 定义杂项函数及内存分配函数，atoi() */
 #include<io.h> /* 跟stdio.h不一样， 这个io.h不是标准C的头文件，eof() */
 #include<math.h> /* 数学函数，floor(),ceil(),abs() */
 #include<process.h> /* 线程的创建和终结，非标准头文件，exit() */

typedef int STS; //函数
typedef int ELT;//数据项类型

 #define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
 #define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 #define OVERFLOW -2
