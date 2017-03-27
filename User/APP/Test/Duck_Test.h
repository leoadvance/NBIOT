/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  Duck_Test.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/08/2017
* Description        :  Duck_Test header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_TEST_H
#define __DUCK_TEST_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     TEST_CMD_START              "Enter Test Mode"               // �������ģʽ
#define     TEST_CMD_MAC                "Set MAC"                       // ����mac��ַ
#define     TEST_CMD_TEST               "Start Test"                    // ��ʼ����
#define     TEST_CMD_TOKEN              "Set Token"                     // ����token
#define     TEST_CMD_DELETE_MAC         "Delete MAC"                    // ɾ��mac

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Duck_Test_Handler(u8* ucData, u16 usLen);                  // �������ݴ���

#endif /* __DUCK_TEST_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/

