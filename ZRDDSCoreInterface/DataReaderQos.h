/**
 * @file:       DataReaderQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataReaderQos_h__
#define DataReaderQos_h__

#include "OsResource.h"
#include "DurabilityQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "HistoryQosPolicy.h"
#include "ResourceLimitsQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "ReaderDataLifecycleQosPolicy.h"
#include "TransportConfigQosPolicy.h"
#include "TypeConsistencyEnforcementQosPolicy.h"
#include "PropertyQosPolicy.h"
#include "QualityEvaluationQosPolicy.h"

/**
 * @struct DDS_DataReaderQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义数据读者的QoS配置。
 */

typedef struct DDS_DataReaderQos
{
    /** @brief   持久化配置。 */
    DDS_DurabilityQosPolicy durability;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   截止时间配置。 */
    DDS_DeadlineQosPolicy deadline;
#endif //_ZRDDS_INCLUDE_DEADLINE_QOS
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   延时优化配置。 */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif //_ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   如何检测匹配数据写者的存活性配置。 */
    DDS_LivelinessQosPolicy liveliness;
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   可靠性配置。 */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   多数据写者的数据样本顺序配置。 */
    DDS_DestinationOrderQosPolicy destination_order;
#endif //_ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   存储队列配置。 */
    DDS_HistoryQosPolicy history;
    /** @brief   资源使用限制配置。 */
    DDS_ResourceLimitsQosPolicy resource_limits;
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   携带数据配置。 */
    DDS_UserDataQosPolicy user_data;
#endif //_ZRDDS_INCLUDE_USER_DATA_QOS
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   数据实例所有权配置。 */
    DDS_OwnershipQosPolicy ownership;
#endif //_ZRDDS_INCLUDE_OWNERSHIP_QOS
#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
    /** @brief   基于事件过滤配置。 */
    DDS_TimeBasedFilterQosPolicy time_based_filter;
#endif //_ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
    /** @brief   数据读者样本声明周期配置。 */
    DDS_ReaderDataLifecycleQosPolicy reader_data_lifecycle;
    /** @brief   类型兼容配置。 */
    DDS_TypeConsistencyEnforcementQosPolicy type_compatibility;
    /** @brief   底层传输协议配置。 */
    DDS_TransportConfigQosPolicy receive_addresses;
    /** @brief   该实体的属性列表。 */
    DDS_PropertyQosPolicy property;
#ifdef _ZRDDS_INCLUDE_BREAKPOINT_RESUME
    /** @brief   断点续传，与消费模式的record_data接口配合使用 （true为允许续传）*/
    ZR_BOOLEAN breakpoint_resume;
#endif //_ZRDDS_INCLUDE_BREAKPOINT_RESUME
#ifdef _ZRDDS_INCLUDE_QUALITY_EVALUATION
    /** @brief   通信质量评估配置。 */
    DDS_QualityEvaluationQosPolicy quality_evaluation;
#endif //_ZRDDS_INCLUDE_QUALITY_EVALUATION
}DDS_DataReaderQos;

#endif /* DataReaderQos_h__*/
