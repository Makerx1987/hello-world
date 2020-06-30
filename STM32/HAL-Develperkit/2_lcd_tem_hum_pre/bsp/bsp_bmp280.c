#include "bsp_bmp280.h"
#include "stm32l4xx.h"
#include "bsp_shtc1.h"
#include "string.h"
#include <math.h>

static bmp280_t p_bmp280;//校准参数


void BMP280_IO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
    s_transstart();
    SHTC1_IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    SHTC1_IIC_Send_Byte(reg);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答
	s_transstart();                
    SHTC1_IIC_Send_Byte((addr<<1)|1); //发送器件地址+读命令
    IIC_Wait_Ack();             //等待应答
    while(len)
    {
        if(len==1)*buf=IIC_Read_Byte(0);//读数据,发送nACK 
		else *buf=IIC_Read_Byte(1);		//读数据,发送ACK  
		len--;
		buf++;  
    }
    IIC_Stop();                 //产生一个停止条件
    return 0;       
}

//IIC写一个字节 
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Byte(uint8_t addr,uint8_t reg,uint8_t data)
{
    s_transstart();
    SHTC1_IIC_Send_Byte((addr<<1)|0); //发送器件地址+写命令
    if(IIC_Wait_Ack())          //等待应答
    {
        IIC_Stop();
        return 1;
    }
    SHTC1_IIC_Send_Byte(reg);         //写寄存器地址
    IIC_Wait_Ack();             //等待应答
    SHTC1_IIC_Send_Byte(data);        //发送数据
    if(IIC_Wait_Ack())          //等待ACK
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}

uint8_t MPU_Read_Byte(uint8_t addr,uint8_t reg)
{
    uint8_t res;
    s_transstart();
    SHTC1_IIC_Send_Byte((addr<<1)|0);		//发送器件地址+写命令
    IIC_Wait_Ack();             			//等待应答
    SHTC1_IIC_Send_Byte(reg);         		//写寄存器地址
    IIC_Wait_Ack();             			//等待应答
	
	s_transstart();                
    SHTC1_IIC_Send_Byte((addr<<1)|1);		//发送器件地址+读命令
    IIC_Wait_Ack();             //等待应答
    res=IIC_Read_Byte(0);		//读数据,发送nACK  
    IIC_Stop();                 //产生一个停止条件
    return res;  
}

uint8_t BMP280_Chack(void)
{
	uint16_t time = 0;
	uint8_t chip_ID = 0;
	while(time<1000)
	{
		chip_ID = BMP280_Read_Byte(BMP280_CHIPID_REG);
		if(chip_ID==0x57||chip_ID==0x58||chip_ID==0x59)break;//检测到芯片
		else time++;
		HAL_Delay(1);
	}
	if(time==1000)return 1;//未检测到芯片
	else 
	{
		p_bmp280.chip_id = chip_ID;//记录芯片ID
		return chip_ID;
	}
}


/**
  * @brief  BMP280软件复位，原因不明，函数使用之后芯片无法使用。
  * @param  None 
  * @retval 0：正常
  *         1：连接不正常
  */
uint8_t BMP280_SetSoftReset(void)
{
	if(BMP280_Write_Byte(BMP280_RESET_REG,BMP280_RESET_VALUE))return 1;
  else return 0;
}

/**
  * @brief  BMP280初始化
  * @param  None 
  * @retval 0：正常
  *         1：连接不正常
  */
uint8_t BMP280_Init(void)
{
	unsigned char cBmp280_id=0;
	
	BMP280_IO_init();
	cBmp280_id = BMP280_Chack();
	if( cBmp280_id== 1)					//BMP280检测芯片
	{
		printf("Can Not Get BMP280 ID\r\n");
		return 1;
	}
	else
	{
		printf("BMP280 ID:0x%x\r\n",cBmp280_id);
		//if(BMP280_SetSoftReset())return 2;//不要使用软件复位指令，使用之后导致bmp280无法使用
		if(BMP280_CalibParam())
			return 3;
		if(BMP280_SetPowerMode(BMP280_NORMAL_MODE))
			return 4;
		if(BMP280_SetWorkMode(BMP280_ULTRA_LOW_POWER_MODE))
			return 5;
		if(BMP280_SetStandbyDurn(BMP280_T_SB_0_5MS))
			return 6;
	}
	return 0;
}

/**
  * @brief  BMP280校准参数
  * @param  None 
  * @retval 0：正常
  *         1：连接不正常
  */
uint8_t BMP280_CalibParam(void)
{
	uint8_t a_data_uint8_t[24],res = 0;
	memset(a_data_uint8_t,0,24*sizeof(uint8_t));
	res =BMP280_Read_Len(BMP280_DIG_T1_LSB_REG,24,a_data_uint8_t);
	p_bmp280.calib_param.dig_T1 = (uint16_t)((((uint16_t)((uint8_t)a_data_uint8_t[1]))<<8)|a_data_uint8_t[0]);
	p_bmp280.calib_param.dig_T2 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[3]))<<8)|a_data_uint8_t[2]);
	p_bmp280.calib_param.dig_T3 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[5]))<<8)|a_data_uint8_t[4]);
	p_bmp280.calib_param.dig_P1 = (uint16_t)((((uint16_t)((uint8_t)a_data_uint8_t[7]))<<8)|a_data_uint8_t[6]);
	p_bmp280.calib_param.dig_P2 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[9]))<<8)|a_data_uint8_t[8]);
	p_bmp280.calib_param.dig_P3 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[11]))<<8)|a_data_uint8_t[10]);
	p_bmp280.calib_param.dig_P4 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[13]))<<8)|a_data_uint8_t[12]);
	p_bmp280.calib_param.dig_P5 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[15]))<<8)|a_data_uint8_t[14]);
	p_bmp280.calib_param.dig_P6 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[17]))<<8)|a_data_uint8_t[16]);
	p_bmp280.calib_param.dig_P7 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[19]))<<8)|a_data_uint8_t[18]);
	p_bmp280.calib_param.dig_P8 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[21]))<<8)|a_data_uint8_t[20]);
	p_bmp280.calib_param.dig_P9 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[23]))<<8)|a_data_uint8_t[22]);
	return res;
}

/**
  * @brief  设置BMP280电源工作模式
  * @param  mode：0,1,2,3 ，
    0：SLEEP_MODE，休眠模式
    1OR2：FORCED_MODE，读取一次后进入SLEEP_MODE.
    3：正常工作模式
  * @retval 0：正常
  *         1：连接不正常
  *         2：参数错误
  */
uint8_t BMP280_SetPowerMode(uint8_t mode)
{
	uint8_t v_mode_uint8_t = 0,res = 0;
	if (mode <= BMP280_NORMAL_MODE) 
	{
		v_mode_uint8_t = (p_bmp280.oversamp_temperature<<5)+(p_bmp280.oversamp_pressure<<2)+mode;
		res = BMP280_Write_Byte(BMP280_CTRLMEAS_REG,v_mode_uint8_t);
	} else res = 2;
	return res;
}

/**
  * @brief  设置BMP280过采样模式设置,可以自己增加模式
  * @param  mode：
			BMP280_ULTRA_LOW_POWER_MODE    ,
			BMP280_LOW_POWER_MODE          ,
			BMP280_STANDARD_RESOLUTION_MODE,
			BMP280_HIGH_RESOLUTION_MODE    ,
			BMP280_ULTRA_HIGH_RESOLUTION_MODE
  * @retval 0：正常
  *         1：连接不正常
  */
uint8_t BMP280_SetWorkMode(WORKING_MODE mode)
{
	uint8_t res = 0,v_data_uint8_t = 0;
	if (mode <= 0x04) 
	{
		v_data_uint8_t = BMP280_Read_Byte(BMP280_CTRLMEAS_REG);//读取出控制寄存器的值
		switch (mode)
		{
			case BMP280_ULTRA_LOW_POWER_MODE:
				p_bmp280.oversamp_temperature =BMP280_P_MODE_x1;
				p_bmp280.oversamp_pressure    =BMP280_P_MODE_x1;
			break;
			case BMP280_LOW_POWER_MODE:
				p_bmp280.oversamp_temperature =BMP280_P_MODE_x1;
				p_bmp280.oversamp_pressure    =BMP280_P_MODE_x2;
			break;
			case BMP280_STANDARD_RESOLUTION_MODE:
				p_bmp280.oversamp_temperature =BMP280_P_MODE_x1;
				p_bmp280.oversamp_pressure    =BMP280_P_MODE_x4;				
			break;
			case BMP280_HIGH_RESOLUTION_MODE:
				p_bmp280.oversamp_temperature =BMP280_P_MODE_x1;
				p_bmp280.oversamp_pressure    =BMP280_P_MODE_x8;
			break;
			case BMP280_ULTRA_HIGH_RESOLUTION_MODE:
				p_bmp280.oversamp_temperature =BMP280_P_MODE_x2;
				p_bmp280.oversamp_pressure    =BMP280_P_MODE_x16;
			break;
		}
		v_data_uint8_t = ((v_data_uint8_t & ~0xE0) | ((p_bmp280.oversamp_temperature<<5)&0xE0));
		v_data_uint8_t = ((v_data_uint8_t & ~0x1C) | ((p_bmp280.oversamp_pressure<<2)&0x1C));
		res = BMP280_Write_Byte(BMP280_CTRLMEAS_REG,v_data_uint8_t);
	} else res = 1;
	return res;
}

/**
  * @brief  闲置时长设置，即两次获取温度和气压的间隔时间长度
  * @param  standby_durn：
  *  BMP280_T_SB_0_5MS  ：0.5ms   
  *  BMP280_T_SB_62_5MS ：62.5ms  
  *  BMP280_T_SB_125MS  ：125ms   
  *  BMP280_T_SB_250MS  ：250ms   
  *  BMP280_T_SB_500MS  ：500ms   
  *  BMP280_T_SB_1000MS ：1000ms  
  *  BMP280_T_SB_2000MS ：2000ms  
  *  BMP280_T_SB_4000MS ：4000ms 
  * @retval 0：正常
  *         1：不正常
  */
uint8_t BMP280_SetStandbyDurn(BMP280_T_SB standby_durn)
{
	uint8_t v_data_uint8_t = 0;
	v_data_uint8_t = BMP280_Read_Byte(BMP280_CONFIG_REG);//读取出寄存器的值
	v_data_uint8_t = ((v_data_uint8_t & ~0xE0) | ((standby_durn<<5)&0xE0));//高3位
	return BMP280_Write_Byte(BMP280_CONFIG_REG,v_data_uint8_t);
}

/**
  * @brief  获取闲置时长，即两次获取温度和气压的间隔时间长度
  * @param  v_standby_durn_uint8_t：
  *  BMP280_T_SB_0_5MS  ：0.5ms   
  *  BMP280_T_SB_62_5MS ：62.5ms  
  *  BMP280_T_SB_125MS  ：125ms   
  *  BMP280_T_SB_250MS  ：250ms   
  *  BMP280_T_SB_500MS  ：500ms   
  *  BMP280_T_SB_1000MS ：1000ms  
  *  BMP280_T_SB_2000MS ：2000ms  
  *  BMP280_T_SB_4000MS ：4000ms 
  * @retval 0：正常
  *         1：不正常
  */
uint8_t BMP280_GetStandbyDurn(uint8_t* v_standby_durn_uint8_t)
{
	uint8_t res  = 0,v_data_uint8_t = 0;
	res = v_data_uint8_t = BMP280_Read_Byte(BMP280_CONFIG_REG);
	*v_standby_durn_uint8_t = (v_data_uint8_t>>5);
	return res;
}

/**
  * @brief  获取未补偿温度
  * @param  un_temp：数据指针
  * @retval 0：正常
  *         1：不正常
  */
uint8_t BMP280_ReadUncompTemperature(int32_t* un_temp)
{
	uint8_t a_data_uint8_tr[3]= {0,0,0},res=0;
	res = BMP280_Read_Len(BMP280_TEMPERATURE_MSB_REG,3,a_data_uint8_tr);
	*un_temp = (int32_t)((((uint32_t)(a_data_uint8_tr[0]))<<12)|(((uint32_t)(a_data_uint8_tr[1]))<<4)|((uint32_t)a_data_uint8_tr[2]>>4));
	return res;
}

/**
  * @brief  获取未补偿气压
  * @param  un_temp：数据指针
  * @retval 0：正常
  *         1：不正常
  */
uint8_t BMP280_ReadUncompPressuree(int32_t *un_press)
{
	uint8_t a_data_uint8_tr[3]= {0,0,0},res = 0;
	res = BMP280_Read_Len(BMP280_PRESSURE_MSB_REG,3,a_data_uint8_tr);
	*un_press = (int32_t)((((uint32_t)(a_data_uint8_tr[0]))<<12)|(((uint32_t)(a_data_uint8_tr[1]))<<4)|((uint32_t)a_data_uint8_tr[2]>>4));
	return res;
}

/**
  * @brief  获取未补偿气压和温度（一起获取，一次读取6个字节数据，比分开读取速度快一丢丢）
  * @param  un_press：未补偿气压数据指针，un_temp：未补偿温度数据指针
  * @retval 0：正常
  *         1：不正常
  */
uint8_t BMP280_ReadUncompPressureTemperature(int32_t *un_press, int32_t *un_temp)
{
	uint8_t a_data_uint8_t[6] = {0,0,0,0,0,0},res = 0;
	res = BMP280_Read_Len(BMP280_PRESSURE_MSB_REG,6,a_data_uint8_t);
	*un_press = (int32_t)((((uint32_t)(a_data_uint8_t[0]))<<12)|(((uint32_t)(a_data_uint8_t[1]))<<4)|((uint32_t)a_data_uint8_t[2]>>4));/*气压*/
	*un_temp = (int32_t)((((uint32_t)(a_data_uint8_t[3]))<<12)| (((uint32_t)(a_data_uint8_t[4]))<<4)|((uint32_t)a_data_uint8_t[5]>>4));/* 温度 */
	return res;
}

/**
  * @brief  获取真实的气压
  * @param  un_temp：未补偿温度数据
  * @retval int32_t：温度值，例如：2255代表22.55 DegC
  *        
  */
int32_t BMP280_CompensateTemperatureInt32(int32_t un_temp)
{
	int32_t v_x1_uint32_tr = 0;
	int32_t v_x2_uint32_tr = 0;
	int32_t temperature = 0;
	v_x1_uint32_tr = ((((un_temp>>3)-((int32_t)p_bmp280.calib_param.dig_T1<<1)))*((int32_t)p_bmp280.calib_param.dig_T2))>>11;
	v_x2_uint32_tr = (((((un_temp>>4)-((int32_t)p_bmp280.calib_param.dig_T1))*((un_temp>>4)-((int32_t)p_bmp280.calib_param.dig_T1)))>>12)*((int32_t)p_bmp280.calib_param.dig_T3))>>14;
	p_bmp280.calib_param.t_fine = v_x1_uint32_tr + v_x2_uint32_tr;
	temperature = (p_bmp280.calib_param.t_fine * 5 + 128)>> 8;
	return temperature;
}

/**
  * @brief  获取真实气压
  * @param  un_press：未补偿气压
  * @retval uint32_t：真实的气压值   
  */
uint32_t BMP280_CompensatePressureInt32(int32_t un_press)
{
	int32_t v_x1_uint32_tr = 0;
	int32_t v_x2_uint32_tr = 0;
	uint32_t v_pressure_uint32_t = 0;
	v_x1_uint32_tr = (((int32_t)p_bmp280.calib_param.t_fine)>> 1) - (int32_t)64000;
	v_x2_uint32_tr = (((v_x1_uint32_tr >> 2)* (v_x1_uint32_tr >> 2))>> 11)* ((int32_t)p_bmp280.calib_param.dig_P6);
	v_x2_uint32_tr = v_x2_uint32_tr + ((v_x1_uint32_tr *((int32_t)p_bmp280.calib_param.dig_P5))<< 1);
	v_x2_uint32_tr = (v_x2_uint32_tr >> 2)+ (((int32_t)p_bmp280.calib_param.dig_P4)<< 16);
	v_x1_uint32_tr = (((p_bmp280.calib_param.dig_P3*(((v_x1_uint32_tr>>2)*(v_x1_uint32_tr>>2))>>13))>>3)+((((int32_t)p_bmp280.calib_param.dig_P2)* v_x1_uint32_tr)>>1))>>18;
	v_x1_uint32_tr = ((((32768 + v_x1_uint32_tr))* ((int32_t)p_bmp280.calib_param.dig_P1))>> 15);
	v_pressure_uint32_t = (((uint32_t)(((int32_t)1048576) - un_press)- (v_x2_uint32_tr >> 12)))* 3125;
	if (v_pressure_uint32_t < 0x80000000)
		if (v_x1_uint32_tr != 0)
			v_pressure_uint32_t = (v_pressure_uint32_t<< 1)/ ((uint32_t)v_x1_uint32_tr);
		else return 0;
	else if (v_x1_uint32_tr != 0)
		v_pressure_uint32_t = (v_pressure_uint32_t / (uint32_t)v_x1_uint32_tr) * 2;
	else return 0;
	v_x1_uint32_tr = (((int32_t)p_bmp280.calib_param.dig_P9) * ((int32_t)(((v_pressure_uint32_t>> 3)* (v_pressure_uint32_t>> 3))>> 13)))>> 12;
	v_x2_uint32_tr = (((int32_t)(v_pressure_uint32_t >>	2))	* ((int32_t)p_bmp280.calib_param.dig_P8))>> 13;
	v_pressure_uint32_t = (uint32_t)((int32_t)v_pressure_uint32_t + ((v_x1_uint32_tr + v_x2_uint32_tr+ p_bmp280.calib_param.dig_P7)>> 4));
	return v_pressure_uint32_t;
}

/**
  * @brief  获取真实气压和温度
  * @param  press：真实的气压指针，temp：真实的温度指针
  * @retval 0：正常
  *         1：不正常
  */
uint8_t BMP280_ReadPressureTemperature(uint32_t *press, int32_t *temp)
{
	int32_t un_press = 0;
	int32_t un_temp = 0;
	uint8_t res=0;
	res = BMP280_ReadUncompPressureTemperature(&un_press,&un_temp);
	/* 读取真实的温度值和气压值*/
	*temp = BMP280_CompensateTemperatureInt32(un_temp);
	*press = BMP280_CompensatePressureInt32(un_press);
	return res;
}
