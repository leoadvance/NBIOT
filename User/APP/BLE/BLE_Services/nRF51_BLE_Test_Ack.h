/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE_Test_Ack.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/10/2017
* Description        :  ����Ӧ�� header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_TEST_ACK_H
#define __NRF51_BLE_TEST_ACK_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     PS_CMD_LCD_TEST             0x0001                          // ��������������
#define     PS_CMD_HALL_TEST            0x0002                          // ������������
#define     PS_CMD_GET_TOKEN            0x0003                          // ��ȡtoken��������
#define     PS_CMD_SET_TOKEN            0x0004                          // ����token��������
#define     PS_CMD_REBOOT               0x0005                          // ����

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
 

/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_PS_Ack_Handler(u8 * p_data, u16 usLen);          // nRF51�������ݴ���
extern  u8 nRF51_BLE_Test_LCD_Prepare(void);                            // ׼��������ʾ����

#endif /* __NRF51_BLE_TEST_ACK_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

