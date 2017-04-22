/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  EEPROM.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROMӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "EEPROM.h"
#include "nrf_gpio.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void EEPROM_Task_Handle(void *p_arg);                                   // EEPROM����
void EEPROM_Task_Create(void);                                          // ����EEPROM����
u8 EEPROM_Write_Data(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);	// д����
u16 EEPROM_Read_Data(u16 usRead_Addr, u8* pBuffer);           			// ������

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  EEPROM_Task_Create
* Description    :  ����EEPROM����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void EEPROM_Task_Create(void)
{
//    u32 err_code = NRF_SUCCESS;

//    // ��ʼ��������IO
//    EEPROM_Variable_Init();
//    EEPROM_Port_Init();
//    
//    // ���ò��� ����ģʽ����
//    EEPROM_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
//    EEPROM_Task.Timeout_handler = EEPROM_Task_Handle;
//    EEPROM_Task.Period          = TASK_TVOC_PERIOD;

//    err_code |= app_timer_create(&EEPROM_Task.p_ID,
//                                 EEPROM_Task.Run_Mode,
//                                 EEPROM_Task.Timeout_handler);
//    // оƬ��ʼ��
//    err_code |= EEPROM_Chip_Init();

//    if (err_code != NRF_SUCCESS)
//    {
//        app_trace_log("EEPROMоƬ��ʼ��ʧ��!\r\n");    
//    }
//    else
//    {
//        err_code |= Task_Timer_Start(&EEPROM_Task, NULL);
//        if (err_code != NRF_SUCCESS)
//        {
//            app_trace_log("Task EEPROM create failed!\r\n");    
//        }
//    }


}// End of void EEPROM_Task_Create(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  EEPROM_Task_Handle
* Description    :  EEPROM����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void EEPROM_Task_Handle(void *p_arg)
{


}// End of void EEPROM_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-04-22
* Function Name  :  EEPROM_Write_Data
* Description    :  EEPROMд����
* Input          :  u16 usWrite_Addr    Ҫд�ĵ�ַ
*                   u8* pBuffer         ����ָ��
*                   u16 usWrite_Len     д�볤�� 
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 EEPROM_Write_Data(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
	u16 usADD = 0;
	u32 uiLen = 0;
	u16 i;
	u8 Result = 1;
	u8 *Write_Buffer;

	Write_Buffer = malloc(usWrite_Len + 4);

	// ���ȵ�ַ
	Write_Buffer[uiLen++] = (usWrite_Len >> 8) & 0xFF;
	Write_Buffer[uiLen++] = (usWrite_Len >> 0) & 0xFF;

	// ����ʵ��
	memcpy(&Write_Buffer[uiLen], pBuffer, usWrite_Len);
	uiLen += usWrite_Len;

	// �����ۼ�
	usADD = 0;
	for (i = 0; i < uiLen; i++)
	{
		usADD += Write_Buffer[i];	
	}
	Write_Buffer[uiLen++] = (usADD >> 8) & 0xFF;
	Write_Buffer[uiLen++] = (usADD >> 0) & 0xFF;

	// �� ���� ���� У��
	Result = EEPROM_Write_Buffer(usWrite_Addr, Write_Buffer, uiLen);


	free(Write_Buffer);
	return (Result);

}// ENd of u8 EEPROM_Write_Data(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           ½��@2017-04-22
* Function Name  :  EEPROM_Write_Buffer
* Description    :  EEPROMд����
* Input          :  u16 usRead_Addr    	Ҫ��ȡ�ĵ�ַ
*                   u8* pBuffer         ����ָ��
* Output         :  None
* Return         :  �ɹ����ض�ȡ���� 0ʧ��
*******************************************************************************/
u16 EEPROM_Read_Data(u16 usRead_Addr, u8* pBuffer)
{
	u16 usADD = 0;
	u8 Buffer[4];
	u16 i;
	u16 usReadLen = 0;

	// ��ȡ����
	EEPROM_Read_Buffer(usRead_Addr, Buffer, 2);
	usRead_Addr += 2;

	// ����
	usReadLen = (Buffer[0] << 8) + Buffer[1];
    
    if (usReadLen > EEPROM_CHIP_SIZE)
    {
        return 0;
    }

	// ��ȡ���ݺ��ۼ�
	EEPROM_Read_Buffer(usRead_Addr, pBuffer, usReadLen);
	EEPROM_Read_Buffer(usRead_Addr + usReadLen, &Buffer[2], 2);
	
	// �����ۼ�
	usADD += Buffer[0];
	usADD += Buffer[1];
	for (i = 0; i < usReadLen; i++)
	{
		usADD += pBuffer[i];	
	}

	// �Ƿ�У��ʧ��
	if (usADD != ((Buffer[2] << 8) + Buffer[3])) 
	{
		usReadLen = 0;
	}


	return (usReadLen);

}// End of u16 EEPROM_Read_Data(u16 usRead_Addr, u8* pBuffer)


/******************* (C) COPYRIGHT 2015 ½�� **************END OF FILE*********/




