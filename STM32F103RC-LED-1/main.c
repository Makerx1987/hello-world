#include"stm32f10x.h"

void SystemInit(void) {}

int main(void)
{ // ���� 1<<4 = 0x04 ��Ŀ��LED��ʱ��λ
  RCC_APB2ENR |= (1<<4); 
  // ����~( 0x0F<<8 ) = ~ 0x 0F00 ��������
  // ��տ��� PC2 �Ķ˿�λ 
  GPIOB_CRL &= ~( 0x0F<< (4*2));
  // ���� PC2 Ϊͨ������������ٶ�Ϊ 10M 	
  GPIOB_CRL |= (1<<4*2); 
	
  // PC2 ��� �͵�ƽ 
  GPIOB_ODR &= ~(1<<2); 	
}
