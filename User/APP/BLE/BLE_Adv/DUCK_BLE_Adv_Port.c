/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Adv_Port.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  �����㲥����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Adv_Port.h"
#include "Duck_BLE_Adv.h"
#include "ble_srv_common.h"
#include "Duck_BLE_Adv_MIOT.h"
#include "Duck_BLE_Private_Service.h"
#include "ble_advdata.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

                                
/* Private function prototypes -----------------------------------------------*/

void BLE_Adv_Start(u32 uiTimeout);                                      // �����㲥
void BLE_Adv_Package(void);                                             // �㲥���ݴ��

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
*                           ½��@2017-01-10
* Function Name  :  BLE_Adv_Package
* Description    :  �㲥���ó�ʼ��
* Input          :  u16 usEvent ��������¼�
*                   MIOT_Typedef *MIOT
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Adv_Package(void)
{
    u32           Err_Code;
//    u8            ucService_Data[MIOT_MAX_SIZE];
    ble_advdata_t Adv_Data;
    ble_advdata_t Scan_Rsp;
//    ble_advdata_service_data_t Service_Data;
    ble_uuid_t Scan_UUIDs[] = {{BLE_UUID_BATTERY_SERVICE, BLE_UUID_TYPE_BLE},
                               {BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}};
    // ��ջ���    
    memset(&Adv_Data, 0, sizeof(Adv_Data));
//    memset(&ucService_Data, 0, MIOT_MAX_SIZE);

//    Scan_Rsp.name_type               = BLE_ADVDATA_FULL_NAME;
    
    // 1��˽�з���
//    Adv_Data.service_data_count   = 1;
//    Service_Data.data.p_data      = ucService_Data;
//    Adv_Data.p_service_data_array = &Service_Data;


    // �㲥����
    Adv_Data.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    

//    // ����UUID
//    Service_Data.service_uuid   = MIOT_SERVICE_ID;

//    // ׼��Ҫ���͵�����
//    MIOT->Frame_Control_Bit.Event_Include = 1;
//    MIOT->Event_ID         = usEvent; 
//    MIOT->Current_Event_ID = MIOT->Event_ID;
//    Service_Data.data.size = BLE_MIOT_Service_Package(MIOT->Event_ID, ucService_Data, MIOT);
//    (MIOT->Frame_Counter)++;

    // ��ջ���
    memset(&Scan_Rsp, 0, sizeof(Scan_Rsp)); 
    Scan_Rsp.name_type               = BLE_ADVDATA_FULL_NAME;
    Scan_Rsp.uuids_complete.uuid_cnt = sizeof(Scan_UUIDs) / sizeof(Scan_UUIDs[0]);
    Scan_Rsp.uuids_complete.p_uuids  = Scan_UUIDs;
    Err_Code = ble_advdata_set(&Adv_Data, &Scan_Rsp);

    
    APP_ERROR_CHECK(Err_Code);
    
}// End of void BLE_Adv_Package(void)

/*******************************************************************************
*                           ½��@2017-01-06
* Function Name  :  BLE_Adv_Start
* Description    :  �����㲥
* Input          :  u32 uiTimeout   ��ʱʱ��
* Output         :  None
* Return         :  None
*******************************************************************************/
void BLE_Adv_Start(u32 uiTimeout)
{
    u32                  Err_Code;    
    ble_gap_adv_params_t Adv_Params;


    BLE_Adv_Package();
    
    // Start advertising.
    memset(&Adv_Params, 0, sizeof(Adv_Params));
    
    Adv_Params.type        = BLE_GAP_ADV_TYPE_ADV_IND;                  // �Ƕ��������ģʽ
    Adv_Params.p_peer_addr = NULL;
    Adv_Params.fp          = BLE_GAP_ADV_FP_ANY;                        // ������
    Adv_Params.interval    = BLE_ADV_INTERVAL;                          // �㲥���
    Adv_Params.timeout     = uiTimeout;                                 // �㲥��ʱʱ��
 
    Err_Code = sd_ble_gap_adv_start(&Adv_Params);

    if (Err_Code != NRF_SUCCESS)
    {
        app_trace_log("�㲥���������� %d!\r\n", Err_Code);

    }
    else
    {
        // ����㲥̬
        Sys_Status = SYS_STATUS_ADV;
    }


}// End of void BLE_Adv_Start(u32 uiTimeout)


/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




