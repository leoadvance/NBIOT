/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD_Port.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  ��ʪ����������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "LCD_Port.h"
#include "nrf_gpio.h"
#include "OLED.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

void LCD_Variable_Init(void);                                           // LCD������ʼ��
u8   LCD_Port_Init(void);                                               // LCD�˿ڳ�ʼ��    

/* Private functions ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           ½��@2017-04-09
* Function Name  :  LCD_Port_Init
* Description    :  LCD�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 LCD_Port_Init(void)
{
    u8 Transfer_Succeeded = 0; 
	OLED_Port_Init();
    return (Transfer_Succeeded);
       
}// End of u8  LCD_Port_Init(void)

/*******************************************************************************
*                           ½��@2017-04-09
* Function Name  :  LCD_Variable_Init
* Description    :  LCD������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LCD_Variable_Init(void)
{
	LCD.Page_Now  = PAGE_SENSOR;	
	LCD.Page_Show = PAGE_SENSOR;
    
}// End of void LCD_Variable_Init(void)



/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/

