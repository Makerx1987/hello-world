#include<stdio.h>
void updn(char ch[])
{
int i,len,leno;char t;
for(i=0;;i++)if(ch[i]=='\0')break;
len=i;printf("%d\n",len);leno=len/2;
for(i=0;i<leno;i++){
	t=ch[i];
	ch[i]=ch[len-i-1];
	ch[len-i-1]=t;}
printf("%s\n",ch);
}
int main(){char a[30];
printf("please input string:");
scanf("%s",&a);
updn(a);
return 0;
}
