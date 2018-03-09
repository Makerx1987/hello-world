#include"c.h"//����ͷ�ļ�
typedef int ELT;//����Ԫ�����ͣ���������ͣ����Ըĳ�double
typedef int * pint;//����pint���ͣ�������ָ��int�ͣ������������
//0��ʾ�ɹ����У�1��ʾ����3��ʾ�ڴ治�㣨�����

int InitTriplet(pint *t ,ELT e1,ELT e2,ELT e3)
{/* ������Ԫ��t,������t������Ԫ�صĳ�ֵΪe1,e2��e3 */
	*t=(ELT *)malloc(sizeof(ELT)*3);
	if(!*t)exit(3);
	else (*t)[0]=e1,(*t)[1]=e2,(*t)[2]=e3;
	return 0;
}

int DestroyTriplet(pint *t)
 { /* ��Ԫ��t������ */
   free(*t);
   *t=NULL;
   return 0;
 }

int Get(pint t,ELT i, ELT *e)
 { /* ��Ԫ��T�Ѵ��ڣ�1��i��3�������������e����t�ĵ�iԪ��ֵ */
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

