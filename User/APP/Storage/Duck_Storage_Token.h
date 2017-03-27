/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_Storage_Token.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  Token��ַ����ͷ�ļ�
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_STORAGE_TOKEN_H
#define __DUCK_STORAGE_TOKEN_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

/* Private define ------------------------------------------------------------*/
#define     TOKEN_PSM_SIZE              64                              // Token�����С
#define     TOKEN_PSM_BLOCK             1                               // ����

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Get_Token(void);                                           // ��ȡToken��ַ
extern  u8 Token_Save(u8 *ucToken);                                     // ����Token��ַ
extern  void Token_Flash_Init(void);                                    // Token flash��ʼ��

#endif /* __DUCK_STORAGE_TOKEN_H */

/******************* (C) COPYRIGHT 2017 ½�� ***** END OF FILE ****************/




