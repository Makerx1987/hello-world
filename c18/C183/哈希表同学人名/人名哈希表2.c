#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int HASHNAME[64];
typedef struct
{
	char pin[16]; //���ֵ�ƴ��
	int h;	 //ƴ������Ӧ������
	int key;
	int slen;
} NAME;
NAME namelist[32];
void HashPrint()
{
	int i;
	printf("���        ����     ��ϣ��ַ        ���ҳ���             �ؼ���ֵ\n");
	for (i = 0; i < 30; i++)
	{
		printf("%2d         %s \t %2d             %d                    %d\n", i + 1, namelist[i].pin, namelist[i].h, namelist[i].slen, namelist[i].key);
	}
}
void HashPrint2()
{
	int i;
	double j = 0,s=0;
	printf("��ϣ���ַ      ���� \n");
	for (i = 0; i < 64; i++)
	{
		if (HASHNAME[i] != 40)
		{
			printf("%2d             %s\n", i, namelist[HASHNAME[i]].pin);
		}
	}
	for (i = 0; i < 30; i++)
	{	
		s+=namelist[i].slen;
		if (namelist[i].slen != 1)
		{
			j++;
		}
	}
	j = j / 30;s=s/30;
	printf("��ͻ��:        %4f", j);
	printf("\nƽ�����ҳ���:  %4f", s);
}

void HASHinit()
{	int i;
	for(i=0;i<30;i++)
	{	printf("��������\n");
		scanf("%s",namelist[i].pin);
	}

	printf("�������ݳ�ʼ�����\n\n");

	printf("����Ѿ�¼�������:\n\n");
	
	HashPrint();
	fflush(stdin);
}
void HASHgetkey()
{

	int i;
	for (i = 0; i < 30; i++)
	{
		namelist[i].key = (namelist[i].pin[0] + namelist[i].pin[1]*5 + namelist[i].pin[2]*11 + namelist[i].pin[3]*17 + namelist[i].pin[4]*23);
	}
}
void HASHbuild(int c)
{
	int i;
	for (i = 0; i < 64; i++)
	{
		HASHNAME[i] = 40;
	}
	for (i = 0; i < 30; i++)
	{
		namelist[i].h = namelist[i].key % c;
		namelist[i].slen = 1;
		while (HASHNAME[namelist[i].h] != 40)
		{
			namelist[i].h = (++namelist[i].key) % c;
			namelist[i].slen ++;
		}
		HASHNAME[namelist[i].h] = i;
	}
}


void HashWindow()
{
	int yourchoice;
	
	printf("\n------------------------��ӭʹ�ù�ϣ���������-------------------------------\n\n");
	printf("\n                               �� �� ѡ ��                                 \n\n");
	printf("        1.����������64��������ɢ����               2.��ӡ���ݱ��               \n");
	printf("        3.���ҹ�ϣ��64��                         4.��ӡ��ϣ����ͻ��               \n");
	printf("        5.�˳�                                     6.����������32��������ɢ����               \n");
	printf("\n-----------------------------------------------------------------------------\n");
	printf("���������ѡ��");
	scanf("%d", &yourchoice);
	while (!(yourchoice == 1 || yourchoice == 2 || yourchoice == 3 || yourchoice == 4 || yourchoice == 5 || yourchoice == 6))
	{
		printf("����ѡ����ȷ��������\n");
		scanf("%d", &yourchoice);
	}
	switch (yourchoice)
	{
		char a[20];int key,h,i;
	case 1:
		HASHbuild(64);
		break;
	case 2:
		HashPrint();
		break;
	case 4:
		HashPrint2();
		break;
	case 5:
		system("cls");
		exit(0);
		break;
	case 3:
		printf("\n������ҵ�����:");
		fflush(stdin);
		scanf("%s", a);
		key = a[0] + a[1]*5 + a[2]*11 + a[3]*17 + a[4]*23;
		h = (int)key % 64;
		printf("�ؼ��ʵ�ֵ%d\n", key);
		printf("����%s�С���\n\n", a);

		for (i = 0; i < 6; i++)
		{
			printf("��ù�ϣ��ַ%d\n", h);
			if (namelist[HASHNAME[h]].pin[0] == a[0])
			{
				printf("\n��ϣ���ַ      ���� \n");
				printf("%2d             %s\n", h, a);
				return;
			};
			h++;
		}
		printf("û���ҵ��� \n");
		fflush(stdin);

		break;
	case 6:
		HASHbuild(32);
		break;
	}
}
int main()
{
	printf("���ݳ�ʼ���С���\n");
	HASHinit();
	HASHgetkey();
	while (1)
	{
		HashWindow();
	}
	return 0;
}