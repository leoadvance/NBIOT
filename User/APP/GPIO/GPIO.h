/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  GPIO.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  GPIO header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "GPIO_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void GPIO_Timer_Handle(void *p_arg);                            // GPIO����
extern  void GPIO_Task_Create(void);                                    // ����GPIO����
extern  void GPIO_TEST_High(void);                                      // Test Pin����
extern  void GPIO_TEST_Low(void);                                       // Test Pin����                      
extern  void GPIO_TEST_Toggle(void);                                    // Test Pin��ת

#endif /* __GPIO_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/

