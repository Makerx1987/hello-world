#include "spi1.h"

//SPI_HandleTypeDef SPI1_Handler;  //SPI2���


/**
 * @brief	SPI2��ʼ�����룬���ó�����ģʽ
 *
 * @param   void
 *
 * @return  void
 */
void SPI1_Init(void)
{
//    SPI1_Handler.Instance=SPI1;                         //SPI2
//	
//    SPI1_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
//    SPI1_Handler.Init.Direction=SPI_DIRECTION_1LINE;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
//    SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
//    SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_LOW;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
//    SPI1_Handler.Init.CLKPhase=SPI_PHASE_1EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
//    SPI1_Handler.Init.NSS=SPI_NSS_HARD_OUTPUT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
//    SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ2
//    SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
//    SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
//    SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
//    SPI1_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
//	SPI1_Handler.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
//	SPI1_Handler.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
//	
//    if(HAL_SPI_Init(&SPI1_Handler))
//		while(1);
    
//    __HAL_SPI_ENABLE(&SPI1_Handler);
	
	
}

/**
 * @brief	SPI2�ײ�������ʱ��ʹ�ܣ���������
 *
 * @param   hspi	SPI���
 *
 * @return  void
 */
//void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//{
//    GPIO_InitTypeDef GPIO_Initure;
//    
//    __HAL_RCC_GPIOB_CLK_ENABLE();       //ʹ��GPIOBʱ��
//    __HAL_RCC_SPI2_CLK_ENABLE();        //ʹ��SPI2ʱ��

//    //PB13.15
//    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_15;
//    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�����������
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //����
//    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;   //80Mhz           
//    GPIO_Initure.Alternate=GPIO_AF5_SPI2;           //PB13.15����ΪSPI2
//    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
//}

/**
 * @brief	SPI2 ��дһ���ֽ�
 *
 * @param   TxData	Ҫд����ֽ�
 *
 * @return  uint8_t		��ȡ�����ֽ�
 */


/**
 * @brief	SPI2 д��һ���ֽ�
 *
 * @param   TxData	Ҫд����ֽ�
 * @param   size	д���ֽڴ�С
 *
 * @return  uint8_t		0:д��ɹ�,����:д��ʧ��
 */
















