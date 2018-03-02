#include"stm32f10x.h"

void SystemInit(void) {}

int main(void)
{ // 通过寄存器结构体指针来控制寄存器
	// 开启 GPIOB 端口时钟
	RCC->APB2ENR |= (1<<3);
	
	//清空控制 PB0 的端口位
	GPIOB->CRL &= ~( 0x0F<< (4*0));
	// 配置 PB0 为通用推挽输出，速度为 10M
	GPIOB->CRL |= (1<<4*0);
	
	// PB0 输出 低电平 
	GPIOB->ODR |= (0<<0); 
	
}
//C语言语法在这里(*pPos).x 和 pPos->y 等价
