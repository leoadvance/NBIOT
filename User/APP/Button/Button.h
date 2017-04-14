/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Button.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/28/2016
* Description        :  Button header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H

/* Includes ------------------------------------------------------------------*/
#include "Button_Port.h"


/* Private define ------------------------------------------------------------*/
#define     CLICK_MIN_DURATION          25                              // ������С����ʱ��ms
#define     CLICK_MAX_DURATION          800                             // ����������ʱ��ms
#define     DOUBLE_HIT_INTERVAL         200                             // ����ʶ���� ���ε����ڼ��������Ϊ����
#define     LONG_CLICK_MIN_DURATION     1500                            // ������С����ʱ��ms
#define     RESET_CLICK_MIN_DURATION    10000                           // ����ϵͳ

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Button_Timer_Handle(void *p_arg);                          // Button����
extern  void Button_Task_Create(void);                                  // ����Button����
extern  void Button_Free_ISR(void);                                     // Button�ͷ��жϴ���
extern  void Button_Push_ISR(void);                                     // Button�½����жϴ���

#endif /* __BUTTON_H */

/******************* (C) COPYRIGHT 2016 ½�� *****END OF FILE******************/

