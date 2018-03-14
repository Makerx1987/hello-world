#include"f.c"
STS wrirelist(SqList L);
STS checklist(SqList L);
int main()
{		
	SqList L;int i;ELT e;

	printf("程序名称：C1821，功能：用于线性表的简单操作\n");
	printf("InitList L \n");
	InitList(&L);L.length=10;
	printf("success \nnow write the linear list...........\n");

	wrirelist(L);
	printf("\n在A处插入一个数据B\n");
	printf("A=");scanf("%d",&i);
	printf("B=");scanf("%d",&e);
	ListInsert(&L,i,e);
	
	checklist(L);

	printf("\n在A处删除一个数据\n");	
	printf("A=");scanf("%d",&i);
	ListDelete(&L,i,&e);
	
	checklist(L);
	system("pause");
	return 0;
}

STS wrirelist(SqList L)
{	
	ELT *p;
	printf("example numbers: 1 2 3 4 65 98 1290 43212 886 -33 \n");
	for(p=L.elem;p<L.elem+L.length;p++)
	{
		printf("input numbers:");
		scanf("%d",p);
		printf("success \n");
	}
	checklist(L);

	return 0;
}

STS checklist(SqList L)
{	
	ELT *p;

	printf("\nnow check value..........\n");
	for(p=L.elem;p<L.elem+L.length;p++)
	printf("check value:%d\n",*p);
	printf("success \n");

	return 0;
}