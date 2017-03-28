/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  nRF51_BLE ����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "nRF51_BLE_Init.h"
#include "nRF51_BLE_Adv_Port.h"
#include "nRF51_BLE_Adv.h"

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
void nRF51_BLE_Task_Create(void);                                        // BLE���񴴽�
void nRF51_BLE_Task_Handle(void *p_arg);                                 // BLE����
void nRF51_BLE_Slave_Evt_Handle(void *p_arg);                            // ������  
void nRF51_BLE_Master_Evt_Handle(void *p_arg);                           // ������
void nRF51_BLE_Int_Evt_Handle(void *p_arg);                              // ��������
void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID);                              // ������������
void nRF51_BLE_Cycle_Evt_Handle(void *p_arg);                            // ����������

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-11
* Function Name  :  nRF51_BLE_Task_Create
* Description    :  ����BLE����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��BLE
    nRF51_BLE_Init();
    
    // ���ò��� ����ģʽ����
    BLE_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    BLE_Task.Timeout_handler = nRF51_BLE_Task_Handle;
    BLE_Task.Period          = TASK_BLE_PERIOD;

    err_code |= app_timer_create(&BLE_Task.p_ID,
                                 BLE_Task.Run_Mode,
                                 BLE_Task.Timeout_handler);

    // ��ʼ����
    err_code |= Task_Timer_Start(&BLE_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Temp&Humi create failed!\r\n");    
    }


    
    
}// End of void nRF51_BLE_Task_Create(void)


/*******************************************************************************
*                           ½��@2017-01-11
* Function Name  :  nRF51_BLE_Task_Handle
* Description    :  BLE����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Task_Handle(void *p_arg)
{

   
}// End of void nRF51_BLE_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  nRF51_BLE_Int_Evt_Handle
* Description    :  ����������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Int_Evt_Handle(void *p_arg)
{

                                                                 
}// End of void nRF51_BLE_Int_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  nRF51_BLE_Int_Evt_Set
* Description    :  ������������
* Input          :  u16 usEvent_ID
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID)
{

    
}// End of void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID)

/*******************************************************************************
*                           ½��@2017-03-02
* Function Name  :  nRF51_BLE_Cycle_Evt_Handle
* Description    :  ������������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Cycle_Evt_Handle(void *p_arg)
{
    
}// End of void nRF51_BLE_Cycle_Evt_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  nRF51_BLE_Master_Evt_Handle
* Description    :  ��������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Master_Evt_Handle(void *p_arg)
{

   

    
}// End of void nRF51_BLE_Master_Evt_Handle(void *p_arg)



/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  nRF51_BLE_Slave_Evt_Handle
* Description    :  ��������
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Slave_Evt_Handle(void *p_arg)
{

    
}// End of void nRF51_BLE_Slave_Evt_Handle(void *p_arg)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




