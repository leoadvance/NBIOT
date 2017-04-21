/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Debug.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/23/2017
* Description        :  DebugӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Debug.h"
#include "app_uart.h"
#include "RTC_DS1307.h"

#include <string.h>

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Debug_Task_Create(void);                                           // ������������
void Debug_Rx_Handle(void *p_arg);                                      // ���Կڽ���������
void Receive_Data_Handler(u8* ucData, u16 usLen);                       // �������ݴ���
void Debug_Send(u8 *ucData, u8 ucLen);                                  // �������ݷ���
void Debug_Send_Wait_Empty(void);                                       // �ȿ�

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-02-23
* Function Name  :  Debug_Rx_Handle
* Description    :  ���Կڽ�������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Rx_Handle(void *p_arg)
{
	// �Ƿ���Կڽ��ճ�ʱ
	if (Debug_UART.Rx_Timeout)
	{
		Debug_UART.Rx_Timeout--;

		// �Ƿ񵽳�ʱʱ���ҽ��ջ���Ϊ��
		if (Debug_UART.Rx_Timeout == 0)
		{	
			// �������������
			Debug_UART.Rx_State = UART_RX_STATE_PENDING;
			Task_Timer_Stop(&Debug_Rx_Task);

			// �����������
            Receive_Data_Handler(Debug_UART.Rx_Data, Debug_UART.Rx_Len);

            Debug_UART.Rx_Len   = 0;
            Debug_UART.Rx_State = UART_RX_STATE_IDLE;

		}
	}

}// End of void Debug_Rx_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  Debug_Send
* Description    :  ���Կڷ�������
* Input          :  u8 *ucData  ����������
*                   u8 ucLen    ����
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Send(u8 *ucData, u8 ucLen)
{

//    Debug_Send_Wait_Empty();

    while(ucLen--)
    {
        app_uart_put(*ucData++);
    }
    
}// End of void Debug_Send(u8 *ucData, u8 ucLen)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  Debug_Send_Wait_Empty
* Description    :  �ȴ��ڷ���
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Send_Wait_Empty(void)
{
    u32 uiTimestamp;
    uiTimestamp = System_ms_Base_Update();

    // 100ms��ʱ
    while (System_ms_Base_Timeout(uiTimestamp, 100) == 0)
    {
        Power_Manage();
    }
    
}// End of void Debug_Send_Wait_Empty(void)


/*******************************************************************************
*                           ½��@2017-02-23
* Function Name  :  Receive_Data_Handler
* Description    :  �������ݴ���
* Input          :  u8* ucData  ����������
*                   u16 usLen   ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void Receive_Data_Handler(u8* ucData, u16 usLen)
{
	Time_t Time;
	int Temp[7];

    ucData[usLen] = '\0';
    
#ifndef SYS_TEST 

    app_trace_log("����: %s\r\n", ucData);
    
#endif

    // δ��ɳ�ʼ��������
    if (Sys_Init != 1)
    {
        return;
    }

    if (memcmp(ucData, "setTime ", 8) == 0)
    {
    	sscanf((char*)ucData, "setTime %d %d %d %d %d %d %d", &Temp[0], &Temp[1], &Temp[2], &Temp[3], &Temp[4], &Temp[5], &Temp[6]);
        Time.Year   = Temp[0] & 0xFF;
        Time.Month  = Temp[1] & 0xFF;
        Time.Day    = Temp[2] & 0xFF;
        Time.Week   = Temp[3] & 0xFF;
        Time.Hour   = Temp[4] & 0xFF;
        Time.Minute = Temp[5] & 0xFF;
        Time.Second = Temp[6] & 0xFF;

    	DS1307_Set_Date(Time);										
    }

}// End of void Receive_Data_Handler(u8* ucData, u16 usLen)


/*******************************************************************************
*                           ½��@2017-02-23
* Function Name  :  Debug_Task_Create
* Description    :  ������������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // �����˿ڳ�ʼ��
    Debug_Variable_Init();
    Debug_Port_Init();
    
    // ���ò��� ��������ģʽ
    Debug_Rx_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Debug_Rx_Task.Period          = 5; 
    Debug_Rx_Task.Timeout_handler = Debug_Rx_Handle;
    
    err_code &= app_timer_create(&Debug_Rx_Task.p_ID,
                                  Debug_Rx_Task.Run_Mode,
                                  Debug_Rx_Task.Timeout_handler);

    if (err_code != NRF_SUCCESS)
    {
        
    }
    nrf_delay_ms(10);
    app_trace_log("\r\n");
    app_trace_log("MCU Software Update %s %s\r\n", __DATE__, __TIME__ );
    app_trace_log("SVN %s\r\n", BLE_FW_REV_STR);
    
}// End of void Debug_Task_Create(void)



/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




