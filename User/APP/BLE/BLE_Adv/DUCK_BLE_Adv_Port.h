/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Adv_Port.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/06/2017
* Description        :  �����㲥����ͷ�ļ�
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_ADV_PORT_H
#define __DUCK_BLE_ADV_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void BLE_Adv_Start(u32 uiTimeout);                              // �����㲥
extern  void BLE_Adv_Package(u16 usEvent, MIOT_Typedef *MIOT);          // �㲥���ݴ��

#endif /* __DUCK_BLE_ADV_PORT_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/

