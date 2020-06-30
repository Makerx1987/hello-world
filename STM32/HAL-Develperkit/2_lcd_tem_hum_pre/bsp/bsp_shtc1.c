#include <math.h>
#include <stdio.h>
#include "stm32l4xx.h"
#include "bsp_shtc1.h"
#include "stdio.h"




//#define HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA) P1_1
//#define SCK P1_0

#define noACK 0
#define ACK 1

//adr command r/w
#define STATUS_REG_W	0x06 //000 0011 0
#define STATUS_REG_R	0x07 //000 0011 1
#define MEASURE_TEMP	0x03 //000 0001 1
#define MEASURE_HUMI	0x05 //000 0010 1
#define RESET			0x1e //000 1111 0

#define SHTC1_DATA  GPIO_PIN_14
#define SHTC_SCK	GPIO_PIN_13

#define SDA_MODE_OUTPUT 	1
#define SDA_MODE_INPUT		0
#define SHTC1_IIC_ADDRESS   0x70
#define SHTC1_IIC_WRITE_COMMAND  0X71
#define SHTC1_IIC_READ_COMMAND   0X70

void SHTC1_SCL_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
}


void SHTC1_SDA_MODE_SET(uint16_t GPIO_Pin,uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = GPIO_Pin;
	
	if( 1 == mode)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	}
	else
	{
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	}
	GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void SHTC1_IIC_NOP(void)//大约4us
{
	int i=0;
	for(i=0;i<160;i++)
	{
	}
}

void SHTC1_IIC_NOP_1us(void)//大约1us
{
	int i=0;
	for(i=0;i<80;i++)
	{
	}
}

void SHTC1_IIC_NOP_2us(void)//大约1us
{
	int i=0;
	for(i=0;i<3;i++)
	{
	}
}


//IIC_Start()
void s_transstart(void)
{
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
    HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_SET);
	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, GPIO_PIN_RESET);
	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
//	SHTC1_IIC_NOP();
}

void IIC_Stop(void)
{
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_RESET);
 	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_SET);
	SHTC1_IIC_NOP();
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint32_t IIC_Wait_Ack(void)
{
	uint32_t ucErrTime=0;
	
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_INPUT);
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_SET);
	SHTC1_IIC_NOP_1us();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET);
	SHTC1_IIC_NOP_1us();
	while(HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA))
	{
		ucErrTime++;
		if(ucErrTime>80000)
		{
			IIC_Stop();
			return ucErrTime;
		}
		else
		{
			//ucErrTime = 0;
		}
	}
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
	return ucErrTime;
} 


//产生ACK应答
void IIC_Ack(void)
{
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
	
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_RESET);
	
	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET);
	
	SHTC1_IIC_NOP();
	SHTC1_IIC_NOP();
	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_SET);
	
	SHTC1_IIC_NOP();
	SHTC1_IIC_NOP();
	SHTC1_IIC_NOP();
	SHTC1_IIC_NOP();
	SHTC1_IIC_NOP();
}


//不产生ACK应答		    
void IIC_NAck(void)
{
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_SET);
	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET);
	SHTC1_IIC_NOP();
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
}


void SHTC1_IIC_Send_Byte(uint8_t data)
{
	uint8_t i;
	
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
	
	for (i=0x80;i>0;i/=2)
	{
		if (i & data) HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_RESET);
		SHTC1_IIC_NOP_2us();
		HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET);
		SHTC1_IIC_NOP_2us();
		HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
		SHTC1_IIC_NOP_2us();
	}
}


uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_INPUT);
    for(i=0;i<8;i++ )
	{
        HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_RESET);
        SHTC1_IIC_NOP_2us();
		HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET);
        receive<<=1;
		SHTC1_IIC_NOP_2us();
        if(HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA))receive++;   
		SHTC1_IIC_NOP_1us();
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
	
    return receive;
}




void SHTC1_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{
	s_transstart();
	SHTC1_IIC_Send_Byte(SHTC1_IIC_ADDRESS);
}

#define POLYNOMIAL 0x131 	// CRC     P(x) = x^8 + x^5 + x^4 + 1 = 100110001
unsigned char SHTC1_CheckCrc(unsigned char data[], unsigned char nbrOfBytes, unsigned char checksum)
{
	unsigned char bit;
	unsigned char crc = 0xFF;
	unsigned char byteCtr;

	for(byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++)
	{
		crc ^= (data[byteCtr]);
		for(bit = 8; bit > 0; --bit)
		{
			if(crc & 0x80) crc = (crc << 1) ^ POLYNOMIAL;
			else crc = (crc << 1);
		}
	}

	if(crc != checksum)
	{
		return 0X01;
	}
	else
	{
		return 0X00;
	}
}



uint8_t SHTC1_ReadOneByte(uint16_t ReadAddr)
{
	unsigned char temp;
	s_transstart();
	SHTC1_IIC_Send_Byte(0XE1);
	IIC_Wait_Ack();
	SHTC1_IIC_Send_Byte(0XC8);
	IIC_Wait_Ack();
	
	s_transstart();
	SHTC1_IIC_Send_Byte(0XE0);
	IIC_Wait_Ack();
	
	temp=IIC_Read_Byte(0);
	temp=temp;
	
	return 0;
}

unsigned char SHTC1_Read2BytesAndCrc(unsigned short *data)
{
	unsigned char error;
	unsigned char bytes[2];
	unsigned char checksum;
	
	bytes[0] = IIC_Read_Byte(1);
	bytes[1] = IIC_Read_Byte(1);
	checksum = IIC_Read_Byte(1);
	error = SHTC1_CheckCrc(bytes, 2, checksum);
	
	*data = (bytes[0] << 8) | bytes[1];
	return error;
}

uint16_t SHTC1_ReadID(void)
{
	unsigned char idbuff[2]={0};
	unsigned char checksum = 0;
	unsigned short SHTC1_ID = 0;
	unsigned char error=0;
	
	s_transstart();
	SHTC1_IIC_Send_Byte(0xe0);					//写
	IIC_Wait_Ack();
	SHTC1_IIC_Send_Byte(0xef);
	IIC_Wait_Ack();
	SHTC1_IIC_Send_Byte(0xc8);
	IIC_Wait_Ack();

	s_transstart();
	SHTC1_IIC_Send_Byte(0xe1);					//读
	IIC_Wait_Ack();
	
	/*
	idbuff[0] = IIC_Read_Byte(1);
	idbuff[1] = IIC_Read_Byte(1);
	checksum  = IIC_Read_Byte(1);
	error = SHTC1_CheckCrc(idbuff , 2 ,checksum );
	*/
	error = SHTC1_Read2BytesAndCrc(&SHTC1_ID);
	IIC_Stop();
	
	if(error)
	{
		return 0;
	}
	else
	{
		return SHTC1_ID;
	}
	
	
}

unsigned char SHTC1_GetTempAndHumiPolling(float *temp, float *humi)
{
	unsigned char error;
	unsigned char maxPolling = 20;
	unsigned short rawValueTemp;
	unsigned short rawValueHumi;
	
	s_transstart();
	SHTC1_IIC_Send_Byte(0xe0);					//写
	error = IIC_Wait_Ack();
	SHTC1_IIC_Send_Byte(0x78);
	error += IIC_Wait_Ack();
	SHTC1_IIC_Send_Byte(0x66);
	error += IIC_Wait_Ack();

	if(error == 0)
	{
		while(maxPolling--)
		{
			s_transstart();
			SHTC1_IIC_Send_Byte(0xe1);					//读
			error = IIC_Wait_Ack();
			
			if(error == 0)
			{
				break;
			}
			HAL_Delay(1000);
		}
	
		if(error == 0)
		{
			error |= SHTC1_Read2BytesAndCrc(&rawValueTemp);
			error |= SHTC1_Read2BytesAndCrc(&rawValueHumi);
			
		}
	}
	IIC_Stop();

	if(error == 0)
	{
		*temp = SHTC1_CalcTemperature(rawValueTemp);
		*humi = SHTC1_CalcHumidity(rawValueHumi);
	}
	return error;
}


float SHTC1_CalcTemperature(unsigned short rawValue)
{
	return 175 * (float)rawValue / 65536 - 45;
}

float SHTC1_CalcHumidity(unsigned short rawValue)
{
	return 100 * (float)rawValue / 65536;
}

//----------------------------------------------------------------------------------
char s_write_byte(unsigned char value)
{
	unsigned char i,error=0;
	
    SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
	
	for (i=0x80;i>0;i/=2) //shift bit for masking
	{
		if (i & value) HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_SET); //masking value with i , write to SENSI-BUS
		else HAL_GPIO_WritePin(GPIOB,SHTC1_DATA,GPIO_PIN_RESET);
		SHTC1_IIC_NOP(); //observe setup time
		HAL_GPIO_WritePin(GPIOB,SHTC_SCK,GPIO_PIN_SET); //clk for SENSI-BUS
		SHTC1_IIC_NOP();
//        SHTC1_IIC_NOP();//仿照原子
//        SHTC1_IIC_NOP(); //pulswith approx. 5 us//仿照原子
		HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
		SHTC1_IIC_NOP(); //observe hold time
	}
	
	HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, GPIO_PIN_SET); //release HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA)-line
	SHTC1_IIC_NOP(); //observe setup time
    SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_INPUT);
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_SET); //clk #9 for ack
	SHTC1_IIC_NOP();
	error=HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA); //check ack (HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA) will be pulled down by SHT11)
	HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
	SHTC1_IIC_NOP();
	
	return error; //error=1 in case of no acknowledge
}

//----------------------------------------------------------------------------------
char s_read_byte(unsigned char ack)
{
    unsigned char i,val=0;
    
    SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
    HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, GPIO_PIN_SET); //release HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA)-line
    for (i=0x80;i>0;i/=2) //shift bit for masking
    {
        HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_SET); //clk for SENSI-BUS
		SHTC1_IIC_NOP();
        SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_INPUT);
        if (HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA)) val=(val | i); //read bit
        HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
		SHTC1_IIC_NOP();
    }
    SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
    HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, (GPIO_PinState)(!ack)); //in case of "ack==1" pull down HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA)-Line
    SHTC1_IIC_NOP(); //observe setup time
    HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_SET); //clk #9 for ack
    SHTC1_IIC_NOP();
    SHTC1_IIC_NOP();
    SHTC1_IIC_NOP(); //pulswith approx. 5 us
    HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
    SHTC1_IIC_NOP(); //observe hold time
    HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, GPIO_PIN_SET);; //release HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA)-line
    return val;
}



//----------------------------------------------------------------------------------
void s_connectionreset(void)
{
    unsigned char i;
    SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_OUTPUT);
    HAL_GPIO_WritePin(GPIOB,SHTC1_DATA, GPIO_PIN_SET);;
    HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET); //Initial state
	SHTC1_IIC_NOP();
    for(i=0;i<9;i++) //9 SCK cycles
    {
        HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_SET);
		SHTC1_IIC_NOP();
        HAL_GPIO_WritePin(GPIOB,SHTC_SCK, GPIO_PIN_RESET);
		SHTC1_IIC_NOP();
    }
    s_transstart(); //transmission start
}

//----------------------------------------------------------------------------------
char s_softreset(void)
{
    unsigned char error=0;
    s_connectionreset(); //reset communication
    error+=s_write_byte(RESET); //send RESET-command to sensor
    return error; //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum)
{
    unsigned char error=0;
    s_transstart(); //transmission start
    error=s_write_byte(STATUS_REG_R); //send command to sensor
    *p_value=s_read_byte(ACK); //read status register (8-bit)
    *p_checksum=s_read_byte(noACK); //read checksum (8-bit)
    return error; //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_write_statusreg(unsigned char *p_value)
{
    unsigned char error=0;
    s_transstart();							//transmission start
    error+=s_write_byte(STATUS_REG_W);		//send command to sensor
    error+=s_write_byte(*p_value);			//send value of status register
    return error;							//error>=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
{
    unsigned char error=0;
    unsigned int i;
    
    s_transstart();												//transmission start
	SHTC1_IIC_Send_Byte(0xe0);
    switch(mode)
    {															//send command to sensor
        case TEMP : error+=s_write_byte(MEASURE_TEMP); break;
        case HUMI : error+=s_write_byte(MEASURE_HUMI); break;
        default : break;
    }
	
	SHTC1_SDA_MODE_SET(SHTC1_DATA, SDA_MODE_INPUT);
    for (i=0;i<65535;i++)
	{
		if(HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA)==0) break; //wait until sensor has finished the measurement
	}
    if(HAL_GPIO_ReadPin(GPIOB,SHTC1_DATA))
	{
		error+=1; // or timeout (~2 sec.) is reached
	}
    *(p_value) =s_read_byte(ACK); //read the first byte (MSB)
    *(p_value+1)=s_read_byte(ACK); //read the second byte (LSB)
    *p_checksum =s_read_byte(noACK); //read checksum
    return error;
}

//----------------------------------------------------------------------------------
void calc_sth11(float *p_humidity ,float *p_temperature)
{
    const float C1=-2.0468; // for 12 Bit RH
    const float C2=+0.0367; // for 12 Bit RH
    const float C3=-0.0000015955; // for 12 Bit RH
    const float T1=+0.01; // for 12 Bit RH
    const float T2=+0.00008; // for 12 Bit RH
    float rh=*p_humidity; // rh: Humidity [Ticks] 12 Bit
    float t=*p_temperature; // t: Temperature [Ticks] 14 Bit
    float rh_lin; // rh_lin: Humidity linear
    float rh_true; // rh_true: Temperature compensated humidity
    float t_C; // t_C : Temperature [癈]
    t_C=t*0.01f - 40.1f; //calc. temperature[癈]from 14 bit temp.ticks @5V
    rh_lin=C3*rh*rh + C2*rh + C1; //calc. humidity from ticks to [%RH]
    rh_true=(t_C-25)*(T1+T2*rh)+rh_lin; //calc. temperature compensated humidity [%RH]
    if(rh_true>100)rh_true=100; //cut if the value is outside of
    if(rh_true<0.1f)rh_true=0.1f; //the physical possible range
    *p_temperature=t_C; //return temperature [癈]
    *p_humidity=rh_true; //return humidity[%RH]
}

//--------------------------------------------------------------------
float calc_dewpoint(float h,float t)
{
    float k=0.0f,dew_point=0.0f ;
//    k = (log10(h)-2)/0.4343f + (17.62f*t)/(243.12f+t);
    dew_point = 243.12f*k/(17.62f-k);
    return dew_point;
}


