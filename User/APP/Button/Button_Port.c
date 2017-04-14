/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Button_Port.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ������������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button_Port.h"
#include "nrf_gpio.h"
#include "Button.h"
#include "app_button.h"


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Button_Variable_Init(void);                                        // ������������ʼ��
void Button_Pin_Handler(u8 ucPin_No, u8 ucAction);                      // �����ܽŴ���


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2014-09-04
* Function Name  :  Button_Variable_Init
* Description    :  ����������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Variable_Init(void)
{
    Button.Free_Timestamp = 0;
    Button.Push_Timestamp = 0;
    Button.Status         = 0;
    Button.Long           = 0;
    
}// End of void Button_Variable_Init(void)


/*******************************************************************************
*                           ½��@2016-05-10
* Function Name  :  Button_Pin_Handler
* Description    :  �����ܽŴ���
* Input          :  u8 ucPin_No     �ܽź�
*                   u8 ucAction     ��Ϊ
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Pin_Handler(u8 ucPin_No, u8 ucAction)
{
    // ����
    if(ucAction == APP_BUTTON_PUSH)
    {
//        app_trace_log("Key1����!\r\n");

        Button_Push_ISR();
    }
    // �ͷ�
    else
    {
        // �½��ش���
//        app_trace_log("Key1�ͷ�!\r\n");

        Button_Free_ISR();

    }

}// End of void Button_Pin_Handler(u8 ucPin_No, u8 ucAction)



/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/

