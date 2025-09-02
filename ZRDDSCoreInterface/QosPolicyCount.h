/**
 * @file:       QosPolicyCount.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QosPolicyCount_h__
#define QosPolicyCount_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "QosPolicyId_t.h"
#include "ZRSequence.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_QosPolicyCount
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   QoS类型次数统计，用于 DDS_OfferedIncompatibleQosStatus 以及 
 *          DDS_RequestedIncompatibleQosStatus 。
 */

typedef struct DDS_QosPolicyCount
{
    /** @brief   枚举类型表示QoS类型。 */
    DDS_QosPolicyId_t last_policy_id;
    /** @brief   #last_policy_id 指定类型的次数。 */
    DDS_Long count;
}DDS_QosPolicyCount;


/**
 * @struct DDS_QosPolicyCountSeq
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   声明内置数据类型 DDS_QosPolicyCount 的序列。
 */
DDS_SEQUENCE_CPP(DDS_QosPolicyCountSeq, DDS_QosPolicyCount);

#ifdef __cplusplus
}
#endif

#endif /* QosPolicyCount_h__*/
