#include<stdio.h>
double mean(double x[],int n){
	double sum=00.0;int i;
	for(i=0;i<n;i++)sum+=x[i];
	sum/=n;
	return sum;}
int main(){
	int i,n;double a[20];
	printf("please input n as length:");
	scanf("%d",&n);
	printf("please input %d numbers:",n);
	for(i=0;i<n;i++)scanf("%f",&a[i]);
	for(i=0;i<n;i++)printf("%4.1f\n",a[i]);
	printf("Average = %f",mean(a,n));
	return 0;}