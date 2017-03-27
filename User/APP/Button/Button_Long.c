/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Button_Long.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ����Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Long.h"
#include "nrf_gpio.h"
#include "LCD.h"
#include "Duck_BLE_Mi_Bond.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Long_Button_Handler(void);                                         // ��������


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Long_Button_Handler
* Description    :  �������¼�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Long_Button_Handler(void)
{
    
    app_trace_log("��������\r\n");

//    // �����л�
//    LCD_Temp_Humi_Change_On_Off();

    // ��ʼ�󶨵�
    Mi_Bond_Start();

}// End of void Long_Button_Handler(void)


/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/




