/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  GPIO_Port.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_PORT_H
#define __GPIO_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/




/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void GPIO_Variable_Init(void);                                  // ��ʪ�ȱ�����ʼ��
extern  void GPIO_Port_Init(void);                                      // �ܽų�ʼ��
extern  void GPIO_Set_Pin_High(u8 ucPin);                               // �ܽ��ø�
extern  void GPIO_Set_Pin_Low(u8 ucPin);                                // �ܽ��õ�   

#endif /* __GPIO_PORT_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/
