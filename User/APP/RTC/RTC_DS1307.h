/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  RTC_DS1307.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/30/2017
* Description        :  RTC_DS1307 header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_DS1307_H
#define __RTC_DS1307_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/
#define     DS1307_ADDR                 0x68                            // DS1307��ַ
#define     DS1307_WRITE_ADDR           (DS1307_ADDR << 1)              // DS1307д��ַ
#define     DS1307_READ_ADDR            (DS1307_WRITE_ADDR | 0x01)      // DS1307����ַ

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
	unsigned char Month;
	unsigned char Day;
	unsigned char Year;
	unsigned char Week;
	unsigned char Hour;
	unsigned char Minute;
	unsigned char Second;
	
} Time_t;   


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern	u8 DS1307_Set_Date(Time_t time);								// ����ʱ��
extern	u8 DS1307_Get_Data(Time_t *time);								// ��ȡʱ��
extern	u8 DS1307_Start(void);											// ����
extern	u32 DS1307_Year_TO_Unix(Time_t time);							// ������תNuix
extern	void DS1307_Unix_TO_Year(u32 uiSec, Time_t *time);				// unixת������

#endif /* __RTC_DS1307_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

