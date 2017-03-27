/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Communal_Timer.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/12/2017
* Description        :  ���ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Communal_Timer.h"
#include "Duck_BLE_Mi_Bond.h"
#include "Hall.h"
#include "LCD_Battery.h"

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void Communal_Timer_Task_Handle(void *p_arg);                           // Communal_Timer����
void Communal_Timer_Task_Create(void);                                  // ����Communal_Timer����

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-02-22
* Function Name  :  Communal_Timer_Task_Create
* Description    :  ����Communal_Timer����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_Timer_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ���ò��� ����ģʽ����
    Communal_Timer_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Communal_Timer_Task.Timeout_handler = Communal_Timer_Task_Handle;
    Communal_Timer_Task.Period          = TASK_COMMUNAL_TIMER_PERIOD;

    err_code &= app_timer_create(&Communal_Timer_Task.p_ID,
                                 Communal_Timer_Task.Run_Mode,
                                 Communal_Timer_Task.Timeout_handler);
    err_code &= Task_Timer_Start(&Communal_Timer_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Communal_Timer create failed!\r\n");    
    }
    else
    {
        app_trace_log("Task Communal_Timer create Success!\r\n"); 
    }

}// End of void Communal_Timer_Task_Create(void)



/*******************************************************************************
*                           ½��@2017-02-22
* Function Name  :  Communal_Timer_Task_Handle
* Description    :  Communal_Timer����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_Timer_Task_Handle(void *p_arg)
{
    // ��֤�����ͬ����˸
    if (Sys_Bond.Blink_Interval++ >= MIOT_BOND_BLINK)
    {
        Sys_Bond.Blink_Interval = 0;
        
    }

    // �󶨳�ʱ�ж�
    Mi_Bond_Timeout_Check();

    // �����ж�
    Hall_Magnet_Check();

    // ������˸
    LCD_Bat_Update_Blink(LCD.Buffer, Sensor.Bat_Percent);
    
}// End of void Communal_Timer_Task_Handle(void *p_arg)


/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




