/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD_Page_Time.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD_Page_Time header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_PAGE_TIME_H
#define __LCD_PAGE_TIME_H

/* Includes ------------------------------------------------------------------*/
#include "LCD_Port.h"


/* Private define ------------------------------------------------------------*/
#define     LCD_BASELINE_Y_ADDR  		32                              // baseline地址
#define     LCD_UNIX_Y_ADDR  			40                              // Unix地址



/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern	void LCD_Page_Time_Prepare(void);								// ׼��Timeҳ��
extern	void LCD_Page_Time(void);										// ��ʾTimeҳ��


#endif /* __LCD_PAGE_TIME_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

