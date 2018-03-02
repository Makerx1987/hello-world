#include<stdio.h>
int main()
{
	int i,j,p=0,x,c[100]={0},b[100]={0},a[100]={0};
	printf("input x:");
	scanf("%d",&x);
			
	for(i=0;i<100;i++)
	{
	a[i]=c[i]=x%10;x=x/10;
	}
	
while(p<27)
	{	p++;
		b[0]=a[0]*c[0];

		for(i=1;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				if(i-j>-1)
				{
				b[i]+=a[j]*c[i-j];
				}
			b[i]+=b[i-1]/10;
			b[i-1]=b[i-1]%10;
			}
		}

		for(i=0;i<100;i++){a[i]=b[i];b[i]=0;}

	}

		
		
for(i=99;i>-1;i--){if(a[i]!=0)printf("%d",a[i]);}

return 0;
}
