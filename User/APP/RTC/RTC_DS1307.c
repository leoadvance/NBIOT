/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  RTC_DS1307.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  RTC_DS1307Ӧ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "RTC_DS1307.h"
#include "Communal_IIC.h"
#include "sensirion_common.h"
#include "nrf_delay.h"

/* Private variables ---------------------------------------------------------*/
  
/* Private function prototypes -----------------------------------------------*/
u8 DS1307_Get_Week(u8 Year, u8 Month, u8 Day);							// ��ȡ����
u8 DS1307_Set_Date(time_t time);										// ����ʱ��
u8 DS1307_Get_Data(time_t *time);										// ��ȡʱ��
u8 DS1307_Start(void);													// ����

/* Private functions ---------------------------------------------------------*/

u8 DS1307_dec2bcd(u8 val)
{
	return val + 6 * (val / 10);
}

/*
 * transform bcd value to deciaml
 */
static u8 DS1307_bcd2dec(u8 val) 
{
	return val - 6 * (val >> 4);
}

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  DS1307_Get_Week
* Description    :  ��ȡ����
* Input          :  u8 Year		��
*                   u8 Month	��	
*                   u8 Day		��
* Output         :  None
* Return         :  ���� 1~7
*******************************************************************************/
u8 DS1307_Get_Week(u8 Year, u8 Month, u8 Day) 
{
	int iWeek = 0;  
    unsigned int y = 0, c = 0, m = 0, d = 0;  
  
    if ( Month == 1 || Month == 2 )  
    {  
        c = ( Year - 1 ) / 100;  
        y = ( Year - 1 ) % 100;  
        m = Month + 12;  
        d = Day;  
    }  
    else  
    {  
        c = Year / 100;  
        y = Year % 100;  
        m = Month;  
        d = Day;  
    }  

    // ���չ�ʽ 
    iWeek = y + y / 4 + c / 4 - 2 * c + 26 * ( m + 1 ) / 10 + d - 1;    

    // iWeekΪ��ʱȡģ 
    iWeek = iWeek >= 0 ? ( iWeek % 7 ) : ( iWeek % 7 + 7 ); 

    //�����ղ���Ϊһ�ܵĵ�һ��  
    if ( iWeek == 0 )    
    {  
        iWeek = 7;  
    } 

	return (u8)iWeek;

}// End of u8 DS1307_Get_Week(u8 Year, u8 Month, u8 Day) 

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  DS1307_Read_Register
* Description    :  ���Ĵ���
* Input          :  u8  ucRead_Addr Ҫ��ȡ�ĵ�ַ
*                   u8* pBuffer     ����ָ��
*                   u16 usRead_Len  ��ȡ����
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 DS1307_Read_Register(u8 ucRead_Addr, u8* pBuffer, u16 usRead_Len)
{
    u8 Transfer_Succeeded = 1;

    if(usRead_Len == 0)
    {
        return 0;
    }

    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, DS1307_WRITE_ADDR, &ucRead_Addr, 1, SW_I2C_DONT_SEND_STOP);
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, DS1307_READ_ADDR, pBuffer, usRead_Len, SW_I2C_NEED_SEND_STOP);

    nrf_delay_us(100);

    return Transfer_Succeeded;
    
}// End of u8 DS1307_Read_Register(u8 ucRead_Addr, u8* pBuffer, u16 usRead_Len)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  DS1307_Write_Register
* Description    :  доƬ�Ĵ���
* Input          :  u8 ucWrite_Addr    	Ҫд��ĵ�ַ
*                   u8* pBuffer         ����ָ��
*                   u16 usWrite_Len     д�볤�� 
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 DS1307_Write_Register(u8 ucWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    unsigned char Transfer_Succeeded = 1;

    // ����д����
    Transfer_Succeeded &= SW_I2C_Transfer(&Communal_IIC_2, DS1307_WRITE_ADDR, &ucWrite_Addr, 1, SW_I2C_DONT_SEND_STOP);
    
    // ���ȱ���
    if (usWrite_Len == 0)
    {
        return 0;
    }

    // ��������
    while (usWrite_Len-- && Transfer_Succeeded)
    {
        Transfer_Succeeded &= SW_IIC_Write_Byte(&Communal_IIC_2, *pBuffer);
        pBuffer++;
    }


    // ����ֹͣλ
    Transfer_Succeeded &= SW_I2C_Stop_Condition(&Communal_IIC_2);

    nrf_delay_us(100);
    
    return Transfer_Succeeded;
    
}// End of u8 DS1307_Write_Register(u8 ucWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  DS1307_Set_Date
* Description    :  ����ʱ��
* Input          :  time_t time �����õ�ʱ��
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 DS1307_Set_Date(time_t time) 
{
	u8 Data[7];
	u8 ucLen = 0;
	// check bounds
	if (time.Second > 59 ||
	    time.Minute > 59 ||
	    time.Hour > 23   ||
	    time.Day < 1    || time.Day > 31    ||
	    time.Month < 1  || time.Month > 12  ||
	    time.Year > 99)
		return 0;

	// get day of week
	time.Week = DS1307_Get_Week(time.Year, time.Month, time.Day);

	// ׼������
	Data[ucLen++] = DS1307_dec2bcd(time.Second) & 0x7F;
	Data[ucLen++] = DS1307_dec2bcd(time.Minute);
	Data[ucLen++] = DS1307_dec2bcd(time.Hour);
	Data[ucLen++] = DS1307_dec2bcd(time.Week);
	Data[ucLen++] = DS1307_dec2bcd(time.Day);
	Data[ucLen++] = DS1307_dec2bcd(time.Month);
	Data[ucLen++] = DS1307_dec2bcd(time.Year);

	// д����
	if (DS1307_Write_Register(0x00, Data, ucLen))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}// End of u8 DS1307_Set_Date(time_t time) 

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  DS1307_Get_Data
* Description    :  ��ȡʱ��
* Input          :  time_t *time ��ȡ��ʱ��
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 DS1307_Get_Data(time_t *time) 
{
	u8 Data[7];
	u8 ucLen = 0;

	// ��ȡʱ��
	if (DS1307_Read_Register(0x00, Data, 7))
	{
		time->Second = DS1307_bcd2dec(Data[ucLen++] & 0x7F);
		time->Minute = DS1307_bcd2dec(Data[ucLen++]);
		time->Hour   = DS1307_bcd2dec(Data[ucLen++]);
		time->Week   = DS1307_bcd2dec(Data[ucLen++]);
		time->Day    = DS1307_bcd2dec(Data[ucLen++]);
		time->Month  = DS1307_bcd2dec(Data[ucLen++]);
		time->Year   = DS1307_bcd2dec(Data[ucLen++]);

		return 1;
	}

	return 0;

}// End of u8 DS1307_Get_Data(time_t *time) 


/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  DS1307_Start
* Description    :  ����ʱ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 DS1307_Start(void) 
{
	u8 Data;

	// ��ȡʱ��
	if (DS1307_Read_Register(0x00, &Data, 1))
	{
		if (Data & 0x80)
		{
			Data &= 0x7F;
			if (DS1307_Write_Register(0x00, &Data, 1))
			{
				return 1;	
			}
			
			return 0;
		}

		return 1;
	}

	return 0;

}// End of u8 DS1307_Start(void) 

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




