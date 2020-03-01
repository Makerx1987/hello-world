
#line 1 "..\main.c" /0
  
#line 1 "..\..\..\..\..\..\..\..\KEIL\C51\INC\REG52.H" /0






 
 
 
 
 
 
 sfr P0    = 0x80;
 sfr P1    = 0x90;
 sfr P2    = 0xA0;
 sfr P3    = 0xB0;
 sfr PSW   = 0xD0;
 sfr ACC   = 0xE0;
 sfr B     = 0xF0;
 sfr SP    = 0x81;
 sfr DPL   = 0x82;
 sfr DPH   = 0x83;
 sfr PCON  = 0x87;
 sfr TCON  = 0x88;
 sfr TMOD  = 0x89;
 sfr TL0   = 0x8A;
 sfr TL1   = 0x8B;
 sfr TH0   = 0x8C;
 sfr TH1   = 0x8D;
 sfr IE    = 0xA8;
 sfr IP    = 0xB8;
 sfr SCON  = 0x98;
 sfr SBUF  = 0x99;
 
 
 sfr T2CON  = 0xC8;
 sfr RCAP2L = 0xCA;
 sfr RCAP2H = 0xCB;
 sfr TL2    = 0xCC;
 sfr TH2    = 0xCD;
 
 
 
 
 sbit CY    = PSW^7;
 sbit AC    = PSW^6;
 sbit F0    = PSW^5;
 sbit RS1   = PSW^4;
 sbit RS0   = PSW^3;
 sbit OV    = PSW^2;
 sbit P     = PSW^0;  
 
 
 sbit TF1   = TCON^7;
 sbit TR1   = TCON^6;
 sbit TF0   = TCON^5;
 sbit TR0   = TCON^4;
 sbit IE1   = TCON^3;
 sbit IT1   = TCON^2;
 sbit IE0   = TCON^1;
 sbit IT0   = TCON^0;
 
 
 sbit EA    = IE^7;
 sbit ET2   = IE^5;  
 sbit ES    = IE^4;
 sbit ET1   = IE^3;
 sbit EX1   = IE^2;
 sbit ET0   = IE^1;
 sbit EX0   = IE^0;
 
 
 sbit PT2   = IP^5;
 sbit PS    = IP^4;
 sbit PT1   = IP^3;
 sbit PX1   = IP^2;
 sbit PT0   = IP^1;
 sbit PX0   = IP^0;
 
 
 sbit RD    = P3^7;
 sbit WR    = P3^6;
 sbit T1    = P3^5;
 sbit T0    = P3^4;
 sbit INT1  = P3^3;
 sbit INT0  = P3^2;
 sbit TXD   = P3^1;
 sbit RXD   = P3^0;
 
 
 sbit SM0   = SCON^7;
 sbit SM1   = SCON^6;
 sbit SM2   = SCON^5;
 sbit REN   = SCON^4;
 sbit TB8   = SCON^3;
 sbit RB8   = SCON^2;
 sbit TI    = SCON^1;
 sbit RI    = SCON^0;
 
 
 sbit T2EX  = P1^1;  
 sbit T2    = P1^0;  
 
 
 sbit TF2    = T2CON^7;
 sbit EXF2   = T2CON^6;
 sbit RCLK   = T2CON^5;
 sbit TCLK   = T2CON^4;
 sbit EXEN2  = T2CON^3;
 sbit TR2    = T2CON^2;
 sbit C_T2   = T2CON^1;
 sbit CP_RL2 = T2CON^0;
 
 
#line 1 "..\main.c" /0
 
  
#line 1 "..\..\..\..\..\..\..\..\KEIL\C51\INC\STDIO.H" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef unsigned int size_t;
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char _getkey (void);
 extern char getchar (void);
 extern char ungetchar (char);
 extern char putchar (char);
 extern int printf   (const char *, ...);
 extern int sprintf  (char *, const char *, ...);
 extern int vprintf  (const char *, char *);
 extern int vsprintf (char *, const char *, char *);
 extern char *gets (char *, int n);
 extern int scanf (const char *, ...);
 extern int sscanf (char *, const char *, ...);
 extern int puts (const char *);
 
 #pragma RESTORE
 
 
 
#line 2 "..\main.c" /0
 
  
#line 1 "..\..\..\..\..\..\..\..\KEIL\C51\INC\STRING.H" /0






 
 
 
 
 
 
#line 13 "..\..\..\..\..\..\..\..\KEIL\C51\INC\STRING.H" /1
  
 
 
#line 16 "..\..\..\..\..\..\..\..\KEIL\C51\INC\STRING.H" /0
 
 
#line 18 "..\..\..\..\..\..\..\..\KEIL\C51\INC\STRING.H" /1
  
 
#line 20 "..\..\..\..\..\..\..\..\KEIL\C51\INC\STRING.H" /0
 
 #pragma SAVE
 #pragma REGPARMS
 extern char *strcat (char *s1, char *s2);
 extern char *strncat (char *s1, char *s2, int n);
 
 extern char strcmp (char *s1, char *s2);
 extern char strncmp (char *s1, char *s2, int n);
 
 extern char *strcpy (char *s1, char *s2);
 extern char *strncpy (char *s1, char *s2, int n);
 
 extern int strlen (char *);
 
 extern char *strchr (const char *s, char c);
 extern int strpos (const char *s, char c);
 extern char *strrchr (const char *s, char c);
 extern int strrpos (const char *s, char c);
 
 extern int strspn (char *s, char *set);
 extern int strcspn (char *s, char *set);
 extern char *strpbrk (char *s, char *set);
 extern char *strrpbrk (char *s, char *set);
 extern char *strstr  (char *s, char *sub);
 extern char *strtok  (char *str, const char *set);
 
 extern char memcmp (void *s1, void *s2, int n);
 extern void *memcpy (void *s1, void *s2, int n);
 extern void *memchr (void *s, char val, int n);
 extern void *memccpy (void *s1, void *s2, char val, int n);
 extern void *memmove (void *s1, void *s2, int n);
 extern void *memset  (void *s, char val, int n);
 #pragma RESTORE
 
 
#line 3 "..\main.c" /0
 
 
 
 sbit receive=P1^3;
 sbit rs=P2^0; 
 sbit lcden=P2^2; 
 sbit rw=P2^1;
  unsigned char  table[]= "Period     .  ms";
  unsigned char  table1[]="Radio     .    %";
  unsigned char  table2[]= "OUT OF RANGE !  ";
  unsigned char  table3[]= "START RESET ... ";
  unsigned char code num[]={'0','1','2','3','4','5','6','7','8','9'};
 long count0=0;
 long count1=0;
 long count2=0;
 
 long radio=0;
 long period=0;
 int a;
 
 





 
 void delay(int x)
 {	unsigned int y;
 for(;x>0;x--)
 {									 
 for(y=100;y>0;y--)
 {};
 }
 }





 
 void Time_Init()
 {
 TMOD = 0x19;	   
 TH0  = 0xff;	   
 TL0  = 0x9a;	
 TR0 = 1;		   
 ET0 = 1;		   
 TH1  = 0xff;	   
 TL1  = 0x9a;	
 TR1 = 1;		   
 ET1 = 1;		   
 count0=0;
 count1=0;
 count2=0;
 EX0 = 1;   
 IT0 = 1;   
 
 }
 





 
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





 
 void lcdwrdata(unsigned char dat)
 {
 
 rs=1; 
 lcden=1;
 P0=dat;
 delay(1);
 lcden=0;
 delay(1);
 }





 
 void lcdwrcom(unsigned char cdat) 
 {	
 
 rs=0; 
 lcden=1;
 P0=cdat; 
 delay(2); 
 lcden=0;
 delay(2);
 }





 
 void lcd_init()
 {
 lcdwrcom(0x38); 
 lcdwrcom(0x0c); 
 lcdwrcom(0x06); 
 lcdwrcom(0x01); 
 }





 
 void display()
 {
  unsigned char n;
 lcdwrcom(0x00|0x80);
 for(n=0;n<16;n++)
 {
 lcdwrdata(table[n]);
 
 }
 
 lcdwrcom(0x40|0x80);
 for(n=0;n<16;n++)
 {
 lcdwrdata(table1[n]);
 
 }
 
 }





 
 void Outside_Int0(void) interrupt 0	
 {
 
 count2++;
 
 }





 
 void main()
 {	
 EA=1;
 rw=0;	
 lcden=0;
 lcd_init();
 lcdwrcom(0x00|0x80);
 Time_Init();
 display();
 
 while(1)
 {
 if(count1>99999999)
 Time_Init();


















 
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
 
 
 }
 }
