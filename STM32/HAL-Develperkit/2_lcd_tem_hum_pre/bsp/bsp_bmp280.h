#ifndef _bsp_bmp280_h_  
#define _bsp_bmp280_h_  

#include "stm32l4xx.h"
#include "stdio.h"

#define BMP280_ADDRESS 0xE0  
  
#define BMP280_RESET_VALUE 0xB6  

#define BMP280_DIG_T1_LSB_REG       0x88  
#define BMP280_DIG_T1_MSB_REG       0x89  
#define BMP280_DIG_T2_LSB_REG       0x8A  
#define BMP280_DIG_T2_MSB_REG       0x8B  
#define BMP280_DIG_T3_LSB_REG       0x8C  
#define BMP280_DIG_T3_MSB_REG       0x8D  
#define BMP280_DIG_P1_LSB_REG       0x8E  
#define BMP280_DIG_P1_MSB_REG       0x8F  
#define BMP280_DIG_P2_LSB_REG       0x90  
#define BMP280_DIG_P2_MSB_REG       0x91  
#define BMP280_DIG_P3_LSB_REG       0x92  
#define BMP280_DIG_P3_MSB_REG       0x93  
#define BMP280_DIG_P4_LSB_REG       0x94  
#define BMP280_DIG_P4_MSB_REG       0x95  
#define BMP280_DIG_P5_LSB_REG       0x96  
#define BMP280_DIG_P5_MSB_REG       0x97  
#define BMP280_DIG_P6_LSB_REG       0x98  
#define BMP280_DIG_P6_MSB_REG       0x99  
#define BMP280_DIG_P7_LSB_REG       0x9A  
#define BMP280_DIG_P7_MSB_REG       0x9B  
#define BMP280_DIG_P8_LSB_REG       0x9C  
#define BMP280_DIG_P8_MSB_REG       0x9D  
#define BMP280_DIG_P9_LSB_REG       0x9E  
#define BMP280_DIG_P9_MSB_REG       0x9F  
  
#define BMP280_CHIPID_REG           0xD0  /*Chip ID Register */  
#define BMP280_RESET_REG            0xE0  /*Softreset Register */  
#define BMP280_STATUS_REG           0xF3  /*Status Register */  
#define BMP280_CTRLMEAS_REG         0xF4  /*Ctrl Measure Register */  
#define BMP280_CONFIG_REG           0xF5  /*Configuration Register */  
#define BMP280_PRESSURE_MSB_REG     0xF7  /*Pressure MSB Register */  
#define BMP280_PRESSURE_LSB_REG     0xF8  /*Pressure LSB Register */  
#define BMP280_PRESSURE_XLSB_REG    0xF9  /*Pressure XLSB Register */  
#define BMP280_TEMPERATURE_MSB_REG  0xFA  /*Temperature MSB Reg */  
#define BMP280_TEMPERATURE_LSB_REG  0xFB  /*Temperature LSB Reg */  
#define BMP280_TEMPERATURE_XLSB_REG	0xFC  /*Temperature XLSB Reg */  
  
/* ��foreced mode�£�1s�Ĳ������ڣ��¶Ⱥ���ѹʹ����͵ľ��Ȳɼ�����ʹ����С���˲���ϵ��, 
 * ���ݵĲɼ�ʱ������6ms��ƽ������Ϊ3.27uA�� 
 * */  
  
/* ��foreced mode�£�1s�Ĳ�������, �¶Ⱥ���ѹʹ����ߵľ��Ȳɼ�����ʹ�������˲���ϵ���� 
 * ���ݵĲɼ�ʱ������70ms��ƽ������Ϊ30uA�� 
 * */  
  
typedef enum {  
    BMP280_T_MODE_SKIP = 0x0,   /*skipped*/  
    BMP280_T_MODE_1,            /*x1*/  
    BMP280_T_MODE_2,            /*x2*/  
    BMP280_T_MODE_3,            /*x4*/  
    BMP280_T_MODE_4,            /*x8*/  
    BMP280_T_MODE_5             /*x16*/  
} BMP280_T_OVERSAMPLING;  //������
  
typedef enum {  
    BMP280_SLEEP_MODE = 0x00,  
    BMP280_FORCED_MODE = 0x01,  
    BMP280_NORMAL_MODE=0x03  
} BMP280_WORK_MODE;  
  
typedef enum {  
    BMP280_P_MODE_SKIP = 0x0,   /*skipped*/  
    BMP280_P_MODE_x1,            /*x1*/  
    BMP280_P_MODE_x2,            /*x2*/  
    BMP280_P_MODE_x4,            /*x4*/  
    BMP280_P_MODE_x8,            /*x8*/  
    BMP280_P_MODE_x16             /*x16*/  
} BMP280_P_OVERSAMPLING;  

/************************************************/
/**@name	          ����ģʽ����                 */
/************************************************/
typedef enum
{
	BMP280_ULTRA_LOW_POWER_MODE = 0x00,
	BMP280_LOW_POWER_MODE = 0x01,
	BMP280_STANDARD_RESOLUTION_MODE = 0x02,
	BMP280_HIGH_RESOLUTION_MODE = 0x03,
	BMP280_ULTRA_HIGH_RESOLUTION_MODE = 0x04
}WORKING_MODE;

typedef enum {  
    BMP280_FILTER_OFF = 0x0,    /*filter off*/  
    BMP280_FILTER_MODE_1,       /*0.223*ODR*/  
    BMP280_FILTER_MODE_2,       /*0.092*ODR*/  
    BMP280_FILTER_MODE_3,       /*0.042*ODR*/  
    BMP280_FILTER_MODE_4        /*0.021*ODR*/  
} BMP280_FILTER_COEFFICIENT;  
  
typedef enum {  
    BMP280_T_SB_0_5MS = 0x00,      /*0.5ms */  
    BMP280_T_SB_62_5MS= 0x01,      /*62.5ms*/  
    BMP280_T_SB_125MS = 0x02,      /*125ms */  
    BMP280_T_SB_250MS = 0x03,      /*250ms */  
    BMP280_T_SB_500MS = 0x04,      /*500ms */  
    BMP280_T_SB_1000MS= 0x05,      /*1000ms*/  
    BMP280_T_SB_2000MS= 0x06,      /*2000ms*/  
    BMP280_T_SB_4000MS= 0x07,      /*4000ms*/  
} BMP280_T_SB;  

typedef struct{
	uint16_t dig_T1;/*У׼T1����*/
	int16_t dig_T2;/*У׼T2����*/
	int16_t dig_T3;/*У׼T3����*/
	uint16_t dig_P1;/*У׼P1����*/
	int16_t dig_P2;/*У׼P2����*/
	int16_t dig_P3;/*У׼P3����*/
	int16_t dig_P4;/*У׼P4����*/
	int16_t dig_P5;/*У׼P5����*/
	int16_t dig_P6;/*У׼P6����*/
	int16_t dig_P7;/*У׼P7����*/
	int16_t dig_P8;/*У׼P8����*/
	int16_t dig_P9;/*У׼P9����*/
	int32_t t_fine;/*У׼t_fine����*/
}bmp280_calib_param_t;

typedef struct  {
	bmp280_calib_param_t calib_param;/*У׼����*/
	uint8_t chip_id;                      /*������ID*/
	uint8_t dev_addr;                     /*������IIC��ַ*/
	uint8_t oversamp_temperature;         /*�¶Ȳ���*/
	uint8_t oversamp_pressure;            /*��ѹ����*/
}bmp280_t;

#define BMP280_SlaveAddr 0x77    //BMP280��������ַ

#define BMP280_Write_Byte(reg,data)  	MPU_Write_Byte(BMP280_SlaveAddr,reg,data)
#define BMP280_Read_Byte(reg) 			MPU_Read_Byte(BMP280_SlaveAddr,reg)
#define BMP280_Read_Len(reg,len,buf) 	MPU_Read_Len(BMP280_SlaveAddr,reg,len,buf)

void BMP280_IO_init(void);
uint8_t BMP280_Chack(void);
uint8_t  BMP280_Init(void);
uint8_t  BMP280_CalibParam(void);
uint8_t  BMP280_GetMode(void);
uint8_t  BMP280_SetMode(BMP280_WORK_MODE mode);
uint8_t  BMP280_SetPowerMode(uint8_t mode);
uint8_t  BMP280_SetWorkMode(WORKING_MODE mode);
uint8_t  BMP280_SetStandbyDurn(BMP280_T_SB v_standby_durn_uint8_t);
uint8_t  BMP280_GetStandbyDurn(uint8_t* v_standby_durn_uint8_t);
uint8_t  BMP280_ReadUncompTemperature(int32_t* un_temp);
uint8_t  BMP280_ReadUncompPressuree(int32_t *un_press);
uint8_t  BMP280_ReadUncompPressureTemperature(int32_t *un_press, int32_t *un_temp);
int32_t BMP280_CompensateTemperatureInt32(int32_t un_temp);
uint32_t BMP280_CompensatePressureInt32(int32_t un_press);
uint8_t  BMP280_ReadPressureTemperature(uint32_t *press, int32_t *temp);

#endif  
