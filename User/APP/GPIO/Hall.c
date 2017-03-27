/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Hall.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/27/2017
* Description        :  HallӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Hall.h"
#include "Duck_BLE.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Hall_Open(void);                                                   // ��hall
void Hall_Close(void);                                                  // ��hall
void Hall_Magnet_Check(void);                                           // ���������ж� 
void Hall_Update(void);                                                 // ����״̬ˢ��
u8 Is_Magnet_Near(void);                                                // �Ƿ��д����ڸ���

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-02-27
* Function Name  :  Hall_Open
* Description    :  Hall��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Open(void)
{
    // ������
    nrf_gpio_pin_set(HALL_EN_PIN);
 
    
}// End of void Hall_Open(void)

/*******************************************************************************
*                           ½��@2017-02-27
* Function Name  :  Hall_Close
* Description    :  Hall�ر�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Close(void)
{
    // �ػ���
    nrf_gpio_pin_clear(HALL_EN_PIN);

    
}// End of void Hall_Close(void)

/*******************************************************************************
*                           ½��@2017-03-15
* Function Name  :  Hall_Update
* Description    :  Hall�ر�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Update(void)
{
    // ��ȡ����״̬
    Hall_Open();
    nrf_delay_ms(100);
    
    // ��ȡ����״̬
    Hall.Magnet_Near = Is_Magnet_Near();
    Hall.Magnet_Last = Hall.Magnet_Near;

    // �ػ���
    Hall_Close();
    
}// End of void Hall_Update(void)

/*******************************************************************************
*                           ½��@2017-02-27
* Function Name  :  Is_Magnet_Near
* Description    :  �Ƿ�����ڸ���
* Input          :  None
* Output         :  None
* Return         :  1 �д��� 0 �޴���
*******************************************************************************/
u8 Is_Magnet_Near(void)
{
    u8 ucReturn = 0;

    // �������� �͵�ƽ
    if (nrf_gpio_pin_read(HALL_OUT_PIN) == 0)
    {
        ucReturn = 1;
    }
    else
    {
        ucReturn = 0;

    }

    return (ucReturn);
    
}// End of u8 Is_Magnet_Near(void)

/*******************************************************************************
*                           ½��@2017-02-27
* Function Name  :  Hall_Magnet_Check
* Description    :  hall�����ж�
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Hall_Magnet_Check(void)
{
    Hall.Timestamp++;

    // �Ƿ񵽼��ʱ�䵽
    if (Hall.Timestamp == TASK_MAGNET_CHECK_PERIOD)
    {
        // ������
        Hall_Open();

    }
    else if (Hall.Timestamp > TASK_MAGNET_CHECK_PERIOD)
    {
              
        Hall.Timestamp = 0;
        
        // ��ȡ����״̬
        Hall.Magnet_Near = Is_Magnet_Near();

        // �ػ���
        Hall_Close();

        // ����״̬�仯
        if (Hall.Magnet_Last != Hall.Magnet_Near)
        {
            // ����ͻ���¼�
            Duck_BLE_Int_Evt_Set(MIOT_EVENT_ID_HALL);

            app_trace_log("Hall = %d !\r\n", Hall.Magnet_Near); 
            
        }

        Hall.Magnet_Last = Hall.Magnet_Near;
    }
    
}// End of void Hall_Magnet_Check(void)


/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




