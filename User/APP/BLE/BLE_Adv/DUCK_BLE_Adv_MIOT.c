/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Adv_MIOT.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  �����㲥����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Adv_MIOT.h"
#include <stdlib.h>
#include <string.h>
#include "Duck_BLE_Adv.h"
#include "ble_srv_common.h"


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT);// MIOT���ݴ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-01-10
* Function Name  :  BLE_MIOT_Service_Package
* Description    :  MIOT���ݴ��
* Input          :  u16 usEvent         ��������¼�
*                   u8* pService_Data   ����
*                   MIOT_Typedef *MIOT  Դ����
* Output         :  None
* Return         :  ������ݳ���
*******************************************************************************/
u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT)
{
    u8 ucLen = 0;

    // Frame_Control����
    ucLen += uint16_encode(MIOT->Frame_Control, &pService_Data[ucLen]);

    // Product ID
    ucLen += uint16_encode(MIOT_PRODUCT_ID, &pService_Data[ucLen]);

    // Frame_Counter
    pService_Data[ucLen++] = MIOT->Frame_Counter;

    // MAC
    if (MIOT->Frame_Control_Bit.MAC_Include)
    {
        pService_Data[ucLen++] = MIOT->MAC[5];
        pService_Data[ucLen++] = MIOT->MAC[4];
        pService_Data[ucLen++] = MIOT->MAC[3];
        pService_Data[ucLen++] = MIOT->MAC[2];
        pService_Data[ucLen++] = MIOT->MAC[1];
        pService_Data[ucLen++] = MIOT->MAC[0];
    }

    // Capability
    if (MIOT->Frame_Control_Bit.Capability_Include)
    {
        pService_Data[ucLen++] = MIOT->Capability;
    }

    // �¼�
    if (MIOT->Frame_Control_Bit.Event_Include)
    {
        // �¼�ID
        ucLen += uint16_encode(MIOT->Event_ID, &pService_Data[ucLen]); 

        // ��ʪ��
        if (usEvent == MIOT_EVENT_ID_TH)
        {   
            // �¼����� �¶� ʪ��
            pService_Data[ucLen++] = MIOT_EVENT_TH_LEN;
            ucLen += uint16_encode(MIOT->Temp_Val, &pService_Data[ucLen]);
            pService_Data[ucLen++] = MIOT->Humi_Val;
        }
        // ����
        else if (usEvent == MIOT_EVENT_ID_BAT)
        {
            // �¼����� ����
            pService_Data[ucLen++] = MIOT_EVENT_BAT_LEN;
            pService_Data[ucLen++] = MIOT->Bat_Percent;
        }
        // ��
        else if (usEvent == MIOT_EVENT_ID_BOND)
        {
            // �¼����� ��
            pService_Data[ucLen++] = MIOT_EVENT_BOND_LEN;
            ucLen += uint16_encode(MIOT_EVENT_ID_TH, &pService_Data[ucLen]);
        }
        // hall
        else if (usEvent == MIOT_EVENT_ID_HALL)
        {
            // hall�¼��������� 
            pService_Data[ucLen++] = MIOT_EVENT_HALL_LEN;
            pService_Data[ucLen++] = Hall.Magnet_Near;
        }
    }
    
    return ucLen;
    
}// End of u8 BLE_MIOT_Service_Package(u16 usEvent, u8* pService_Data, MIOT_Typedef *MIOT)





/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




