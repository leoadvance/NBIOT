/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_Storage_MAC.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  mac��ַ����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_Storage_MAC.h"
#include "Duck_Storage.h"
#include "nrf_soc.h"
#include "Communal_Flash.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Get_MAC(void);                                                     // ��ȡMAC��ַ
void MAC_Flash_Init(void);                                              // mac flash��ʼ��
u8 MAC_Save(u8 *ucMAC);                                                 // ����mac��ַ
u8 MAC_Read(u8 *ucMAC);                                                 // ��ȡmac��ַ
u8 MAC_Delete(void);                                                    // ɾ��mac��ַ


                                               
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-10
* Function Name  :  Get_MAC
* Description    :  ��ȡMAC��ַ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Get_MAC(void)
{

    u32 Err_Code;
    ble_gap_addr_t MAC_Addr;
    u8 ucTemp[MAC_FLASH_SIZE + 1];

    // û��MAC����
    if (MAC_Read(ucTemp) == 0)
    {
        

        Err_Code = sd_ble_gap_address_get(&MAC_Addr);
        APP_ERROR_CHECK(Err_Code); 

        // �������mac
        MIOT_Adv.MAC[0] = MAC_Addr.addr[5];
        MIOT_Adv.MAC[1] = MAC_Addr.addr[4];
        MIOT_Adv.MAC[2] = MAC_Addr.addr[3];
        MIOT_Adv.MAC[3] = MAC_Addr.addr[2];
        MIOT_Adv.MAC[4] = MAC_Addr.addr[1];
        MIOT_Adv.MAC[5] = MAC_Addr.addr[0];

        MAC_Addr.addr[5]  &= 0x3F;

            
        app_trace_log("\r\nδ��¼mac��ַ!\r\n");
        
    }
    else
    {
        // ����mac��ַ
        MAC_Addr.addr[5] = ucTemp[0];
        MAC_Addr.addr[4] = ucTemp[1];
        MAC_Addr.addr[3] = ucTemp[2];
        MAC_Addr.addr[2] = ucTemp[3];
        MAC_Addr.addr[1] = ucTemp[4];
        MAC_Addr.addr[0] = ucTemp[5]; 
        
        MIOT_Adv.MAC[0] = MAC_Addr.addr[5];
        MIOT_Adv.MAC[1] = MAC_Addr.addr[4];
        MIOT_Adv.MAC[2] = MAC_Addr.addr[3];
        MIOT_Adv.MAC[3] = MAC_Addr.addr[2];
        MIOT_Adv.MAC[4] = MAC_Addr.addr[1];
        MIOT_Adv.MAC[5] = MAC_Addr.addr[0];    
    }
    
    // д��mac��ַ
    MIOT_Adv.Frame_Control_Bit.MAC_Include = 1;
    MAC_Addr.addr_type =  BLE_GAP_ADDR_TYPE_PUBLIC; 
    Err_Code = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_NONE, &MAC_Addr);
    APP_ERROR_CHECK(Err_Code); 
        
    app_trace_log("Current MAC = %02X:%02X:%02X:%02X:%02X:%02X\r\n", MIOT_Adv.MAC[0],
                                                                     MIOT_Adv.MAC[1],
                                                                     MIOT_Adv.MAC[2],
                                                                     MIOT_Adv.MAC[3],
                                                                     MIOT_Adv.MAC[4],
                                                                     MIOT_Adv.MAC[5]);


    
    
}// End of void Get_MAC(void)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  MAC_Save
* Description    :  ����MAC��ַ
* Input          :  u8 *ucMAC �������mac
* Output         :  None
* Return         :  1 �ɹ� 0 ʧ��
*******************************************************************************/
u8 MAC_Save(u8 *ucMAC)
{
    u8 ucTemp[MAC_FLASH_SIZE + 2];
    u32 Err_Code;
    u8 ucReturn = 0;

    // ����mac
    ucTemp[0] = 0xAA;
    memcpy(&ucTemp[1], ucMAC, MAC_FLASH_SIZE);

    // дflash
    Err_Code = Communal_Flash_Update(&MAC_Flash_Handle, ucTemp, MAC_FLASH_SIZE + 2, 0);
    APP_ERROR_CHECK(Err_Code);

    // ��ȡ
    if (MAC_Read(ucTemp))
    {
        if (memcmp(ucTemp, ucMAC, MAC_FLASH_SIZE) == 0)
        {
            ucReturn = 1;
        }
    }

    return ucReturn;

}// End of u8 MAC_Save(u8 *ucMAC)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  MAC_Delete
* Description    :  ɾ��MAC��ַ
* Input          :  None
* Output         :  None
* Return         :  1 �ɹ� 0 ʧ��
*******************************************************************************/
u8 MAC_Delete(void)
{
    u32 Err_Code;
    u8 ucReturn = 0;
    u8 ucBuffer[MAC_FLASH_SIZE];

    // дflash
    Err_Code = Communal_Flash_Clear(&MAC_Flash_Handle, MAC_PSM_SIZE);
    APP_ERROR_CHECK(Err_Code);

    // ɾ���ɹ�
    if (Err_Code == NRF_SUCCESS)
    {

        ucReturn = 1;

        MAC_Read(ucBuffer);

    }

    return ucReturn;

}// End of u8 MAC_Delete(void)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  MAC_Read
* Description    :  ��ȡMAC��ַ
* Input          :  u8 *ucMAC �������mac
* Output         :  None
* Return         :  1 �ɹ� 0 ʧ��
*******************************************************************************/
u8 MAC_Read(u8 *ucMAC)
{
    u8 ucTemp[MAC_FLASH_SIZE + 1];
    u32 Err_Code;
    u8 ucReturn = 0;

    // ��
    System_Err.MAC = 1;
    Err_Code = Communal_Flash_Load(ucTemp, &MAC_Flash_Handle, MAC_FLASH_SIZE + 1, 0);

    // ��ȡ�ɹ�
    if ((Err_Code == NRF_SUCCESS) && ucTemp[0] == 0xAA)
    {
        memcpy(ucMAC, &ucTemp[1], MAC_FLASH_SIZE); 
        System_Err.MAC = 0;

        ucReturn = 1;
    }

    return ucReturn;
    
}// End of u8 MAC_Read(u8 *ucMAC)

/*******************************************************************************
*                           ½��@2017-02-15
* Function Name  :  MAC_Flash_Init
* Description    :  MAC flash��ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void MAC_Flash_Init(void)
{
    u32 Err_Code;    
    pstorage_module_param_t param;
    
    // Register
    param.block_size  = MAC_PSM_SIZE;
    param.block_count = MAC_PSM_BLOCK;
    param.cb          = Duck_Storage_Callback;

    Err_Code = pstorage_register(&param, &MAC_Flash_Handle);
    if (Err_Code == NRF_SUCCESS) 
    {
        app_trace_log("MAC flash register succ\r\n");
    } 
    else 
    {
        app_trace_log("MAC flash register fail\r\n");
    }

    
}// End of static void MAC_Flash_Init(void)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/










