 /* c.h (程序名)单纯的C语言包含标准头文件，其应用的头文件更多 */
 
#include<malloc.h> 
 /* malloc()等，非标准头文件，malloc.h，动态存储分配函数头文件,当对内存区进行操作时,
 调用相关函数.
  ANSI标准建议使用stdlib.h头文件,但许多C编译要求用malloc.h,使用时应查阅有关手册。 */

 #include<stdio.h> 
/* 定义输入/输出函数，EOF(=^Z或F6),NULL */

 #include<process.h> 
/* 线程的创建和终结，非标准头文件，exit() */
