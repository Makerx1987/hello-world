#include<stdio.h>
void hanuo(int n,char a,char b,char c)
{
	if(n==1)printf("%c->%c\n",a,c);
	else{hanuo(n-1,a,c,b);printf("%c->%c\n",a,c);hanuo(n-1,b,a,c);}
}
int main()
{int n;printf("输入汉诺塔的个数：");scanf("%d",&n);
hanuo(n,'A','B','C');return 0;}