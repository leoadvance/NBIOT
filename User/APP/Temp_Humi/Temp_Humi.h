/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Temp_Humi.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Temp_Humi header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMP_HUMI_H
#define __TEMP_HUMI_H

/* Includes ------------------------------------------------------------------*/
#include "Temp_Humi_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Temp_Humi_Timer_Handle(void *p_arg);                           // Temp_Humi����
extern  void Temp_Humi_Task_Create(void);                                   // ����Temp_Humi����
extern  void Temp_Humi_Get(void);                                           // ��ȡ��ʪ��

#endif /* __TEMP_HUMI_H */

/******************* (C) COPYRIGHT 2016 ½�� **** END OF FILE *****************/

