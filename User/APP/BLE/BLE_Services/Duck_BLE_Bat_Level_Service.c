/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Bat_Level_Service.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/12/2017
* Description        :  ����DevInfo����Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Bat_Level_Service.h"
#include <stdlib.h>
#include <string.h>
#include "ble_bas.h"
#include "Battery.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_Bat_Level_Services_Init(void);                            // Duck BLE ���������ʼ��  
void Battery_BLE_Service_Update(void);                                  // ����BLE����

/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  Duck_BLE_Bat_Level_Services_Init
* Description    :  Duck BLE ���������ʼ��    
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Bat_Level_Services_Init(void)
{
    u32            Err_Code;
    ble_bas_init_t Bas_Init;

    // Initialize Battery Service.
    memset(&Bas_Init, 0, sizeof(Bas_Init));

    // Here the sec level for the Battery Service can be changed/increased.
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Bas_Init.battery_level_char_attr_md.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Bas_Init.battery_level_char_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&Bas_Init.battery_level_char_attr_md.write_perm);

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Bas_Init.battery_level_report_read_perm);

    Bas_Init.evt_handler          = NULL;
    Bas_Init.support_notification = true;
    Bas_Init.p_report_ref         = NULL;
    Bas_Init.initial_batt_level   = Get_Battery_Percent();

    Err_Code = ble_bas_init(&Bat_Level_Service, &Bas_Init);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Duck_BLE_Bat_Level_Services_Init(void)

/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  Battery_BLE_Service_Update
* Description    :  ����ˢ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Battery_BLE_Service_Update(void)
{
    u32 Err_Code;

    // ������״̬
    if (Sys_Status != SYS_STATUS_CONNECT)
    {
        return;
    }

    // ���µ�������
    Err_Code = ble_bas_battery_level_update(&Bat_Level_Service, Sensor.Bat_Percent);
    if ((Err_Code != NRF_SUCCESS) &&
        (Err_Code != NRF_ERROR_INVALID_STATE) &&
        (Err_Code != BLE_ERROR_NO_TX_BUFFERS) &&
        (Err_Code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
        )
    {
        APP_ERROR_HANDLER(Err_Code);
    }
    
}// End of void Battery_BLE_Service_Update(void)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




