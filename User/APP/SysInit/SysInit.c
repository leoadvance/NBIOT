/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  SysInit.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  ϵͳ��ʼ��
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "SysInit.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "app_scheduler.h"
#include "app_timer_appsh.h"
#include "app_button.h"
#include "nrf_drv_clock.h"
#include "Communal_IIC.h"
#include "tVOC.h"

#include <stdbool.h>
#include <stdint.h>
#include "ble_advdata.h"
#include "nordic_common.h"
#include "softdevice_handler.h"

#include "nRF51_BLE_Init.h"
#include "Button_Port.h"
#include "Button.h"
#include "Temp_Humi.h"
#include "GPIO.h"
#include "nRF51_BLE.h"
#include "WDT.h"
#include "LCD.h"
#include "Communal_Timer.h"
#include "app_trace.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void System_Init(void);                                                 // ϵͳ��ʼ��
void Variable_Init(void);                                               // ������ʼ��
void Peripheral_Init(void);                                             // �����ʼ��
void GPIO_Low_Power_Init(void);                                         // ����IOΪ��͹���ģʽ
void IO_Interrupt_Init(void);                                           // IO�ж��¼���ʼ��
void Task_Init(void);                                                 	// �����ʼ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2015-04-18
* Function Name  :  HFCLK_Crystal_Oscillato_Start
* Description    :  �����ⲿ���� 16M
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void HFCLK_Crystal_Oscillato_Start(void)
{
    // �����ⲿʱ��
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART    = 1;

    // �ȴ���������
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);    

}// End of void HFCLK_Crystal_Oscillato_Start(void)

/*******************************************************************************
*                           ½��@2015-04-18
* Function Name  :  LFCLK_Crystal_Oscillato_Start
* Description    :  �����ⲿ���پ��� 32k
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void LFCLK_Crystal_Oscillato_Start(void)
{
    // ѡ���ⲿ����Ϊʱ��Դ
//    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_RC << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;

     // �ȴ���������
    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);

}// End of void LFCLK_Crystal_Oscillato_Start(void)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  System_Init
* Description    :  ϵͳ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void System_Init(void)
{

    
    // ������ʼ��
    Variable_Init();

    // �����ʼ��
    Peripheral_Init();

    // �����ʼ��
    Task_Init();
    
    app_trace_log("System init!!!\r\n");

    // ��ɳ�ʼ��
    Sys_Init = 1;


}// End of void System_Init(void)



/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  Variable_Init
* Description    :  ������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Variable_Init(void)
{
    // ��մ����־λ
    System_Err.ALL     = 0;
    
    // Ĭ���ڿ���̬
    Sys_Status         = SYS_STATUS_IDLE;

    // ��ʼ������״̬
    BLE_Connect_Handle = BLE_CONN_HANDLE_INVALID;


    // Ĭ��δ��ռ��
    Flash_Used = 0;

    // Ĭ��δ��ʼ��
    Sys_Init = 0;

	// ��baseline��λ
    Sensor.tVOC_Baseline_Timestamp = 0;
    Sensor.tVOC_Baseline_Reset     = 0;

}// End of void Variable_Init(void)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  GPIO_Low_Power_Init
* Description    :  ����IOΪ��͹���ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void GPIO_Low_Power_Init(void)
{
    u8 i;
    for(i = 0; i < 32; i++ ) 
    {
        NRF_GPIO->PIN_CNF[i] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                             | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                             | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                             | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                             | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
    }
    
}// End of void GPIO_Low_Power_Init(void)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  Peripheral_Init
* Description    :  �����ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Peripheral_Init(void)
{


    // ����IOΪ��͹���ģʽ
    GPIO_Low_Power_Init();
    
#ifndef BLE_OPEN


    APP_TIMER_INIT(APP_TIMER_DIV, SYS_MAX_TIMERS, SYS_MAX_OP_QUEUE_SIZE, NULL);

#else

    APP_TIMER_INIT(APP_TIMER_DIV, SYS_MAX_TIMERS, SYS_MAX_OP_QUEUE_SIZE, app_timer_evt_schedule);
    APP_SCHED_INIT(sizeof(app_timer_event_t) , MAX_EVENT_QUEUE_SIZE);
    
#endif

    // trace����
    app_trace_init();  
      
    // IO�ж��¼���ʼ��
    IO_Interrupt_Init();

    // ͨѶIIC��ʼ��
    Communal_IIC_Init();


    
}// End of void Peripheral_Init(void)

/*******************************************************************************
*                           ½��@2017-01-11
* Function Name  :  Task_Init
* Description    :  �����ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Task_Init(void)
{


    // ������������
    Button_Task_Create();

    // ��ʪ�ȼ��
    Temp_Humi_Task_Create();

    // tVOC
    tVOC_Task_Create();
    
    // GPIO
    GPIO_Task_Create();

	// LCD����
	LCD_Task_Create();

    // ���ö�ʱ������
    Communal_Timer_Task_Create();

    // �����Ź�
    WDT_Task_Init();

    // BLE����
    nRF51_BLE_Task_Create();




}// End of void Task_Init(void)
																				
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  IO_Interrupt_Init
* Description    :  IO�ж��¼���ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void IO_Interrupt_Init(void)
{
    u8 i = 0;
    
    // GPOUT ���ùܽ� ������� ��Ч��ƽ��������

    Button_Cfg[i].pin_no         = BOUTTON_PIN;
    Button_Cfg[i].button_handler = Button_Pin_Handler;
    Button_Cfg[i].active_state   = APP_BUTTON_ACTIVE_LOW;
    Button_Cfg[i].pull_cfg       = NRF_GPIO_PIN_PULLUP;
    i++;
    
    app_button_init(Button_Cfg, MAX_INTERRUPT_PIN_NUM, APP_TIMER_TICKS(BUTTEN_EVENT_DELAY_MS, APP_TIMER_DIV)); 
    app_button_enable();
    
}// End of void IO_Interrupt_Init(void)



/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/




