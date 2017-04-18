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
#include "sgpc1x.h"


#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void RTC_Task_Handle(void *p_arg);                                     // RTC����
void RTC_Task_Create(void);                                            // ����RTC����
void RTC_Port_Init(void);                                              // RTC�ܽų�ʼ��
void RTC_Variable_Init(void);                                          // ������ʼ��
u32 RTC_Chip_Init(void);                                               // оƬ��ʼ��

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
    u32 Err_Code = NRF_SUCCESS;


    // Ĭ�ϴ�����error
    System_Err.RTC = 1;

	if (sgp_probe() != STATUS_OK) 
	{
		app_trace_log("RTCоƬ��ʼ��ʧ��!\r\n"); 
		Err_Code = 0xFFFFFFFF;
	}
	else
	{
		System_Err.RTC = 0;
	}

    return Err_Code;
        
}// End of u32 RTC_Chip_Init(void)

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
    u8 err;
    u16 tvoc_ppb, co2_eq_ppm;


    if (Sensor.RTC_Baseline_Reset == 0)
    {
    	Sensor.RTC_Baseline_Timestamp++;

		// 15��������
    	if (Sensor.RTC_Baseline_Timestamp >= 15 * 60)
    	{
    		Sensor.RTC_Baseline_Reset = 1;

    		if (sgp_iaq_init() == STATUS_OK)
    		{
    			app_trace_log("RTC  sgp_iaq_init Success \r\n");	
    		}
    		else
    		{
    			app_trace_log("RTC  sgp_iaq_init Failed \r\n");		
    		}
    	}
    }

	err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
	if (err == STATUS_OK) 
	{
		 app_trace_log("RTC  Concentration: %dppb\n", tvoc_ppb);
		 app_trace_log("CO2eq Concentration: %dppm\n", co2_eq_ppm);

		 // ��¼RTC eCO2
		 Sensor.RTC = tvoc_ppb;
		 Sensor.eCO2 = co2_eq_ppm;


	} 
	else 
	{
		 app_trace_log("error reading IAQ values\n"); 
	}


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




