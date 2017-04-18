/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Communal_IIC_2.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  ͨ��IIC2��������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Communal_IIC_2.h"
#include "nrf_gpio.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Communal_IIC_2_Delay(void);                                        // ��ʱ
void Communal_IIC_2_Delay_us(void);                                     // us��ʱ
void Communal_IIC_2_Pin_Init(void);                                     // �ܽų�ʼ��
void Communal_IIC_2_SDA_High(void);                                     // ����������
void Communal_IIC_2_SDA_Low(void);                                      // ����������
void Communal_IIC_2_SCL_High(void);                                     // ����ʱ��
void Communal_IIC_2_SCL_Low(void);                                      // ����ʱ��
void Communal_IIC_2_Set_SDA_Input(void);                                // ����SDAΪ����ģʽ
void Communal_IIC_2_Set_SDA_Output(void);                               // ����SDAΪ���ģʽ
void Communal_IIC_2_Set_SCL_Output(void);                               // ����SCLΪ���ģʽ
u8   Communal_IIC_2_SDA_Read(void);                                     // ��ȡSDA��ƽ
u8   Communal_IIC_2_SCL_Read(void);                                     // ��ȡSCL��ƽ

void Communal_IIC_2_Variable_Init(void);                                  // Communal_IIC_2������ʼ��
u8   Communal_IIC_2_Init(void);                                           // Communal_IIC_2�˿ڳ�ʼ��    

/* Private functions ---------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Delay
* Description    :  Communal_IIC_2��ʱ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Delay(void)
{
    nrf_delay_us(1);
    
}// End of void Communal_IIC_2_Delay(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Delay_us
* Description    :  Communal_IIC_2 us��ʱ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Delay_us(void)
{
    nrf_delay_us(1);
    
}// End of void Communal_IIC_2_Delay_us(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Pin_Init
* Description    :  �ܽų�ʼ��                   
* Input          :  P0.14   -->   COMMUNAL_IIC_2_SCL_PIN
*                   P0.15   -->   COMMUNAL_IIC_2_SDA_PIN
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
void Communal_IIC_2_Pin_Init(void)
{
    
    // ���ùܽ�Ϊ��©ģʽ
    NRF_GPIO->PIN_CNF[COMMUNAL_IIC_2_SCL_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled  << GPIO_PIN_CNF_SENSE_Pos) \
                                                | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                                | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                                                | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                                | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

    NRF_GPIO->PIN_CNF[COMMUNAL_IIC_2_SDA_PIN]  =  (GPIO_PIN_CNF_SENSE_Disabled  << GPIO_PIN_CNF_SENSE_Pos) \
                                                | (GPIO_PIN_CNF_DRIVE_S0D1     << GPIO_PIN_CNF_DRIVE_Pos) \
                                                | (GPIO_PIN_CNF_PULL_Pullup    << GPIO_PIN_CNF_PULL_Pos)  \
                                                | (GPIO_PIN_CNF_INPUT_Connect  << GPIO_PIN_CNF_INPUT_Pos) \
                                                | (GPIO_PIN_CNF_DIR_Output     << GPIO_PIN_CNF_DIR_Pos);

}// End of u8  Communal_IIC_2_Pin_Init(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_SDA_High
* Description    :  Communal_IIC_2����SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SDA_High(void)
{
    NRF_GPIO->OUTSET = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_SDA_High(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_SDA_Low
* Description    :  Communal_IIC_2����SDA
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SDA_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_SDA_Low(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_SCL_High
* Description    :  Communal_IIC_2����SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SCL_High(void)
{
    NRF_GPIO->OUTSET = (1UL << COMMUNAL_IIC_2_SCL_PIN);
    
}// End of void Communal_IIC_2_SCL_High(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_SCL_Low
* Description    :  Communal_IIC_2����SCL
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_SCL_Low(void)
{
    NRF_GPIO->OUTCLR = (1UL << COMMUNAL_IIC_2_SCL_PIN);
    
}// End of void Communal_IIC_2_SCL_Low(void)


/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Set_SDA_Input
* Description    :  ����SDA�ܽ�Ϊ����ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Set_SDA_Input(void)
{
    NRF_GPIO->DIRCLR = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_Set_SDA_Input(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Set_SDA_Output
* Description    :  ����SDA�ܽ�Ϊ���ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Set_SDA_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << COMMUNAL_IIC_2_SDA_PIN);
    
}// End of void Communal_IIC_2_Set_SDA_Output(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Set_SCL_Output
* Description    :  ����SCL�ܽ�Ϊ���ģʽ
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Set_SCL_Output(void)
{
    NRF_GPIO->DIRSET = (1UL << COMMUNAL_IIC_2_SCL_PIN);
    
}// End of void Communal_IIC_2_Set_SCL_Output(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_SDA_Read
* Description    :  ��ȡSDA�ܽŵ�ƽ
* Input          :  None
* Output         :  None
* Return         :  �ߵ�ƽ����1 �͵�ƽ����0
*******************************************************************************/
u8 Communal_IIC_2_SDA_Read(void)
{
    return((NRF_GPIO->IN >> COMMUNAL_IIC_2_SDA_PIN) & 0x1UL);
    
}// End of u8 Communal_IIC_2_SDA_Read(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_SCL_Read
* Description    :  ��ȡSCL�ܽŵ�ƽ
* Input          :  None
* Output         :  None
* Return         :  �ߵ�ƽ����1 �͵�ƽ����0
*******************************************************************************/
u8 Communal_IIC_2_SCL_Read(void)
{
    return((NRF_GPIO->IN >> COMMUNAL_IIC_2_SCL_PIN) & 0x1UL);
    
}// End of u8 Communal_IIC_2_SCL_Read(void)

/*******************************************************************************
*                           ½��@2017-12-23
* Function Name  :  Communal_IIC_2_Init
* Description    :  Communal_IIC_2�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 Communal_IIC_2_Init(void)
{
    u8 Transfer_Succeeded; 

    // ������ʼ��
    Communal_IIC_2_Variable_Init();
    
    Communal_IIC_2.Dealy                 = Communal_IIC_2_Delay;
    Communal_IIC_2.Dealy_us              = Communal_IIC_2_Delay_us;
    Communal_IIC_2.Pin_Init              = Communal_IIC_2_Pin_Init;
    Communal_IIC_2.SDA_High              = Communal_IIC_2_SDA_High;
    Communal_IIC_2.SDA_Low               = Communal_IIC_2_SDA_Low;
    Communal_IIC_2.SCL_High              = Communal_IIC_2_SCL_High;
    Communal_IIC_2.SCL_Low               = Communal_IIC_2_SCL_Low;
    Communal_IIC_2.Set_SDA_Input         = Communal_IIC_2_Set_SDA_Input; 
    Communal_IIC_2.Set_SDA_Output        = Communal_IIC_2_Set_SDA_Output; 
    Communal_IIC_2.Set_SCL_Output        = Communal_IIC_2_Set_SCL_Output;   
    Communal_IIC_2.SDA_Read              = Communal_IIC_2_SDA_Read; 
    Communal_IIC_2.SCL_Read              = Communal_IIC_2_SCL_Read;
    Communal_IIC_2.Wait_Scl_Free_Timeout = COMMUNAL_IIC_2_MAX_LPPOS;
    Transfer_Succeeded = SW_I2C_Init(&Communal_IIC_2);
    
    return (Transfer_Succeeded);
       
}// End of u8  Communal_IIC_2_Init(void)

/*******************************************************************************
*                           ½��@2017-04-19
* Function Name  :  Communal_IIC_2_Variable_Init
* Description    :  ͨ��IIC2��ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Communal_IIC_2_Variable_Init(void)
{
    // Ĭ��δ��ʼ��
    Communal_IIC_2.Inited = 0;
    
}// End of void Communal_IIC_2_Variable_Init(void)


/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/

