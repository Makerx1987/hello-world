#include"stm32f10x.h"

void SystemInit(void) {}

int main(void)
{ // 这里 1<<4 = 0x04 是目标LED的时钟位
  RCC_APB2ENR |= (1<<4); 
  // 这里~( 0x0F<<8 ) = ~ 0x 0F00 用来清零
  // 清空控制 PC2 的端口位 
  GPIOB_CRL &= ~( 0x0F<< (4*2));
  // 配置 PC2 为通用推挽输出，速度为 10M 	
  GPIOB_CRL |= (1<<4*2); 
	
  // PC2 输出 低电平 
  GPIOB_ODR &= ~(1<<2); 	
}
