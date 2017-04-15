/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCDӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD.h"
#include "nrf_gpio.h"
#include "nRF51_BLE_Private_Service.h"
#include "OLED.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void LCD_Task_Handle(void *p_arg);                                      // LCD����
void LCD_Task_Create(void);                                             // ����LCD����
u32 LCD_Chip_Init(void);                                                // оƬ��ʼ��


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-09
* Function Name  :  LCD_Task_Create
* Description    :  ����LCD����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��������IO
    LCD_Variable_Init();
    LCD_Port_Init();
    
    // ���ò��� ����ģʽ����
    LCD_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    LCD_Task.Timeout_handler = LCD_Task_Handle;
    LCD_Task.Period          = TASK_LCD_PERIOD;

    err_code |= app_timer_create(&LCD_Task.p_ID,
                                 LCD_Task.Run_Mode,
                                 LCD_Task.Timeout_handler);
    // оƬ��ʼ��
    err_code |= LCD_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("LCDоƬ��ʼ��ʧ��!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&LCD_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task LCD create failed!\r\n");    
        }
    }


}// End of void LCD_Task_Create(void)

/*******************************************************************************
*                           ½��@2017-04-09
* Function Name  :  LCD_Chip_Init
* Description    :  оƬ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS �ɹ� 1ʧ��
*******************************************************************************/
u32 LCD_Chip_Init(void)
{
    u32 Err_Code = NRF_SUCCESS;

	OLED_Init();

    return Err_Code;
        
}// End of u32 LCD_Chip_Init(void)

/*******************************************************************************
*                           ½��@2017-04-09
* Function Name  :  LCD_Task_Handle
* Description    :  LCD����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Task_Handle(void *p_arg)
{
	u8 x = 0, y = 0, i, j;
	u8 temp[2] = {0xAA, 0xAA};
	OLED_Fill(0xF0);
	for (i = 0; i < 128; i++)
	{
		j++;
		if (j >= 64)
		{
			j = 0;
		}

		OLED_Draw_YPage(i, j, temp, 2);

	}
	//OLED_DrawPixel(x,y++,1);
   
}// End of void LCD_Task_Handle(void *p_arg)

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




