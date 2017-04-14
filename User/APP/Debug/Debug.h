/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  Debug.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/23/2017
* Description        :  Debug header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H
#define __DEBUG_H

/* Includes ------------------------------------------------------------------*/
#include "Debug_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Debug_Task_Create(void);                                   // ������������
extern  void Receive_Data_Handler(u8* ucData, u16 usLen);               // �������ݴ���
extern  void Debug_Send(u8 *ucData, u8 ucLen);                          // �������ݷ���
extern  void Debug_Send_Wait_Empty(void);                               // �ȿ�

#endif /* __DEBUG_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/

