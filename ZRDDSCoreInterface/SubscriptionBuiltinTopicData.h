/**
 * @file:       SubscriptionBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SubscriptionBuiltinTopicData_h__
#define SubscriptionBuiltinTopicData_h__

#include "BuiltinTopicKey_t.h"
#include "DurabilityQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PropertyList.h"
#include "PartitionQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "ZRSequence.h"
#include "ContentFilterProperty_t.h"
#include "TypeObject.h"
#include "TypeConsistencyEnforcementQosPolicy.h"
#ifdef _ZRDDSSECURITY
#include "DataTags.h"
#include "DDSBuiltinSecurityCommon.h"
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_SubscriptionBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   该结构体用于存储远程数据写者的信息。
 */

typedef struct DDS_SubscriptionBuiltinTopicData
{
    /** @brief   数据读者的唯一标识。 */
    DDS_BuiltinTopicKey_t key;
    /** @brief   数据读者所属域参与者的唯一标识。 */
    DDS_BuiltinTopicKey_t participant_key;
    /** @brief   数据读者关联的主题的主题名称。 */
    DDS_Char* topic_name;
    /** @brief   数据读者关联的主题关联的数据类型的名称。 */
    DDS_Char* type_name;
    /** @brief   数据读者的属性列表。 */
    DDS_PropertyList property_list;
#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC
    /** @brief   如果数据读者关联的是基于内容过滤的主题，则该成员表示基于内容过滤相关信息。 */
    DDS_ContentFilterProperty_t content_filter_property;
#endif /* _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC  */
    /** @brief   持久化配置。 */
    DDS_DurabilityQosPolicy durability;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   数据读者的截止时间配置。 */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   数据读者的延时优化配置。 */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   数据读者的存活性配置。 */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   数据读者数据实例所有权配置。 */
    DDS_OwnershipQosPolicy ownership;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   数据读者的样本顺序配置。 */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   数据读者的携带数据配置。 */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
    /** @brief   数据读者的基于事件过滤的配置。 */
    DDS_TimeBasedFilterQosPolicy time_based_filter;
#endif /* _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS */
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief   数据读者所属订阅者的数据表现配置。 */
    DDS_PresentationQosPolicy presention; 
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
    DDS_TypeConsistencyEnforcementQosPolicy type_compatibility;
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief   数据读者所属订阅者的分区配置。 */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   数据读者关联的主题的携带数据配置。 */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief   数据读者所属订阅者的携带数据配置。 */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /** @brief   数据读者关联主题关联的数据类型的描述。 */
    TypeObject* type_object;
#endif /* _ZRDDS_INCLUDE_TYPE_OBJECT */
#ifdef _ZRDDSSECURITY
    /** @brief The data tags */
    DDS_DataTags data_tags;
    /** @brief 实体安全相关信息 */
    DDS_EndpointSecurityInfo security_info;
    /** @brief 发现过程是否需要被保护 */
    DDS_Boolean protected_discovery;
#endif /* _ZRDDSSECURITY */
}DDS_SubscriptionBuiltinTopicData;

DCPSDLL void DDS_SubscriptionBuiltinTopicDataInitial(DDS_SubscriptionBuiltinTopicData* self);

DCPSDLL void DDS_SubscriptionBuiltinTopicDataDestroy(DDS_SubscriptionBuiltinTopicData* self);

DCPSDLL DDS_Long DDS_SubscriptionBuiltinTopicDataCopy(DDS_SubscriptionBuiltinTopicData* dst, const DDS_SubscriptionBuiltinTopicData* src);

/* 定义sequence结构*/
DDS_SEQUENCE_CPP(DDS_SubscriptionBuiltinTopicDataSeq, DDS_SubscriptionBuiltinTopicData);

#ifdef _ZRDDSSECURITY
typedef DDS_SubscriptionBuiltinTopicData DDS_SubscriptionBuiltinTopicDataSecure;
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
}
#endif

#endif /* SubscriptionBuiltinTopicData_h__*/
