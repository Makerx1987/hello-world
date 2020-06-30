#include "main.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_led.h"
#include "bsp_shtc1.h"
#include "bsp_bmp280.h"



char buf1[16];
char buf2[16];
char buf3[16];

UART_HandleTypeDef hlpuart1;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);

unsigned int shtc1id=0;

#pragma import(__use_no_semihosting)    

//标准库需要的支持函数                 
struct __FILE 
{
	int handle; 
};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x)
{
	x = x; 
}
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&hlpuart1,(uint8_t *)(&ch),1,1000);
	//while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	//{}
	return ch;
}


int main(void)
{
	unsigned char color = 0;
	value humi_val,temp_val;
	float dew_point;
	unsigned char error,checksum;
	unsigned int i;
	uint32_t bmp280_press;
	int32_t bmp280_temperature;
	unsigned char cBmp280_init_flag = 0;
	float sht1c_temperature = 0;
	float sht1c_humidity = 0;
	
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_LPUART1_UART_Init();
	LED_GPIO_Config();
	LCD_Init();
	
	BSP_LCD_Clear(0);

//	Display_ALIENTEK_LOGO(0,0);
//	LCD_Clear(RED);
//	LCD_ShowString(0, 60, 240, 32, 32, "Pioneer");
//	LCD_ShowString(0, 100, 240, 32, 32, "STM32L496VGT6");
//	LCD_ShowString(0, 140, 240, 24, 24, "TFTLCD TEST 240*240");
//	LCD_ShowString(0, 200, 240, 32, 32, "2019/09/09");
	
//	LCD_ShowNum(0,40,123456789,9,24);
	
	//HAL_Delay(50);


	//BMP280_IO_init();
	cBmp280_init_flag = BMP280_Init();
//	if(cBmp280_init_flag == 0)
//	{
//		printf("BMP280 Init OK\r\n");
//	}
//	else
//	{
//		printf("BMP280 Init Error:%d\r\n",cBmp280_init_flag);
//	}
//	if(BMP280_CalibParam() == 0)
//	{
//		printf("BMP280 Calibration OK\r\n");
//	}
	s_connectionreset();
	shtc1id = SHTC1_ReadID();
	printf("SHTC1  ID:0x%x\r\n",shtc1id);
	
	
//	BMP280_ReadPressureTemperature(&press,&temperature);
	while (1)
	{
		//HAL_UART_Transmit(&hlpuart1,(uint8_t *)"aaa\r\n",5,1000);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_Delay(100);

		if(BMP280_ReadPressureTemperature(&bmp280_press,&bmp280_temperature) == 0)
		{
			printf("BMP280:  pressure:%dPa  temperature:%.02f°C\r\n",bmp280_press,bmp280_temperature/100.0);
		}
		
		if(SHTC1_GetTempAndHumiPolling(&sht1c_temperature,&sht1c_humidity) == 0 )
		{
			printf("SHT1C:  temperature:%.02f°C  humidity:%.02f%%\r\n",sht1c_temperature,sht1c_humidity);
		}
		sprintf(buf1," %d Pa",bmp280_press);
		sprintf(buf2," %.02f *C",bmp280_temperature/200.0+sht1c_temperature/2);
		sprintf(buf3," %.02f %%",sht1c_humidity);
		LCD_ShowString(0, 00, 240, 240, 32, "Thermograph");
		LCD_ShowString(0, 32, 240, 240, 32, "pressure:");
		LCD_ShowString(0, 96, 240, 240, 32, "temperature:");
		LCD_ShowString(0, 160, 240, 240, 32, "humidity:");
		LCD_ShowString(0, 64, 240, 240, 32, buf1);
		LCD_ShowString(0, 128, 240, 240, 32, buf2);
		LCD_ShowString(0, 192, 240, 240, 32, buf3);
		
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_Delay(100);
//	    switch(color % 12)
//        {
//            case 0:
//                LCD_Clear(WHITE);
//                break;
//            case 1:
//                LCD_Clear(BLACK);
//                break;
//            case 2:
//                LCD_Clear(BLUE);
//                break;
//            case 3:
//                LCD_Clear(RED);
//                break;
//            case 4:
//                LCD_Clear(MAGENTA);
//                break;
//            case 5:
//                LCD_Clear(GREEN);
//                break;
//            case 6:
//                LCD_Clear(CYAN);
//                break;
//            case 7:
//                LCD_Clear(YELLOW);
//                break;
//            case 8:
//                LCD_Clear(BRRED);
//                break;
//            case 9:
//                LCD_Clear(GRAY);
//                break;
//            case 10:
//                LCD_Clear(LGRAY);
//                break;
//            case 11:
//                LCD_Clear(BROWN);
//                break;
//            default :
//                color = 0;
//                break;
//        }

//        Display_ALIENTEK_LOGO(0, 0);
//        POINT_COLOR = RED;
//        BACK_COLOR = WHITE;
//        LCD_ShowString(0, 100, 240, 32, 32, "Pandora STM32L4");
//        LCD_ShowString(0, 140, 240, 24, 24, "TFTLCD TEST 240*240");

//        POINT_COLOR = WHITE;
//        BACK_COLOR = BLUE;
//        LCD_ShowString(0, 170, 240, 16, 16, "ATOM@ALIENTEK");
//        LCD_ShowString(0, 200, 240, 12, 12, "2018/10/28");
//        color++;
		
		
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

//  /** Initializes the CPU, AHB and APB busses clocks 
//  */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
//  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
//  RCC_OscInitStruct.MSICalibrationValue = 0;
//  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Initializes the CPU, AHB and APB busses clocks 
//  */
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1;
//  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
//  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure the main internal regulator output voltage 
//  */
//  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
//  {
//    Error_Handler();
//  }

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	/**Configure LSE Drive Capability 
	*/
	HAL_PWR_EnableBkUpAccess();

	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

	/**Initializes the CPU, AHB and APB busses clocks 
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_LSE
							  |RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 40;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	while(1);
	}

	/**Initializes the CPU, AHB and APB busses clocks 
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
	while(1);
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3
							  |RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_SAI2
							  |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_I2C3
							  |RCC_PERIPHCLK_I2C4|RCC_PERIPHCLK_USB
							  |RCC_PERIPHCLK_SDMMC1|RCC_PERIPHCLK_ADC;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
	PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	PeriphClkInit.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
	PeriphClkInit.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
	PeriphClkInit.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLLSAI1;
	PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
	PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLSAI1;
	PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
	PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
	PeriphClkInit.PLLSAI1.PLLSAI1N = 24;
	PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV2;
	PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
	PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
	PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK|RCC_PLLSAI1_48M2CLK
							  |RCC_PLLSAI1_ADC1CLK;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
	while(1);
	}

	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI48, RCC_MCODIV_2);

	/**Configure the main internal regulator output voltage 
	*/
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
	while(1);
	}

	/**Configure the Systick interrupt time 
	*/
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/8000);

	/**Configure the Systick 
	*/
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);

	/**Enable MSI Auto calibration 
	*/
	HAL_RCCEx_EnableMSIPLLMode();

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
  hlpuart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  hlpuart1.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//  /*Configure GPIO pins : PB10 PB11 */
	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF8_LPUART1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
