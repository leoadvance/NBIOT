/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  WDT.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/24/2017
* Description        :  WDT header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WDT_H
#define __WDT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void WDT_Task_Init(void);                                       // ���Ź���ʼ��
extern  void WDT_Feed(void);                                            // ι��

#endif /* __WDT_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/

