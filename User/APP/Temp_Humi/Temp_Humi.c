/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Temp_Humi.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ��ʪ��Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi.h"
#include "nrf_gpio.h"
#include "Temp_Humi_SHT30.h"
#include "Duck_BLE_Private_Service.h"
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void Temp_Humi_Task_Handle(void *p_arg);                                // Temp_Humi����
void Temp_Humi_Task_Create(void);                                       // ����Temp_Humi����
u32 Temp_Humi_Chip_Init(void);                                          // оƬ��ʼ��
void Temp_Humi_Update(float fTemp, float fHumi);                        // ������ʪ������
void Temp_Humi_Get(void);                                               // ��ȡ��ʪ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Task_Create
* Description    :  ����Temp_Humi����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��������IO
    Temp_Humi_Variable_Init();
    Temp_Humi_Port_Init();
    
    // ���ò��� ����ģʽ����
    Temp_Humi_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    Temp_Humi_Task.Timeout_handler = Temp_Humi_Task_Handle;
    Temp_Humi_Task.Period          = TASK_TEMP_HUMI_PERIOD;

    err_code &= app_timer_create(&Temp_Humi_Task.p_ID,
                                 Temp_Humi_Task.Run_Mode,
                                 Temp_Humi_Task.Timeout_handler);
    // оƬ��ʼ��
    err_code &= Temp_Humi_Chip_Init();
    err_code &= Task_Timer_Start(&Temp_Humi_Task, NULL);
    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("Task Temp&Humi create failed!\r\n");    
    }


}// End of void Temp_Humi_Task_Create(void)

/*******************************************************************************
*                           ½��@2017-01-03
* Function Name  :  Temp_Humi_Chip_Init
* Description    :  оƬ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS �ɹ� 1ʧ��
*******************************************************************************/
u32 Temp_Humi_Chip_Init(void)
{
    u32 Err_Code = 0xFFFF;
    u8 ucSN[8];

    float Temp;
    float Humi;

    // Ĭ�ϴ�����error
    System_Err.Temp_Humi = 1;

    if (SHT3x_Soft_Reset() == 1)
    {
        if (SHT3x_Read_SN(ucSN))
        {
            Err_Code             = NRF_SUCCESS;
            System_Err.Temp_Humi = 0;
            
            app_trace_log("SHT3x_SN = 0x%02X%02X%02X%02X\r\n", ucSN[0], ucSN[1], ucSN[2], ucSN[3]);


            // �״ζ�ȡ��ʪ��
            SHT3x_Get_Temp_Humi(&Temp, &Humi);
            Temp_Humi_Update(Temp, Humi);
        }
    }

    return Err_Code;
        
}// End of u32 Temp_Humi_Chip_Init(void)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Temp_Humi_Get
* Description    :  ��ȡ��ʪ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Get(void)
{

    float Temp;
    float Humi;
    static u8 ucError_Times = 0;

    if(SHT3x_Get_Temp_Humi(&Temp, &Humi))
    {
        // ��ճ������
        ucError_Times = 0;

        // ������ʪ������
        Temp_Humi_Update(Temp, Humi);

        // ��մ����־λ
        System_Err.Temp_Humi = 0;
        
    }
    else
    {
        ucError_Times++;

        if (ucError_Times > MAX_GET_SENSOR_ERROR)
        {
            ucError_Times        = 0;

            // ��λ�����־λ
            System_Err.Temp_Humi = 1;

            // ���� ���㲥��������
            app_trace_log("SHT30 Sensor Error!\r\n");

        }
    }

   
}// End of void Temp_Humi_Get(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Task_Handle
* Description    :  Temp_Humi����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Task_Handle(void *p_arg)
{

    Temp_Humi_Get();
   
}// End of void Temp_Humi_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-01-12
* Function Name  :  Temp_Humi_Update
* Description    :  ������ʪ������
* Input          :  float fTemp  �¶�
*                   float fHumi  ʪ�� 
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Update(float fTemp, float fHumi)
{

    short sTemp_Now = -99;
    u16   usHumi_Now;

    // ����float����
    Sensor.fTemp = fTemp;
    Sensor.fHumi = fHumi;
    
    // �������� ��ȷ��1λС��
    fTemp     += 0.05;
    fTemp     *= 10;
    sTemp_Now  = (s16)fTemp;
    
    fHumi     += 0.05;
    fHumi     *= 10;
    usHumi_Now = (s16)fHumi;


    // ������ˢ��
    if((sTemp_Now != Sensor.sTemp) || (usHumi_Now != Sensor.usHumi))
    {
        Sensor.sTemp               = sTemp_Now;
        Sensor.usHumi              = usHumi_Now;
        
    }
    else
    {
        app_trace_log("                                             ��ʪ�������ޱ仯!\r\n");    
    }
   
   
}// End of void Temp_Humi_Update(float fTemp, float fHumi)



/******************* (C) COPYRIGHT 2016 ½�� ************* END OF FILE ********/




