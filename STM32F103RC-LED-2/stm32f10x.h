//�Ĵ�����ֵ������оƬ�����Զ����ĵģ���ʹ CPU û��ִ�г���Ҳ�п��ܷ����仯  
//�������п��ܻ��û��ִ�г���ı��������Ż��������� volatile �����μĴ�������
//volatile ��ʾ�ױ�ı�������ֹ�������Ż�
#define     __IO    volatile 
typedef unsigned int uint32_t;  
typedef unsigned short uint16_t;


// GPIO �Ĵ����ṹ�嶨�壬�ṹ����Ȼ��ռȥ�ռ䣬�������� 
typedef struct
{ 
	__IO uint32_t CRL; 
	// ���˿����õͼĴ�����     ��ַƫ�� 0X00 
	__IO uint32_t CRH;      
	// ���˿����ø߼Ĵ�����     ��ַƫ�� 0X04     
	__IO uint32_t IDR;       
	// ���˿���������Ĵ�����   ��ַƫ�� 0X08
	__IO uint32_t ODR;       
	// ���˿���������Ĵ�����   ��ַƫ�� 0X0C 
	__IO uint32_t BSRR;      
	// ���˿�λ����/����Ĵ�������ַƫ�� 0X10 
  __IO uint32_t BRR;       
	// ���˿�λ����Ĵ�����     ��ַƫ�� 0X14 
	__IO uint32_t LCKR;      
	// ���˿����������Ĵ�����   ��ַƫ�� 0X18
} GPIO_TypeDef;

// RCC �Ĵ����ṹ��RCC��STM32��ʱ�ӿ��������ɿ�����رո����ߵ�ʱ�ӣ���ʹ�ø����蹦�ܱ����ȿ������Ӧ��ʱ�ӣ�û�����ʱ���ڲ��ĸ������Ͳ������С�
//��RTC��STM32�ڲ����ɵ�һ���򵥵�ʱ��(��ʱ��)��������þ͹رգ��õĻ���Ҫͨ��RCC������ʱ��Դ���ɿ�����һ������������
typedef struct    
{    
  __IO uint32_t CR;
	//��ʱ�ӿ��ƼĴ�����ƫ�Ƶ�ַ0x00    
  __IO uint32_t CFGR;
	//��ʱ�����üĴ�����ƫ�Ƶ�ַ0x04    
  __IO uint32_t CIR;
	//��ʱ���жϼĴ�����ƫ�Ƶ�ַ0x08    
  __IO uint32_t APB2RSTR;
	//��APB2���踴λ�Ĵ�����ƫ�Ƶ�ַ0x0c    
  __IO uint32_t APB1RSTR;
	//��APB1���踴λ�Ĵ�����ƫ�Ƶ�ַ0x10    
  __IO uint32_t AHBENR;
	//��AHB����ʱ��ʹ�ܼĴ�����ƫ�Ƶ�ַ0x14    
  __IO uint32_t APB2ENR;
	//��APB2����ʱ��ʹ�ܼĴ�����ƫ�Ƶ�ַ0x18    
  __IO uint32_t APB1ENR;
	//��APB1����ʱ��ʹ�ܼĴ�����ƫ�Ƶ�ַ0x1c    
  __IO uint32_t BDCR;
	//����������ƼĴ�����ƫ�Ƶ�ַ0x20    
  __IO uint32_t CSR;
	//������/״̬�Ĵ�����ƫ�Ƶ�ַ0x24    
} RCC_TypeDef;


/*���������ַ*/ 
#define PERIPH_BASE         ((unsigned int)0x40000000) 
/*���ص�APB2���߻�����ַ*/ 
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x10000)
/* AHB ���߻�����ַ */
#define AHBPERIPH_BASE      (PERIPH_BASE + 0x20000) 
/*GPIOX�Ľӿڵ�����Ļ�����ַ*/ 
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400) 
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)

/*RCC������ĵ�ַ*/ 	
#define RCC_BASE            (APB2PERIPH_BASE + 0x1000)
// GPIO �������� 
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE) 
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)  
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)  
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE) 
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)  
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)  
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)  
// RCC �������� 
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
/*RCC��APB2ENRʱ��*/ 
#define RCC_APB2ENR        *(unsigned int*)(RCC_BASE+0x18)

