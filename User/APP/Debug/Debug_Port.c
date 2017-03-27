/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Debug_Port.c
* Author             :  ½��
* CPU Type           :  nRF51822
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/17/2017
* Description        :  Debug��������
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Debug_Port.h"
#include "nrf_gpio.h"
#include "app_uart.h"
#include "app_error.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Debug_Variable_Init(void);                                         // Debug������ʼ��
void Debug_Port_Init(void);                                             // Debug�˿ڳ�ʼ��  
void Debug_Uart_Event_Handle(app_uart_evt_t * Event_Ptr);               // ����Handle����

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-02-17
* Function Name  :  Debug_Uart_Event_Handle
* Description    :  ����Handle����
* Input          :  app_uart_evt_t * Event_Ptr  ��������¼�ָ��
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Uart_Event_Handle(app_uart_evt_t * Event_Ptr)
{
    u8 ucTemp;
    
    // �ж��¼�����
    switch (Event_Ptr->evt_type)
    {
        case APP_UART_DATA_READY:
        {

            while (app_uart_get(&ucTemp) != NRF_ERROR_NOT_FOUND)
            {
                // �ǵȴ�����״̬
                if (Debug_UART.Rx_State != UART_RX_STATE_PENDING)
                {
                    // ����̬
                    Debug_UART.Rx_State = UART_RX_STATE_BUSY;

                    // �����
                    if (Debug_UART.Rx_Len < 128)
                    {
                        // �״ν��� ������ʱ��
                        if(Debug_UART.Rx_Len == 0)
                        {
                            Task_Timer_Start(&Debug_Rx_Task, NULL);
                        }
                        
                        Debug_UART.Rx_Data[Debug_UART.Rx_Len++] = ucTemp;
                    }

                    // ˢ�½��ճ�ʱ
                    Debug_UART.Rx_Timeout = 2;
                }


            }
            
        }break;

        case APP_UART_COMMUNICATION_ERROR:
        {
            // ��ʱ�ų����մ���
            if (Event_Ptr->data.error_communication & 0x03)
            {
                APP_ERROR_HANDLER(Event_Ptr->data.error_communication);
            }
            else
            {
                app_trace_log("---------------------------------------------- Rx Error = 0x%02X\r\n", Event_Ptr->data.error_communication);
            }
            
        }break;

        case APP_UART_FIFO_ERROR:
        {
            APP_ERROR_HANDLER(Event_Ptr->data.error_code);
            
        }break;

        default:
        break;
    }
    
}// End of void Debug_Uart_Event_Handle(app_uart_evt_t * Event_Ptr)


/*******************************************************************************
*                           ½��@2017-02-17
* Function Name  :  Debug_Variable_Init
* Description    :  Debug������ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Variable_Init(void)
{
    Debug_UART.Rx_Len      = 0;
    Debug_UART.Rx_State    = UART_RX_STATE_IDLE;
    Debug_UART.Tx_Len      = 0;


    
}// End of void Debug_Variable_Init(void)

/*******************************************************************************
*                           ½��@2017-02-17
* Function Name  :  Debug_Port_Init
* Description    :  Debug�˿ڳ�ʼ�� 
*                   P.25   <--   DEBUG_RX_PIN
*                   P.24    -->  DEBUG_TX_PIN
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void Debug_Port_Init(void)
{
    uint32_t err_code = NRF_SUCCESS;
    
    const app_uart_comm_params_t Debug_UART_Params =
    {
        UART_RX_PIN,
        UART_TX_PIN,
        0xFF,
        0xFF,
        APP_UART_FLOW_CONTROL_DISABLED,
        false,
        UART_BAUDRATE_BAUDRATE_Baud115200
    };

    APP_UART_FIFO_INIT( &Debug_UART_Params,                 // ���ڲ���
                        UART_RX_BUF_SIZE,                   // ���ջ����С
                        UART_TX_BUF_SIZE,                   // ���ͻ����С
                        Debug_Uart_Event_Handle,            // �ص������ж�
                        APP_IRQ_PRIORITY_LOW,               // �ж����ȼ�
                        err_code);
                        
    APP_ERROR_CHECK(err_code);
    
    
}// End of void Debug_Port_Init(void)



/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/

