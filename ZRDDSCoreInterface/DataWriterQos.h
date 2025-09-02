/**
 * @file:       DataWriterQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriterQos_h__
#define DataWriterQos_h__

#include "OsResource.h"
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
#include "UserDataQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "OwnershipStrengthQosPolicy.h"
#include "WriterDataLifecycleQosPolicy.h"
#include "BatchQosPolicy.h"
#include "PublishModeQosPolicy.h"
#include "DataWriterProtocolQosPolicy.h"
#include "DataWriterResourceLimitsQosPolicy.h"
#include "DataWriterMessageModeQosPolicy.h"
#include "ZRDDSCommon.h"
#include "TransportConfigQosPolicy.h"
#include "PropertyQosPolicy.h"

/**
 * @struct DDS_DataWriterQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief 定义数据写者的QoS
 */
typedef struct DDS_DataWriterQos
{
    /** @brief 持久化配置。 */
    DDS_DurabilityQosPolicy durability;
    /** @brief 持久化历史数据配置。 */
    DDS_DurabilityServiceQosPolicy durability_service;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief 截止时间配置。 */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief 延时优化配置。 */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief 如何检测匹配数据写者的存活性配置。 */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    /** @brief 可靠性配置。 */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief 多数据写者的数据样本顺序配置。 */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
    /** @brief 存储队列配置。 */
    DDS_HistoryQosPolicy history;
    /** @brief 资源使用限制配置。 */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
    /** @brief 传输优先级配置，暂未使用。 */
    DDS_TransportPriorityQosPolicy transport_priority;
#endif /* _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief 数据有效期配置。 */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief 携带数据配置。 */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief 数据实例所有权配置。 */
    DDS_OwnershipQosPolicy ownership;
    /** @brief 所有权值配置。 */
    DDS_OwnershipStrengthQosPolicy ownership_strength;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
    /** @brief 数据写者样本声明周期配置。 */
    DDS_WriterDataLifecycleQosPolicy writer_data_lifecycle;
    
    /* 扩展QoS */
#ifdef _ZRDDS_INCLUDE_BATCH
    /** @brief 批量发送配置。 */
    DDS_BatchQosPolicy batch;
#endif /* _ZRDDS_INCLUDE_BATCH */
    /** @brief 数据写者发布模式配置。 */
    DDS_PublishModeQosPolicy publish_mode;
    /** @brief 数据写者中与RTPS协议相关的行为配置。 */
    DDS_DataWriterProtocolQosPolicy protocol;
    /** @brief 数据写者资源限制QoS配置。 */
    DDS_DataWriterResourceLimitsQosPolicy writer_resource_limits;
    /** @brief 提供控制DataWriter消息处理的功能。 */
    DDS_DataWriterMessageModeQosPolicy message_mode;
    /** @brief   DataWriter使用的独立于Participant的地址监听列表。 */
    DDS_TransportConfigQosPolicy receive_addresses;
    /** @brief   该实体的属性列表。 */
    DDS_PropertyQosPolicy property;
#ifdef _ZRDDS_INCLUDE_BIND_SENDADDR
    /** @brief   DataWriter绑定的本地地址，只能有一个地址，端口号为65536表示系统自选端口 */
    DDS_TransportConfigQosPolicy send_addresses;
#endif /*_ZRDDS_INCLUDE_BIND_SENDADDR*/
}DDS_DataWriterQos;

#endif /* DataWriterQos_h__*/
