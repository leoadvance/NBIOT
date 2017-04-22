/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  LCD_Page_Baseline.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  04/09/2017
* Description        :  LCD_Page_Baseline header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_PAGE_BASELINE_H
#define __LCD_PAGE_BASELINE_H

/* Includes ------------------------------------------------------------------*/
#include "LCD_Port.h"


/* Private define ------------------------------------------------------------*/
#define     LCD_BASE_NOW_Y_ADDR  		16                            	// ��ǰbaseline��ʾ��ַ
#define     LCD_BASE_SAVE_Y_ADDR  		32                              // �����baseline��ʾ��ַ
#define     LCD_BASE_SAVETIME_Y_ADDR  	48                              // �����baseline ʱ����ʾ��ַ





/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern	void LCD_Page_Baseline_Prepare(void);						    // ׼��Baselineҳ��
extern	void LCD_Page_Baseline(void);								    // ��ʾBaselineҳ��


#endif /* __LCD_PAGE_BASELINE_H */

/******************* (C) COPYRIGHT 2017 ½�� **** END OF FILE *****************/

