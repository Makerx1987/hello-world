#include "spi1.h"

//SPI_HandleTypeDef SPI1_Handler;  //SPI2句柄


/**
 * @brief	SPI2初始化代码，配置成主机模式
 *
 * @param   void
 *
 * @return  void
 */
void SPI1_Init(void)
{
//    SPI1_Handler.Instance=SPI1;                         //SPI2
//	
//    SPI1_Handler.Init.Mode=SPI_MODE_MASTER;             //设置SPI工作模式，设置为主模式
//    SPI1_Handler.Init.Direction=SPI_DIRECTION_1LINE;   //设置SPI单向或者双向的数据模式:SPI设置为双线模式
//    SPI1_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //设置SPI的数据大小:SPI发送接收8位帧结构
//    SPI1_Handler.Init.CLKPolarity=SPI_POLARITY_LOW;    //串行同步时钟的空闲状态为高电平
//    SPI1_Handler.Init.CLKPhase=SPI_PHASE_1EDGE;         //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
//    SPI1_Handler.Init.NSS=SPI_NSS_HARD_OUTPUT;                 //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
//    SPI1_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;//定义波特率预分频的值:波特率预分频值为2
//    SPI1_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
//    SPI1_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //关闭TI模式
//    SPI1_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//关闭硬件CRC校验
//    SPI1_Handler.Init.CRCPolynomial=7;                  //CRC值计算的多项式
//	SPI1_Handler.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
//	SPI1_Handler.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
//	
//    if(HAL_SPI_Init(&SPI1_Handler))
//		while(1);
    
//    __HAL_SPI_ENABLE(&SPI1_Handler);
	
	
}

/**
 * @brief	SPI2底层驱动，时钟使能，引脚配置
 *
 * @param   hspi	SPI句柄
 *
 * @return  void
 */
//void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//{
//    GPIO_InitTypeDef GPIO_Initure;
//    
//    __HAL_RCC_GPIOB_CLK_ENABLE();       //使能GPIOB时钟
//    __HAL_RCC_SPI2_CLK_ENABLE();        //使能SPI2时钟

//    //PB13.15
//    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_15;
//    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //复用推挽输出
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;   //80Mhz           
//    GPIO_Initure.Alternate=GPIO_AF5_SPI2;           //PB13.15复用为SPI2
//    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
//}

/**
 * @brief	SPI2 读写一个字节
 *
 * @param   TxData	要写入的字节
 *
 * @return  uint8_t		读取到的字节
 */


/**
 * @brief	SPI2 写入一个字节
 *
 * @param   TxData	要写入的字节
 * @param   size	写入字节大小
 *
 * @return  uint8_t		0:写入成功,其他:写入失败
 */
















