/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE_Private_Service.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/13/2017
* Description        :  ˽�з���Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_BLE_Private_Service.h"
#include "nRF51_BLE_Test_Ack.h"
#include <stdlib.h>
#include <string.h>


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void nRF51_BLE_Private_Services_Init(void);                             // ˽�з����ʼ��  
void nRF51_BLE_Receive_Data_Handler(u8 * p_data, u16 length);           // nRF51�������ݴ���
u32 nRF51_Temp_Characteristic_Add(BLE_Service_Typedef * pnRF51);        // �����¶ȷ���
u32 nRF51_Message_Characteristic_Add(BLE_Service_Typedef * pnRF51);     // ����ͨѶ����
u8 nRF51_Temp_Humi_Encode(s16 sTemp, u16 usHumi, u8 * pBuffer);         // ��ʪ�����ݴ��
void nRF51_BLE_Private_Evt(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt);   // nRF51�¼�����
void nRF51_BLE_ON_Write(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt);      // nRF51���մ���
void nRF51_BLE_ON_Disconnect(BLE_Service_Typedef * pnRF51);             // �Ͽ�����
void nRF51_BLE_ON_Connect(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt);    // ����
u32 nRF51_BLE_String_Send(BLE_Service_Typedef * pnRF51, u16 usValue_Handle, u8 * pString, u16 usLen); // ��������
void Temp_BLE_Service_Update(BLE_Service_Typedef * pnRF51);             // �����¶�

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-15
* Function Name  :  nRF51_BLE_Receive_Data_Handler
* Description    :  nRF51�������ݴ���
* Input          :  u8* p_data          ��������ָ��
*                   u16 length          ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Receive_Data_Handler(u8 * p_data, u16 length)
{

    app_trace_log("    �յ���Ϣ!\r\n");
    
}// End of void nRF51_BLE_Receive_Data_Handler(u8 * p_data, u16 length)

/*******************************************************************************
*                           ½��@2017-01-13
* Function Name  :  nRF51_BLE_Private_Services_Init
* Description    :  nRF51 BLE ˽�з����ʼ��    
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Private_Services_Init(void)
{
    u32             Err_Code;
    ble_uuid128_t   nRF51_Base_UUID = NRF51_BASE_UUID;
    ble_uuid_t      BLE_UUID;


    // ���������ʼ��
    nRF51_BLE_Service.Conn_Handle  = BLE_CONN_HANDLE_INVALID;

    

    // ���ӷ���UUID
    Err_Code = sd_ble_uuid_vs_add(&nRF51_Base_UUID, &nRF51_BLE_Service.UUID_Type);
    APP_ERROR_CHECK(Err_Code);

    // ����UUID���ͺ�ֵ 
    BLE_UUID.type = nRF51_BLE_Service.UUID_Type;
    BLE_UUID.uuid = BLE_UUID_NRF51;

    // ����һ������
    Err_Code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &BLE_UUID,
                                        &nRF51_BLE_Service.Service_Handle);
                                        
    APP_ERROR_CHECK(Err_Code);
    

    // ���ӷ��ͷ���
    nRF51_BLE_Service.Temp_Humi_Listening_En = false;
    Err_Code = nRF51_Temp_Characteristic_Add(&nRF51_BLE_Service);
    APP_ERROR_CHECK(Err_Code);

    nRF51_BLE_Service.Message_Listening_En = false;
    Err_Code = nRF51_Message_Characteristic_Add(&nRF51_BLE_Service);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void nRF51_BLE_Private_Services_Init(void)


/*******************************************************************************
*                           ½��@2017-01-15
* Function Name  :  nRF51_Temp_Characteristic_Add
* Description    :  �����¶ȷ��ͷ���
* Input          :  BLE_Service_Typedef * pnRF51 �������
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u32 nRF51_Temp_Characteristic_Add(BLE_Service_Typedef * pnRF51) 
{
    // ��������Ȩ����
    ble_gatts_char_md_t char_md;
    ble_gatts_char_pf_t accel_pf;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          BLE_UUID;
    ble_gatts_attr_md_t attr_md;
    u8 ucEncode[BLE_NRF51_MAX_DATA_LEN];
    static char User_Desc[] = "Temp&Humi";

    // �ͻ�������ֵ���������� ����notify
    ble_gatts_attr_md_t cccd_md;
    
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;
     
    
    // �������ݸ�ʽ
    memset(&accel_pf, 0, sizeof(accel_pf));
    accel_pf.format    = BLE_GATT_CPF_FORMAT_UTF8S;

    memset(&char_md, 0, sizeof(char_md));


    char_md.char_props.notify       = 1;                            // ����Ȩ��
    char_md.char_props.read         = 0;                            // ��Ȩ��
    char_md.char_props.write        = 0;                            // дȨ��
    char_md.p_char_user_desc        = (u8 *) User_Desc;             // ����������
    char_md.char_user_desc_size     = strlen(User_Desc);
    char_md.char_user_desc_max_size = strlen(User_Desc);
    char_md.p_char_pf               = &accel_pf;                    // ��ʽ
    char_md.p_user_desc_md          = NULL;
    char_md.p_cccd_md               = &cccd_md;                         // �ͻ�����������������Ȩ�� 0x2902 �鿴Notify֪ͨ
    char_md.p_sccd_md               = NULL;

    // �������ͺ�������
    BLE_UUID.type = pnRF51->UUID_Type;
    BLE_UUID.uuid = NRF51_TEMP_CHARACTERISTIC;

    memset(&attr_md, 0, sizeof(attr_md));

    // û�ж�дȨ��
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &BLE_UUID;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = nRF51_Temp_Humi_Encode(Sensor.sTemp, Sensor.usHumi, ucEncode);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BLE_NRF51_MAX_DATA_LEN;
    attr_char_value.p_value   = ucEncode;

    return sd_ble_gatts_characteristic_add(pnRF51->Service_Handle,
                                           &char_md,
                                           &attr_char_value,
                                           &pnRF51->Temp_Humi_Handle);
                                           
}// End of u32 nRF51_Temp_Characteristic_Add(BLE_Service_Typedef * pnRF51) 

/*******************************************************************************
*                           ½��@2017-03-09
* Function Name  :  nRF51_Message_Characteristic_Add
* Description    :  ����ͨѶ����
* Input          :  BLE_Service_Typedef * pnRF51 �������
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u32 nRF51_Message_Characteristic_Add(BLE_Service_Typedef * pnRF51) 
{
    // ��������Ȩ����
    ble_gatts_char_md_t char_md;
//    ble_gatts_char_pf_t accel_pf;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          BLE_UUID;
    ble_gatts_attr_md_t attr_md;
    static char User_Desc[] = "Message";
    ble_gatts_attr_md_t cccd_md;
    
    memset(&cccd_md, 0, sizeof(cccd_md));
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;
     
    // �������ݸ�ʽ
//    memset(&accel_pf, 0, sizeof(accel_pf));
//    accel_pf.format    = BLE_GATT_CPF_FORMAT_UTF8S;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.notify       = 1;                            // ����Ȩ��
    char_md.char_props.read         = 0;                            // ��Ȩ��
    char_md.char_props.write        = 1;                            // дȨ��
    char_md.p_char_user_desc        = (u8 *) User_Desc;             // ����������
    char_md.char_user_desc_size     = strlen(User_Desc);
    char_md.char_user_desc_max_size = strlen(User_Desc);
    char_md.p_char_pf               = NULL;                         // ��ʽ
    char_md.p_user_desc_md          = NULL;
    char_md.p_cccd_md               = &cccd_md;                     // �ͻ�����������������Ȩ�� 0x2902 �鿴Notify֪ͨ
    char_md.p_sccd_md               = NULL;

    // �������ͺ�������
    BLE_UUID.type = pnRF51->UUID_Type;
    BLE_UUID.uuid = NRF51_MESSAGE_CHARACTERISTIC;

    memset(&attr_md, 0, sizeof(attr_md));

    // ֻд����
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);

    attr_md.vloc    = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth = 0;
    attr_md.wr_auth = 0;
    attr_md.vlen    = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &BLE_UUID;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BLE_NRF51_MAX_DATA_LEN;

    return sd_ble_gatts_characteristic_add(pnRF51->Service_Handle,
                                           &char_md,
                                           &attr_char_value,
                                           &pnRF51->Message_Handle);
                                           
}// End of u32 nRF51_Message_Characteristic_Add(BLE_Service_Typedef * pnRF51) 

/*******************************************************************************
*                           ½��@2017-01-15
* Function Name  :  nRF51_Temp_Humi_Encode
* Description    :  ����¶�����
* Input          :  s16 sData    ��ʪ�ȶ�����
*                   u8 * pBuffer  ����
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u8 nRF51_Temp_Humi_Encode(s16 sTemp, u16 usHumi, u8 * pBuffer)
{
    u8 ucLen = 0;

    // 16����תASCII
    ucLen            = sprintf((char*)pBuffer, "T=%d.%d H=%d.%d", sTemp/10 , sTemp % 10, usHumi / 10, usHumi % 10);
    
    pBuffer[ucLen++] = 0;
    return ucLen;
    
}// End of u8 nRF51_Temp_Humi_Encode(s16 sTemp, u16 usHumi, u8 * pBuffer))



/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  nRF51_BLE_Private_Evt
* Description    :  nRF51�¼�����
* Input          :  BLE_Service_Typedef * pnRF51 �������
*                   ble_evt_t * pBLE_Evt  BLE�¼�
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_Private_Evt(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt)
{
    if ((pnRF51 == NULL) || (pBLE_Evt == NULL))
    {
        return;
    }

    switch (pBLE_Evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:

            nRF51_BLE_ON_Connect(pnRF51, pBLE_Evt);
            
            break;

        case BLE_GAP_EVT_DISCONNECTED:
        
            nRF51_BLE_ON_Disconnect(pnRF51);
            
            break;

        case BLE_GATTS_EVT_WRITE:
        
            nRF51_BLE_ON_Write(pnRF51, pBLE_Evt);
            
            break;
        
        default:
            // No implementation needed.
            break;
    }
    
}// End of void nRF51_BLE_Private_Evt(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  nRF51_BLE_ON_Write
* Description    :  BLE_GATTS_EVT_WRITE         �¼�����
* Input          :  BLE_Service_Typedef * pnRF51 �������
*                   ble_evt_t * pBLE_Evt  BLE�¼�
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_ON_Write(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt)
{
    ble_gatts_evt_write_t * p_evt_write = &pBLE_Evt->evt.gatts_evt.params.write;

    // ����ͨ��
    if ((p_evt_write->handle == pnRF51->Temp_Humi_Handle.cccd_handle))
    {
        if (ble_srv_is_notification_enabled(p_evt_write->data) && (p_evt_write->len == 2))
        {
            pnRF51->Temp_Humi_Listening_En = true;
            app_trace_log("    ��ʼ���� nRF51 Temp!\r\n");

        }
        else
        {
            pnRF51->Temp_Humi_Listening_En = false;
            app_trace_log("    ֹͣ���� nRF51 Temp!\r\n");
        }
    }
    else if ((p_evt_write->handle == pnRF51->Message_Handle.cccd_handle))
    {
        if (ble_srv_is_notification_enabled(p_evt_write->data) && (p_evt_write->len == 2))
        {
            pnRF51->Message_Listening_En = true;
            app_trace_log("    ��ʼ���� nRF51 Message!\r\n");

        }
        else
        {
            pnRF51->Message_Listening_En = false;
            app_trace_log("    ֹͣ���� nRF51 Message!\r\n");
        }    
    }
    // massage����
    else if (p_evt_write->handle == pnRF51->Message_Handle.value_handle)
    {
        nRF51_BLE_PS_Ack_Handler(p_evt_write->data, p_evt_write->len);
    }

    

}// End of void nRF51_BLE_ON_Write(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  nRF51_BLE_ON_Disconnect
* Description    :  �Ͽ�����
* Input          :  BLE_Service_Typedef * pnRF51 �������
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_ON_Disconnect(BLE_Service_Typedef * pnRF51)
{
    pnRF51->Conn_Handle            = BLE_CONN_HANDLE_INVALID;
    pnRF51->Temp_Humi_Listening_En = false;
    pnRF51->Message_Listening_En   = false;

}// End of void void nRF51_BLE_ON_Disconnect(BLE_Service_Typedef * pnRF51)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  nRF51_BLE_ON_Connect
* Description    :  ����
* Input          :  BLE_Service_Typedef * pnRF51 �������
*                   ble_evt_t * pBLE_Evt  BLE�¼�
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_BLE_ON_Connect(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt)
{
    pnRF51->Conn_Handle = pBLE_Evt->evt.gap_evt.conn_handle;

}// End of void void nRF51_BLE_ON_Connect(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  nRF51_BLE_String_Send
* Description    :  �����ַ���
* Input          :  BLE_Service_Typedef * pnRF51 �������
*                   u16 usValue_Handl           Ŀ��handle
*                   u8 * pString                ����������
*                   u16 usLen                   �����ͳ���
* Output         :  None
* Return         :  NRF_SUCCESS on success, otherwise an error code.
*******************************************************************************/
u32 nRF51_BLE_String_Send(BLE_Service_Typedef * pnRF51, u16 usValue_Handle, u8 * pString, u16 usLen)
{
    ble_gatts_hvx_params_t hvx_params;
    u32 uiResult;
    u8 ucRetry = 3;
    static u8 i = 0;

    if (pnRF51 == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if ((pnRF51->Conn_Handle == BLE_CONN_HANDLE_INVALID))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (usLen > BLE_NRF51_MAX_DATA_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    do
    {
        i++;
        pString[usLen++] = i;
        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = usValue_Handle;
        hvx_params.p_data = pString;
        hvx_params.p_len  = &usLen;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
    
        uiResult = sd_ble_gatts_hvx(pnRF51->Conn_Handle, &hvx_params);
        if (uiResult != NRF_SUCCESS)
        {
            nrf_delay_ms(10);
            ucRetry--;
        }
//        app_trace_log("BLE Send Success!\r\n");
        
    }while((uiResult != NRF_SUCCESS) && ucRetry);
    
    if (uiResult != NRF_SUCCESS)
    {
        app_trace_log("BLE Send Failed = %d!\r\n", uiResult);
        APP_ERROR_CHECK(uiResult);

    }
    
    return uiResult;
    
    
}// End of u32 nRF51_BLE_String_Send(BLE_Service_Typedef * pnRF51, u16 usValue_Handle, u8 * pString, u16 usLen)

/*******************************************************************************
*                           ½��@2017-01-16
* Function Name  :  Temp_BLE_Service_Update
* Description    :  �¶�ˢ��
* Input          :  BLE_Service_Typedef * pnRF51 �������
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_BLE_Service_Update(BLE_Service_Typedef * pnRF51)
{
    u32 Err_Code;
    u8 ucEncode[BLE_NRF51_MAX_DATA_LEN];
    u16 usLen;
    
    // ������״̬
    if (!pnRF51->Temp_Humi_Listening_En)
    {
        return;
    }

    // �������
    usLen = nRF51_Temp_Humi_Encode(Sensor.sTemp, Sensor.usHumi, ucEncode);
    
    // ���µ�������
    Err_Code = nRF51_BLE_String_Send(pnRF51, pnRF51->Temp_Humi_Handle.value_handle, ucEncode, usLen);
    if ((Err_Code != NRF_SUCCESS))
    {
        APP_ERROR_HANDLER(Err_Code);
    }
    
}// End of void Temp_BLE_Service_Update(BLE_Service_Typedef * pnRF51)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




