/**
 * @file:       QosPolicyId_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QosPolicyId_t_h__
#define QosPolicyId_t_h__

#include "ZRDDSCommon.h"

/**
 * @enum DDS_QosPolicyId_t
 *
 * @ingroup CoreQosStruct
 *
 * @brief   枚举值标识QoS的类型。
 */

typedef enum DDS_QosPolicyId_t
{
    /** @brief  无效的标识。 @ingroup CoreQosStruct */
    DDS_INVALID_QOS_POLICY_ID = 0,
    /** @brief  标识 DDS_UserDataQosPolicy 。 @ingroup CoreQosStruct */
    DDS_USERDATA_QOS_POLICY_ID = 1,
    /** @brief  标识 DDS_DurabilityQosPolicy 。 @ingroup CoreQosStruct */
    DDS_DURABILITY_QOS_POLICY_ID = 2,
    /** @brief  标识 DDS_PresentationQosPolicy 。 @ingroup CoreQosStruct */
    DDS_PRESENTATION_QOS_POLICY_ID = 3,
    /** @brief  标识 DDS_DeadlineQosPolicy 。 @ingroup CoreQosStruct */
    DDS_DEADLINE_QOS_POLICY_ID = 4,
    /** @brief  标识 DDS_LatencyBudgetQosPolicy 。 @ingroup CoreQosStruct */
    DDS_LATENCYBUDGET_QOS_POLICY_ID = 5,
    /** @brief  标识 DDS_OwnershipQosPolicy 。 @ingroup CoreQosStruct */
    DDS_OWNERSHIP_QOS_POLICY_ID = 6,
    /** @brief  标识 DDS_OwnershipStrengthQosPolicy 。 @ingroup CoreQosStruct */
    DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID = 7,
    /** @brief  标识 DDS_LivelinessQosPolicy 。 @ingroup CoreQosStruct */
    DDS_LIVELINESS_QOS_POLICY_ID = 8,
    /** @brief  标识 DDS_TimeBasedFilterQosPolicy 。 @ingroup CoreQosStruct */
    DDS_TIMEBASEDFILTER_QOS_POLICY_ID = 9,
    /** @brief  标识 DDS_PartitionQosPolicy 。 @ingroup CoreQosStruct */
    DDS_PARTITION_QOS_POLICY_ID = 10,
    /** @brief  标识 DDS_ReliabilityQosPolicy 。 @ingroup CoreQosStruct */
    DDS_RELIABILITY_QOS_POLICY_ID = 11,
    /** @brief  标识 DDS_DestinationOrderQosPolicy 。 @ingroup CoreQosStruct */
    DDS_DESTINATIONORDER_QOS_POLICY_ID = 12,
    /** @brief  标识 DDS_HistoryQosPolicy 。 @ingroup CoreQosStruct */
    DDS_HISTORY_QOS_POLICY_ID = 13,
    /** @brief  标识 DDS_ResourceLimitsQosPolicy 。 @ingroup CoreQosStruct */
    DDS_RESOURCELIMITS_QOS_POLICY_ID = 14,
    /** @brief  标识 DDS_EntityFactoryQosPolicy 。 @ingroup CoreQosStruct */
    DDS_ENTITYFACTORY_QOS_POLICY_ID = 15,
    /** @brief  标识 DDS_WriterDataLifeCycleQosPolicy 。 @ingroup CoreQosStruct */
    DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID = 16,
    /** @brief  标识 DDS_ReaderDataLifeCycleQosPolicy 。 @ingroup CoreQosStruct */
    DDS_READERDATALIFECYCLE_QOS_POLICY_ID = 17,
    /** @brief  标识 DDS_TopicDataQosPolicy 。 @ingroup CoreQosStruct */
    DDS_TOPICDATA_QOS_POLICY_ID = 18,
    /** @brief  标识 DDS_GroupDataQosPolicy 。 @ingroup CoreQosStruct */
    DDS_GROUPDATA_QOS_POLICY_ID = 19,
    /** @brief  标识 DDS_TransportPriorityQosPolicy 。 @ingroup CoreQosStruct */
    DDS_TRANSPORTPRIORITY_QOS_POLICY_ID = 20,
    /** @brief  标识 DDS_LifespanQosPolicy 。 @ingroup CoreQosStruct */
    DDS_LIFESPAN_QOS_POLICY_ID = 21,
    /** @brief  标识 DDS_DurabilityServiceQosPolicy 。 @ingroup CoreQosStruct */
    DDS_DURABILITYSERVICE_QOS_POLICY_ID = 22,
    /** @brief  标识 DDS_RepresentationQosPolicy 。 @ingroup CoreQosStruct */
    DDS_DATA_REPRESENTATION_QOS_POLICY_ID = 23,
    /** @brief  保留类型。 @ingroup CoreQosStruct */
    DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID = 24,
    /** @brief  保留类型。 @ingroup CoreQosStruct */
    DDS_NETWORKCONFIG_QOS_POLICY_ID = 50,
    /** @brief  保留类型。 @ingroup CoreQosStruct */
    DDS_DISCOVERYCONFIG_QOS_POLICY_ID = 51
}DDS_QosPolicyId_t;

#endif /* QosPolicyId_t_h__*/
