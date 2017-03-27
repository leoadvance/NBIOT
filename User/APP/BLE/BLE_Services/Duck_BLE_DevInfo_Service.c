/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_DevInfo_Service.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/12/2017
* Description        :  ����DevInfo����Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_DevInfo_Service.h"
#include <stdlib.h>
#include <string.h>
#include "ble_dis.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_DevInfo_Services_Init(void);                              // ϵͳ��Ϣ�����ʼ��


/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
*                           ½��@2017-01-12
* Function Name  :  Duck_BLE_DevInfo_Services_Init
* Description    :  DevInfo�����ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_DevInfo_Services_Init(void)
{
    u32             Err_Code;

    // BLE�豸��Ϣ
    ble_dis_init_t  BLE_Dis; 
    
    // ��ձ���
    memset(&BLE_Dis, 0, sizeof(BLE_Dis));

    // ��ʼ��ģ����Ϣ
    ble_srv_ascii_to_utf8(&BLE_Dis.manufact_name_str,   BLE_MANUFACTURER_NAME);
    ble_srv_ascii_to_utf8(&BLE_Dis.fw_rev_str,          BLE_FW_REV_STR);
    ble_srv_ascii_to_utf8(&BLE_Dis.model_num_str,       BLE_MODULE_NUM);

    
    
    // ����Ӳ���汾
    ble_srv_ascii_to_utf8(&BLE_Dis.hw_rev_str,          DEFAULT_HARDWARE_VERSION);    


    
    // ���ö�дȨ��
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&BLE_Dis.dis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&BLE_Dis.dis_attr_md.write_perm);


    Err_Code = ble_dis_init(&BLE_Dis);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Duck_BLE_DevInfo_Services_Init(void)



/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




