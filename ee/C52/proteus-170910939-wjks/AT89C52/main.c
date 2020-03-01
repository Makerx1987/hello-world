#include "reg52.h"
#include <stdio.h>
#include <string.h>
#define uchar unsigned char 
#define uint unsigned int
sbit receive=P1^3;
sbit rs=P2^0;//H���ݣ�L����
sbit lcden=P2^2;//������ʹ�ܣ�ʹ��������С150ns
sbit rw=P2^1;
uchar  table[]= "Period     .  ms";
uchar  table1[]="Radio     .    %";
uchar  table2[]= "OUT OF RANGE !  ";
uchar  table3[]= "START RESET ... ";
uchar code num[]={'0','1','2','3','4','5','6','7','8','9'};
long count0=0;
long count1=0;
long count2=0;

long radio=0;
long period=0;
int a;
//bit flag=0;
//bit first=0;
/********************************************************************
* ���� : delay(int x)
* ���� : ��ʱ����
* ���� : x 
* ��� : ��
***********************************************************************/
void delay(int x)
{	uint y;
	for(;x>0;x--)
	 {									 
		for(y=100;y>0;y--)
				{};
	 }
}
/********************************************************************
* ���� : Time0_Init()
* ���� : ��ʱ���ĳ�ʼ����11.0592MZ����0.1ms,921600
* ���� : ��
* ��� : ��
***********************************************************************/
void Time_Init()
{
   TMOD = 0x19;	  //��ʱ��0ѡ�÷�ʽ1�����崥������ʱ��1ʹ�÷�ʽ1�����ϼ���
	TH0  = 0xff;	  //��ֵ�ļ���
	TL0  = 0x9a;	
	TR0 = 1;		  //������ʱ��
	ET0 = 1;		  //�򿪶�ʱ���ж�����λ
	TH1  = 0xff;	  //��ֵ�ļ���
	TL1  = 0x9a;	
	TR1 = 1;		  //������ʱ��
	ET1 = 1;		  //�򿪶�ʱ���ж�����λ
	count0=0;
	 count1=0;
        count2=0;
   	EX0 = 1;  //���ⲿ�ж�0
	IT0 = 1;  //�����ش���

}

/********************************************************************
* ���� : Time_Int()
* ���� : ��ʱ���жϣ��ж���ʵ�� �������
* ���� : ��
* ��� : ��
***********************************************************************/
void Time0_Int() interrupt 1
{
	TH0 = 0xff;
	TL0 = 0x9a;
	count0=count0+1;
}
void Time1_Int() interrupt 3
{
	TH1 = 0xff;
	TL1 = 0x9a;
	count1=count1+1;
}
/********************************************************************
* ���� : lcdwrcom(uchar cdat)
* ���� : LCD1602д���ݵ�LCD1602
* ���� : cdat 
* ��� : ��
***********************************************************************/
void lcdwrdata(uchar dat)
{
   // dat = ((dat&0x01)<<7)|((dat&0x02)<<5)|((dat&0x04)<<3)|((dat&0x08)<<1)|((dat&0x10)>>1)|((dat&0x20)>>3)|((dat&0x40)>>5)|((dat&0x80)>>7);
	rs=1;//д����ʱRS����
	lcden=1;
	P0=dat;
	delay(1);
	lcden=0;
	delay(1);
}
/********************************************************************
* ���� : lcdwrcom(uchar cdat)
* ���� : LCD1602д���LCD1602
* ���� : cdat 
* ��� : ��
***********************************************************************/
void lcdwrcom(uchar cdat)//дָ�����ݵ�LCD  
{	
   // cdat = ((cdat&0x01)<<7)|((cdat&0x02)<<5)|((cdat&0x04)<<3)|((cdat&0x08)<<1)|((cdat&0x10)>>1)|((cdat&0x20)>>3)|((cdat&0x40)>>5)|((cdat&0x80)>>7);
    rs=0;//дָ��ʱRS����
	lcden=1;
    P0=cdat;//
	delay(2);//���Ӵ���ʱ�����²���д��ָ�����д����ʾ����
	lcden=0;
	delay(2);
}
/********************************************************************
* ���� : lcd_init()
* ���� : LCD1602��ʼ��
* ���� : ��
* ��� : ��
***********************************************************************/
void lcd_init()
{
	lcdwrcom(0x38);//0x38������ʾģʽΪ��16X2 ��ʾ,5X7 ����,8 λ���ݽӿ�
	lcdwrcom(0x0c);//����ʾ�����˸
	lcdwrcom(0x06);//
	lcdwrcom(0x01);//
}
/********************************************************************
* ���� : display()
* ���� : LCD��ʾ����
* ���� : 
* ��� : ��
***********************************************************************/
void display()
{
	 uchar n;
	 lcdwrcom(0x00|0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table[n]);
		//delay(100);
	}

	lcdwrcom(0x40|0x80);
	for(n=0;n<16;n++)
	{
		lcdwrdata(table1[n]);
		//delay(100);
	}
   
}
/********************************************************************
* ���� : Outside_Int0()
* ���� : �ⲿ�ж�0 ���жϴ���
* ���� : ��
* ��� : ��
***********************************************************************/
void Outside_Int0(void) interrupt 0	
{
	
	count2++;
	
}
/********************************************************************
* ���� : main()
* ���� : ������
* ���� : ��
* ��� : ��
***********************************************************************/
void main()
{	
	EA=1;
	rw=0;	
	lcden=0;
	lcd_init();
	lcdwrcom(0x00|0x80);
	 Time_Init();
	 display();
	 //while(receive==1);
	while(1)
	{
	   if(count1>99999999)
	      Time_Init();
	    /*count3++;
	   if(receive==1)
	      {
		 if(flag==0){
		    flag=1;
		    count2++;
		    }
	         TR1=0;
		 TR0=1;		 
	      }
	    else
	      {
	       if(flag==1){
		    flag=0;
		    count2++;
		    }
	       TR1=1;
	       TR0=0;
	      }*/
	   if(count2!=0)period=(float)(count1)/(float)(count2)*1.25;   
	   if(period!=0)radio=(float)(count0)/(float)(count1)*10000;
	   if(period>100000)
	   {
		   strcpy(table,table2);
		   strcpy(table1,table3);
		   display();
		   delay(1000);
		   break;
	   }

	   a=(period/10000)%10;
	   table[7]=num[a];
	   a=(period/1000)%10;
	   table[8]=num[a];
	   a=(period/100)%10;
	   table[9]=num[a];
	   a=(period/10)%10;
	   table[10]=num[a];
	   table[11]='.';
	   a=(period)%10;
	   table[12]=num[a]; 

	   a=(radio/1000)%10;
	   table1[8]=num[a];
	   a=(radio/100)%10;
	   table1[9]=num[a];
	   table1[10]='.';
	   a=(radio/10)%10;
	   table1[11]=num[a];
	   a=(radio)%10;
	   table1[12]=num[a];

	   
	    

	      
	   display();
	   //delay(1);
	   
	}
}
