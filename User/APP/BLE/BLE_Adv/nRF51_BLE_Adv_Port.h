/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE_Adv_Port.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  �㲥���ӿ�ͷ�ļ�
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_ADV_PORT_H
#define __NRF51_BLE_ADV_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void BLE_Adv_Start(u32 uiTimeout);                              // �����㲥��
extern  void BLE_Adv_Package(void);                                     // ���

#endif /* __NRF51_BLE_ADV_PORT_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/


