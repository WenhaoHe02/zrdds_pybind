/**
 * @file:       TopicQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TopicQos_h__
#define TopicQos_h__

#include "TopicDataQosPolicy.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "HistoryQosPolicy.h"
#include "ResourceLimitsQosPolicy.h"
#include "TransportPriorityQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "OwnershipQosPolicy.h"

/**
 * @struct DDS_TopicQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   主题实体的QoS配置。
 *
 * @details 主题实体的QoS为数据写者以及数据读者的QoS配置的集合+ #topic_data 配置，主题实体的QoS配置通常在以下两个
 *          情况下使用：
 *          - 用于构造数据写者以及数据读者QoS配置，参见 DDS::Subscriber::copy_from_topic_qos 以及  
 *          - 在构造内置主题数据时，使用 #topic_data 携带主题数据。
 */

typedef struct DDS_TopicQos
{
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   主题携带数据配置。 */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
    DDS_DurabilityQosPolicy durability;
    /** @brief 持久化历史数据配置。 */
    DDS_DurabilityServiceQosPolicy durability_service;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   截止时间配置。 */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   延时优化配置。 */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   如何检测匹配数据写者的存活性配置。 */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   多数据写者的数据样本顺序配置。 */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
    DDS_HistoryQosPolicy history;
    /** @brief   资源使用限制配置。 */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
    /** @brief 传输优先级配置，暂未使用。 */
    DDS_TransportPriorityQosPolicy transport_priority;
#endif /* _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief 数据有效期配置。 */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   数据实例所有权配置。 */
    DDS_OwnershipQosPolicy ownership;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
}DDS_TopicQos;

#endif /* TopicQos_h__*/
