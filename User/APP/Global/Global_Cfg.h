/******************** (C) COPYRIGHT 2016 ½�� **********************************
* File Name          :  Global_Cfg.h
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  12/23/2016
* Description        :  Global header file
* Description        :  ȫ�ֶ���
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_CFG_H
#define __GLOBAL_CFG_H

/* Includes ------------------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
//----------------------- System ----------------------------------------------/
#define     DEBUG
#ifdef      DEBUG
#define     ENABLE_DEBUG_LOG_SUPPORT                                    // ʹ��ϵͳ����
#endif
//#define     SYS_WDT                                                     // ʹ�ܿ��Ź�
//#define     BLE_OPEN                                                    // ʹ��BLE



#define     SYS_STATUS_IDLE             0x00                            // Ĭ��״̬
#define     SYS_STATUS_ADV              0x01                            // �㲥̬
#define     SYS_STATUS_CONNECT          0x02                            // ����̬



#define     APP_TIMER_DIV               0                               // APP��ʱ����Ƶ
#define     SYS_MAX_TIMERS              2 + 10                          // ��ඨʱ������   GPIOEռ��һ��  m_conn_params_timer_id ռ��һ��   
#define     SYS_MAX_OP_QUEUE_SIZE       12                              // ������������
#define     MAX_EVENT_QUEUE_SIZE        (2 * SYS_MAX_OP_QUEUE_SIZE)     // ���������¼����д�С


#define     TICK_TO_MS                  33                              // tick��ת��ms

//----------------------- Task ------------------------------------------------/
#define     TASK_BATTERY_PERIOD         (10 * 1000)                     // ���������������
#define     TASK_TEMP_HUMI_PERIOD       (1 * 1000)                      // ��ʪ�ȼ����������
#define     TASK_TVOC_PERIOD      	    (1 * 1000)                      // tVOC�����������
#define     TASK_BLE_PERIOD             (1 * 1000)                      // BLE��������
#define     TASK_LCD_PERIOD             (1 * 1000)                      // LCD��������
#define     TASK_COMMUNAL_TIMER_PERIOD  (1 * 100)                       // ���ö�ʱ����������
#define     TASK_COMMUNAL_TIMER_FREQ    (1000 / TASK_COMMUNAL_TIMER_PERIOD) // ���ö�ʱ������Ƶ��
#define     TASK_MAGNET_CHECK_PERIOD    (1 * TASK_COMMUNAL_TIMER_FREQ)  // �����������

//----------------------- BLE -------------------------------------------------/
#define     CENTRAL_LINK_COUNT          0                               // ���ӵ���������    
#define     PERIPHERAL_LINK_COUNT       1                               // ���ӵĴӻ�����
#define     BLE_DEVICE_NAME             "NBIOT"                         // BLE�豸����

#define     BLE_MANUFACTURER_NAME       "Cleargrass Inc"                // ������          
#define     BLE_FW_REV_STR              "00.00.17"                       // ����汾
#define     BLE_MODULE_NUM              "Duck"                          // �ͺ� 
#define     DEFAULT_HARDWARE_VERSION    "2.00"                          // Ĭ��Ӳ���汾  

#define     BLE_ADV_INTERVAL            MSEC_TO_UNITS(1000, UNIT_0_625_MS) // �㲥���                          // BLE�豸����
#define     MIN_CONN_INTERVAL           MSEC_TO_UNITS(20, UNIT_1_25_MS)             /**< Minimum acceptable connection interval (20 ms), Connection interval uses 1.25 ms units. */
#define     MAX_CONN_INTERVAL           MSEC_TO_UNITS(75, UNIT_1_25_MS)             /**< Maximum acceptable connection interval (75 ms), Connection interval uses 1.25 ms units. */
#define     SLAVE_LATENCY               0                                           /**< Slave latency. */
#define     CONN_SUP_TIMEOUT            MSEC_TO_UNITS(4000, UNIT_10_MS)             /**< Connection supervisory timeout (4 seconds), Supervision Timeout uses 10 ms units. */

#define     DUCK_FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000, APP_TIMER_DIV)  /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define     DUCK_NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000, APP_TIMER_DIV) /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define     DUCK_MAX_CONN_PARAMS_UPDATE_COUNT    3  

//----------------------- flash -----------------------------------------------/
#define     MAC_FLASH_SIZE              6                               // mac flash�����ֽ�
#define     TOKEN_FLASH_SIZE            8                               // token flash�����ֽ�

//----------------------- BLE MIOT --------------------------------------------/
#define     MIOT_EVENT_ID_TH            0x100D                          // ��ʪ���¼�ID
#define     MIOT_EVENT_TH_LEN           3                               // ��ʪ���¼����� 

#define     MIOT_EVENT_ID_BAT           0x100A                          // �����¼�ID 
#define     MIOT_EVENT_BAT_LEN          1                               // �����¼����� 

#define     MIOT_EVENT_ID_HALL          0x2400                          // hall�¼�ID 
#define     MIOT_EVENT_HALL_LEN         1                               // hall�¼����� 

#define     MIOT_EVENT_ID_BOND          0x0002                          // ���¼� 
#define     MIOT_EVENT_BOND_LEN         2                               // ���¼�����  


#define     MIOT_SERVICE_ID             0xFE95                          // MIOT����ID 
#define     MIOT_PRODUCT_ID             0x01AA                          // MIOT��ƷID 
#define     MIOT_VERSION                (0x02 & 0x0F)                   // Э��汾  
#define     MIOT_NEED_BOND              0x01                            // ��Ҫ��  

#define     MIOT_MAX_SIZE               (BLE_GAP_ADV_MAX_SIZE - 3 - 4)  // ����ֽ��� flag 3�ֽ� MIOT 4�ֽ�

#define     MIOT_MASTER_EVENT_INTERVAL  10                              // ��������
#define     MIOT_SLAVE_EVENT_INTERVAL   (1 + MIOT_MASTER_EVENT_INTERVAL)// ��������

#define     MIOT_HALL_EVENT_INTERVAL    5                               // �������
#define     MIOT_BAT_EVENT_INTERVAL     10                              // ��ؼ��

//----------------------- BLE Bond --------------------------------------------/
#define     MIOT_EVENT_ID_BOND_DURATION 30 * TASK_COMMUNAL_TIMER_FREQ   // ���¼�����ʱ�� 
#define     MIOT_BOND_BLINK             (500 / TASK_COMMUNAL_TIMER_PERIOD)// 500ms ��˸һ��
#define     MIOT_BOND_STOP_DELAY        5 * TASK_COMMUNAL_TIMER_FREQ    // 5s �󶨺������˸һ��

//----------------------- LCD -------------------------------------------------/
#define     LCD_BUFFER_SIZE             13                              // LCD�����С

//----------------------- Sensor ----------------------------------------------/
#define     MAX_GET_SENSOR_ERROR        10                              // ���ɼ�������������

//----------------------- Special Code ----------------------------------------/
#define     SPECIAL_CODE_RESET          0x10000000                      // ��Ϊ��λ

//----------------------- Pin Config ------------------------------------------/
#define     GPIO_TEST_PIN               1                               // �ٶȲ��� �ܽ�

#define     BAT_ADC_PIN                 3                             	// ���ADC �ܽ�

#define     COMMUNAL_IIC_2_SCL_PIN      7                              	// ͨ��IICʱ��
#define     COMMUNAL_IIC_2_SDA_PIN      8                              	// ͨ��IIC����


#define     UART_TX_PIN                 9                               // ����
#define     UART_RX_PIN                 11


#define     SHT30_SCL_PIN               12                              // ��ʪ��ʱ��
#define     SHT30_SDA_PIN               13                              // ��ʪ������

#define     COMMUNAL_IIC_SCL_PIN        14                              // ͨ��IICʱ��
#define     COMMUNAL_IIC_SDA_PIN        15                              // ͨ��IIC����

#define     OLED_SCL_PIN                25                              // OLED SCL �ܽ�
#define     OLED_SDA_PIN               	24                              // OLED SDA �ܽ�
#define     OLED_RST_PIN               	23                              // OLED RST �ܽ�
#define     OLED_DC_PIN               	22                              // OLED DC �ܽ� ��������ѡ��ܽ�






#define     BOUTTON_PIN                 17                              // �����ܽ�




#define     MAX_INTERRUPT_PIN_NUM       1                               // �жϹܽ�����
#define     BUTTEN_EVENT_DELAY_MS       10                              // �����¼���ʱʱ��

//----------------------- Battery ---------------------------------------------/

#define     BAT_ADC_CHANNEL             NRF_ADC_CONFIG_INPUT_4          // ���ADCͨ��
#define     BAT_ADC_BUFFER_SIZE         8                               // ADC�������


/* Private typedef -----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

#endif /* __GLOBAL_CFG_H */

/******************* (C) COPYRIGHT 2016 ½�� ********END OF FILE***************/
