/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  WDT.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/24/2017
* Description        :  ��ʱ��
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "WDT.h"
#include "nrf51.h"
#include "nrf_drv_wdt.h"
#include "nrf_drv_wdt.h"
#include "app_util_platform.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void WDT_Task_Init(void);                                               // ���Ź���ʼ��
void WDT_Event_Handler(void);                                           // ���Ź��жϴ���
void WDT_Timeout_Handler(void *p_arg);                                  // WDT��ʱ����
void WDT_Feed(void);                                                    // ι��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-24
* Function Name  :  WDT_Event_Handler
* Description    :  ���Ź��жϴ���
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Event_Handler(void)
{

}// End of void WDT_Event_Handler(void)

/*******************************************************************************
*                           ½��@2017-01-24
* Function Name  :  WDT_Timeout_Handler
* Description    :  WDT��ʱ����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Timeout_Handler(void *p_arg)
{

    
#ifdef SYS_WDT

    nrf_drv_wdt_channel_feed(WDT_Channel);
    
#endif


}// End of void WDT_Timeout_Handler(void *p_arg)

/*******************************************************************************
*                           ½��@2017-01-24
* Function Name  :  WDT_Task_Init
* Description    :  ���Ź���ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Task_Init(void)
{

    u32 Err_Code = NRF_SUCCESS;
    
#ifdef SYS_WDT


    nrf_drv_wdt_config_t WDT_Cfg;

    // ����˯�߼��� ��ʱʱ�� �ж����ȼ�
    WDT_Cfg.behaviour          = NRF_WDT_BEHAVIOUR_RUN_SLEEP;
    WDT_Cfg.reload_value       = 50000; 
    WDT_Cfg.interrupt_priority = APP_IRQ_PRIORITY_LOW;
    
    Err_Code = nrf_drv_wdt_init(&WDT_Cfg, WDT_Event_Handler);
    APP_ERROR_CHECK(Err_Code);
    Err_Code = nrf_drv_wdt_channel_alloc(&WDT_Channel);
    APP_ERROR_CHECK(Err_Code);
    nrf_drv_wdt_enable();

  
#endif

    // ���ò��� ��������ģʽ
    WDT_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    WDT_Task.Period          = 10000; 
    WDT_Task.Timeout_handler = WDT_Timeout_Handler;

    Err_Code = app_timer_create(&WDT_Task.p_ID,
                                 WDT_Task.Run_Mode,
                                 WDT_Task.Timeout_handler);
    APP_ERROR_CHECK(Err_Code);

    Task_Timer_Start(&WDT_Task, NULL);

}// End of void WDT_Task_Init(void)

/*******************************************************************************
*                           ½��@2017-01-24
* Function Name  :  WDT_Feed
* Description    :  ι��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void WDT_Feed(void)
{

    
#ifdef SYS_WDT

    nrf_drv_wdt_channel_feed(WDT_Channel);
    
#endif


}// End of void WDT_Feed(void)

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




