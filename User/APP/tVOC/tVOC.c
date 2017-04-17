/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  tVOC.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/29/2017
* Description        :  tVOCӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "tVOC.h"
#include "nrf_gpio.h"
#include "sgpc1x.h"


#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void tVOC_Task_Handle(void *p_arg);                                     // tVOC����
void tVOC_Task_Create(void);                                            // ����tVOC����
void tVOC_Get(void);                                                    // ��ȡtVOC
void tVOC_Port_Init(void);                                              // tVOC�ܽų�ʼ��
void tVOC_Variable_Init(void);                                          // ������ʼ��
u32 tVOC_Chip_Init(void);                                               // оƬ��ʼ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-03-29
* Function Name  :  tVOC_Task_Create
* Description    :  ����tVOC����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��������IO
    tVOC_Variable_Init();
    tVOC_Port_Init();
    
    // ���ò��� ����ģʽ����
    tVOC_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    tVOC_Task.Timeout_handler = tVOC_Task_Handle;
    tVOC_Task.Period          = TASK_TVOC_PERIOD;

    err_code |= app_timer_create(&tVOC_Task.p_ID,
                                 tVOC_Task.Run_Mode,
                                 tVOC_Task.Timeout_handler);
    // оƬ��ʼ��
    err_code |= tVOC_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("tVOCоƬ��ʼ��ʧ��!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&tVOC_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task tVOC create failed!\r\n");    
        }
    }


}// End of void tVOC_Task_Create(void)

/*******************************************************************************
*                           ½��@2017-01-03
* Function Name  :  tVOC_Chip_Init
* Description    :  оƬ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS �ɹ� 1ʧ��
*******************************************************************************/
u32 tVOC_Chip_Init(void)
{
    u32 Err_Code = NRF_SUCCESS;


    // Ĭ�ϴ�����error
    System_Err.tVOC = 1;

	if (sgp_probe() != STATUS_OK) 
	{
		app_trace_log("tVOCоƬ��ʼ��ʧ��!\r\n"); 
		Err_Code = 0xFFFFFFFF;
	}
	else
	{
		System_Err.tVOC = 0;
	}

    return Err_Code;
        
}// End of u32 tVOC_Chip_Init(void)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  tVOC_Get
* Description    :  ��ȡtVOC
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Get(void)
{

   
}// End of void tVOC_Get(void)

/*******************************************************************************
*                           ½��@2017-03-29
* Function Name  :  tVOC_Task_Handle
* Description    :  tVOC����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Task_Handle(void *p_arg)
{
    u8 err;
    u16 tvoc_ppb, co2_eq_ppm;

	err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
	if (err == STATUS_OK) 
	{
		 app_trace_log("tVOC  Concentration: %dppb\n", tvoc_ppb);
		 app_trace_log("CO2eq Concentration: %dppm\n", co2_eq_ppm);

	} 
	else 
	{
		 app_trace_log("error reading IAQ values\n"); 
	}


}// End of void tVOC_Task_Handle(void *p_arg)



/*******************************************************************************
*                           ½��@2016-03-29
* Function Name  :  tVOC_Port_Init
* Description    :  tVOC�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
void tVOC_Port_Init(void)
{

       
}// End of void tVOC_Port_Init(void)

/*******************************************************************************
*                           ½��@2017-03-29
* Function Name  :  tVOC_Variable_Init
* Description    :  tVOC������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Variable_Init(void)
{

    
}// End of void tVOC_Variable_Init(void)

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




