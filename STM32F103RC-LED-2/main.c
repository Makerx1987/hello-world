#include"stm32f10x.h"

void SystemInit(void) {}

int main(void)
{ // ͨ���Ĵ����ṹ��ָ�������ƼĴ���
	// ���� GPIOB �˿�ʱ��
	RCC->APB2ENR |= (1<<3);
	
	//��տ��� PB0 �Ķ˿�λ
	GPIOB->CRL &= ~( 0x0F<< (4*0));
	// ���� PB0 Ϊͨ������������ٶ�Ϊ 10M
	GPIOB->CRL |= (1<<4*0);
	
	// PB0 ��� �͵�ƽ 
	GPIOB->ODR |= (0<<0); 
	
}
//C�����﷨������(*pPos).x �� pPos->y �ȼ�
