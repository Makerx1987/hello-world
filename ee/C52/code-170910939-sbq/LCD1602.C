#include "reg52.h"
#include <stdio.h>
#include <string.h>
#define uchar unsigned char 
#define uint unsigned int
sbit receive=P1^3;
sbit rs=P2^0;//H数据，L命令
sbit lcden=P2^2;//高脉冲使能，使能脉宽最小150ns
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
* 名称 : delay(int x)
* 功能 : 延时函数
* 输入 : x 
* 输出 : 无
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
* 名称 : Time0_Init()
* 功能 : 定时器的初始化，11.0592MZ晶振，0.1ms,921600
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Time_Init()
{
   TMOD = 0x19;	  //定时器0选用方式1，脉冲触发，定时器1使用方式1，不断计数
	TH0  = 0xff;	  //初值的计算
	TL0  = 0x9a;	
	TR0 = 1;		  //启动定时器
	ET0 = 1;		  //打开定时器中断允许位
	TH1  = 0xff;	  //初值的计算
	TL1  = 0x9a;	
	TR1 = 1;		  //启动定时器
	ET1 = 1;		  //打开定时器中断允许位
	count0=0;
	 count1=0;
        count2=0;
   	EX0 = 1;  //开外部中断0
	IT0 = 1;  //负边沿触发

}

/********************************************************************
* 名称 : Time_Int()
* 功能 : 定时器中断，中断中实现 脉冲输出
* 输入 : 无
* 输出 : 无
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
* 名称 : lcdwrcom(uchar cdat)
* 功能 : LCD1602写数据到LCD1602
* 输入 : cdat 
* 输出 : 无
***********************************************************************/
void lcdwrdata(uchar dat)
{
   // dat = ((dat&0x01)<<7)|((dat&0x02)<<5)|((dat&0x04)<<3)|((dat&0x08)<<1)|((dat&0x10)>>1)|((dat&0x20)>>3)|((dat&0x40)>>5)|((dat&0x80)>>7);
	rs=1;//写数据时RS拉高
	lcden=1;
	P0=dat;
	delay(1);
	lcden=0;
	delay(1);
}
/********************************************************************
* 名称 : lcdwrcom(uchar cdat)
* 功能 : LCD1602写命令到LCD1602
* 输入 : cdat 
* 输出 : 无
***********************************************************************/
void lcdwrcom(uchar cdat)//写指令数据到LCD  
{	
   // cdat = ((cdat&0x01)<<7)|((cdat&0x02)<<5)|((cdat&0x04)<<3)|((cdat&0x08)<<1)|((cdat&0x10)>>1)|((cdat&0x20)>>3)|((cdat&0x40)>>5)|((cdat&0x80)>>7);
    rs=0;//写指令时RS拉低
	lcden=1;
    P0=cdat;//
	delay(2);//不加此延时将导致不能写入指令，但能写入显示数据
	lcden=0;
	delay(2);
}
/********************************************************************
* 名称 : lcd_init()
* 功能 : LCD1602初始化
* 输入 : 无
* 输出 : 无
***********************************************************************/
void lcd_init()
{
	lcdwrcom(0x38);//0x38设置显示模式为：16X2 显示,5X7 点阵,8 位数据接口
	lcdwrcom(0x0c);//打开显示光标闪烁
	lcdwrcom(0x06);//
	lcdwrcom(0x01);//
}
/********************************************************************
* 名称 : display()
* 功能 : LCD显示函数
* 输入 : 
* 输出 : 无
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
* 名称 : Outside_Int0()
* 功能 : 外部中断0 的中断处理
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Outside_Int0(void) interrupt 0	
{
	
	count2++;
	
}
/********************************************************************
* 名称 : main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
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
