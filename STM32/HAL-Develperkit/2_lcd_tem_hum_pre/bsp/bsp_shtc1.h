#ifndef __BSP_SHTC1_H
#define __BSP_SHTC1_H

typedef union
{
	unsigned int i;
	float f;
}value;

enum {TEMP,HUMI};

void SHTC1_SCL_init(void);
void SHTC1_SDA_MODE_SET(uint16_t GPIO_Pin,uint8_t mode);
char s_write_byte(unsigned char value);
char s_read_byte(unsigned char ack);
void s_transstart(void);
void s_connectionreset(void);
char s_softreset(void);
char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum);
char s_write_statusreg(unsigned char *p_value);
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
void calc_sth11(float *p_humidity ,float *p_temperature);
float calc_dewpoint(float h,float t);


uint16_t SHTC1_ReadID(void);
unsigned char SHTC1_GetTempAndHumiPolling(float *temp, float *humi);
float SHTC1_CalcTemperature(unsigned short rawValue);
float SHTC1_CalcHumidity(unsigned short rawValue);
unsigned char SHTC1_Read2BytesAndCrc(unsigned short *data);


void SHTC1_IIC_Send_Byte(uint8_t data);
uint32_t IIC_Wait_Ack(void);
uint8_t IIC_Read_Byte(unsigned char ack);
void IIC_Stop(void);


unsigned char SHTC1_CheckCrc(unsigned char data[], unsigned char nbrOfBytes, unsigned char checksum);
#endif

