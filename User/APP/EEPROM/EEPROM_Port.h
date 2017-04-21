/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  EEPROM_Port.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/23/2015
* Description        :  EEPROM_Port header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_PORT_H
#define __EEPROM_PORT_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "nrf_delay.h"

/* Private define ------------------------------------------------------------*/
#define     EEPROM_WRITE_ADDR           0xA0                            // EEPROMд��ַ
#define     EEPROM_READ_ADDR            (EEPROM_WRITE_ADDR + 1)         // EEPROM����ַ
#define     EEPROM_PAGE_SIZE            32                              // EEPROMҳ��С
#define     EEPROM_CHIP_SIZE            0x2000                          // EEPROM�ܴ�С
#define     EEPROM_WRITE_PAGE_TIME      10                              // EEPROMдҳʱ�� ms

#define     EEPROM_TEST_ADDR            EEPROM_CHIP_SIZE - 32           // EEPROM�������ݵ�ַ

#define     EEPROM_ADDR_BASELINE        (1 << 5)          				// EEPROMbaseline��ַ




/* Private typedef -----------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  u8 EEPROM_Read_Buffer(u16 usRead_Addr, u8* pBuffer, u16 usRead_Len);    // EEPROM��ȡ����
extern  u8 EEPROM_Write_Page(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len);   // дҳ����
extern  u8 EEPROM_Write_Buffer(u16 usWrite_Addr, u8* pBuffer, u16 usWrite_Len); // EEPROMд����
extern  u8 EEPROM_Chip_Init(void);                                      // оƬ��ʼ��

#endif /* __EEPROM_PORT_H */

/******************* (C) COPYRIGHT 2015 ½�� *****END OF FILE******************/
