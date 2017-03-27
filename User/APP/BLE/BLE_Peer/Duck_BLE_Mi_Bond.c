/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Mi_Bond.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/15/2017
* Description        :  Duck_BLE ��
*                       �󶨳ɹ� ��ʱ5s
*                       ��ʧ�� ��ʱ30s��ʱ�˳�
*                       ����ʱ���������볬ʱʱ��
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Mi_Bond.h"
#include "nrf51.h"
#include "nrf_delay.h"
#include "app_gpiote.h"
#include "softdevice_handler_appsh.h"
#include "pstorage.h"
#include "app_trace.h"
#include "ble_mis.h"
#include "mibeacon.h"
#include "LCD_BT.h"
#include "Communal_Flash.h"
#include <string.h>

/* Private variables ---------------------------------------------------------*/
static pstorage_handle_t Mi_Bond_Flash_Handler;                         // С������flash����

/* Private function prototypes -----------------------------------------------*/
void Mi_Bond_Start(void);                                               // ������
void Mi_Bond_Stop(void);                                                // ������
void Duck_BLE_Mi_Services_Init(void);                                   // С�׷����ʼ��
void Mi_Bond_Status_Handler(ble_mis_evt_type_t evt);                    // ��״̬����
void Mi_Bond_Timeout_Check(void);                                       // �󶨳�ʱ���ж�
static void Mi_Bond_Flash_Init(void);                                   // miflash��ʼ��
static void Mi_Bond_Flash_Callback(pstorage_handle_t *  handle, u8   OP_Code, u32  Err_Code, u8*  pData, u32 uiData_Len); // �ص�
int Mi_Bond_Flash_Write(u32 uiAddr, u8* pData, u16 usLen);              // дflash
int Mi_Bond_Flash_Read(u32 uiAddr, u8* pData, u16 usLen);               // ��flash

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Status_Handler
* Description    :  mi��״̬����
* Input          :  ble_mis_evt_type_t evt ״̬
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Status_Handler(ble_mis_evt_type_t evt)
{
    if (evt == BLE_MIS_EVT_BOND_SUCC) 
    {
        // �󶨳ɹ� ��ʱ�˳���״̬
        Sys_Bond.Time_Left = MIOT_BOND_STOP_DELAY;
        Sys_Bond.Count++;
        app_trace_log("app bond succ\r\n");
    } 
    else 
    {

        app_trace_log("app bond fail\r\n");
  
    }
    
}// End of void Mi_Bond_Status_Handler(ble_mis_evt_type_t evt)


/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Flash_Write
* Description    :  mi��дflash
* Input          :  u32 uiAddr ������ַ
*                   u8* pData  Ҫд�������
*                   u16 usLen  ����
* Output         :  None
* Return         :  None
*******************************************************************************/
int Mi_Bond_Flash_Write(u32 uiAddr, u8* pData, u16 usLen)
{
    u32  Err_Code;
    pstorage_handle_t *Base_Handle = (pstorage_handle_t*)uiAddr;

    // д����
    Err_Code = Communal_Flash_Update(Base_Handle, pData, usLen, 0);
    return Err_Code;
    
}// End of int Mi_Bond_Flash_Write(u32 uiAddr, u8* pData, u16 usLen)


/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Flash_Write
* Description    :  mi��дflash
* Input          :  u32 uiAddr ������ַ
*                   u8* pData  ���ݻ���
*                   u16 usLen  ����
* Output         :  None
* Return         :  None
*******************************************************************************/
int Mi_Bond_Flash_Read(u32 uiAddr, u8* pData, u16 usLen)
{
    u32  Err_Code;
    pstorage_handle_t *Base_Handle = (pstorage_handle_t*)uiAddr;

    // ��ȡ
    Err_Code = Communal_Flash_Load(pData, Base_Handle, usLen, 0);
    return Err_Code;
    
}// End of int Mi_Bond_Flash_Read(u32 uiAddr, u8* pData, u16 usLen)

/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Flash_Callback
* Description    :  mi��flash�ص�
* Input          :  u32  Err_Code   �������
*                   u8   OP_Code    ������(����ԭ��) 
*                   u8*  pData      Ҫд���ֵ
*                   u32  Data_Len   ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
static void Mi_Bond_Flash_Callback(pstorage_handle_t *  handle,
                                   u8   OP_Code,
                                   u32  Err_Code,
                                   u8*  pData,
                                   u32  uiData_Len)
{
    if (Err_Code != NRF_SUCCESS)
    {
        // Load operation failed.
        app_trace_log("[E]: flash operation error, opcode:%d\r\n", OP_Code);
        return ;
    }
    
    app_trace_log("Mi_Bond_Flash_Callback!\r\n");


    switch (OP_Code) 
    {
        case PSTORAGE_LOAD_OP_CODE:
        {
        
            // Load operation successful.
            app_trace_log("[D]: load succ, len = %d\r\n", uiData_Len);
            // memcpy(mis_token, p_data, MIIO_BLE_TOKEN_LEN);
            //memcpy(mis_sn, p_data + MIIO_BLE_TOKEN_LEN, MIIO_BLE_SN_LEN);
            //memcpy(mis_beaconKey, p_data + MIIO_BLE_TOKEN_LEN + MIIO_BLE_SN_LEN, MIIO_BLE_BEACONKEY_LEN);
            //LOG_DEBUG("retrive token, %02x %02x\r\n", mis_token[10], mis_token[11]);
            // Source memory can now be reused or freed.

        }break;

        case PSTORAGE_STORE_OP_CODE:
        {
            app_trace_log("[D]: store succ. len = %d\r\n", uiData_Len);
            
        }break;

        case PSTORAGE_UPDATE_OP_CODE:
        {
            app_trace_log("[D]: update succ. len = %d\r\n", uiData_Len);
            
        }break;

        case PSTORAGE_CLEAR_OP_CODE:
        {
            app_trace_log("[D]: clear succ. len = %d\r\n", uiData_Len);
            
        }break;

        default:
            break;
            
    }

    // �ͷ�flashռ��
    Flash_Used = 0;
    
}// End of static void Mi_Bond_Flash_Callback

/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Flash_Init
* Description    :  mi����flash��ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
static void Mi_Bond_Flash_Init(void)
{
    u32 Err_Code;    
    pstorage_module_param_t param;
    
    // Register
    param.block_size  = MISERVICE_PSM_SIZE;
    param.block_count = MISERVICE_PSM_BLOCK;
    param.cb          = Mi_Bond_Flash_Callback;

    Err_Code = pstorage_register(&param, &Mi_Bond_Flash_Handler);
    if (Err_Code == NRF_SUCCESS) 
    {
        app_trace_log("[D]: miio ble flash register succ\r\n");
    } 
    else 
    {
        app_trace_log("[E]: miio ble flash register fail\r\n");
    }
    
}// End of static void Mi_Bond_Flash_Init(void)

/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Duck_BLE_Mi_Services_Init
* Description    :  �󶨷����ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_Mi_Services_Init(void)
{
    uint32_t       Err_Code;
    ble_mis_init_t Mi_Bond_Init;
    char ver[MIIO_BLE_VER_LEN] = {"1.0.1_1"};

    // Init FLASH
    Mi_Bond_Flash_Init();

    // Init Mi Service
    Mi_Bond_Init.productId     = MIOT_PRODUCT_ID;
    Mi_Bond_Init.relation      = MIIO_BLE_DEV_RELATION_WEAK;
    Mi_Bond_Init.evt_handler   = (ble_mis_evt_handler_t)Mi_Bond_Status_Handler;

    Mi_Bond_Init.flashBaseAddr = (uint32_t)&Mi_Bond_Flash_Handler;
    Mi_Bond_Init.flashWriteFn  = Mi_Bond_Flash_Write;
    Mi_Bond_Init.flashReadFn   = Mi_Bond_Flash_Read;
    memcpy(Mi_Bond_Init.version, ver, MIIO_BLE_VER_LEN); 
    
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Mi_Bond_Init.mis_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&Mi_Bond_Init.mis_attr_md.write_perm);

    Err_Code = ble_mis_init(&Mi_Bond_Init);
    APP_ERROR_CHECK(Err_Code);
    
}// End of void Duck_BLE_Mi_Services_Init(void)

/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Start
* Description    :  ������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Start(void)
{

    // ˢ�°�ʱ��
    Sys_Bond.Time_Left = MIOT_EVENT_ID_BOND_DURATION; 

    // �ǰ�̬
    if (Sys_Bond.Adv_En == 0)
    {
        // �����̬
        Sys_Bond.Adv_En = 1;
        Sys_Bond.Count  = 0;

        // ׼������
        MIOT_Adv.Frame_Control_Bit.Factory_New        = MIBEACON_ITEM_FACTORY_NEW;
        MIOT_Adv.Frame_Control_Bit.Capability_Include = 1;


        // ������ �ɼ��� �ɰ�
        MIOT_Adv.Capability_Bit.Connectable           = 1;
        MIOT_Adv.Capability_Bit.Encrypt_Ability       = 1;
        MIOT_Adv.Capability_Bit.Bond_Ability          = MIBEACON_BOND_PREBINDING;


        // ��λLED��˸
        Sys_Bond.Blink_Interval = 0;
        LCD_BT_Update_Blink();

        app_trace_log("---------------------��ʼ������!\r\n");
    }
    else
    {
        app_trace_log("---------------------����������!\r\n");    
    }

    

}// End of void Mi_Bond_Start(void)

/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  Mi_Bond_Stop
* Description    :  ������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Stop(void)
{

    // ˢ�°�ʱ��
    Sys_Bond.Time_Left = 0; 

    // �ǰ�̬
    Sys_Bond.Adv_En =0;


    // ȡ��������λ
    MIOT_Adv.Frame_Control_Bit.Factory_New        = 0;
    MIOT_Adv.Frame_Control_Bit.Capability_Include = 0;

    // ������ʾLOGO
    LCD_BT_Update_Signal(1);
    
    app_trace_log("---------------------����������!\r\n");

}// End of void Mi_Bond_Stop(void)

/*******************************************************************************
*                           ½��@2017-02-24
* Function Name  :  Mi_Bond_Timeout_Check
* Description    :  �󶨳�ʱ�ж�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Mi_Bond_Timeout_Check(void)
{
    // �ڹ㲥��
    if (Sys_Bond.Adv_En)
    {
        // ����;�в����㳬ʱ
        if (Button.Long == 0)
        {
            if (Sys_Bond.Time_Left)
            {
                Sys_Bond.Time_Left--;   
            }
        }
        // ��ʱ�˳��󶨹㲥
        if (Sys_Bond.Time_Left == 0)
        {
            // ������
            Mi_Bond_Stop();
            app_trace_log("��ʱ�˳��󶨹㲥!\r\n"); 
        }


        // blink
        if (Sys_Bond.Blink_Interval == 0)
        { 
            LCD_BT_Update_Blink();
        }
    }

}// End of void Mi_Bond_Timeout_Check(void)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




