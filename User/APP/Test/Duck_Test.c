/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_Test.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/08/2017
* Description        :  ���Գ���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Duck_Test.h"
#include "Duck_Storage_Token.h"
#include "Battery.h"
#include "Duck_Storage_MAC.h"
#include "Debug.h"
#include "WDT.h"
#include "Temp_Humi.h"
#include "Hall.h"
#include "Temp_Humi_SHT30.h"
#include <string.h>
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Duck_Test_Handler(u8* ucData, u16 usLen);                          // �������ݴ���
void Duck_Test_Ack(u8 *ucCMD, u8* ucData, u16 usLen);                   // ����Ӧ��
void Duck_CMD_Test_Handler(void);                                       // ���������
void Duck_CMD_MAC_Handler(u8 *ucMAC);                                   // ����дmac�����

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Duck_Test_Handler
* Description    :  �������ݴ���
* Input          :  u8* ucData  ����������
*                   u16 usLen   ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_Test_Handler(u8* ucData, u16 usLen)
{
    u16 usAdd_Sun = 0;
    u8 i;
    usLen -= 2;
    u8 ucCMD[16];
    u8 ucCMD_Len = 0;
    u8 ucBuffer[16];

    // ι��
    WDT_Feed();
    
    // �ۼ�
    for (i = 0; i < usLen; i++)
    {
        usAdd_Sun += ucData[i];
    }

    //���ۼ�У��
    if ((ucData[usLen] << 8) + ucData[usLen + 1] != usAdd_Sun)
    {
        app_trace_log("���������ۼ�У�����!\r\n");
        return;
    }

    // ��ȡ������
    ucCMD_Len = ucData[2];
    memcpy(ucCMD, &ucData[3], ucCMD_Len);

    // ��ʼ����  
    if (memcmp(ucCMD, TEST_CMD_START, ucCMD_Len) == 0)
    {
        // Ӧ��
        Duck_Test_Ack(TEST_CMD_START, "Success", strlen("Success"));    
    }

    // дmac
    else if (memcmp(ucCMD, TEST_CMD_MAC, ucCMD_Len) == 0)
    {
        // ��ȡmac
        memcpy(ucBuffer, &ucData[3 + 1 + ucCMD_Len], MAC_FLASH_SIZE);
        
        Duck_CMD_MAC_Handler(ucBuffer);
        
    }
    // ɾ��mac
    else if (memcmp(ucCMD, TEST_CMD_DELETE_MAC, ucCMD_Len) == 0)
    {
        // д�ɹ�
        if (MAC_Delete())
        {
            Duck_Test_Ack(TEST_CMD_DELETE_MAC, "Success", strlen("Success"));  
        }
        else
        {
            // ʧ��
            Duck_Test_Ack(TEST_CMD_DELETE_MAC, "Error", strlen("Error"));  
        }
        
    }
    // дtoken
    else if (memcmp(ucCMD, TEST_CMD_TOKEN, ucCMD_Len) == 0)
    {
        // ��ȡtoken
        memcpy(ucBuffer, &ucData[3 + 1 + ucCMD_Len], TOKEN_FLASH_SIZE);

        // д�ɹ�
        if (Token_Save(ucBuffer))
        {
            Duck_Test_Ack(TEST_CMD_TOKEN, "Success", strlen("Success"));  
        }
        else
        {
            // ʧ��
            Duck_Test_Ack(TEST_CMD_TOKEN, "Error", strlen("Error"));  
        }
        
    }
    // ��ʽ����
    else if (memcmp(ucCMD, TEST_CMD_TEST, ucCMD_Len) == 0)
    {

        Duck_CMD_Test_Handler();
    }
    
    
}// End of void Duck_Test_Handler(u8* ucData, u16 usLen)

/*******************************************************************************
*                           ½��@2017-03-09
* Function Name  :  Duck_CMD_MAC_Handler
* Description    :  ����дmac�����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_CMD_MAC_Handler(u8 *ucMAC)
{
    // ��mac
    if (System_Err.MAC == 1)
    {

        // д�ɹ�
        if (MAC_Save(ucMAC))
        {
            Duck_Test_Ack(TEST_CMD_MAC, "Success", strlen("Success"));  
        }
        else
        {
            // ʧ��
            Duck_Test_Ack(TEST_CMD_MAC, "Error", strlen("Error"));  
        }
    }
    else
    {
        // ����mac����
        Duck_Test_Ack(TEST_CMD_MAC, "Lock", strlen("Lock"));  
    }
    
}// End of void Duck_CMD_MAC_Handler(u8 *ucMAC)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Duck_CMD_Test_Handler
* Description    :  ���������
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Duck_CMD_Test_Handler(void)
{

    u8 *Buffer;
    u8 Buffer_Len = 0;
    float fTemp, fHumi;
    s16 Temp, Humi;
    
    Buffer = malloc(128);
    
    // ��ȡ��ѹ
    Battery_Handle();

    // ��ȡ����״̬
    Hall_Update();

    // ��ȡ�¶�
    if (SHT3x_Get_Temp_Humi(&fTemp, &fHumi))
    {
        fTemp = (fTemp + 0.05) * 10;
        Temp  = (s16)fTemp;
        fHumi = (fHumi + 0.05) * 10;
        Humi  = (s16)fHumi;
        Buffer_Len = sprintf((char *)Buffer, "Temp = %d.%01d, Humi = %d.%01d, ", Temp / 10, abs(Temp) % 10, Humi / 10, Humi % 10);    
    }
    else
    {
        Buffer_Len = sprintf((char *)Buffer, "Temp = --, Humi = --, ");      
    }

    // ��ѹ��������
    Buffer_Len += sprintf((char *)&Buffer[Buffer_Len], "Vol = %dmV, Hall = %d", Battery_ADC.Vol_mv, Hall.Magnet_Near); 

    // ack
    Duck_Test_Ack(TEST_CMD_TEST, Buffer, Buffer_Len);
    
    // �ͷŻ���
    free(Buffer);
    
}// End of void Duck_CMD_Test_Handler(void)

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
void Duck_Test_Ack(u8 *ucCMD, u8* ucData, u16 usLen)
{
    u8 Buffer[128];
    u8 Buffer_Len = 0;
    u8 i;
    u16 usAdd_Sun = 0;

    // ��ͷ
    Buffer[Buffer_Len++] = 'C';
    Buffer[Buffer_Len++] = 'G';

    // ������
    Buffer[Buffer_Len++] = strlen((const char *)ucCMD);
    memcpy(&Buffer[Buffer_Len], ucCMD, Buffer[Buffer_Len - 1]);
    Buffer_Len += Buffer[Buffer_Len - 1];

    // ����ʵ��
    Buffer[Buffer_Len++] = usLen;
    if (usLen)
    {
        memcpy(&Buffer[Buffer_Len], ucData, Buffer[Buffer_Len - 1]);
    }
    Buffer_Len += Buffer[Buffer_Len - 1];

    // �ۼ�
    for (i = 0; i < Buffer_Len; i++)
    {
        usAdd_Sun += Buffer[i];
    }
    Buffer[Buffer_Len++] = (usAdd_Sun >> 8) & 0xFF;
    Buffer[Buffer_Len++] = (usAdd_Sun >> 0) & 0xFF;


    // ��ʱ �������
    

    // ��������
    Debug_Send(Buffer, Buffer_Len);

}// End of void Duck_Test_Ack(u8 *ucCMD, u8* ucData, u16 usLen)

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




