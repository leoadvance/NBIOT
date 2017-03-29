/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  SW_I2C.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/26/2016
* Description        :  SW_I2C header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SW_I2C_H
#define __SW_I2C_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define     SW_I2C_SEND_ACK             0x01                            // ����Ӧ��
#define     SW_I2C_DONT_SEND_ACK        0x00                            // ������Ӧ��
#define     SW_I2C_NEED_SEND_STOP       1                               // ��Ҫ����ֹͣλ
#define     SW_I2C_DONT_SEND_STOP       0                               // ���跢��ֹͣλ

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
    void                (*Dealy)(void);                                 // ��ʱ
    void                (*Dealy_us)(void);                              // us��ʱ
    void                (*Pin_Init)(void);                              // �ܽų�ʼ��
    void                (*SDA_High)(void);                              // ����SDA
    void                (*SDA_Low)(void);                               // ����SDA
    void                (*SCL_High)(void);                              // ����SCL
    void                (*SCL_Low)(void);                               // ����SCL                
    void                (*Set_SDA_Input)(void);                         // ��������λ����ܽ�
    void                (*Set_SDA_Output)(void);                        // ��������λ����ܽ�
    void                (*Set_SCL_Output)(void);                        // ����ʱ��λ����ܽ�
    unsigned char       (*SDA_Read)(void);                              // ��SDA�ܽ�
    unsigned char       (*SCL_Read)(void);                              // ��SCL�ܽ�  
    unsigned char       Inited;                                         // ��һ��ʾ�Ѿ���ʼ��
    unsigned int        Wait_Scl_Free_Timeout;                          // �ȴ�SCL���ͷų�ʱʱ��                             
    
} SW_I2C_Typedef;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  unsigned char SW_I2C_Init(SW_I2C_Typedef *SW_I2C);                              // �ܽų�ʼ��
extern  unsigned char SW_IIC_Write_Byte(SW_I2C_Typedef *SW_I2C, unsigned char ucData);  // IICд�ֽ�
extern  unsigned char SW_IIC_Read_Byte(SW_I2C_Typedef *SW_I2C, unsigned char *Data_Byte, unsigned char Need_Ack);   // IIC���ֽ�
extern  unsigned char SW_I2C_Start_Condition(SW_I2C_Typedef *SW_I2C);           // ������ʼ�ź�
extern  unsigned char SW_I2C_Stop_Condition(SW_I2C_Typedef *SW_I2C);            // ����ֹͣ�ź�
extern  unsigned char SW_I2C_Transfer(SW_I2C_Typedef *SW_I2C, unsigned char Chip_Addr, unsigned char *Data, unsigned short Data_Len, unsigned char Stop_Condition); // ��������

#endif /* __SW_I2C_H */

/******************* (C) COPYRIGHT 2016 ½�� *****END OF FILE******************/

