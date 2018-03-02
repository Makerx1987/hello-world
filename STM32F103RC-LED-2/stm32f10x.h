//寄存器的值常常是芯片外设自动更改的，即使 CPU 没有执行程序，也有可能发生变化  
//编译器有可能会对没有执行程序的变量进行优化，所以用 volatile 来修饰寄存器变量
//volatile 表示易变的变量，防止编译器优化
#define     __IO    volatile 
typedef unsigned int uint32_t;  
typedef unsigned short uint16_t;


// GPIO 寄存器结构体定义，结构体自然会占去空间，就像数组 
typedef struct
{ 
	__IO uint32_t CRL; 
	// ↑端口配置低寄存器，     地址偏移 0X00 
	__IO uint32_t CRH;      
	// ↑端口配置高寄存器，     地址偏移 0X04     
	__IO uint32_t IDR;       
	// ↑端口数据输入寄存器，   地址偏移 0X08
	__IO uint32_t ODR;       
	// ↑端口数据输出寄存器，   地址偏移 0X0C 
	__IO uint32_t BSRR;      
	// ↑端口位设置/清除寄存器，地址偏移 0X10 
  __IO uint32_t BRR;       
	// ↑端口位清除寄存器，     地址偏移 0X14 
	__IO uint32_t LCKR;      
	// ↑端口配置锁定寄存器，   地址偏移 0X18
} GPIO_TypeDef;

// RCC 寄存器结构体RCC是STM32的时钟控制器，可开启或关闭各总线的时钟，在使用各外设功能必须先开启其对应的时钟，没有这个时钟内部的各器件就不能运行。
//而RTC是STM32内部集成的一个简单的时钟(计时用)，如果不用就关闭，用的话先要通过RCC配置其时钟源，可看作是一个外设器件。
typedef struct    
{    
  __IO uint32_t CR;
	//↑时钟控制寄存器，偏移地址0x00    
  __IO uint32_t CFGR;
	//↑时间配置寄存器，偏移地址0x04    
  __IO uint32_t CIR;
	//↑时钟中断寄存器，偏移地址0x08    
  __IO uint32_t APB2RSTR;
	//↑APB2外设复位寄存器，偏移地址0x0c    
  __IO uint32_t APB1RSTR;
	//↑APB1外设复位寄存器，偏移地址0x10    
  __IO uint32_t AHBENR;
	//↑AHB外设时钟使能寄存器，偏移地址0x14    
  __IO uint32_t APB2ENR;
	//↑APB2外设时钟使能寄存器，偏移地址0x18    
  __IO uint32_t APB1ENR;
	//↑APB1外设时钟使能寄存器，偏移地址0x1c    
  __IO uint32_t BDCR;
	//↑备份域控制寄存器，偏移地址0x20    
  __IO uint32_t CSR;
	//↑控制/状态寄存器，偏移地址0x24    
} RCC_TypeDef;


/*外设基本地址*/ 
#define PERIPH_BASE         ((unsigned int)0x40000000) 
/*挂载到APB2总线基本地址*/ 
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x10000)
/* AHB 总线基本地址 */
#define AHBPERIPH_BASE      (PERIPH_BASE + 0x20000) 
/*GPIOX的接口的外设的基本地址*/ 
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400) 
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)

/*RCC的外设的地址*/ 	
#define RCC_BASE            (APB2PERIPH_BASE + 0x1000)
// GPIO 外设声明 
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE) 
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)  
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)  
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE) 
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)  
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)  
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)  
// RCC 外设声明 
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
/*RCC的APB2ENR时钟*/ 
#define RCC_APB2ENR        *(unsigned int*)(RCC_BASE+0x18)

