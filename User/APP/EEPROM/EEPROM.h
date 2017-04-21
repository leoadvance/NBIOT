/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  EEPROM.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "EEPROM_Port.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void EEPROM_Task_Handle(void *p_arg);                           // EEPROM����
extern  void EEPROM_Task_Create(void);                                  // ����EEPROM����


#endif /* __EEPROM_H */

/******************* (C) COPYRIGHT 2015 ½�� *****END OF FILE******************/

