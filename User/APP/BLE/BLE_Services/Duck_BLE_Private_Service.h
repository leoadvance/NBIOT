/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Private_Service.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/13/2017
* Description        :  ˽�з��� header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_PRIVATE_SERVICE_H
#define __DUCK_BLE_PRIVATE_SERVICE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     BLE_DUCK_MAX_DATA_LEN       20                              // ������ֽ�

#define     BLE_UUID_DUCK               0x0000                          // Amber����UUID
#define     DUCK_TEMP_CHARACTERISTIC    0xAA55                          // �¶�UUID
#define     DUCK_MESSAGE_CHARACTERISTIC 0xBB55                          // ��ϢUUID

#define     DUCK_BASE_UUID              {0x6D, 0x66, 0x70, 0x44, 0x73, 0x66, 0x62, 0x75, 0x66, 0x45, 0x76, 0x64, 0x00, 0x00, 0x6C, 0x22}


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Duck_BLE_Private_Services_Init(void);                      // ˽�з����ʼ��    
extern  void Duck_BLE_Private_Evt(BLE_Service_Typedef * pDuck, ble_evt_t * pBLE_Evt);   // Duck�¼�����
extern  void Temp_BLE_Service_Update(BLE_Service_Typedef * pDuck);      // �����¶�
extern  u32 Duck_BLE_String_Send(BLE_Service_Typedef * pDuck, u16 usValue_Handle, u8 * pString, u16 usLen); // ��������

#endif /* __DUCK_BLE_PRIVATE_SERVICE_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

