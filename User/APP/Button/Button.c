/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Button.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ButtonӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Button.h"
#include "nrf_gpio.h"
#include "Button_Single.h"
#include "Button_Long.h"
#include "Button_Double.h"

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void Button_Task_Handle(void *p_arg);                                   // Button����
void Button_Task_Create(void);                                          // ����Button����
void Button_Free_ISR(void);                                             // Button�ͷ��жϴ���
void Button_Push_ISR(void);                                             // Button[�����жϴ���


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Button_Task_Create
* Description    :  ����Button����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��������IO
    Button_Variable_Init();
    
    // ���ò��� ����ģʽ����
    Button_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Button_Task.Timeout_handler = Button_Task_Handle;
    Button_Task.Period          = 50;

    err_code = app_timer_create(&Button_Task.p_ID,
                                 Button_Task.Run_Mode,
                                 Button_Task.Timeout_handler);
    
    if (err_code != NRF_SUCCESS)
    {
        
    }
    
}// End of void Button_Task_Create(void)



/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Button_Task_Handle
* Description    :  Button����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Task_Handle(void *p_arg)
{
    // �������, ʱ���
    u32 Time_Interval, Timestamp;

    // ��¼ʱ��
    Timestamp = Timestamp_Get();

    // �����ΰ��¹�
    if (Button.Status == 1)
    {
        // ��ȡʱ���
        Time_Interval  = Timestamp_Interval_Get(Timestamp, Button.Push_Timestamp);
        Time_Interval /= TICK_TO_MS;
        
        // �������¼�
        if ((Time_Interval >= LONG_CLICK_MIN_DURATION) && (Time_Interval < RESET_CLICK_MIN_DURATION))
        {
            // �����δ���
            if (Button.Long == 0)
            {
                Button.Long = 1;
                
                // �������¼�
                Long_Button_Handler();
            }
        }
//        else if (Time_Interval > RESET_CLICK_MIN_DURATION)
//        {
//            if (Button.Long)
//            {
//                app_trace_log("������������ϵͳ!\r\n");
//                nrf_delay_ms(100);
//                APP_ERROR_CHECK(SPECIAL_CODE_RESET);
//            }

//        }
    }
    else if (Button.Status == 2)
    {
        // �ϴ��ͷź󾭹���ʱ��
        Time_Interval  = Timestamp_Interval_Get(Timestamp, Button.Free_Timestamp);
        Time_Interval /= TICK_TO_MS;  

        // �����ź�
        if ((Time_Interval < CLICK_MAX_DURATION) && (Time_Interval > DOUBLE_HIT_INTERVAL))
        {
            // ֹͣ����ʶ��
            Task_Timer_Stop(&Button_Task);
            Button_Variable_Init();
            
            // �����¼�
            Single_Button_Handler();
        }
    }

   
}// End of void Button_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2016-04-26
* Function Name  :  Button_Push_ISR
* Description    :  Button�������жϴ���
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Push_ISR(void)
{

    
    Button.Long  = 0;

    // ��¼����ʱ��
    Button.Push_Timestamp = Timestamp_Get(); 

    // �״ΰ���������ʱ��
    if (Button.Status == 0)

    {
        Button.Status = 1;
        
        // ������ʱ��
        Task_Timer_Start(&Button_Task, NULL);
    }
    // ���ΰ���
    else if (Button.Status == 2)
    {
        Button.Status = 3;   
    }

}// End of void Button_Push_ISR(void)

/*******************************************************************************
*                           ½��@2017-01-19
* Function Name  :  Button_Free_ISR
* Description    :  Button�ͷ��жϴ���
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Button_Free_ISR(void)
{
    // ����ʱ��
    u32 Time_Interval;

    if (Button.Status == 0)
    {
        return;    
    }

    // ��¼ʱ���
    Button.Free_Timestamp = Timestamp_Get(); 

    // ���㰴�����
    Time_Interval  = Timestamp_Interval_Get(Button.Free_Timestamp, Button.Push_Timestamp);
    Time_Interval /= TICK_TO_MS;
    
    // ��һ��̧��
    if (Button.Status == 1)
    {
        // �����ͷ�
        if (Button.Long)
        {
            Task_Timer_Stop(&Button_Task);

            Button_Variable_Init();

            app_trace_log("�����ͷ�!\r\n");
        }
        else
        {
            Button.Status = 2;
        }
    }
    else if (Button.Status == 3)
    {

        Task_Timer_Stop(&Button_Task);

        Button_Variable_Init(); 
        
        // �󴥷�
        if (Time_Interval < CLICK_MIN_DURATION)
        {
            // ֹͣ��ʱ�� ��ձ���
            app_trace_log("С����С����ʱ��!\r\n");
        }
        // �������δ���
        else if (Time_Interval < CLICK_MAX_DURATION)
        {
            // ˫������
            Double_Button_Handler();
        }
        // ���̰�֮����󴥷�
        else if (Time_Interval < LONG_CLICK_MIN_DURATION)
        {
            
            app_trace_log("���ڳ��̰�֮����󴥷�!\r\n");
        }
    
    }
    
    
}// End of void Button_Free_ISR(void)


/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/




