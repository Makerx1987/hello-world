#include"c.h"//配置头文件
typedef int ELT;//定义元素类型，这儿是整型，可以改成double
typedef int * pint;//定义pint类型，即二级指针int型，方便管理链表
//0表示成功运行，1表示出错，3表示内存不足（溢出）

int InitTriplet(pint *t ,ELT e1,ELT e2,ELT e3)
{/* 构造三元组t,依次置t的三个元素的初值为e1,e2和e3 */
	*t=(ELT *)malloc(sizeof(ELT)*3);
	if(!*t)exit(3);
	else (*t)[0]=e1,(*t)[1]=e2,(*t)[2]=e3;
	return 0;
}

int DestroyTriplet(pint *t)
 { /* 三元组t被销毁 */
   free(*t);
   *t=NULL;
   return 0;
 }

int Get(pint t,ELT i, ELT *e)
 { /* 三元组T已存在，1≤i≤3。操作结果：用e返回t的第i元的值 */
   if(i<1||i>3)
     return 1;
   *e=t[i-1];
   return 0;
 }


int main()
{
	pint myadt;
	int i=2;ELT e1=2661,e2=57,e3=98,output;

	printf("e1=2661,e2=57,e3=98\n");
	InitTriplet(&myadt,e1,e2,e3);

	printf("i=2\n");
	Get(myadt, i, &output);
	printf("Get function's output is %d\n",output);

	DestroyTriplet(&myadt);
	
	return 0;

}

