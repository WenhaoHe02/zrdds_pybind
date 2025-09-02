/**
 * @file:       TopicBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TopicBuiltinTopicData_h__
#define TopicBuiltinTopicData_h__

#include "BuiltinTopicKey_t.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "TransportPriorityQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PartitionQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "ZRSequence.h"
#include "ContentFilterProperty_t.h"
#include "TypeObject.h"
#include "ResourceLimitsQosPolicy.h"

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_TopicBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   该结构体用于存储发现的远程主题信息。
 */

typedef struct DDS_TopicBuiltinTopicData
{
    /** @brief   主题的唯一标识。 */
    DDS_BuiltinTopicKey_t key;
    /** @brief   主题名称。 */
    DDS_Char* topic_name;
    /** @brief   主题关联的数据类型的名称。 */
    DDS_Char* type_name;
    /** @brief   持久化配置。 */
    DDS_DurabilityQosPolicy durability;
    /** @brief   持久化历史数据配置。 */
    DDS_DurabilityServiceQosPolicy durability_service;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   主题的截止时间配置。 */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   主题的延时优化配置。 */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   主题的存活性配置。 */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
    /** @brief   主题关联的传输优先级配置。 */
    DDS_TransportPriorityQosPolicy transport_priority;
#endif /*_ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief   主题数据有效期的配置。 */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   主题数据实例所有权配置。 */
    DDS_OwnershipQosPolicy ownership;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   主题的样本顺序配置。 */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   主题关联的主题的携带数据配置。 */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
    /** @brief   历史数据队列配置。 */
    DDS_HistoryQosPolicy history;
    /** @brief   资源限制配置。 */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /** @brief   主题关联主题关联的数据类型的描述。 */
    TypeObject* type_object;
#endif /* _ZRDDS_INCLUDE_TYPE_OBJECT */
}DDS_TopicBuiltinTopicData;

DCPSDLL extern void DDS_TopicBuiltinTopicDataInitial(
    DDS_TopicBuiltinTopicData* self);

DCPSDLL extern void DDS_TopicBuiltinTopicDataDestroy(
    DDS_TopicBuiltinTopicData* self);

DCPSDLL extern DDS_Long DDS_TopicBuiltinTopicDataCopy(
    DDS_TopicBuiltinTopicData* dst, 
    const DDS_TopicBuiltinTopicData* src);

/* 定义sequence结构*/
DDS_SEQUENCE_CPP(DDS_TopicBuiltinTopicDataSeq, DDS_TopicBuiltinTopicData);

#ifdef __cplusplus
}
#endif
#else
typedef struct DDS_TopicBuiltinTopicData DDS_TopicBuiltinTopicData;
#endif /* _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA */

#endif /* TopicBuiltinTopicData_h__ */
