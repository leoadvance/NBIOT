/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Struct.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/25/2016
* Description        :  �ṹ�嶨��
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STRUCT_H
#define __STRUCT_H

#if defined(__CC_ARM)
#pragma anon_unions
#endif

/* Includes ------------------------------------------------------------------*/
#include "Global_Cfg.h"
#include "app_timer.h"
#include "ble_gatts.h"
#include "nrf_adc.h"

/* Private define ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

typedef struct
{

    unsigned int        ms;                                             // ʱ���׼
    unsigned int        Last_Tick;                                      // �ϴ�Tick
    
} Time_Base_Typedef;                                                	// ʱ���׼�ṹ��

typedef struct
{

    unsigned char       Adv_En;                                         // ��һʹ�ܰ󶨹㲥
    unsigned char       Blink_Interval;                                 // ��˸���
    unsigned short      Count;                                          // �󶨼���
    unsigned short      Time_Left;                                      // ʣ��ʱ�� s
    
    
} Bond_Typedef;                                                     	// ʱ���׼�ṹ��

typedef struct
{

    unsigned char       Magnet_Near;                                    // ��һʹ��������
    unsigned char       Magnet_Last;                                    // �ϴ�״̬
    unsigned short      Timestamp;                                      // ʱ���
    
    
} Hall_Typedef;                                                     	// ʱ���׼�ṹ��

typedef struct
{
    unsigned char       Status;                                         // ״̬
    unsigned char       Long;                                           // ����
    unsigned int        Push_Timestamp;                                 // ����ʱ���
    unsigned int        Free_Timestamp;                                 // �ͷ�ʱʱ���

} Button_Typedef;   

typedef struct
{
    float               fTemp;                                          // �¶�
    float               fHumi;                                          // ʪ��
    short               sTemp;                                          // �¶����� * 0.1
    unsigned short      usHumi;                                         // ʪ������ * 0.1
    unsigned short      tVOC;                                         	// tVOC ppb
    unsigned short      eCO2;                                         	// eCO2 ppm
    unsigned short      Bat_Val_mv;                                     // ��ص�ѹ mv
    unsigned char       Bat_Percent;                                    // �����ٷֱ�
    
    
} Sensor_Typedef;                                                		// �������ṹ��

typedef struct
{

    unsigned int      	Baseline_Timestamp;                        		// tVOC ��¼baselineʱ���
    unsigned int      	Baseline_Saved;                        			// tVOC ��¼baselineʱ���
    unsigned int      	Baseline_Now;                        			// tVOC ��¼baselineʱ���
    unsigned int      	Baseline_LastSave_Timestamp;                    // tVOC �ϴμ�¼baselineʱ���
    unsigned char       Baseline_Valid;                           		// baseline��Ч
    unsigned char       Baseline_15min_Reset;							// tVOC 15�������ñ�־λ
    unsigned char       Baseline_Refresh;								// tVOC ˢ��
    
} tVOC_Typedef;                                                			// tVOC�ṹ��

typedef struct
{
    unsigned char       Buffer[HISTORICAL_DATA_SIZE];					// ��ʷ����
	unsigned char       Head_Sign;										// ͷλ��
	unsigned char       End_Sign;										// βλ��
	unsigned short      ADD_Num;                        				// �����ۼӺ�����
	unsigned int      	Timestamp;                        				// ʱ���
	unsigned int      	ADD_Sun;                        				// �ۼӺ�

} Historical_Typedef;                                             		// ��ʷ���ݽṹ��


typedef struct
{
    unsigned char       Running;                                        // ��һʱ��ʾ��������
    app_timer_mode_t    Run_Mode;                                       // ����ģʽ�����λ�������
    unsigned int        Period;                                         // ��������(ms) ���512000
    app_timer_id_t      p_ID;
    app_timer_timeout_handler_t Timeout_handler;                        // ��ʱ���г���

} Task_Typedef;                                                      	// ����ṹ��

typedef struct
{
    nrf_adc_config_t    Channel_Config;                                 // ͨ������
    unsigned int        Vol_mv;                                         // ��ѹ mv   

} ADC_Typedef;                                                        	// ����ṹ��

typedef struct
{
    
    unsigned char       Frame_Counter;                                  // ֡����
    unsigned char       MAC[MAC_FLASH_SIZE];                            // MAC��ַ
    unsigned char       Token[TOKEN_FLASH_SIZE];                        // MAC��ַ
    unsigned char       MACToken[MAC_FLASH_SIZE + TOKEN_FLASH_SIZE];    // MAC��ַ
    unsigned char       Int_Event;                                      // ����EvEnt�¼�
    unsigned char       Int_Event_ID;                                   // ����EvEnt�¼�ID
    unsigned short      Timestamp_Hall;                                 // ����ʱ���
    unsigned short      Timestamp_Bat;                                  // ����ʱ���
    
    unsigned short      Event_ID;                                       // �¼�ID
    unsigned short      Current_Event_ID;                               // ��ǰ�¼�ID
    short               Temp_Val;                                       // ��ʪ�� 0.1���϶�
    unsigned char       Humi_Val;                                       // ʪ��ֵ
    unsigned char       Temp_Humi_Refresh;                              // ��һʱˢ������
    unsigned char       Bat_Percent;                                    // ���� 0~100%
    unsigned char       Need_Update;                                    // ��һʱ��Ҫ��������

    union
    {
        unsigned short  Frame_Control;
        struct
        {
            unsigned short  Factory_New             : 1;                // 1 δ�� ���ڳ�������        0 �Ѿ����󶨹��û�����Ҫ��
            unsigned short  Connected               : 1;                // 1 �ѽ�����                   0 δ����
            unsigned short  Central                 : 1;                // 1 ��ǰ��Central              0 ��ǰ��Peripheral ���Cennected Ϊ1���bit��Ч
            unsigned short  Encrypted               : 1;                // 1 �Ѿ�����                   0 ��ǰδ����
            unsigned short  MAC_Include             : 1;                // 1 Frame_Control�����mac��ַ 0 ������MAC��ַ
            unsigned short  Capability_Include      : 1;                // 1 ����Capability����         0 ������Capability����
            unsigned short  Event_Include           : 1;                // 1 ����Event����              0 ������Event����
            unsigned short  Private_Include         : 1;                // 1 ��������˽������           0 ����������˽������
            unsigned short  Subheading_Include      : 1;                // 1 ����������                 0 ������������
            unsigned short  Band_Confirm            : 1;                // 1 ��ȷ�ϰ�                 0 �ǰ�ȷ�ϰ�  
            unsigned short  Reserved                : 2;                // Ԥ��
            unsigned short  Version                 : 4;                // Э��汾��
     
        }Frame_Control_Bit;
    };
    
    union
    {
        unsigned char   Capability;
        struct
        {
            unsigned char   Connectable             : 1;                // 1 �豸����������             0 �豸û���������� 
            unsigned char   Be_Central              : 1;                // 1 �豸������������           0 �豸û������������
            unsigned char   Encrypt_Ability         : 1;                // 1 �豸�м�������             0 �豸û�м�������
            unsigned char   Bond_Ability            : 2;                // 0x00 ����� 0x01 ʹ��MIOTǰ�� 0x10 ʹ��MIOT��� 0x11 Ԥ��
            unsigned char   Reserved                : 3;                // Ԥ��

            
        }Capability_Bit;
    };

    union
    {
        unsigned char   Adv_En;                                         // 0 ������㲥
        struct
        {
            unsigned char   Temp_Humi               : 1;                // �����¶ȹ㲥
            unsigned char   Bat_Percent             : 1;                // ��������㲥
            unsigned char   Reserved                : 6;                // Ԥ��

            
        }Adv_En_Bit;
    };

}MIOT_Typedef;    

typedef union
{
    unsigned long       ALL;                                            // ȫ��״̬
    struct
    {
        unsigned long   Temp_Humi               : 1;                    // ��ʪ��
        unsigned long   tVOC                    : 1;                    // tVOC
        unsigned long   EEPROM                  : 1;                    // EEPROM
        unsigned long   RTC                  	: 1;                    // RTC
        unsigned long   Reserved                : 28;
    };
    
}System_ERR_Typedef;


typedef void (*DUCK_BLE_Data_Handler_t) (unsigned char * pData, unsigned short usLength);

typedef struct 
{
    unsigned char       Temp_Humi_Listening_En;                         // ��һʱʹ��֪ͨ
    unsigned char       Message_Listening_En;                           // ��һʱʹ��֪ͨ
    unsigned char       UUID_Type;                                      // UUID���� 16Bit����128Bit
    unsigned short      Service_Handle;                                 // SoftDevice�ṩ�ķ�����
    unsigned short      Conn_Handle;                                    // SoftDevice�ṩ�ĵ�ǰ���Ӵ���
    
    ble_gatts_char_handles_t Temp_Humi_Handle;                          // SoftDevice�ṩ��ʪ�ȶȴ���
    ble_gatts_char_handles_t Message_Handle;                            // SoftDevice�ṩ��ʪ�ȶȴ���
    
}BLE_Service_Typedef;                                              		// BLE Service �ṹ��

typedef struct 
{
    unsigned char       Page_Show;									    // ��Ļ����
    unsigned char       Page_Now;										// ��ǰ����
    
    union
    {
        unsigned char   Need_Update;                                    // �Ƿ���Ҫˢ��
        struct
        {
            unsigned char   Temp_Humi               : 1;                // �¶���Ҫˢ��
            unsigned char   Bat_Percent             : 1;                // ������Ҫˢ��
            unsigned char   BT_LOGO                 : 1;                // ����LOGO��Ҫˢ��
            unsigned char   Reserved                : 5;                // Ԥ��

            
        }Need_Update_Bit;
    };
    
}LCD_Typedef;                                                     		// LCD �ṹ��

typedef struct
{
    unsigned char       Rx_Data[128];                                   // ���ջ���
    unsigned char       Rx_State;                                       // ״̬
    unsigned char       Rx_Timeout;                                     // ���ճ�ʱ
    unsigned short      Rx_Len;                                         // ���ճ���
    unsigned short      Tx_Len;                                         // ���ճ���

    
}UART_Typedef;

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

typedef struct
{
	Time_t              Time;											// ϵͳʱ��
    unsigned long		Unix_Sec;										// unixʱ��

    
}System_Typedef;


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

#endif /* __STRUCT_H */

/******************* (C) COPYRIGHT 2016 ½�� *****END OF FILE******************/
