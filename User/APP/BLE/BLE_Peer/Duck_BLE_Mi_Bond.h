/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Duck_BLE_Mi_Bond.h
* Author             :  ½�� 
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/15/2017
* Description        :  Duck_BLE_Mi_Bond header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DUCK_BLE_MI_BOND_H
#define __DUCK_BLE_MI_BOND_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     MISERVICE_PSM_SIZE          64                              // mi���񴢴��С
#define     MISERVICE_PSM_BLOCK         1                               // ����

/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Mi_Bond_Start(void);                                       // ������
extern  void Mi_Bond_Stop(void);                                        // ������
extern  void Duck_BLE_Mi_Services_Init(void);                           // С�װ󶨷����ʼ��
extern  void Mi_Bond_Timeout_Check(void);                               // �󶨳�ʱ���ж�


#endif /* __DUCK_BLE_MI_BOND_H */

/******************* (C) COPYRIGHT 2017 ½�� ***** END OF FILE ****************/

