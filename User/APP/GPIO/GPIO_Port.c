/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  GPIO_Port.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO��������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "GPIO_Port.h"
#include "nrf_gpio.h"



/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void GPIO_Variable_Init(void);                                          // GPIO������ʼ��
void GPIO_Port_Init(void);                                              // GPIO�˿ڳ�ʼ��    
void GPIO_Set_Pin_High(u8 ucPin);                                       // �ܽ��ø�
void GPIO_Set_Pin_Low(u8 ucPin);                                        // �ܽ��õ�   

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-03
* Function Name  :  GPIO_Port_Init
* Description    :  GPIO�˿ڳ�ʼ��
* Input          :  P0.01   -->   GPIO_TEST_PIN
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Port_Init(void)
{
    // ���ùܽ�Ϊ���
    nrf_gpio_cfg_output(GPIO_TEST_PIN);

       
}// End of void  GPIO_Port_Init(void)

/*******************************************************************************
*                           ½��@2017-01-03
* Function Name  :  GPIO_Variable_Init
* Description    :  GPIO������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Variable_Init(void)
{

  
}// End of void GPIO_Variable_Init(void)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  GPIO_Set_Pin_High
* Description    :  �ܽ��ø�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Set_Pin_High(u8 ucPin)
{
    
    nrf_gpio_pin_set(ucPin);
       
}// End of void GPIO_Set_Pin_High(u8 ucPin)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  GPIO_Set_Pin_Low
* Description    :  �ܽ��õ�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Set_Pin_Low(u8 ucPin)
{
    nrf_gpio_pin_clear(ucPin);
    
}// End of void GPIO_Set_Pin_Low(u8 ucPin)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/

