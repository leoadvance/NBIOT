/******************** (C) COPYRIGHT 2015 ½�� **********************************
* File Name          :  Task.h
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.4
* Version            :  V1.0
* Date               :  04/28/2015
* Description        :  Task header file
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define __TASK_H

/* Includes ------------------------------------------------------------------*/
#include "Global.h"


/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
extern  u32 Task_Timer_Start(Task_Typedef *Task, void * p_context);     // ��������
extern  u32 Task_Timer_Stop(Task_Typedef *Task);                        // ����ֹͣ


#endif /* __TASK_H */

/******************* (C) COPYRIGHT 2015 ½�� *****END OF FILE******************/

