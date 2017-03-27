/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Bat_Level_Service.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/12/2017
* Description        :  BLE �������� header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_BAT_LEVEL_SERVICE_H
#define __DUCK_BLE_BAT_LEVEL_SERVICE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Duck_BLE_Bat_Level_Services_Init(void);                    // Duck BLE ���������ʼ��    
extern  void Battery_BLE_Service_Update(void);                          // ����BLE����

#endif /* __DUCK_BLE_BAT_LEVEL_SERVICE_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

