/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD_Page_Baseline.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/20/2017
* Description        :  LCD_Page_BaselineӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Page_Baseline.h"
#include "nrf_gpio.h"
#include "OLED.h"
#include "sensirion_common.h"
#include "sgpc1x.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void LCD_Page_Baseline_Prepare(void);									    // ׼��Baselineҳ��
void LCD_Page_Baseline(void);											    // ��ʾBaselineҳ��


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  LCD_Page_Baseline_Prepare
* Description    :  ׼��Baselineҳ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Baseline_Prepare(void)
{
    u8 ucLen;
	OLED_CLS();
    ucLen = strlen("Baseline");
    OLED_String_8x16(OLED_Pos_Center(ucLen << 3),  0,     "Baseline", ucLen);
    OLED_String_8x16(0,  LCD_BASE_NOW_Y_ADDR,  "Now : ", strlen("Now : "));
    OLED_String_8x16(0,  LCD_BASE_SAVE_Y_ADDR, "Save: ", strlen("Save: "));
	LCD.Page_Now = LCD_PAGE_BASELINE;
	
}// End of void LCD_Page_Baseline_Prepare(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  LCD_Page_Baseline
* Description    :  ��ʾBaselineҳ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Page_Baseline(void)
{
	u8 Temp[16];
	u8 ucLen;


	// �жϵ�ǰ�Ƿ�Baselineҳ��
	if (LCD.Page_Now != LCD_PAGE_BASELINE)
	{
		LCD_Page_Baseline_Prepare();
	}

	// baseline
	ucLen= sprintf((char *)Temp, "0x%08X", tVOC.Baseline_Now);
	OLED_String_8x16(6 * 8,  LCD_BASE_NOW_Y_ADDR, Temp, ucLen);	

	if (Log_Sign < (1000 / TASK_COMMUNAL_TIMER_PERIOD))
	{
		app_trace_log("-------------------baseline = 0x%08X\r\n", tVOC.Baseline_Now);
	}

	
}// End of void LCD_Page_Baseline(void)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




