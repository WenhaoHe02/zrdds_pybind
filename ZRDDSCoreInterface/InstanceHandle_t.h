/**
 * @file:       InstanceHandle_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDS_InstanceHandle_t_h__
#define DDS_InstanceHandle_t_h__

#include "OsResource.h"
#include "ZRSequence.h"

/**
 * @struct DDS_InstanceHandle_t
 *
 * @ingroup CoreBaseStruct
 *          
 * @brief   用来表示一个实体或者一个数据实例。
 *
 * @details  - 唯一标识域参与者、数据写者、数据读者等实体；
 *           - 唯一标识数据实例（键值相同的样本），16字节的内容取决于键值CDR序列化的结果，不满16字节补零，大于16字节则取序列化结果的MD5码.
 */

typedef struct DCPSDLL DDS_InstanceHandle_t
{
    /**   
     * @brief   16字节唯一标识实体。
     * 
     * @details 其中：
     *          - [0-3]字节标识实体所属节点IP。
     *          - [4-7]字节标识实体所属进程(任务)ID。
     *          - [8-11]字节标识实体所属域参与者ID(域参与者ID在进程内从1开始递增)。  
     *          - [12-14]字节标识实体ID。  
     *          - 15字节标识实体类型：  
     *              - 高2位标识实体种类：  
     *                  - 0x00：用户自定义实体；  
     *                  - 0x11：DDS内置实体；  
     *                  - 0x01：厂商自定义实体；  
     *              - 低6位标识实体类型：  
     *                  - 0x02表示实体为具有Key的数据写者；  
     *                  - 0x03表示实体为无Key的数据写者；
     *                  - 0x07表示实体为具有Key的数据读者；  
     *                  - 0x04表示实体为无Key的数据写读者；
     */
    DDS_Octet value[16];
    /** 
     * @brief   该成员为true时表示value值有效，否则该DDS_InstanceHandle_t无效。
     * 
     * @note    在使用value之前应判断valid是否为true。
     */
    DDS_Boolean valid;
#ifdef _ZRDDSCPPINTERFACE

    /**
     * @fn  DDS_Boolean operator==(const DDS_InstanceHandle_t& handle) const;
     *
     * @brief   C++接口中重载的相等比较操作符，比较规则参见 ::DDS_InstanceHandle_t_Compare 。
     *
     * @param   handle  操作数。
     *
     * @return  true表示两者相等，否则两者不等。
     */

    DDS_Boolean operator==(const DDS_InstanceHandle_t& handle) const;

    /**
     * @fn  DDS_Boolean operator<(const DDS_InstanceHandle_t& handle) const;
     *
     * @brief   C++接口重载的比较操作符，比较规则参见 ::DDS_InstanceHandle_t_Compare 。
     *
     * @param   handle  操作数。
     *
     * @return  true 表示this < handle，false表示 this >= handle。
     */

    DDS_Boolean operator<(const DDS_InstanceHandle_t& handle) const;
#endif
}DDS_InstanceHandle_t;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @fn  DCPSDLL DDS_Long DDS_InstanceHandle_t_Compare(const DDS_InstanceHandle_t* handle1, const DDS_InstanceHandle_t* handle2);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   C风格的 DDS_InstanceHandle_t 比较函数。
 *
 * @details 比较规则：所有无效的DDS_InstanceHandle_t均相等，且小于所有有效 DDS_InstanceHandle_t 。
 *
 * @param   handle1 操作数1。
 * @param   handle2 操作数2。
 *
 * @return  0表示相等，1表示handle1 &gt; handle2，-1表示handle1 &lt; handle2。
 */

DCPSDLL DDS_Long DDS_InstanceHandle_t_Compare(const DDS_InstanceHandle_t* handle1, const DDS_InstanceHandle_t* handle2);

/**
 * @brief   表示无效的 DDS_InstanceHandle_t 。 
 *
 * @ingroup CoreVar
 */
DCPSDLL extern const DDS_InstanceHandle_t DDS_HANDLE_NIL_NATIVE;

/**
 * @typedef DDS_InstanceHandle_t DDS_KeyHash_t
 * 
 * @ingroup CoreBaseStruct
 *
 * @brief   DDS_KeyHash_t 作为当 DDS_InstanceHandle_t 作为数据实例的唯一标识时的别名。
 *
 * @note    用户不会显式的使用该结构体。
 */

typedef DDS_InstanceHandle_t DDS_KeyHash_t;

/**
 * @struct DDS_InstanceHandleSeq 
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   声明 DDS_InstanceHandle_t 的序列类型，参见 #DDS_USER_SEQUENCE_CPP 。
 */

DDS_SEQUENCE_CPP(DDS_InstanceHandleSeq, DDS_InstanceHandle_t);

#ifdef __cplusplus
}
#endif

#endif /* DDS_InstanceHandle_t_h__*/
