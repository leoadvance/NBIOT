/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  SW_I2C.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  ��I2C
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "SW_I2C.h"

/* Private define ------------------------------------------------------------*/
#define     SW_I2C_ACK                  0x00                            // ��Ӧ��
#define     SW_I2C_NACK                 0x01                            // ��Ӧ��

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C);                              // �ܽų�ʼ��
unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData);  // IICд�ֽ�
unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Need_Ack);   // IIC���ֽ�
unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C);           // ������ʼ�ź�
unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C);            // ����ֹͣ�ź�
unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition); // ��������

static unsigned char SW_I2C_Wait_SCL_Turn_High(SW_I2C_Typedef *SW_I2C); // �ȴ�SCL���ӻ��ͷ�
static unsigned char SW_I2C_Clear_Bus(SW_I2C_Typedef *SW_I2C);          // �������


/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_I2C_Init
* Description    :  I2C�˿ڳ�ʼ�� 
* Input          :  SW_I2C_Typedef *SW_I2C  I2C����
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C)
{
    // ��ֹ��γ�ʼ��
    if (SW_I2C->Inited)
    {
        return 1;
    }

    SW_I2C->Inited = 1;

    // �ܽų�ʼ��
    SW_I2C->Pin_Init();
    
    return SW_I2C_Clear_Bus(SW_I2C);
       
}// End of unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_I2C_Wait_SCL_Turn_High
* Description    :  �ȴ�SCL���ӻ��ͷ�
* Input          :  SW_I2C_Typedef *SW_I2C  �����ṹ��ָ��
*                   unsigned char ucData    Ҫ���͵�����       
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
static unsigned char SW_I2C_Wait_SCL_Turn_High(SW_I2C_Typedef *SW_I2C)
{

    unsigned int volatile Timeout_Counter = SW_I2C->Wait_Scl_Free_Timeout;


    // �ͷ�SCL
    SW_I2C->SCL_High();

    // �ȴ�ʱ��Ϊ��
    while (SW_I2C->SCL_Read() == 0)
    {
        if (Timeout_Counter == 0)
        {
            // ��ʱ
            return 0;
        }
        else
        {
            Timeout_Counter--;
            SW_I2C->Dealy_us();
        }
    }
    SW_I2C->Dealy();
    return 1;
    
}// End of static unsigned char SW_I2C_Wait_SCL_Turn_High(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_IIC_Write_Byte
* Description    :  IICд����
* Input          :  SW_I2C_Typedef *SW_I2C  �����ṹ��ָ��
*                   unsigned char ucData    Ҫ���͵�����       
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData)
{
    unsigned char Transfer_Succeeded = 1;
    unsigned char i;
    
    // ����SDAΪ���ģʽ
    SW_I2C->Set_SDA_Output();

    // ����ʱ��
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    // �ȷ��͸��ֽ�
    for (i = 0x80; i > 0; i >>= 1)
    {
        if (ucData & i)
        {
            SW_I2C->SDA_High();
        }
        else
        {
            SW_I2C->SDA_Low();
        }

        // �ȴ�Scl�ͷ�
        if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
        {
            // ��ʱ
            Transfer_Succeeded = 0; 
            break;
        }

        // ����ʱ��
        SW_I2C->SCL_Low();
        SW_I2C->Dealy();
    }

    // ����Ϊ����ģʽ
    SW_I2C->Set_SDA_Input();
    SW_I2C->Dealy();

    // �ȴ�ʱ�ӿ���
    Transfer_Succeeded &= SW_I2C_Wait_SCL_Turn_High(SW_I2C);

    // ��ȡACK
    if (SW_I2C->SDA_Read() & SW_I2C_NACK)
    {
        // ��Ӧ��
        Transfer_Succeeded = 0x00;    
    }
    else
    {
        // ��Ӧ��
        Transfer_Succeeded &= 0x01;    
    }

    // �������ʱ��
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    // ��ԭΪ����ģʽ
    SW_I2C->Set_SDA_Output();

    return Transfer_Succeeded;
    
}// End of unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData)


/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_IIC_Read_Byte
* Description    :  IIC��ȡһ���ֽ�����
* Input          :  SW_I2C_Typedef *SW_I2C      �����ṹ��ָ��
*                   unsigned char *Data_Byte    ��ȡ���ݻ���
*                   unsigned char Need_Ack      ��һ�Ƿ���ACK
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Send_Ack)
{
    unsigned char Byte_Read          = 0;
    unsigned char Transfer_Succeeded = 1;
    unsigned char i;

    // ����SDAΪ����ģʽ������
    SW_I2C->Set_SDA_Input();

    // ��λ��ǰ
    for (i = 0x80; i > 0; i >>= 1)
    {
        // �ȴ�IIC�ͷ�
        if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
        {
            Transfer_Succeeded = 0;
            break;
        }

        if (SW_I2C->SDA_Read())
        {
            Byte_Read |= i;
        }

        SW_I2C->SCL_Low();
        SW_I2C->Dealy();
    }

    // �ָ�SDAΪ���ģʽ
    SW_I2C->Set_SDA_Output();

    // ��¼����
    *Data_Byte = Byte_Read;
    
    // ����ACK
    if (Send_Ack == SW_I2C_SEND_ACK)
    {
        SW_I2C->SDA_Low();
    }
    else
    {
        SW_I2C->SDA_High();
    }

    // ��ʱ
    SW_I2C->Dealy();

    // �ȴ��ӻ���Ӧ
    if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
    {
        // ��ʱ
        Transfer_Succeeded = 0; 
    }

    // ������ʱ��
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    return Transfer_Succeeded;
    
}// End of unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Need_Ack)

/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_I2C_Clear_Bus
* Description    :  �������
* Input          :  SW_I2C_Typedef *SW_I2C  ����ָ��
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
static unsigned char SW_I2C_Clear_Bus(SW_I2C_Typedef *SW_I2C)
{
    unsigned char  Bus_Clear;
    unsigned char  i;

    // �ͷ�����
    SW_I2C->SDA_High();
    SW_I2C->SCL_High();
    SW_I2C->Dealy();

    if (SW_I2C->SDA_Read() == 1 && SW_I2C->SCL_Read() == 1)
    {
        Bus_Clear = 1;
    }
    else if (SW_I2C->SCL_Read() == 1)
    {
        Bus_Clear = 0;
      
        for(i = 0; i < 18; i++)
        {
            SW_I2C->SCL_Low();
            SW_I2C->Dealy();
            SW_I2C->SCL_High();
            SW_I2C->Dealy();

            if (SW_I2C->SDA_Read() == 1)
            {
                Bus_Clear = 1;
                break;
            }
        }
    }
    else
    {
        Bus_Clear = 0;
    }

    return Bus_Clear;
    
}// End of static unsigned char SW_I2C_Clear_Bus(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_I2C_Start_Condition
* Description    :  ����I2C��ʼ�ź�
* Input          :  SW_I2C_Typedef *SW_I2C  ����ָ��
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C)
{


    // ����SDA SCL
    SW_I2C->SDA_High();
    SW_I2C->Dealy();

    // �ȴ�SCL���
    if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
    {
        return 0;
    }

    // �������ݺ�ʱ�Ӳ�����ʼ����
    SW_I2C->SDA_Low();
    SW_I2C->Dealy();
    SW_I2C->SCL_Low();
    SW_I2C->Dealy();

    return 1;
    
}// End of unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C)


/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_I2C_Stop_Condition
* Description    :  ����I2Cֹͣ�ź�
* Input          :  SW_I2C_Typedef *SW_I2C  ����ָ��
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C)
{

    // �ȵͺ�߲���ֹͣ�ź�
    SW_I2C->SDA_Low();
    SW_I2C->Dealy();
    if (SW_I2C_Wait_SCL_Turn_High(SW_I2C) == 0)
    {
        return 0;
    }

    SW_I2C->SDA_High();
    SW_I2C->Dealy();

    return 1;
    
}// End of unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C)

/*******************************************************************************
*                           ½��@2016-12-26
* Function Name  :  SW_I2C_Transfer
* Description    :  I2C��������
* Input          :  SW_I2C_Typedef *SW_I2C  ����ָ��
*                   unsigned char Chip_Addr оƬ��ַ
*                   unsigned char  *Data    ����ָ��
*                   unsigned short Data_Len ���ݳ���
*                   unsigned char Stop_Condition    ��һʱ����ֹͣ�ź�
* Output         :  None
* Return         :  �ɹ�����1 ʧ�ܷ���0
*******************************************************************************/
unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition)
{
    unsigned char Transfer_Succeeded = 1;

    Transfer_Succeeded &= SW_I2C_Start_Condition(SW_I2C);
    Transfer_Succeeded &= SW_IIC_Write_Byte(SW_I2C, Chip_Addr);

    // ���ȱ���
    if (Data_Len == 0)
    {
        return 0;
    }
    if (Chip_Addr & 0x01)
    {
        /* Transfer direction is from Slave to Master */
        while (Data_Len-- && Transfer_Succeeded)
        {
            // ���һ���ֽڷ���NO ACK
            if (Data_Len == 0)
            {
                Transfer_Succeeded &= SW_IIC_Read_Byte(SW_I2C, Data, SW_I2C_DONT_SEND_ACK);
            }
            else
            {
                Transfer_Succeeded &= SW_IIC_Read_Byte(SW_I2C, Data, SW_I2C_SEND_ACK);
            }
            Data++;
        }
    }
    else
    {
        // ��������
        while (Data_Len-- && Transfer_Succeeded)
        {
            Transfer_Succeeded &= SW_IIC_Write_Byte(SW_I2C, *Data);
            Data++;
        }
    }

    // ��ֹͣ�źŻ��߷���ʧ��
    if (Stop_Condition || (Transfer_Succeeded == 0))
    {
        Transfer_Succeeded &= SW_I2C_Stop_Condition(SW_I2C);
    }

    return Transfer_Succeeded;
    
}// End of unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition)

/******************* (C) COPYRIGHT 2016 ½�� **************END OF FILE*********/






