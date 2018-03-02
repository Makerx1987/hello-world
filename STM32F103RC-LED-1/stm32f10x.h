/*外设基本地址*/ 
#define PERIPH_BASE         ((unsigned int)0x40000000) 
/*总线基本地址，挂载到APB2*/ 
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x10000)
/*GPIOB的接口的外设的基本地址*/ 
#define GPIOB_BASE          (APB2PERIPH_BASE + 0x0C00)
/*各种被指向特殊内存的宏名（也就是寄存器）的地址，定义为指针*/ 
#define GPIOB_CRL           *(unsigned int*)(GPIOB_BASE+0x00) 
#define GPIOB_CRH           *(unsigned int*)(GPIOB_BASE+0x04) 
#define GPIOB_IDR           *(unsigned int*)(GPIOB_BASE+0x08) 
#define GPIOB_ODR           *(unsigned int*)(GPIOB_BASE+0x0C)
#define GPIOB_BSRR          *(unsigned int*)(GPIOB_BASE+0x10)
#define GPIOB_BRR           *(unsigned int*)(GPIOB_BASE+0x14)
#define GPIOB_LCKR          *(unsigned int*)(GPIOB_BASE+0x18)
/*RCC的外设的地址*/ 	
#define RCC_BASE            (APB2PERIPH_BASE + 0x1000)
/*RCC的APB2ENR时钟*/ 
#define RCC_APB2ENR        *(unsigned int*)(RCC_BASE+0x18)

