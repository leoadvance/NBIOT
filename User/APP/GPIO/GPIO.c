/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  GPIO.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIOӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
#include "nrf_gpio.h"




/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void GPIO_Task_Handle(void *p_arg);                                     // GPIO����
void GPIO_Task_Create(void);                                            // ����GPIO����
void GPIO_TEST_High(void);                                              // Test Pin����
void GPIO_TEST_Low(void);                                               // Test Pin����                      
void GPIO_TEST_Toggle(void);                                            // Test Pin��ת

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  GPIO_Task_Create
* Description    :  ����GPIO����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Task_Create(void)
{


    // ��ʼ��������IO
    GPIO_Variable_Init();
    GPIO_Port_Init();

    // Ĭ������
    GPIO_TEST_Low();
    

    
    
}// End of void GPIO_Task_Create(void)



/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  GPIO_Task_Handle
* Description    :  GPIO����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Task_Handle(void *p_arg)
{

   
}// End of void GPIO_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  GPIO_TEST_High
* Description    :  GPIO ����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_TEST_High(void)
{
    GPIO_Set_Pin_High(GPIO_TEST_PIN);
   
}// End of void GPIO_TEST_High(void)

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  GPIO_TEST_Low
* Description    :  GPIO ����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_TEST_Low(void)
{
    GPIO_Set_Pin_Low(GPIO_TEST_PIN);
   
}// End of void GPIO_TEST_Low(void)

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  GPIO_TEST_Toggle
* Description    :  GPIO ��ת
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_TEST_Toggle(void)
{

    nrf_gpio_pin_toggle(GPIO_TEST_PIN);
    
}// End of void GPIO_TEST_Toggle(void)


/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




