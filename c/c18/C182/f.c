#include"c.h"

typedef struct
 {
   ELT *elem; /* 存储空间基址 */
   int length; /* 当前长度（数据项个数) */
   int listsize; /* 当前分配的存储容量(以sizeof(ELT)为单位) */
} SqList;//定义顺序表SqList，包括一个指针，一个长度，一个总大小



STS InitList(SqList *L)
 { /* 初始化：构造一个空的顺序线性表L，*L才是内容本体，所以定义时可用&L */
   (*L).elem=(ELT*)malloc(LIST_INIT_SIZE*sizeof(ELT));//malloc动态分配内存
   if(!(*L).elem)
     exit(OVERFLOW); /* 存储分配失败 */
   (*L).length=0; /* 空表长度为0 */
   (*L).listsize=LIST_INIT_SIZE; /* 初始存储容量=10 */
   return OK;
 }

STS equal(ELT c1,ELT c2)
 { /* 判断是否相等的函数，Union()用到 */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 STS DestroyList(SqList *L)
 { /* 初始条件：顺序线性表L已存在。操作结果：销毁顺序线性表L */
   free((*L).elem);
   (*L).elem=NULL;//变为真空，不指向任何东西
   (*L).length=0;//归零
   (*L).listsize=0;//归零
   return OK;
 }

 STS ClearList(SqList *L)
 { /* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 ，但是表依然存在*/
   (*L).length=0;
   return OK;
 }

 STS ListIfEmpty(SqList L)
 { /* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L.length==0)
     return TRUE;
   else
     return FALSE;
 }

 STS GetElem(SqList L,int i,ELT *e)//同理，这儿要传一个指针e（形参），比如&e（输入的实参）
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：用e返回L中第i个数据元素的值 */
   if(i<1||i>L.length)
     exit(ERROR);
   *e=*(L.elem+i-1);//同理实际输出e=*&e
   return OK;
 }

STS LocateElem(SqList L,ELT e,STS(*compare)(ELT,ELT))
 { /* 初始条件：顺序线性表L已存在，STS(*compare)(ELT,ELT)函数指针，指向一个二元函数*/
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0。算法2.6 */
   ELT *p;
   int i=1; /* i的初值为第1个元素的位序 */
   p=L.elem; /* p的初值为第1个元素的存储位置 */
   while(i<=L.length && !compare(*p++,e))//比如0&&1的结果
     ++i;
   if(i<=L.length)
     return i;
   else
     return ERROR;
 }

STS PriorElem(SqList L,ELT cur_e,ELT *pre_e)
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   int i=2;
   ELT *p=L.elem+1;
   while(i<=L.length&&*p!=cur_e)
   {
     p++;
     i++;
   }
   if(i>L.length)
     return INFEASIBLE;
   else
   {
     *pre_e=*--p;
     return OK;
   }
 }

 STS ListInsert(SqList *L,int i,ELT e) /* 算法2.4 */
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
   /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
   ELT *newbase,*q,*p;
   if(i<1||i>(*L).length+1) /* i值不合法 */
   {printf("ERROR");
	   return ERROR;}
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ELT *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ELT));//重新分配内存，指针名=（数据类型*）realloc（要改变内存大小的指针名，新的大小）。
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 ，旧指针还行，能活一会儿*/
     (*L).listsize+=LISTINCREMENT; /* 表明了存储容量的增加 */
   }
   q=(*L).elem+i-1; /* q为插入位置 */
   for(p=(*L).elem+(*L).length-1;p>=q;--p) /* 插入位置及之后的元素右移 */
     *(p+1)=*p;
   *q=e; /* 插入e */
   ++(*L).length; /* 表明了表长增1，好像放在上面也可以 */
   return OK;
 }

 STS ListDelete(SqList *L,int i,ELT *e) /* 算法2.5 */
 { /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
   /* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
   ELT *p,*q;
   if(i<1||i>(*L).length) /* i值不合法 */
   {printf("ERROR");
	   return ERROR;}
   p=(*L).elem+i-1; /* p为被删除元素的位置 */
   *e=*p; /* 被删除元素的值赋给e */
   q=(*L).elem+(*L).length-1; /* 表尾元素的位置 */
   for(++p;p<=q;++p) /* 被删除元素之后的元素左移 */
     *(p-1)=*p;//这里初始++p所以没毛病
   (*L).length--; /* 表长减1 */
	printf("删除的数据是:%d",*e);
   return OK;
 }

 STS ListTraverse(SqList L,void(*vi)(ELT*))
 { /* 初始条件：顺序线性表L已存在 */
   /* 操作结果：遍历元素调用函数vi()。一旦vi()失败，则操作失败 */
   /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
   ELT *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     vi(p++);
   printf("\n");
   return OK;
 }
 