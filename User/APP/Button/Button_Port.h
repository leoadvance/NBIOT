/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Button_Port.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Button_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_PORT_H
#define __BUTTON_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Button_Variable_Init(void);                                // ������������ʼ��
extern  void Button_Pin_Handler(u8 ucPin_No, u8 ucAction);              // �����ܽŴ���


#endif /* __BUTTON_PORT_H */

/******************* (C) COPYRIGHT 2016 ½�� *****END OF FILE******************/
