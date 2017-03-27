/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Task.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ��ʱ��
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Task.h"
#include "nrf51.h"

#include "app_scheduler.h"
#include "app_timer_appsh.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
u32 Task_Timer_Start(Task_Typedef *Task, void * p_context);             // ��������
u32 Task_Timer_Stop(Task_Typedef *Task);                                // ����ֹͣ

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Task_Timer_Start
* Description    :  ��������
* Input          :  Task_Typedef *Task  ����������
*                   u32 Period                  ����
*                   void * p_context            ����ʱ���ݸ�����Ĳ���
* Output         :  None
* Return         :  �����ɹ�����ʧ�ܵ�ԭ��
*******************************************************************************/
u32 Task_Timer_Start(Task_Typedef *Task, void * p_context)
{
    u32 Err_Code;

    
    Err_Code = app_timer_start(Task->p_ID, APP_TIMER_TICKS(Task->Period, APP_TIMER_DIV), p_context);


    return Err_Code;
    
}// End of void Task_Timer_Start(Task_Typedef *Task, void * p_context)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Task_Timer_Stop
* Description    :  ����ֹͣ
* Input          :  Task_Typedef *Task  ����������
* Output         :  None
* Return         :  ֹͣ�ɹ�����ʧ�ܵ�ԭ��
*******************************************************************************/
u32 Task_Timer_Stop(Task_Typedef *Task)
{
    u32 Err_Code;


    // ֹͣ��ʱ�� ��ձ���
    Err_Code = app_timer_stop(Task->p_ID);


    return Err_Code;
    
}// End of void Task_Timer_Stop(Task_Typedef *Task)


/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/




