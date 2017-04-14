/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE_Adv.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  �����㲥������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE_Adv.h"
#include <stdlib.h>
#include <string.h>
#include "nrf_soc.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt);           // �㲥�¼�����
void nRF51_BLE_Bond_Adv_Handle(void *p_arg);                            // �󶨹㲥

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  BLE_Advertising_on_ble_evt
* Description    :  �㲥�¼�����
* Input          :  ble_evt_t const * p_ble_evt ʱ�����
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
//        case BLE_GAP_EVT_CONNECTED:
//        {
//            app_trace_log("��ʼ���ӣ��㲥�̵߳���Ϣ!\r\n");
//        }
//        break;

//        // Upon disconnection, whitelist will be activated and direct advertising is started.
//        case BLE_GAP_EVT_DISCONNECTED:
//        {
//            app_trace_log("�������ӣ��㲥�̵߳���Ϣ!\r\n");
//            
//        }break;

        
        // Upon time-out, the next advertising mode is started, i.e. go from fast to slow or from slow to idle.
        case BLE_GAP_EVT_TIMEOUT:
        {
            if (p_ble_evt->evt.gap_evt.params.timeout.src == BLE_GAP_TIMEOUT_SRC_ADVERTISING)
            {
                app_trace_log("�㲥��ʱ���㲥�̵߳���Ϣ!\r\n"); 


            }
            
        }break;

        default:
        break;
    }
    
}// End of void BLE_Advertising_on_ble_evt(ble_evt_t const * p_ble_evt)

/*******************************************************************************
*                           ½��@2017-02-22
* Function Name  :  nRF51_BLE_Bond_Adv_Handle
* Description    :  �󶨹㲥����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Bond_Adv_Handle(void *p_arg)
{


}// End of void nRF51_BLE_Bond_Adv_Handle(void *p_arg)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/










