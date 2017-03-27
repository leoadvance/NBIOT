/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Debug_Port.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/17/2017
* Description        :  Debug_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_PORT_H
#define __DEBUG_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/

#ifndef UART_TX_BUF_SIZE
    #define UART_TX_BUF_SIZE 256                                        // UART TX buffer size
#endif
#ifndef UART_RX_BUF_SIZE
    #define UART_RX_BUF_SIZE 16                                         //  UART RX buffer size
#endif

#define		UART_RX_STATE_IDLE		    0x00 							// �ӿڿ���
#define		UART_RX_STATE_BUSY			0x01 							// ������
#define		UART_RX_STATE_PENDING		0x02 							// ������

/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  void Debug_Port_Init(void);                                     // Debug�˿ڳ�ʼ��  
extern  void Debug_Variable_Init(void);                                 // Debug������ʼ��


#endif /* __DEBUG_PORT_H */

/******************* (C) COPYRIGHT 2017 ½�� *****END OF FILE******************/
