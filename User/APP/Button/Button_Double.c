/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Button_Double.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/19/2016
* Description        :  ˫��Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Double.h"
#include "nrf_gpio.h"
#include "LCD.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Double_Button_Handler(void);                                       // ˫������



/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-19
* Function Name  :  Double_Button_Handler
* Description    :  ����˫���¼�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Double_Button_Handler(void)
{
    app_trace_log("˫������!\r\n");

    // ��̬�л�
//    LCD_Temp_Humi_Change_Dynamic();
   
}// End of void Double_Button_Handler(void)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




