/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Test_Ack.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/10/2017
* Description        :  ���Է���Ӧ��
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_BLE_Test_Ack.h"
#include "Duck_BLE_Private_Service.h"

#include <stdlib.h>
#include <string.h>


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen);                  // Duckps����Ӧ����
void Duck_BLE_App_Ack_Handler(u8 * p_data, u16 usLen);                 // Duck��������
void Duck_App_Ack(u8 *ucCMD, u8* ucData, u16 usLen);                   // Ӧ��
void Duck_BLE_CMD_Table_Handler(u8 * p_data);
u8 Duck_BLE_Test_LCD_Prepare(void);                                     // ׼��������ʾ����

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-03-10
* Function Name  :  Duck_BLE_PS_Ack_Handler
* Description    :  Duck�������ݴ���
* Input          :  u8* p_data          ��������ָ��
*                   u16 usLen           ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen)
{

    app_trace_log("    �յ���Ϣ!\r\n");

    // Duck��������
    if (p_data[0] == 'C' && p_data[1] == 'G')
    {
        Duck_BLE_App_Ack_Handler(&p_data[2], usLen - 2);
    }
    else
    {
        Duck_BLE_CMD_Table_Handler(p_data);   
    }
    
}// End of void Duck_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen)



/*******************************************************************************
*                           ½��@2017-03-10
* Function Name  :  Duck_BLE_App_Ack_Handler
* Description    :  Duck�������ݴ���
* Input          :  u8* p_data          ��������ָ��
*                   u16 usLen           ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_App_Ack_Handler(u8 * p_data, u16 usLen)
{

    
    
}// End of void Duck_BLE_App_Ack_Handler(u8 * p_data, u16 usLen)

/*******************************************************************************
*                           ½��@2017-03-13
* Function Name  :  Duck_BLE_Test_LCD_Prepare
* Description    :  ׼��������ʾ����
* Input          :  None
* Output         :  None
* Return         :  1 �ɹ� 0 ʧ��
*******************************************************************************/
u8 Duck_BLE_Test_LCD_Prepare(void)
{


    return 1;
    
}// End of u8 Duck_BLE_Test_LCD_Prepare(void)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Duck_Test_Ack
* Description    :  ��������Ӧ��
* Input          :  u8 *ucCMD   ���ظ�����
*                   u8* ucData  ���ظ�����
*                   u16 usLen   ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_App_Ack(u8 *ucCMD, u8* ucData, u16 usLen)
{
    u8 Buffer[32];
    u8 Buffer_Len = 0;
    u32 Err_Code;

    // ����
    if (Duck_BLE_Service.Message_Listening_En != 1)
    {
        app_trace_log("    Message Service δ����!\r\n");
        return;
    }

    // ��ͷ
    Buffer[Buffer_Len++] = 'C';
    Buffer[Buffer_Len++] = 'G';

    // 2�ֽ�������
    memcpy(&Buffer[Buffer_Len], ucCMD, 2);
    Buffer_Len += 2;

    // ����ʵ��
    if (usLen)
    {
        memcpy(&Buffer[Buffer_Len], ucData, usLen);
    }
    Buffer_Len += usLen;
    app_trace_log("    ack!\r\n");
    Err_Code = Duck_BLE_String_Send(&Duck_BLE_Service, Duck_BLE_Service.Message_Handle.value_handle, Buffer, Buffer_Len);
    if ((Err_Code != NRF_SUCCESS))
    {
        APP_ERROR_HANDLER(Err_Code);
    }
    
//app_trace_log("    Message Service �ظ�\r\n");

}// End of void Duck_App_Ack(u8 *ucCMD, u8* ucData, u16 usLen)

/*******************************************************************************
*                           ½��@2017-03-15
* Function Name  :  Duck_BLE_CMD_Table_Handler
* Description    :  Duck�������ݴ���
* Input          :  u8* p_data          ��������ָ��
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_BLE_CMD_Table_Handler(u8 * p_data)
{
    u32 Err_Code;
    const char CMD_Table_1[] = {0x77, 0x68, 0x6F, 0x20, 0x61, 0x72, 0x65, 0x20, 0x79, 0x6F, 0x75};
    const char CMD_Table_2[] = {0x49, 0x27, 0x6D, 0x20, 0x44, 0x75, 0x63, 0x6B, 0x21};
    const char CMD_Table_3[] = {0x4C, 0x65, 0x6F, 0x20, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x20, 0x6D, 0x65, 0x21};

    if (memcmp(p_data, CMD_Table_1, strlen(CMD_Table_1)) == 0)
    {
        Err_Code = Duck_BLE_String_Send(&Duck_BLE_Service, Duck_BLE_Service.Message_Handle.value_handle, (u8 *)CMD_Table_2, strlen(CMD_Table_2));
        Err_Code = Duck_BLE_String_Send(&Duck_BLE_Service, Duck_BLE_Service.Message_Handle.value_handle, (u8 *)CMD_Table_3, strlen(CMD_Table_3));
        if ((Err_Code != NRF_SUCCESS))
        {
            APP_ERROR_HANDLER(Err_Code);
        }    
    }

}// End of void Duck_BLE_CMD_Table_Handler(u8 * p_data)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




