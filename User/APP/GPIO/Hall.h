/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Hall.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/27/2017
* Description        :  Hall header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HALL_H
#define __HALL_H

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Hall_Open(void);                                           // ��hall
extern  void Hall_Close(void);                                          // ��hall
extern  void Hall_Magnet_Check(void);                                   // ���������ж� 
extern  void Hall_Update(void);                                         // ����״̬ˢ��
extern  u8 Is_Magnet_Near(void);                                        // �Ƿ��д����ڸ���

#endif /* __HALL_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

