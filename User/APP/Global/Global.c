/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Global.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  ȫ�ֱ���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private variables ---------------------------------------------------------*/
//----------------------- System ----------------------------------------------/
u8                      Root_Access;                                    // ����Ȩ��
u8                      Sys_Status;                                     // ϵͳ״̬
u8                      Sys_Init;                                       // ��һ��ɳ�ʼ�� 
LCD_Typedef				LCD;											// LCD
Task_Typedef            Button_Task;                                    // ��������
Task_Typedef            RTC_Task;										// RTC����
Task_Typedef            LCD_Task;                                       // LCD����
Task_Typedef            tVOC_Task;                                      // tVOC����
Task_Typedef            Communal_Timer_Task;                            // ���ö�ʱ������
Task_Typedef            Battery_Task;                                   // �������
Task_Typedef            Temp_Humi_Task;                                 // ��ʪ������
Task_Typedef            BLE_Task;                                       // BLE����
Task_Typedef            WDT_Task;                                       // WDT����
Task_Typedef            Debug_Rx_Task;                                  // ���Կڽ�������
Bond_Typedef            Sys_Bond;                                       // ��
UART_Typedef            Debug_UART;                                     // ���Դ���
Button_Typedef          Button;                                         // �����ṹ��
Sensor_Typedef          Sensor;                                         // Sensor
Time_Base_Typedef       System_Time_Base;                               // ϵͳʱ���׼
System_ERR_Typedef      System_Err;                                     // ϵͳ����ṹ��
BLE_Service_Typedef     nRF51_BLE_Service;                              // nRF51 BLE˽�з���
nrf_drv_wdt_channel_id  WDT_Channel;                                    // �������Ź�ͨ������

//----------------------- BLE -------------------------------------------------/
u16                     BLE_Connect_Handle;                             // ��ǰ���Ӵ���״̬
ble_bas_t               Bat_Level_Service;                              // ��������
dm_application_instance_t   DM_App_Handle;                              // dm handle
ble_dfu_t               nRF51_DFU_Services;                             // DFU service

//----------------------- flash -----------------------------------------------/
u8                      Flash_Used;                                     // ��һʱflash��ռ��
pstorage_handle_t       MAC_Flash_Handle;                               // mac flash����
pstorage_handle_t       Token_Flash_Handle;                             // Token lash��ַ

//----------------------- Button ----------------------------------------------/
app_button_cfg_t        Button_Cfg[MAX_INTERRUPT_PIN_NUM];              // Button���ýṹ��


//----------------------- Software IIC ----------------------------------------/
SW_I2C_Typedef          Temp_Humi_I2C;                                  // ��ʪ�ȵ�IIC
SW_I2C_Typedef          Communal_IIC;                                   // ͨ��IIC
SW_I2C_Typedef          Communal_IIC_2;                                 // ͨ��IIC_2


/* Private function prototypes -----------------------------------------------*/
u32  Timestamp_Interval_Get(u32 Time1, u32 Time2);                      // ����ʱ���ֵ
u32  Timestamp_Get(void);                                               // ��ȡʱ���
u8   Timestamp_Timeout(u32 Time, u32 Timeout);                          // ��ʱ����
u8   System_ms_Base_Timeout(u32 Time, u32 Timeout);                     // ms��ʱ
u32  System_ms_Base_Update(void);                                       // msʱ�������

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  Timestamp_Interval_Get
* Description    :  ����ʱ������
* Input          :  u32 Time1   ����ʱ��
*                   u32 Time2   ǰ��ʱ��
* Output         :  None
* Return         :  ���ߺ�ǰ�߲�ֵ
*******************************************************************************/
u32 Timestamp_Interval_Get(u32 Time1, u32 Time2)
{
    u32 Time_Interval;
    

    Time_Interval = (Time1 - Time2) & 0x00FFFFFF; 

    return Time_Interval;
    
}// End of u32 Timestamp_Interval_Get(u32 Time1, u32 Time2)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  Timestamp_Timeout
* Description    :  ����ʱ������
* Input          :  u32 Time    ���Ƚ�ʱ��
*                   u32 Timeout ��ʱʱ�� ms
* Output         :  None
* Return         :  ��ʱ����1 ���򷵻�0
*******************************************************************************/
u8 Timestamp_Timeout(u32 Time, u32 Timeout)
{
    u32 Time_Interval;
    u32 Current_Time = Timestamp_Get();

    Time_Interval = (Current_Time - Time) & 0x00FFFFFF; 

    Time_Interval /= TICK_TO_MS;
    if (Time_Interval > Timeout)
    {
        return 1;    
    }
    else
    {
        return 0;
    }

    
}// End of u8 Timestamp_Timeout(u32 Time, u32 Timeout)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  System_ms_Base_Timeout
* Description    :  ����ʱ������ ms
* Input          :  u32 Time    ���Ƚ�ʱ��
*                   u32 Timeout ��ʱʱ�� ms
* Output         :  None
* Return         :  ��ʱ����1 ���򷵻�0
*******************************************************************************/
u8 System_ms_Base_Timeout(u32 Time, u32 Timeout)
{
    System_ms_Base_Update();
    if ((System_Time_Base.ms - Time)  >= Timeout)
    {
        return 1;    
    }
    else
    {
        return 0;
    }

    
}// End of u8 System_ms_Base_Timeout(u32 Time, u32 Timeout)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  System_ms_Base_Update
* Description    :  ����ʱ�������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 System_ms_Base_Update(void)
{
    u32 Current_Time            = NRF_RTC1->COUNTER;
    u32 Time_Interval           = (Current_Time - System_Time_Base.Last_Tick) & 0x00FFFFFF;
    
    Time_Interval              /= TICK_TO_MS;
    System_Time_Base.ms        += Time_Interval;
    System_Time_Base.Last_Tick  = Current_Time;
    
    return System_Time_Base.ms;
    
}// End of u32 System_ms_Base_Update(void)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  Timestamp_Get
* Description    :  ��ȡʱ���
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Timestamp_Get(void)
{
    return NRF_RTC1->COUNTER;
    
}// End of u32 Timestamp_Get(void)

/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/
