/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Temp_Humi_SHT30.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ��ʪ��Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi_SHT30.h"
#include "nrf_gpio.h"




/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
u8 SHT3x_Read_SN(u8 *ucSN);                                             // ��ȡSN
u8 SHT3x_Soft_Reset(void);                                              // ��λ
u8 SHT3x_Check_CRC(u8 *ucData, u8 ucLen, u8 ucCheck_Sum);               // CRCУ��
u8 SHT3x_Get_Temp_Humi(float *fTemp, float *fHumi);                     // ��ȡ��ʪ��
float SHT3x_CalcTemperature(u16 usValue);                               // �����¶�
float SHT3x_CalcHumidity(u16 usValue);                                  // ����ʪ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  SHT3x_Read_SN
* Description    :  ��SN
* Input          :  u8 ��ȡ��SN
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 SHT3x_Read_SN(u8 *ucSN)
{

    return(Temp_Humi_Read_Register(CMD_READ_SERIALNBR, ucSN, 4));

}// End of u8 SHT3x_Read_SN(u8 *ucSN)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  SHT3x_Get_Temp_Humi
* Description    :  ��ȡ��ʪ��
* Input          :  float *fTemp    �¶�����
*                   float *fHumi    ʪ������
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 SHT3x_Get_Temp_Humi(float *fTemp, float *fHumi)
{
    u8 ucResult = 0;
    u8 ucRead_Data[6];
    
    ucResult = Temp_Humi_Read_Register(CMD_MEAS_CLOCKSTR_L, ucRead_Data, 6);
    
    if (ucResult)
    {
        // ͨ����CRC
        if (SHT3x_Check_CRC(ucRead_Data, 2, ucRead_Data[2]) &&  SHT3x_Check_CRC(&ucRead_Data[3], 2, ucRead_Data[5]))
        {
            // ������ʪ��
            *fTemp = SHT3x_CalcTemperature((ucRead_Data[0] << 8) + ucRead_Data[1]);
            *fHumi = SHT3x_CalcHumidity((ucRead_Data[3] << 8) + ucRead_Data[4]);
            

        }
        else
        {
            ucResult = 0;
        }
    }
    
    return(ucResult);

}// End of u8 SHT3x_Get_Temp_Humi(float *fTemp, float *fHumi)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  SHT3x_CalcTemperature
* Description    :  �¶ȼ���
* Input          :  u16 usValue 16bit�¶�
* Output         :  None
* Return         :  float���¶�
*******************************************************************************/
float SHT3x_CalcTemperature(u16 usValue)
{
    // calculate temperature [��C]
    // T = -45 + 175 * rawValue / (2^16-1)

    float fTemp = 0.0;
    fTemp  = (175.0 * usValue) / 65535.0;
    fTemp -= 45.0;
    
    return fTemp ;
    
}// End of float SHT3x_CalcTemperature(u16 usValue)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  SHT3x_CalcHumidity
* Description    :  ʪ�ȼ���
* Input          :  u16 usValue 16bitʪ��
* Output         :  None
* Return         :  float��ʪ��
*******************************************************************************/
float SHT3x_CalcHumidity(u16 usValue)
{
    // calculate relative humidity [%RH]
    // RH = rawValue / (2^16-1) * 100
    
    float fHumi = 0.0;
    fHumi  = (100.0 * usValue) / 65535.0;
    
    return fHumi;
    
}// End of float SHT3x_CalcHumidity(u16 usValue)
    
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  SHT3x_Check_CRC
* Description    :  CRC�ж�
*                   ��λ����Ҫ����delay 1ms
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 SHT3x_Check_CRC(u8 *ucData, u8 ucLen, u8 ucCheck_Sum)
{
    u8 bit ;

    u8 crc = 0xFF ;

    u8 i ;

    for(i = 0; i < ucLen; i++)
    {
        crc ^= ucData[i];
        
        for(bit = 8; bit > 0; --bit)
        {
            if(crc & 0x80)
            {
                crc = (crc << 1 ) ^ 0x131 ;
            }
            else 
            {
                crc = crc << 1;
            }
        }
    }

    if(crc != ucCheck_Sum)
	{
		return 0;
	}
	else
	{
		return 1;
	}
    
}// u8 SHT3x_Check_CRC(u8 *ucData, u8 ucLen, u8 ucCheck_Sum)
    
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  SHT3x_Soft_Reset
* Description    :  ��λ 
*                   ��λ����Ҫ����delay 1ms
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 SHT3x_Soft_Reset(void)
{
    unsigned char Transfer_Succeeded = 1;
    u8 ucWrite_Addr[2];

    ucWrite_Addr[0] = (CMD_SOFT_RESET >> 8) & 0xFF;
    ucWrite_Addr[1] = (CMD_SOFT_RESET >> 0) & 0xFF;
    
    // ����д����
    Transfer_Succeeded = SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_WRITE_ADDR, ucWrite_Addr, 2, SW_I2C_NEED_SEND_STOP);

    nrf_delay_ms(5);
    
    return(Transfer_Succeeded);

}// End of u8 SHT3x_Soft_Reset(void)


/******************* (C) COPYRIGHT 2016 ½�� ************* END OF FILE ********/




