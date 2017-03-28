/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Global.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  Global header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_H
#define __GLOBAL_H
/* Includes ------------------------------------------------------------------*/
#include "Global_Cfg.h"
#include "Struct.h"
#include "nrf51.h"
#include "ble.h"
#include "nrf_delay.h"
#include "Global_Typedef.h"
#include "SW_I2C.h"
#include "nordic_common.h"
#include "stdio.h"
#include "app_button.h"
#include "Task.h"
#include "ble_bas.h"
#include "GPIO.h"
#include "nrf_drv_wdt.h"
#include "app_trace.h"
#include "device_manager.h"
#include "ble_dfu.h"
#include "pstorage.h"

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
//----------------------- System ----------------------------------------------/
extern  u8                      Root_Access;                            // ����Ȩ��
extern  u8                      Sys_Status;                             // ϵͳ״̬
extern  u8                      Sys_Init;                               // ��һ��ɳ�ʼ�� 
extern  Task_Typedef            Button_Task;                            // ��������
extern  Task_Typedef            Communal_Timer_Task;                    // ���ö�ʱ������
extern  Task_Typedef            Battery_Task;                           // �������
extern  Task_Typedef            Temp_Humi_Task;                         // ��ʪ������
extern  Task_Typedef            BLE_Task;                               // BLE����
extern  Task_Typedef            WDT_Task;                               // WDT����
extern  Task_Typedef            Debug_Rx_Task;                          // ���Կڽ�������
extern  Test_Typedef            Test;                                   // ����
extern  Bond_Typedef            Sys_Bond;                               // ��
extern  UART_Typedef            Debug_UART;                             // ���Դ���
extern  Button_Typedef          Button;                                 // �����ṹ��
extern  Sensor_Typedef          Sensor;                                 // Sensor
extern  Time_Base_Typedef       System_Time_Base;                       // ϵͳʱ���׼
extern  System_ERR_Typedef      System_Err;                             // ϵͳ����ṹ��
extern  BLE_Service_Typedef     nRF51_BLE_Service;                      // nRF51 BLE˽�з���
extern  nrf_drv_wdt_channel_id  WDT_Channel;                            // �������Ź�ͨ������

//----------------------- BLE -------------------------------------------------/
extern  u16                     BLE_Connect_Handle;                     // ��ǰ���Ӵ���״̬
extern  ble_bas_t               Bat_Level_Service;                      // ��������
extern  dm_application_instance_t   DM_App_Handle;                      // dm handle
extern  ble_dfu_t               nRF51_DFU_Services;                     // DFU service

//----------------------- flash -----------------------------------------------/
extern  u8                      Flash_Used;                             // ��һʱflash��ռ��
extern  pstorage_handle_t       MAC_Flash_Handle;                       // mac flash����
extern  pstorage_handle_t       Token_Flash_Handle;                     // Token lash��ַ

//----------------------- Button ----------------------------------------------/
extern  app_button_cfg_t        Button_Cfg[MAX_INTERRUPT_PIN_NUM];      // Button���ýṹ��

//----------------------- Software IIC ----------------------------------------/
extern  SW_I2C_Typedef          Temp_Humi_I2C;                          // ��ʪ�ȵ�IIC

/* Private function prototypes -----------------------------------------------*/
extern  u32  Timestamp_Interval_Get(u32 Time1, u32 Time2);              // ����ʱ���ֵ
extern  u32  Timestamp_Get(void);                                       // ��ȡʱ���
extern  u8   Timestamp_Timeout(u32 Time, u32 Timeout);                  // ��ʱ����
extern  u8   System_ms_Base_Timeout(u32 Time, u32 Timeout);             // ms��ʱ
extern  u32  System_ms_Base_Update(void);                               // msʱ�������
extern  void Power_Manage(void);                                        // ��Դ���� ����͹���ģʽ

#endif /* __GLOBAL_H */

/******************* (C) COPYRIGHT 2016 ½�� ********END OF FILE***************/
