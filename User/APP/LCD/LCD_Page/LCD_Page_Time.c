/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD_Page_Time.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/20/2017
* Description        :  LCD_Page_TimeӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Page_Time.h"
#include "nrf_gpio.h"
#include "nRF51_BLE_Private_Service.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void LCD_Page_Time_Prepare(void);									    // ׼��Timeҳ��
void LCD_Page_Time(void);											    // ��ʾTimeҳ��


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  LCD_Page_Time_Prepare
* Description    :  ׼��Timeҳ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Time_Prepare(void)
{
	OLED_CLS();
	

	LCD.Page_Now = LCD_PAGE_TIME;
	
}// End of void LCD_Page_Time_Prepare(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  LCD_Page_Time
* Description    :  ��ʾTimeҳ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Time(void)
{

	// �жϵ�ǰ�Ƿ�Timeҳ��
	if (LCD.Page_Now != LCD_PAGE_TIME)
	{
		LCD_Page_Time_Prepare();
	}

	
}// End of void LCD_Page_Time(void)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




