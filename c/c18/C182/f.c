#include"c.h"

typedef struct
 {
   ELT *elem; /* �洢�ռ��ַ */
   int length; /* ��ǰ���ȣ����������) */
   int listsize; /* ��ǰ����Ĵ洢����(��sizeof(ELT)Ϊ��λ) */
} SqList;//����˳���SqList������һ��ָ�룬һ�����ȣ�һ���ܴ�С



STS InitList(SqList *L)
 { /* ��ʼ��������һ���յ�˳�����Ա�L��*L�������ݱ��壬���Զ���ʱ����&L */
   (*L).elem=(ELT*)malloc(LIST_INIT_SIZE*sizeof(ELT));//malloc��̬�����ڴ�
   if(!(*L).elem)
     exit(OVERFLOW); /* �洢����ʧ�� */
   (*L).length=0; /* �ձ���Ϊ0 */
   (*L).listsize=LIST_INIT_SIZE; /* ��ʼ�洢����=10 */
   return OK;
 }

STS equal(ELT c1,ELT c2)
 { /* �ж��Ƿ���ȵĺ�����Union()�õ� */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 STS DestroyList(SqList *L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������˳�����Ա�L */
   free((*L).elem);
   (*L).elem=NULL;//��Ϊ��գ���ָ���κζ���
   (*L).length=0;//����
   (*L).listsize=0;//����
   return OK;
 }

 STS ClearList(SqList *L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� �����Ǳ���Ȼ����*/
   (*L).length=0;
   return OK;
 }

 STS ListIfEmpty(SqList L)
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
   if(L.length==0)
     return TRUE;
   else
     return FALSE;
 }

 STS GetElem(SqList L,int i,ELT *e)//ͬ�����Ҫ��һ��ָ��e���βΣ�������&e�������ʵ�Σ�
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
   /* �����������e����L�е�i������Ԫ�ص�ֵ */
   if(i<1||i>L.length)
     exit(ERROR);
   *e=*(L.elem+i-1);//ͬ��ʵ�����e=*&e
   return OK;
 }

STS LocateElem(SqList L,ELT e,STS(*compare)(ELT,ELT))
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�STS(*compare)(ELT,ELT)����ָ�룬ָ��һ����Ԫ����*/
   /* �������������L�е�1����e�����ϵcompare()������Ԫ�ص�λ�� */
   /*           ������������Ԫ�ز����ڣ��򷵻�ֵΪ0���㷨2.6 */
   ELT *p;
   int i=1; /* i�ĳ�ֵΪ��1��Ԫ�ص�λ�� */
   p=L.elem; /* p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ�� */
   while(i<=L.length && !compare(*p++,e))//����0&&1�Ľ��
     ++i;
   if(i<=L.length)
     return i;
   else
     return ERROR;
 }

STS PriorElem(SqList L,ELT cur_e,ELT *pre_e)
 { /* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* �����������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ���� */
   /*           �������ʧ�ܣ�pre_e�޶��� */
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

 STS ListInsert(SqList *L,int i,ELT e) /* �㷨2.4 */
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L)+1 */
   /* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
   ELT *newbase,*q,*p;
   if(i<1||i>(*L).length+1) /* iֵ���Ϸ� */
   {printf("ERROR");
	   return ERROR;}
   if((*L).length>=(*L).listsize) /* ��ǰ�洢�ռ�����,���ӷ��� */
   {
     newbase=(ELT *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ELT));//���·����ڴ棬ָ����=����������*��realloc��Ҫ�ı��ڴ��С��ָ�������µĴ�С����
     if(!newbase)
       exit(OVERFLOW); /* �洢����ʧ�� */
     (*L).elem=newbase; /* �»�ַ ����ָ�뻹�У��ܻ�һ���*/
     (*L).listsize+=LISTINCREMENT; /* �����˴洢���������� */
   }
   q=(*L).elem+i-1; /* qΪ����λ�� */
   for(p=(*L).elem+(*L).length-1;p>=q;--p) /* ����λ�ü�֮���Ԫ������ */
     *(p+1)=*p;
   *q=e; /* ����e */
   ++(*L).length; /* �����˱���1�������������Ҳ���� */
   return OK;
 }

 STS ListDelete(SqList *L,int i,ELT *e) /* �㷨2.5 */
 { /* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
   /* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
   ELT *p,*q;
   if(i<1||i>(*L).length) /* iֵ���Ϸ� */
   {printf("ERROR");
	   return ERROR;}
   p=(*L).elem+i-1; /* pΪ��ɾ��Ԫ�ص�λ�� */
   *e=*p; /* ��ɾ��Ԫ�ص�ֵ����e */
   q=(*L).elem+(*L).length-1; /* ��βԪ�ص�λ�� */
   for(++p;p<=q;++p) /* ��ɾ��Ԫ��֮���Ԫ������ */
     *(p-1)=*p;//�����ʼ++p����ûë��
   (*L).length--; /* ����1 */
	printf("ɾ����������:%d",*e);
   return OK;
 }

 STS ListTraverse(SqList L,void(*vi)(ELT*))
 { /* ��ʼ������˳�����Ա�L�Ѵ��� */
   /* �������������Ԫ�ص��ú���vi()��һ��vi()ʧ�ܣ������ʧ�� */
   /*           vi()���βμ�'&'��������ͨ������vi()�ı�Ԫ�ص�ֵ */
   ELT *p;
   int i;
   p=L.elem;
   for(i=1;i<=L.length;i++)
     vi(p++);
   printf("\n");
   return OK;
 }
 