/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  tVOC.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/29/2017
* Description        :  tVOC header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TVOC_H
#define __TVOC_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void tVOC_Timer_Handle(void *p_arg);                           // tVOC����
extern  void tVOC_Task_Create(void);                                   // ����tVOC����
extern  void tVOC_Get(void);                                           // ��ȡ��ʪ��

#endif /* __TVOC_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

