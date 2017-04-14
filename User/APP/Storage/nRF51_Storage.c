/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  nRF51_Storage.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  03/07/2017
* Description        :  mac��ַ����
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "nRF51_Storage.h"
#include "nrf_soc.h"
#include "Communal_Flash.h"
#include <stdlib.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void nRF51_Storage_Init(void);                                          // nRF51_Storage��ʼ��
void nRF51_Storage_Callback(pstorage_handle_t *  handle, u8   OP_Code,
                           u32  Err_Code, u8*  pData, u32  uiData_Len); // ����flash�ص�
                                               
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-03-09
* Function Name  :  nRF51_Storage_Init
* Description    :  MAC flash��ʼ��
* Input          :  None
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_Storage_Init(void)
{


}// End of void nRF51_Storage_Init(void)

/*******************************************************************************
*                           ½��@2017-03-09
* Function Name  :  nRF51_Storage_Callback
* Description    :  flash�����ص�
* Input          :  u32  Err_Code   �������
*                   u8   OP_Code    ������(����ԭ��) 
*                   u8*  pData      Ҫд���ֵ
*                   u32  Data_Len   ���ݳ���
* Output         :  None
* Return         :  None
*******************************************************************************/
void nRF51_Storage_Callback(pstorage_handle_t *  handle, u8   OP_Code,
                           u32  Err_Code, u8*  pData, u32  uiData_Len)
{
    if (Err_Code != NRF_SUCCESS)
    {
        // Load operation failed.
        app_trace_log("[E]: flash operation error, opcode:%d Err_Code:%d\r\n", OP_Code, Err_Code);

        // �ͷ�flashռ��
        Flash_Used = 0;

        return ;
    }
    
//    app_trace_log("MAC_Flash_Callback!\r\n");


    switch (OP_Code) 
    {
        case PSTORAGE_LOAD_OP_CODE:
        {
//            app_trace_log("MAC��ַ��ȡ�ɹ�!\r\n");
           
        }break;

        case PSTORAGE_STORE_OP_CODE:
        {
          
            
        }break;

        case PSTORAGE_UPDATE_OP_CODE:
        {
//            app_trace_log("MAC��ַ����ɹ�!\r\n");
               
        }break;

        case PSTORAGE_CLEAR_OP_CODE:
        {
            
            
        }break;

        default:
            break;
            
    }

    // �ͷ�flashռ��
    Flash_Used = 0;
    
}// End of static void nRF51_Storage_Callback

/******************* (C) COPYRIGHT 2017 ½�� ************* END OF FILE ********/










