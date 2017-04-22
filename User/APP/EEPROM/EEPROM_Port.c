/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  EEPROM_Port.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM��������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "EEPROM_Port.h"
#include "nrf_gpio.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_delay.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);    // EEPROM��ȡ����
u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);   // дҳ����
u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len); // EEPROMд����
u8 EEPROM_Chip_Init(void);                                              // оƬ��ʼ��
void EEPROM_Variable_Init(void);                                        // EEPROM������ʼ��
u8   EEPROM_Port_Init(void);                                            // EEPROM�˿ڳ�ʼ��  

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2015-04-26
* Function Name  :  EEPROM_Read_Buffer
* Description    :  EEPROM������
* Input          :  u16 usRead_Addr Ҫ��ȡ�ĵ�ַ
*                   u8* pBuffer     ����ָ��
*                   u16 usRead_Len  ��ȡ����
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)
{
    u8 Transfer_Succeeded = 1;
    u8 ucRead_Addr[2];
    
    if(usRead_Len == 0)
    {
        return 1;
    }
    
    // ׼����ַ����
    ucRead_Addr[0] = (usRead_Addr >> 8) & 0xFF;
    ucRead_Addr[1] = (usRead_Addr >> 0) & 0xFF;
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, EEPROM_WRITE_ADDR, ucRead_Addr, 2, SW_I2C_DONT_SEND_STOP);
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, EEPROM_READ_ADDR, pBuffer, usRead_Len, SW_I2C_NEED_SEND_STOP);

    if (Transfer_Succeeded == 0)
    {
        System_Err.EEPROM = 1;
  
    }
    else
    {
        System_Err.EEPROM = 0;
    }
    return Transfer_Succeeded;
    
}// End of u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)

/*******************************************************************************
*                           ½��@2015-04-26
* Function Name  :  EEPROM_Write_Page
* Description    :  EEPROMдҳ����
* Input          :  u16 usWrite_Addr    Ҫ��ȡ�ĵ�ַ
*                   u8* pBuffer         ����ָ��
*                   u16 usWrite_Len     д�볤�� < EEPROM_PAGE_SIZE;
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    u8 Transfer_Succeeded = 1;
    u8 ucWrite_Addr[2];

    // ���ȱ���
    if(usWrite_Len == 0)
    {
        return 1;
    }

    // ׼����ַ����
    ucWrite_Addr[0] = (usWrite_Addr >> 8) & 0xFF;
    ucWrite_Addr[1] = (usWrite_Addr >> 0) & 0xFF;

    // ����д����
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, EEPROM_WRITE_ADDR, ucWrite_Addr, 2, SW_I2C_DONT_SEND_STOP);

    // д����
    while (usWrite_Len-- && Transfer_Succeeded)
    {
        Transfer_Succeeded &= SW_IIC_Write_Byte(&Communal_IIC_2, *pBuffer);
        pBuffer++;
    }

    // ����ֹͣ����
    Transfer_Succeeded &= SW_I2C_Stop_Condition(&Communal_IIC_2);
    
  
    // ��ʱ ��֤д�������
    nrf_delay_ms(EEPROM_WRITE_PAGE_TIME);

    return Transfer_Succeeded;

}// End of u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           ½��@2015-04-26
* Function Name  :  EEPROM_Write_Buffer
* Description    :  EEPROMд����
* Input          :  u16 usWrite_Addr    Ҫ��ȡ�ĵ�ַ
*                   u8* pBuffer         ����ָ��
*                   u16 usWrite_Len     д�볤�� 
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    u8 Transfer_Succeeded = 1;  
    u16 usTemp;

    // ������дָ��͵�ַ
    u8 Read_Buffer[36];
    u8 *Write_Buffer = pBuffer;
    u16 usRead_Addr  = usWrite_Addr;
    u16 usRead_Len   = usWrite_Len;

    // ���ȱ���
    if (usWrite_Len == 0)
    {
        return 1;
    }
    else 
    {
        // ����Խ��
        if (usWrite_Addr + usWrite_Len > EEPROM_CHIP_SIZE)
        {
            return 0;
        }
    }
   
    while(usWrite_Len && Transfer_Succeeded)
    {

        // ��ҳд������
        usTemp = usWrite_Addr % EEPROM_PAGE_SIZE;
        if (usTemp + usWrite_Len < EEPROM_PAGE_SIZE)
        {
            Transfer_Succeeded &= EEPROM_Write_Page(usWrite_Addr, pBuffer, usWrite_Len);
            usWrite_Len = 0;
        }
        else
        {
            // ����д�볤��
            usTemp = EEPROM_PAGE_SIZE - usTemp; 
            Transfer_Succeeded &= EEPROM_Write_Page(usWrite_Addr, pBuffer, usTemp);  
            usWrite_Addr += usTemp;
            pBuffer      += usTemp;
            usWrite_Len  -= usTemp;
        }
    }
   
    // �Ƚ�д������
    if (Transfer_Succeeded)
    {
        if (Read_Buffer)
        {
            // ��ȡд�����ݲ��Ƚ�
            Transfer_Succeeded &= EEPROM_Read_Buffer(usRead_Addr, Read_Buffer, usRead_Len);
               
            if (Transfer_Succeeded)
            {
                for (usTemp = 0; usTemp < usRead_Len; usTemp++)
                {
                    if (Read_Buffer[usTemp] != Write_Buffer[usTemp])
                    {
                        Transfer_Succeeded = 0;
                        break;
                    }
                }
            }
        }
        else
        {
            Transfer_Succeeded = 0;  
        }  

          
    }

    if (Transfer_Succeeded == 0)
    {
        System_Err.EEPROM = 1;
        app_trace_log("EEPROM Write Err!");   
    }
    else
    {
        System_Err.EEPROM = 0;
    }
    
    return Transfer_Succeeded;
    
}// End of u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           ½��@2015-05-05
* Function Name  :  EEPROM_Chip_Init
* Description    :  EEPROMоƬ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  ����1�ɹ� ����0ʧ��
*******************************************************************************/
u8 EEPROM_Chip_Init(void)
{

    u8 ucResult = 1;

    // ������ʼ��
    EEPROM_Variable_Init();

    // �ܽų�ʼ��
    ucResult &= EEPROM_Port_Init();

        
// ��EEPROM
#ifdef DONT_USE_EEPROM


    
#else

    const u8 EEPROM_Test_Data = 0x55;
    
    // �ܽų�ʼ���ɹ�
    if (ucResult)
    {
        ucResult &= EEPROM_Write_Buffer(EEPROM_TEST_ADDR, (u8*)&EEPROM_Test_Data, 1);      
    }
    

#endif


    System_Err.EEPROM = ucResult ^ 0x01;
    
    if (System_Err.EEPROM == 0)
    {
        app_trace_log("EEPROM Init Success!\r\n");
    }

    return ucResult;
    
}// End of u8 EEPROM_Chip_Init(void)

/*******************************************************************************
*                           ½��@2014-09-04
* Function Name  :  EEPROM_Variable_Init
* Description    :  EEPROM������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void EEPROM_Variable_Init(void)
{


    
}// End of void EEPROM_Variable_Init(void)

/*******************************************************************************
*                           ½��@2015-04-23
* Function Name  :  EEPROM_Port_Init
* Description    :  EEPROM�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 EEPROM_Port_Init(void)
{
    u8 Transfer_Succeeded = 1; 

    
    return (Transfer_Succeeded);
       
}// End of u8  EEPROM_Port_Init(void)

/******************* (C) COPYRIGHT 2015 ½�� **************END OF FILE*********/

