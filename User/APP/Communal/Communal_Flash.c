/******************** (C) COPYRIGHT 2017 ½�� **********************************
* File Name          :  Communal_Flash.c
* Author             :  ½��
* CPU Type           :  nRF51802
* IDE                :  IAR 7.8
* Version            :  V1.0
* Date               :  02/12/2017
* Description        :  ���ó���
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "Communal_Flash.h"


/* Private variables ---------------------------------------------------------*/
        
/* Private function prototypes -----------------------------------------------*/
u32 Communal_Flash_Load(uint8_t           * p_dest,
                        pstorage_handle_t * p_src,
                        pstorage_size_t     size,
                        pstorage_size_t     offset);                    // ��ȡ

                        
u32 Communal_Flash_Update(pstorage_handle_t * p_dest,
                          uint8_t           * p_src,
                          pstorage_size_t     size,
                          pstorage_size_t     offset);                  // д��
                          
u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size); // ɾ��

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Communal_Flash_Load
* Description    :  flash������
* Input          :  uint8_t           * p_dest ��ȡ����
*                   pstorage_handle_t * p_src  ��ַ
*                   pstorage_size_t     size   ����
*                   pstorage_size_t     offset ƫ��
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Communal_Flash_Load(uint8_t           * p_dest,
                        pstorage_handle_t * p_src,
                        pstorage_size_t     size,
                        pstorage_size_t     offset)
{
    u32 Err_Code;
    
    // �ȴ����ͷ�
    while(Flash_Used)
    {
        Power_Manage();
    }

    // ռ��flash
    Flash_Used = 1;
    Err_Code = pstorage_load(p_dest, p_src, size, offset);

    if (Err_Code == NRF_SUCCESS)
    {
        // �ȴ����ͷ�
        while(Flash_Used)
        {
            Power_Manage();
        }
    }
    else
    {
        // ���ռ��
        Flash_Used = 0;
    }

    return Err_Code;
    
}// End of u32 Communal_Flash_Load

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Communal_Flash_Update
* Description    :  flashд����
* Input          :  pstorage_handle_t * p_dest ��ַ
*                   uint8_t           * p_src  ��д������
*                   pstorage_size_t     size   ����
*                   pstorage_size_t     offset ƫ��
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Communal_Flash_Update(pstorage_handle_t * p_dest,
                          uint8_t           * p_src,
                          pstorage_size_t     size,
                          pstorage_size_t     offset)
{
    u32 Err_Code;
    
    // �ȴ����ͷ�
    while(Flash_Used)
    {
        Power_Manage();
    }

    // ռ��flash
    Flash_Used = 1;
    Err_Code = pstorage_update(p_dest, p_src, size, offset);

    if (Err_Code == NRF_SUCCESS)
    {
        // �ȴ����ͷ�
        while(Flash_Used)
        {
            Power_Manage();
        }
    }
    else
    {
        // ���ռ��
        Flash_Used = 0;
    }

    return Err_Code;
    
}// End of u32 Communal_Flash_Update

/*******************************************************************************
*                           ½��@2017-03-08
* Function Name  :  Communal_Flash_Clear
* Description    :  flashɾ��
* Input          :  pstorage_handle_t * p_dest ��ɾ����ַ
*                   pstorage_size_t     size   ����
* Output         :  None
* Return         :  None
*******************************************************************************/
u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size)
{
    u32 Err_Code;
    
    // �ȴ����ͷ�
    while(Flash_Used)
    {
        Power_Manage();
    }

    // ռ��flash
    Flash_Used = 1;
    Err_Code = pstorage_clear(p_dest, size);

    if (Err_Code == NRF_SUCCESS)
    {
        // �ȴ����ͷ�
        while(Flash_Used)
        {
            Power_Manage();
        }
    }
    else
    {
        // ���ռ��
        Flash_Used = 0;
    }

    return Err_Code;
    
}// End of u32 Communal_Flash_Clear(pstorage_handle_t * p_dest, pstorage_size_t size)

/******************* (C) COPYRIGHT 2017 ½�� **************END OF FILE*********/




