/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  Duck_BLE ����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "Duck_BLE_Init.h"
#include "Duck_BLE_Adv_Port.h"
#include "Duck_BLE_Adv.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_Task_Create(void);                                        // BLE���񴴽�
void Duck_BLE_Task_Handle(void *p_arg);                                 // BLE����
void Duck_BLE_Slave_Evt_Handle(void *p_arg);                            // ������  
void Duck_BLE_Master_Evt_Handle(void *p_arg);                           // ������
void Duck_BLE_Int_Evt_Handle(void *p_arg);                              // ��������
void Duck_BLE_Int_Evt_Set(u16 usEvent_ID);                              // ������������
void Duck_BLE_Cycle_Evt_Handle(void *p_arg);                            // ����������

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-11
* Function Name  :  Duck_BLE_Task_Create
* Description    :  ����BLE����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��BLE
    Duck_BLE_Init();
    
    // ���ò��� ����ģʽ����
    BLE_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    BLE_Task.Timeout_handler = Duck_BLE_Task_Handle;
    BLE_Task.Period          = TASK_BLE_PERIOD;

    err_code &= app_timer_create(&BLE_Task.p_ID,
                                 BLE_Task.Run_Mode,
                                 BLE_Task.Timeout_handler);

    // ��ʼ����
    err_code &= Task_Timer_Start(&BLE_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Temp&Humi create failed!\r\n");    
    }


    
    
}// End of void Duck_BLE_Task_Create(void)


/*******************************************************************************
*                           ½��@2017-01-11
* Function Name  :  Duck_BLE_Task_Handle
* Description    :  BLE����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Task_Handle(void *p_arg)
{

    // �Ƿ��ڹ㲥̬
    if (Sys_Status != SYS_STATUS_ADV)
    {
        return;
    }

    // �Ƿ��Ͱ󶨹㲥
    if (Sys_Bond.Adv_En)
    {
        Duck_BLE_Bond_Adv_Handle(p_arg);
    }
    else
    {
        // �Ƿ������¼�
        if (MIOT_Adv.Int_Event)
        {
            Duck_BLE_Int_Evt_Handle(p_arg);
        }
        else
        {
            // ���ڹ㲥
            Duck_BLE_Cycle_Evt_Handle(p_arg);    
        }
        
    }
   
}// End of void Duck_BLE_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  Duck_BLE_Int_Evt_Handle
* Description    :  ����������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Int_Evt_Handle(void *p_arg)
{
    MIOT_Adv.Int_Event = 0;

    BLE_Adv_Package(MIOT_Adv.Int_Event_ID, &MIOT_Adv);

    app_trace_log("�����¼��㲥!\r\n"); 
                                                                 
}// End of void Duck_BLE_Int_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  Duck_BLE_Int_Evt_Set
* Description    :  ������������
* Input          :  u16 usEvent_ID
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Int_Evt_Set(u16 usEvent_ID)
{
    MIOT_Adv.Int_Event    = 1;
    MIOT_Adv.Int_Event_ID = usEvent_ID;
    
}// End of void Duck_BLE_Int_Evt_Set(u16 usEvent_ID)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  Duck_BLE_Cycle_Evt_Handle
* Description    :  ������������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Cycle_Evt_Handle(void *p_arg)
{
    if (MIOT_Adv.Timestamp_Hall++ > MIOT_HALL_EVENT_INTERVAL)
    {
        MIOT_Adv.Timestamp_Hall = 0;
        
        // ����
        BLE_Adv_Package(MIOT_EVENT_ID_HALL, &MIOT_Adv);
        app_trace_log("�㲥�����¼�!\r\n");
    }
    else if (MIOT_Adv.Timestamp_Bat++ > MIOT_BAT_EVENT_INTERVAL)
    {
        MIOT_Adv.Timestamp_Bat = 0;
        
        // ����
        BLE_Adv_Package(MIOT_EVENT_ID_BAT, &MIOT_Adv);
        app_trace_log("�㲥�����¼�!\r\n");
    }
    else
    {
        // �Ƿ��Ѿ��ڹ㲥��ʪ���¼�
        if (MIOT_Adv.Current_Event_ID != MIOT_EVENT_ID_TH)
        {
            BLE_Adv_Package(MIOT_EVENT_ID_TH, &MIOT_Adv);
        }
        else
        {
            // �Ƿ�ˢ��
            if (MIOT_Adv.Temp_Humi_Refresh)
            {
                MIOT_Adv.Temp_Humi_Refresh = 0;
                BLE_Adv_Package(MIOT_EVENT_ID_TH, &MIOT_Adv);
            }
            else
            {
                app_trace_log("                                             �Ѿ��ڹ㲥�¶��¼������ظ�����!\r\n");
            }
        } 
    }
    
}// End of void Duck_BLE_Cycle_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  Duck_BLE_Master_Evt_Handle
* Description    :  ��������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Master_Evt_Handle(void *p_arg)
{

   

    
}// End of void Duck_BLE_Master_Evt_Handle(void *p_arg)



/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  Duck_BLE_Slave_Evt_Handle
* Description    :  ��������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Slave_Evt_Handle(void *p_arg)
{
    // �Ƿ���/ADC�쳣
    if (System_Err.Battery == 0)
    {
        // �Ƿ��Ѿ��ڹ㲥���¼�
        if (MIOT_Adv.Current_Event_ID != MIOT_EVENT_ID_BAT)
        {
            BLE_Adv_Package(MIOT_EVENT_ID_BAT, &MIOT_Adv);
        }
        else
        {
            app_trace_log("�Ѿ��ڹ㲥�����¼������ظ�����!\r\n");
        }
    }
    else
    {

        app_trace_log("Battery Err, ���㲥�����¼�!\r\n");
    }
    
    
}// End of void Duck_BLE_Slave_Evt_Handle(void *p_arg)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




