 /* c.h (������)������C���԰�����׼ͷ�ļ�����Ӧ�õ�ͷ�ļ����� */
 #include<string.h>/* �ַ������� */
 #include<ctype.h>/* �ַ����� */
 #include<malloc.h> 
 /* malloc()�ȣ��Ǳ�׼ͷ�ļ���malloc.h����̬�洢���亯��ͷ�ļ�,�����ڴ������в���ʱ,������غ���.
  ANSI��׼����ʹ��stdlib.hͷ�ļ�,�����C����Ҫ����malloc.h,ʹ��ʱӦ�����й��ֲᡣ */
 #include<limits.h> /* �����������������ֵ������INT_MAX�� */
 #include<stdio.h> /* ��������/���������EOF(=^Z��F6),NULL */
 #include<stdlib.h> /* ������������ڴ���亯����atoi() */
 #include<io.h> /* ��stdio.h��һ���� ���io.h���Ǳ�׼C��ͷ�ļ���eof() */
 #include<math.h> /* ��ѧ������floor(),ceil(),abs() */
 #include<process.h> /* �̵߳Ĵ������սᣬ�Ǳ�׼ͷ�ļ���exit() */

typedef int STS; //����
typedef int ELT;//����������

 #define LIST_INIT_SIZE 10 /* ���Ա�洢�ռ�ĳ�ʼ������ */
 #define LISTINCREMENT 2 /* ���Ա�洢�ռ�ķ������� */
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 #define OVERFLOW -2
