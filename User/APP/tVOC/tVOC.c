/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  tVOC.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/29/2017
* Description        :  tVOCӦ�ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "tVOC.h"
#include "nrf_gpio.h"
#include "sgpc1x.h"
#include "EEPROM.h"



#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
void tVOC_Task_Handle(void *p_arg);                                     // tVOC����
void tVOC_Task_Create(void);                                            // ����tVOC����
void tVOC_Get(void);                                                    // ��ȡtVOC
void tVOC_Baseline_Handle(void);										// baseline����
void tVOC_Port_Init(void);                                              // tVOC�ܽų�ʼ��
void tVOC_Variable_Init(void);                                          // ������ʼ��
u32 tVOC_Chip_Init(void);                                               // оƬ��ʼ��
u32 tVOC_Get_Saved_Baseline(u32 uiSec, u32 *pBaseline);					// ��ȡbaseline
u8 tVOC_Save_Baseline(u32 uiSec, u32 uiBaseline);						// ����baseline

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-03-29
* Function Name  :  tVOC_Task_Create
* Description    :  ����tVOC����
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Task_Create(void)
{
    u32 err_code = NRF_SUCCESS;

    // ��ʼ��������IO
    tVOC_Variable_Init();
    tVOC_Port_Init();
    
    // ���ò��� ����ģʽ����
    tVOC_Task.Run_Mode        = APP_TIMER_MODE_REPEATED;
    tVOC_Task.Timeout_handler = tVOC_Task_Handle;
    tVOC_Task.Period          = TASK_TVOC_PERIOD;

    err_code |= app_timer_create(&tVOC_Task.p_ID,
                                 tVOC_Task.Run_Mode,
                                 tVOC_Task.Timeout_handler);
    // оƬ��ʼ��
    err_code |= tVOC_Chip_Init();

    if (err_code != NRF_SUCCESS)
    {
        app_trace_log("tVOCоƬ��ʼ��ʧ��!\r\n");    
    }
    else
    {
        err_code |= Task_Timer_Start(&tVOC_Task, NULL);
        if (err_code != NRF_SUCCESS)
        {
            app_trace_log("Task tVOC create failed!\r\n");    
        }
    }


}// End of void tVOC_Task_Create(void)

/*******************************************************************************
*                           ½��@2017-01-03
* Function Name  :  tVOC_Chip_Init
* Description    :  оƬ��ʼ��
* Input          :  None
* Output         :  None
* Return         :  NRF_SUCCESS �ɹ� 1ʧ��
*******************************************************************************/
u32 tVOC_Chip_Init(void)
{
    u32 Err_Code = NRF_SUCCESS;
    
    // Ĭ�ϴ�����error
    System_Err.tVOC = 1;

	if (sgp_probe() != STATUS_OK) 
	{
		app_trace_log("tVOCоƬ��ʼ��ʧ��!\r\n"); 
		Err_Code = 0xFFFFFFFF;
	}
	else
	{
		System_Err.tVOC = 0;

		// ��ȡbaseline
		tVOC_Get_Saved_Baseline(System.Unix_Sec, &tVOC.Baseline_Saved);

		
	}

    return Err_Code;
        
}// End of u32 tVOC_Chip_Init(void)

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  tVOC_Get
* Description    :  ��ȡtVOC
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Get(void)
{

   
}// End of void tVOC_Get(void)

/*******************************************************************************
*                           ½��@2017-03-29
* Function Name  :  tVOC_Task_Handle
* Description    :  tVOC����
* Input          :  void *p_arg
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Task_Handle(void *p_arg)
{
    u8 err;
    u16 tvoc_ppb, co2_eq_ppm;

	// ����baseline
	tVOC_Baseline_Handle();

	err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
	if (err == STATUS_OK) 
	{
		if (Log_Sign < (1000 / TASK_COMMUNAL_TIMER_PERIOD))
		{
			app_trace_log("tVOC  Concentration: %dppb\n", tvoc_ppb);
			app_trace_log("CO2eq Concentration: %dppm\n", co2_eq_ppm);
		}
		 // ��¼tVOC eCO2
		 Sensor.tVOC = tvoc_ppb;
		 Sensor.eCO2 = co2_eq_ppm;


	} 
	else 
	{
		 app_trace_log("error reading IAQ values\n"); 
	}


}// End of void tVOC_Task_Handle(void *p_arg)

/*******************************************************************************
*                           ½��@2017-04-22
* Function Name  :  tVOC_Baseline_Handle
* Description    :  tVOC baseline
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Baseline_Handle(void)
{
	u32 Temp;

	// ��ȡ����baseline
    if (sgp_get_iaq_baseline(&Temp) == STATUS_OK)
    {
    	tVOC.Baseline_Now = Temp;	
    }
    
	// baseline��Ч
	if (tVOC.Baseline_Valid)
	{
	
	}
	else
	{
		
		// 15��������
	    if (tVOC.Baseline_15min_Reset == 0)
	    {
	    	tVOC.Baseline_Timestamp++;

			// 15��������
	    	if (tVOC.Baseline_Timestamp >= 15 * 60)
	    	{
	    		tVOC.Baseline_15min_Reset = 1;
				tVOC.Baseline_Timestamp   = 0;
				
	    		if (sgp_iaq_init() == STATUS_OK)
	    		{
	    			app_trace_log("tVOC  sgp_iaq_init Success \r\n");	
	    		}
	    		else
	    		{
	    			app_trace_log("tVOC  sgp_iaq_init Failed \r\n");		
	    		}
	    	}
	    }
	    else
	    {
	    	// 12 Сʱ�״δ�baseline
	    	if (tVOC.Baseline_Timestamp >= 12 * 60 * 60)
	    	{
	    		tVOC_Save_Baseline(System.Unix_Sec, tVOC.Baseline_Now);	
	    	}
	    }
    }



}// End of void tVOC_Baseline_Handle(void)

/*******************************************************************************
*                           ½��@2017-04-22
* Function Name  :  tVOC_Save_Baseline
* Description    :  tVOC����baseline
* Input          :  u32 uiSec			��ǰunix��
*					u32 uiBaseline		tVOC Baseline
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
u8 tVOC_Save_Baseline(u32 uiSec, u32 uiBaseline)
{
	u32 Buffer[2];
	Buffer[0] = uiSec;
	Buffer[0] = uiBaseline;

	// ��
	if (EEPROM_Write_Data(EEPROM_ADDR_BASELINE, (u8*)&Buffer, 8))
	{
		// ��λbaseline��Ч
		tVOC.Baseline_Valid              = 1;
		tVOC.Baseline_LastSave_Timestamp = uiSec; 
        
        return 1;
	}
	else
	{
		tVOC.Baseline_Valid = 0;
		return 0;
	}


}// End of u8 tVOC_Save_Baseline(u32 uiSec, u32 uiBaseline) 

/*******************************************************************************
*                           ½��@2017-04-22
* Function Name  :  tVOC_Save_Baseline
* Description    :  tVOC��ȡbaseline
* Input          :  u32 uiSec			��ǰunix��
*					u32 *pBaseline		��ȡ��baseline
* Output         :  None
* Return         :  �ɹ� ���ش���ʱʱ��          0ʧ�� baseline����7��Ҳ��ʧ��
*******************************************************************************/
u32 tVOC_Get_Saved_Baseline(u32 uiSec, u32 *pBaseline)
{
	u32 Buffer[2];
	u32 ucResult = 0;

	// ��ȡ�ɹ�
	if (EEPROM_Read_Data(EEPROM_ADDR_BASELINE, (u8*)&Buffer))
	{
		// ���7����
		if ((uiSec > Buffer[0]) && (uiSec - Buffer[0] < (7 * 24 * 60 * 60)))
		{
			// ��ȡbaseline
			*pBaseline = Buffer[1];	

			// ��ȡ����ʱ��
			ucResult   = Buffer[0];

			tVOC.Baseline_Valid              = 1;
			tVOC.Baseline_LastSave_Timestamp = ucResult;
			app_trace_log("-------------------Get Saved baseline = 0x%08X\r\n", *pBaseline);
			
		}
		else
		{
			tVOC.Baseline_Valid = 0;
			app_trace_log("-------------------No Saved baseline!\r\n");
		}
	}

	return ucResult;

}// End of u32 tVOC_Get_Saved_Baseline(u32 uiSec, u32 *pBaseline) 


/*******************************************************************************
*                           ½��@2016-03-29
* Function Name  :  tVOC_Port_Init
* Description    :  tVOC�˿ڳ�ʼ��
* Input          :  None
* Output         :  None
* Return         :  1�ɹ� 0ʧ��
*******************************************************************************/
void tVOC_Port_Init(void)
{

       
}// End of void tVOC_Port_Init(void)

/*******************************************************************************
*                           ½��@2017-03-29
* Function Name  :  tVOC_Variable_Init
* Description    :  tVOC������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void tVOC_Variable_Init(void)
{
	// Ĭ��baseline��Ч
	tVOC.Baseline_Valid = 0;
    
}// End of void tVOC_Variable_Init(void)

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/




