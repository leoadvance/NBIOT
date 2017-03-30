/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE_Evt_Handler.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  BLE event ���� ����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE_Evt_Handler.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "ble_hci.h"
#include "ble_advertising.h"
#include "nRF51_BLE_Adv.h"
#include "nRF51_BLE_Private_Service.h"
#include "pstorage.h"
#include "device_manager.h"
#include "ble_conn_params.h"
#include "nRF51_BLE_Adv_Port.h"

/* Private variables ---------------------------------------------------------*/
#define APP_FEATURE_NOT_SUPPORTED       BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2        /**< Reply when unsupported features are requested. */


/* Private function prototypes -----------------------------------------------*/
void ON_BLE_Event(ble_evt_t * p_ble_evt);                               // BLE�¼�����
void nRF51_Sys_Evt_Handler(uint32_t sys_evt);                           // sys�¼��ص�
void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt);                      // BLE�¼��ص�

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  ON_BLE_EVENT
* Description    :  BLE�¼��ص�����
* Input          :  ble_evt_t * p_ble_evt   // ��������¼�
* Output         :  None
* Return         :  None
*******************************************************************************/
void ON_BLE_Event(ble_evt_t * p_ble_evt)
{
    u32 err_code;
    switch (p_ble_evt->header.evt_id)
    {
        // ���ӽ���
        case BLE_GAP_EVT_CONNECTED:

            BLE_Connect_Handle = p_ble_evt->evt.gap_evt.conn_handle;
            app_trace_log("��ʼ���ӣ�ON_BLE_Event�̵߳���Ϣ!\r\n");

            // ��������̬
            Sys_Status = SYS_STATUS_CONNECT;
//            LCD_BT_Update_Signal(1);

            break;

        // �Ͽ�����
        case BLE_GAP_EVT_DISCONNECTED:

            BLE_Connect_Handle = BLE_CONN_HANDLE_INVALID;
            app_trace_log("�������ӣ�ON_BLE_Event�̵߳���Ϣ!\r\n");
//            LCD_BT_Update_Signal(0);

            // ���·��͹㲥��
            BLE_Adv_Start(0);

            break;
        
       case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            err_code = sd_ble_gatts_sys_attr_set(BLE_Connect_Handle, NULL, 0, 0);
            APP_ERROR_CHECK(err_code);
            break;
          
        default:
            // No implementation needed.
            break;
    }
    
}// End of void ON_BLE_Event(ble_evt_t * p_ble_evt)

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  nRF51_Sys_Evt_Handler
* Description    :  Sys�¼��ص�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_Sys_Evt_Handler(uint32_t sys_evt)
{
    // ϵͳдflash�¼��ص�
    pstorage_sys_event_handler(sys_evt);

//    // fdsʧ�ܺ��ٴι㲥
//    ble_advertising_on_sys_evt(sys_evt);
    
}// End of void nRF51_Sys_Evt_Handler(uint32_t sys_evt)

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  nRF51_BLE_Evt_Handler
* Description    :  BLE�¼��ص�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt)
{

    // ���¼�
    dm_ble_evt_handler(p_ble_evt);
    ble_conn_params_on_ble_evt(p_ble_evt);
    ble_bas_on_ble_evt(&Bat_Level_Service, p_ble_evt);
    ON_BLE_Event(p_ble_evt);
    BLE_Advertising_on_ble_evt(p_ble_evt);

    // dfu�¼�
    ble_dfu_on_ble_evt(&nRF51_DFU_Services, p_ble_evt);

    nRF51_BLE_Private_Evt(&nRF51_BLE_Service, p_ble_evt);
    



}// End of void nRF51_BLE_Evt_Handler(ble_evt_t * p_ble_evt)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




