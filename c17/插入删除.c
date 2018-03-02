#include<stdio.h>
int main()
{
int i,j,k,a[10];
printf("input 10 datas:");
for(i=0;i<10;i++)
	scanf("%d",&a[i]);
for(j=0;j<9;j++)
for(i=0;i<9-j;i++)
	if(a[i]<a[i+1])
		{k=a[i];a[i]=a[i+1];a[i+1]=k;}
for(i=0;i<10;i++)
	printf("%d",a[i]);
return 0;
}
