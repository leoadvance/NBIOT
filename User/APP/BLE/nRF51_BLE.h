/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/11/2017
* Description        :  nRF51_BLE header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_H
#define __NRF51_BLE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_Task_Create(void);                               // BLE���񴴽�
extern  void nRF51_BLE_Int_Evt_Set(u16 usEvent_ID);                     // ������������



#endif /* __NRF51_BLE_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/
