/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  RTC.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/19/2017
* Description        :  RTC header file
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
extern  void RTC_Timer_Handle(void *p_arg);                             // RTC����
extern  void RTC_Task_Create(void);                                     // ����RTC����


#endif /* __TVOC_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

