/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_Storage_MAC.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  mac��ַ����ͷ�ļ�
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_STORAGE_MAC_H
#define __DUCK_STORAGE_MAC_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

/* Private define ------------------------------------------------------------*/
#define     MAC_PSM_SIZE                64                              // mac�����С
#define     MAC_PSM_BLOCK               1                               // ����

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Get_MAC(void);                                             // ��ȡMAC��ַ
extern  void MAC_Flash_Init(void);                                      // mac flash��ʼ��
extern  u8 MAC_Delete(void);                                            // ɾ��mac��ַ
extern  u8 MAC_Save(u8 *ucMAC);                                         // ����mac��ַ

#endif /* __DUCK_STORAGE_MAC_H */

/******************* (C) COPYRIGHT 2017 ½�� ***** END OF FILE ****************/




