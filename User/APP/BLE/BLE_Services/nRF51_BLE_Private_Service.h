/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_BLE_Private_Service.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  01/13/2017
* Description        :  ˽�з��� header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NRF51_BLE_PRIVATE_SERVICE_H
#define __NRF51_BLE_PRIVATE_SERVICE_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     BLE_NRF51_MAX_DATA_LEN       20                              // ������ֽ�

#define     BLE_UUID_NRF51               0x0000                          // Amber����UUID
#define     NRF51_TEMP_CHARACTERISTIC    0xAA55                          // �¶�UUID
#define     NRF51_MESSAGE_CHARACTERISTIC 0xBB55                          // ��ϢUUID

#define     NRF51_BASE_UUID              {0x6D, 0x66, 0x70, 0x44, 0x73, 0x66, 0x62, 0x75, 0x66, 0x45, 0x76, 0x64, 0x00, 0x00, 0x6C, 0x22}


/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void nRF51_BLE_Private_Services_Init(void);                     // ˽�з����ʼ��    
extern  void nRF51_BLE_Private_Evt(BLE_Service_Typedef * pnRF51, ble_evt_t * pBLE_Evt);   // nRF51�¼�����
extern  void Temp_BLE_Service_Update(BLE_Service_Typedef * pnRF51);     // �����¶�
extern  u32 nRF51_BLE_String_Send(BLE_Service_Typedef * pnRF51, u16 usValue_Handle, u8 * pString, u16 usLen); // ��������

#endif /* __NRF51_BLE_PRIVATE_SERVICE_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

