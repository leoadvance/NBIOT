/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Temp_Humi_Port.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  ��ʪ����������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi_Port.h"
#include "nrf_gpio.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Temp_Humi_Delay(void);                                             // ��ʱ
void Temp_Humi_Delay_us(void);                                          // us��ʱ
void Temp_Humi_Pin_Init(void);                                          // �ܽų�ʼ��
void Temp_Humi_SDA_High(void);                                          // ����������
void Temp_Humi_SDA_Low(void);                                           // ����������
void Temp_Humi_SCL_High(void);                                          // ����ʱ��
void Temp_Humi_SCL_Low(void);                                           // ����ʱ��
void Temp_Humi_Set_SDA_Input(void);                                     // ����SDAΪ����ģʽ
void Temp_Humi_Set_SDA_Output(void);                                    // ����SDAΪ���ģʽ
void Temp_Humi_Set_SCL_Output(void);                                    // ����SCLΪ���ģʽ
u8   Temp_Humi_SDA_Read(void);                                          // ��ȡSDA��ƽ
u8   Temp_Humi_SCL_Read(void);                                          // ��ȡSCL��ƽ

void Temp_Humi_Variable_Init(void);                                     // Temp_Humi������ʼ��
u8   Temp_Humi_Port_Init(void);                                         // Temp_Humi�˿ڳ�ʼ��    
u8 Temp_Humi_Read_Register(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);// ���Ĵ���
u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);// д�Ĵ���
/* Private functions ---------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Delay
* Description    :  Temp_Humi��ʱ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Delay(void)
{
    nrf_delay_us(1);
    
}// End of void Temp_Humi_Delay(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Delay_us
* Description    :  Temp_Humi us��ʱ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Delay_us(void)
{
    nrf_delay_us(1);
    
}// End of void Temp_Humi_Delay_us(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Pin_Init
* Description    :  �ܽų�ʼ��                   
* Input          :  P0.12   -->   SHT30_SCL_PIN
*                   P0.13   -->   SHT30_SDA_PIN
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
void Temp_Humi_Pin_Init(void)
{
    
    // ���ùܽ�Ϊ��©ģʽ
    NRF_GPIO->PIN_CNF[SHT30_SCL_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                                        | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                        | (GPIO_PIN_CNF_PULL_Disabled  << GPIO_PIN_CNF_PULL_Pos)  \
                                        | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                        | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

    NRF_GPIO->PIN_CNF[SHT30_SDA_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) \
                                        | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                        | (GPIO_PIN_CNF_PULL_Disabled  << GPIO_PIN_CNF_PULL_Pos)  \
                                        | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                        | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

}// End of u8  Temp_Humi_Pin_Init(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_SDA_High
* Description    :  Temp_Humi����SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SDA_High(void)
{
    NRF_GPIO->OUTSET = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_SDA_High(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_SDA_Low
* Description    :  Temp_Humi����SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SDA_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_SDA_Low(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_SCL_High
* Description    :  Temp_Humi����SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SCL_High(void)
{
    NRF_GPIO->OUTSET = (1UL << SHT30_SCL_PIN);
    
}// End of void Temp_Humi_SCL_High(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_SCL_Low
* Description    :  Temp_Humi����SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_SCL_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << SHT30_SCL_PIN);
    
}// End of void Temp_Humi_SCL_Low(void)


/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Set_SDA_Input
* Description    :  ����SDA�ܽ�Ϊ����ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Set_SDA_Input(void)
{
    NRF_GPIO->DIRCLR = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_Set_SDA_Input(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Set_SDA_Output
* Description    :  ����SDA�ܽ�Ϊ���ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Set_SDA_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << SHT30_SDA_PIN);
    
}// End of void Temp_Humi_Set_SDA_Output(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Set_SCL_Output
* Description    :  ����SCL�ܽ�Ϊ���ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Set_SCL_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << SHT30_SCL_PIN);
    
}// End of void Temp_Humi_Set_SCL_Output(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_SDA_Read
* Description    :  ��ȡSDA�ܽŵ�ƽ
* Input          :  None
* Output         :  None
* Return         :  �ߵ�ƽ����1 �͵�ƽ����0
*******************************************************************************/
u8 Temp_Humi_SDA_Read(void)
{
    return((NRF_GPIO->IN >> SHT30_SDA_PIN) & 0x1UL);
    
}// End of u8 Temp_Humi_SDA_Read(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_SCL_Read
* Description    :  ��ȡSCL�ܽŵ�ƽ
* Input          :  None
* Output         :  None
* Return         :  �ߵ�ƽ����1 �͵�ƽ����0
*******************************************************************************/
u8 Temp_Humi_SCL_Read(void)
{
    return((NRF_GPIO->IN >> SHT30_SCL_PIN) & 0x1UL);
    
}// End of u8 Temp_Humi_SCL_Read(void)

/*******************************************************************************
*                           ½��@2016-12-23
* Function Name  :  Temp_Humi_Port_Init
* Description    :  Temp_Humi�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 Temp_Humi_Port_Init(void)
{
    u8 Transfer_Succeeded; 

    Temp_Humi_I2C.Dealy                 = Temp_Humi_Delay;
    Temp_Humi_I2C.Dealy_us              = Temp_Humi_Delay_us;
    Temp_Humi_I2C.Pin_Init              = Temp_Humi_Pin_Init;
    Temp_Humi_I2C.SDA_High              = Temp_Humi_SDA_High;
    Temp_Humi_I2C.SDA_Low               = Temp_Humi_SDA_Low;
    Temp_Humi_I2C.SCL_High              = Temp_Humi_SCL_High;
    Temp_Humi_I2C.SCL_Low               = Temp_Humi_SCL_Low;
    Temp_Humi_I2C.Set_SDA_Input         = Temp_Humi_Set_SDA_Input; 
    Temp_Humi_I2C.Set_SDA_Output        = Temp_Humi_Set_SDA_Output; 
    Temp_Humi_I2C.Set_SCL_Output        = Temp_Humi_Set_SCL_Output;   
    Temp_Humi_I2C.SDA_Read              = Temp_Humi_SDA_Read; 
    Temp_Humi_I2C.SCL_Read              = Temp_Humi_SCL_Read;
    Temp_Humi_I2C.Wait_Scl_Free_Timeout = TEMP_HUMI_MAX_TIMEOUT_LOOPS;
    Transfer_Succeeded = SW_I2C_Init(&Temp_Humi_I2C);
    
    return (Transfer_Succeeded);
       
}// End of u8  Temp_Humi_Port_Init(void)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Variable_Init
* Description    :  ��ʪ�ȱ�����ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Temp_Humi_Variable_Init(void)
{

    
}// End of void Temp_Humi_Variable_Init(void)




/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Read_Register
* Description    :  ���Ĵ���
* Input          :  u16 usRead_Addr Ҫ��ȡ�ĵ�ַ
*                   u8* pBuffer     ����ָ��
*                   u16 usRead_Len  ��ȡ����
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 Temp_Humi_Read_Register(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)
{
    u8 Transfer_Succeeded = 1;
    u8 ucRead_Addr[2];
    if(usRead_Len == 0)
    {
        return 0;
    }
    ucRead_Addr[0] = (usRead_Addr >> 8) & 0xFF;
    ucRead_Addr[1] = (usRead_Addr >> 0) & 0xFF;
    Transfer_Succeeded &= SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_WRITE_ADDR, ucRead_Addr, 2, SW_I2C_DONT_SEND_STOP);
    Transfer_Succeeded &= SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_READ_ADDR, pBuffer, usRead_Len, SW_I2C_NEED_SEND_STOP);

    nrf_delay_us(100);

    return Transfer_Succeeded;
    
}// End of u8 Temp_Humi_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len)

/*******************************************************************************
*                           ½��@2016-12-28
* Function Name  :  Temp_Humi_Write_Register
* Description    :  доƬ�Ĵ���
* Input          :  u16 usWrite_Addr    Ҫд��ĵ�ַ
*                   u8* pBuffer         ����ָ��
*                   u16 usWrite_Len     д�볤�� 
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)
{
    unsigned char Transfer_Succeeded = 1;
    u8 ucWrite_Addr[2];

    ucWrite_Addr[0] = (usWrite_Addr >> 8) & 0xFF;
    ucWrite_Addr[1] = (usWrite_Addr >> 0) & 0xFF;
    
    // ����д����
    Transfer_Succeeded &= SW_I2C_Transfer(&Temp_Humi_I2C, SHT3x_WRITE_ADDR, ucWrite_Addr, 2, SW_I2C_DONT_SEND_STOP);
    
    // ���ȱ���
    if (usWrite_Len == 0)
    {
        return 0;
    }

    // ��������
    while (usWrite_Len-- && Transfer_Succeeded)
    {
        Transfer_Succeeded &= SW_IIC_Write_Byte(&Temp_Humi_I2C, *pBuffer);
        pBuffer++;
    }


    // ����ֹͣλ
    Transfer_Succeeded &= SW_I2C_Stop_Condition(&Temp_Humi_I2C);

    nrf_delay_us(100);
    
    return Transfer_Succeeded;
    
}// End of u8 Temp_Humi_Write_Register(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len)

/******************* (C) COPYRIGHT 2016 ½�� ************* END OF FILE ********/

