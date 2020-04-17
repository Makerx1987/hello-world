#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int HASHNAME[64];
typedef struct
{
	char *pin; //名字的拼音
	int h;	 //拼音所对应的整数
	int key;
	int slen;
} NAME;
NAME namelist[32];
void HashPrint()
{
	int i;
	printf("编号        人名     哈希地址        查找长度             关键词值\n");
	for (i = 0; i < 30; i++)
	{
		printf("%2d         %s \t %2d             %d                    %d\n", i + 1, namelist[i].pin, namelist[i].h, namelist[i].slen, namelist[i].key);
	}
}
void HashPrint2()
{
	int i;
	double j = 0,s=0;
	printf("哈希表地址      人名 \n");
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
	printf("冲突率:        %4f", j);
	printf("\n平均查找长度:  %4f", s);
}

void HASHinit()
{
	namelist[0].pin = "JinJie";
	namelist[1].pin = "ChenQiQi";
	namelist[2].pin = "LiuHaoDong";
	namelist[3].pin = "HeLiangYu";
	namelist[4].pin = "WangYanDa";
	namelist[5].pin = "YangZhiNing";
	namelist[6].pin = "ZhuangQi";
	namelist[7].pin = "ZhuangZi";
	namelist[8].pin = "WangSiYao";
	namelist[9].pin = "WangXinYi";
	namelist[10].pin = "XianYaFei";
	namelist[11].pin = "YangHong";
	namelist[12].pin = "YangZiYi";
	namelist[13].pin = "ZhaoJiaYi";
	namelist[14].pin = "GuoShuYan";
	namelist[15].pin = "ZhangBin";
	namelist[16].pin = "WangZiYan";
	namelist[17].pin = "YangTing";
	namelist[18].pin = "SongYuQing";
	namelist[19].pin = "KeYunLi";
	namelist[20].pin = "ZhaoHongZhi";
	namelist[21].pin = "WangTaoYi";
	namelist[22].pin = "XuWei";
	namelist[23].pin = "WangQing";
	namelist[24].pin = "YaoShengXu";
	namelist[25].pin = "XiaJia";
	namelist[26].pin = "YangXiao";
	namelist[27].pin = "SongYue";
	namelist[28].pin = "BaoHongQuan";
	namelist[29].pin = "PangCheng";
	namelist[30].pin = "Panan";
	namelist[31].pin = "CaiJunYang";

	printf("内置数据初始化完成\n\n");

	printf("输出已经录入的数据:\n\n");
	HashPrint();
}
void HASHgetkey()
{

	int i;
	for (i = 0; i < 30; i++)
	{	
		if(!namelist[i].pin[4])namelist[i].pin[4]=0;
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
	
	printf("\n------------------------欢迎使用哈希表操作程序-------------------------------\n\n");
	printf("\n                               菜 单 选 择                                 \n\n");
	printf("        1.除留余数（64）线性再散构造               2.打印数据表格               \n");
	printf("        3.查找哈希表（64）                         4.打印哈希表及冲突率               \n");
	printf("        5.退出                                     6.除留余数（32）线性再散构造               \n");
	printf("\n-----------------------------------------------------------------------------\n");
	printf("请输入你的选择：");
	scanf("%d", &yourchoice);
	while (!(yourchoice == 1 || yourchoice == 2 || yourchoice == 3 || yourchoice == 4 || yourchoice == 5 || yourchoice == 6))
	{
		printf("输入选择不明确，请重输\n");
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
	 	printf("\n输入查找的名字:");
		fflush(stdin);
		scanf("%s", a);
		
		key = a[0] + a[1]*5 + a[2]*11 + a[3]*17 + a[4]*23;
		h = (int)key % 64;
		printf("关键词的值%d\n", key);
		printf("查找%s中……\n\n", a);

		for (i = 0; i < 6; i++)
		{
			printf("获得哈希地址%d\n", h);
			if (namelist[HASHNAME[h]].pin[0] == a[0])
			{
				printf("\n哈希表地址      人名 \n");
				printf("%2d             %s\n", h, a);
				return;
			};
			h++;
		}
		printf("没有找到！ \n");
		fflush(stdin);

		break;
	case 6:
		HASHbuild(32);
		break;
	}
}
int main()
{
	printf("内置数据初始化中……\n");
	HASHinit();
	HASHgetkey();
	while (1)
	{
		HashWindow();
	}
	return 0;
}