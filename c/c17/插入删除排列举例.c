#include<stdio.h>
int main(){
	int a[9]={1,9,5,3,6,7,11,14},c[8]={0},i,k,m;
	printf("this series is:");
	for(i=0;i<8;i++){
		printf("%-4d",a[i]);}
	printf("\n");	
	printf("please input insert num:");
	scanf("%d",&k);
	printf("and its location(0~7):");
	scanf("%d",&m);
	for(i=8;i>-1;i--){
		if(i<m);if(i==m)a[i]=k;if(i>m)a[i]=a[i-1];}
	printf("this series is:");
	for(i=0;i<9;i++){
		printf("%-4d",a[i]);}
	printf("\n");
	printf("input delete location(0~8):");
	scanf("%d",&m);
	for(i=0;i<9;i++){
		if(i<m);if(i>=m)a[i]=a[i+1];}
	printf("this series is:");
	for(i=0;i<8;i++){
		printf("%-4d",a[i]);}
	return 0;}