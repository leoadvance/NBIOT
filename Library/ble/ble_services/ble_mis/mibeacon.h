#ifndef __MIBEACON_H
#define __MIBEACON_H


#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "mi.h"

/*********************************************************************
 * CONSTANTS
 */


/*
"Bit 0: 1 δ�󶨣����ڳ�������, 0 �Ѿ����û��󶨹�����Ҫ��
 Bit 1: 1 ��ǰ������, 0 ��ǰδ����
 Bit 2: 1 ��ǰ��Central��0����ǰ��Peripheral,���bit1Ϊ1�����λ��Ч
 Bit 3: 1 �ð��Ѽ��ܣ�0���ð�δ����
 Bit 4: 1 Frame control�����6��byte��MAC��ַ��0 ������6��BYTE��MAC��ַ
 Bit 5: 1 ����capability, 0 ������capability
 Bit 6: 1 �����¼���0 �������¼�
 Bit 7: 1 ���������Զ������ݣ�0�������Զ�������"
 
"Bit 0: 1 ���������Զ������ܼ�ͥ������չʾ���ݣ�0���������������� 
 Bit 1: 1 ��ȷ�ϰ��� 0���ǰ�ȷ�ϰ�
 Bit 2~3: ����
 Bit 4~7: ��"
 */

#define MIBEACON_FC_DEFAULT                           0x0000
#define MISERVICE_UUID                                0xFE95

#define ADV_TYPE_SERVCIE_DATA                         0x16


/**
 * MI Beacon minium length.
 * Including len(1) + type(1) + serviceUUID(2) + FrameCtrl(2) + Product ID(2)
 */
#define MIBEACON_MIN_LEN                              5


/**
 * MI Beacon items.
 */
#define MIBEACON_ITEM_FACTORY_NEW                     0x0001
#define MIBEACON_ITEM_CONNECTED                       0x0002
#define MIBEACON_ITEM_CENTRAL                         0x0004
#define MIBEACON_ITEM_SEC_ENABLE                      0x0008
#define MIBEACON_ITEM_MAC_INCLUDE                     0x0010
#define MIBEACON_ITEM_CAP_INCLUDE                     0x0020
#define MIBEACON_ITEM_EVT_INCLUDE                     0x0040
#define MIBEACON_ITEM_MIHOME_TITLE_INCLUDE            0x0080
#define MIBEACON_ITEM_MANUFACTORY_DATA_INCLUDE        0x0100
#define MIBEACON_ITEM_BINDING_CFM                     0x0200

#define MIBEACON_ITEM_VERSION                         0x4000
#define MIBEACON_ITEM_PRODUCT_ID                      0x8000


/**
 * Definition for IO capability type.
 */
#define MIBEACON_BOND_NONE                            0x00
#define MIBEACON_BOND_PREBINDING                      0x01
#define MIBEACON_BOND_POSTBINDING                     0x02





/*********************************************************************
 * TYPEDEFS
 */

/**
 * Event format in Mi Beacon
 */
typedef struct {
    uint16_t eventID;
    uint8_t  eventData[1];
} mibeacon_evt_t;


/**
 * Capability format in Mi Beacon
 */
typedef union {
    struct {
        uint8_t connectable : 1;
        uint8_t centralable : 1;
        uint8_t encryptable : 1;
        uint8_t bondAbility : 2;
        uint8_t reserved    : 3;
    } bf;
    uint8_t value;
} mibeacon_capability_t;


/**
 * MI Beacon format
 */
typedef struct {
    uint8_t  len;
    uint8_t  type;           // 0x16, Service Data
    uint16_t serviceUUID;   // 0xFE95, MI Service
    uint16_t frameCtrl;  
    uint16_t productID;
    uint8_t  frameCounter;
    uint8_t  variableData[1];
} mibeacon_fmt_t;


/*********************************************************************
 * MACROS
 */


/*********************************************************************
 * Profile Callbacks
 */
 

/*********************************************************************
 * API FUNCTIONS 
 */


/*
 * mibeacon_set - API to set mi beacon parameters
 *
 * @param   item - ID of optional parameters
 * @param   data - adv data of specified mi beacon item
 * @param   len  - len of the data
 */
mi_sts_t mibeacon_set(uint16_t item, uint8_t* data, uint8_t len);

/*
 * mibeacon_append   - Append mi beacon data to user adv data.
 *
 * @param   advData  - The pointer of user advertising data.
 * @param   len      - The length of user advertising data.
 * @param   totalLen - The total length after append the Mi beacon
 *
 * @return  Status.
 */
mi_sts_t mibeacon_append(uint8_t* advData, uint8_t len, uint8_t* totalLen);

/*
 * mibeacon_set_and_append   - Set some item and send it immediatelly.
 *
 * @param   item - ID of optional parameters
 * @param   data - adv data of specified mi beacon item
 * @param   len  - len of the data
 * @param   advData  - The pointer of user advertising data.
 * @param   len      - The length of user advertising data.
 * @param   totalLen - The total length after append the Mi beacon
 *
 * @return  Status.
 */
mi_sts_t mibeacon_set_and_append(uint16_t item, uint8_t* data, uint8_t len, uint8_t* advData, uint8_t advLen, uint8_t *totalLen);



#define MIBEACON_SET_BINDING_CFM_AND_APPEND(adv, advLen, sts, totalLen)   \
    do {uint8 t = 1; sts = mibeacon_set_and_append(MIBEACON_ITEM_BINDING_CFM,&t,1,adv,advLen,totalLen);} while(0)
      
#define MIBEACON_CLR_BINDING_CFM_AND_APPEND(adv, advLen, sts, totalLen)   \
    do {sts = mibeacon_set_and_append(MIBEACON_ITEM_BINDING_CFM,NULL,0,adv,advLen, totalLen);} while(0)


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* __MIBEACON_H */
