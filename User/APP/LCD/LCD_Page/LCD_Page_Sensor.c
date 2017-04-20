/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD_Page_Sensor.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD_Page_SensorӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Page_Sensor.h"
#include "nrf_gpio.h"
#include "nRF51_BLE_Private_Service.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void LCD_Page_Sensor_Prepare(void);									    // ׼��sensorҳ��
void LCD_Page_Sensor(void);											    // ��ʾsensorҳ��


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  LCD_Page_Sensor_Prepare
* Description    :  ׼��sensorҳ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Sensor_Prepare(void)
{
	OLED_CLS();
	
    // ��ʾ��ʪ�ȱ��
	OLED_String_8x16(0,   0, "Temp: ", sizeof("Temp: ") - 1);
	OLED_String_8x16(0,   16, "Humi: ", sizeof("humi: ") - 1);
	OLED_String_16x16(96, 0, (u8*)Temp_Unit, 1);
	OLED_String_8x16(102, 16, "%", sizeof("%") - 1);

	// tVOC eCO2
	OLED_String_8x16(0,  32, "tVOC:  ...", sizeof("tVOC:  ...") - 1);
	OLED_String_8x16(0,  48, "eCO2:  ...", sizeof("eCO2:  ...") - 1);
	OLED_String_8x16(96, 32, "ppb", sizeof("ppb") - 1);
	OLED_String_8x16(96, 48, "ppm", sizeof("ppm") - 1);

	LCD.Page_Now = PAGE_SENSOR;
	
}// End of void LCD_Page_Sensor_Prepare(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  LCD_Page_Sensor
* Description    :  ��ʾsensorҳ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Sensor(void)
{
	u8 ucTemp[6];
	u8 ucLen;

	// �жϵ�ǰ�Ƿ�sensorҳ��
	if (LCD.Page_Now != PAGE_SENSOR)
	{
		LCD_Page_Sensor_Prepare();
	}
	
	// �¶ȴ���0
	if (Sensor.sTemp >= 0)
	{
		// ʮ����
		if (Sensor.sTemp < 100)
		{
			sprintf((char *)ucTemp, "  %01d.%01d", Sensor.sTemp / 10, Sensor.sTemp % 10);
		}
		else
		{
			sprintf((char *)ucTemp, " %02d.%01d", Sensor.sTemp / 10, Sensor.sTemp % 10);
		}
		
	}
	else
	{
		Sensor.sTemp = abs(Sensor.sTemp);
		sprintf((char *)ucTemp, "-%02d.%01d", Sensor.sTemp / 10, Sensor.sTemp % 10);

	}
	OLED_String_8x16(6 * 8, 0, ucTemp, 5);
	
	// ʪ��
	sprintf((char *)ucTemp, " %02d.%01d", Sensor.usHumi / 10, Sensor.usHumi % 10);
	OLED_String_8x16(6 * 8, 16, ucTemp, 5);
	
	// tVOC eCO2
	ucLen = sprintf((char *)ucTemp, " %4d", Sensor.tVOC);
	OLED_String_8x16(6 * 8, 32, ucTemp, ucLen);
	ucLen = sprintf((char *)ucTemp, " %4d", Sensor.eCO2);
	OLED_String_8x16(6 * 8, 48, ucTemp, ucLen);
	
}// End of void LCD_Page_Sensor(void)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




