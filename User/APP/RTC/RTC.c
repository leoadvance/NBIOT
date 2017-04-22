/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  RTC.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  RTCӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "RTC.h"
#include "nrf_gpio.h"



#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void RTC_Task_Handle(void *p_arg);                                     	// RTC����
void RTC_Task_Create(void);                                            	// ����RTC����
void RTC_Port_Init(void);                                              	// RTC�ܽų�ʼ��
void RTC_Variable_Init(void);                                          	// ������ʼ��
u32 RTC_Chip_Init(void);                                               	// оƬ��ʼ��
void RTC_Time_Refresh(void);											// ˢ��ʱ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  RTC_Task_Create
* Description    :  ����RTC����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��������IO
    RTC_Variable_Init();
    RTC_Port_Init();
    
    // ���ò��� ����ģʽ����
    RTC_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    RTC_Task.Timeout_handler = RTC_Task_Handle;
    RTC_Task.Period          = TASK_TVOC_PERIOD;

    err_code |= app_timer_create(&RTC_Task.p_ID,
                                 RTC_Task.Run_Mode,
                                 RTC_Task.Timeout_handler);
    // оƬ��ʼ��
    err_code |= RTC_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("RTCоƬ��ʼ��ʧ��!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&RTC_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task RTC create failed!\r\n");    
        }
    }


}// End of void RTC_Task_Create(void)

/*******************************************************************************
*                           ½��@2017-01-03
* Function Name  :  RTC_Chip_Init
* Description    :  оƬ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS �ɹ� 1ʧ��
*******************************************************************************/
u32 RTC_Chip_Init(void)
{
	
	// ����RTC
    if (DS1307_Start())
    {
    	System_Err.RTC = 0;
    	RTC_Time_Refresh();
    	return NRF_SUCCESS;
    }
    else
    {
    	System_Err.RTC = 1;
    	return 0xFFFFFFFF;	
    }

    
        
}// End of u32 RTC_Chip_Init(void)


/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  RTC_Time_Refresh
* Description    :  ˢ��ʱ��
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Time_Refresh(void)
{

	if (DS1307_Get_Data(&System.Time))
	{

		System.Unix_Sec = DS1307_Year_TO_Unix(&System.Time);
	}

}// End of void RTC_Time_Refresh(void *p_arg)


/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  RTC_Task_Handle
* Description    :  RTC����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Task_Handle(void *p_arg)
{

	RTC_Time_Refresh();

}// End of void RTC_Task_Handle(void *p_arg)



/*******************************************************************************
*                           ½��@2016-04-19
* Function Name  :  RTC_Port_Init
* Description    :  RTC�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
void RTC_Port_Init(void)
{

       
}// End of void RTC_Port_Init(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  RTC_Variable_Init
* Description    :  RTC������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void RTC_Variable_Init(void)
{

    
}// End of void RTC_Variable_Init(void)

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




