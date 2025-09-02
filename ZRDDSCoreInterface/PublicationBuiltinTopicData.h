/**
 * @file:       PublicationBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PublicationBuiltinTopicData_h__
#define PublicationBuiltinTopicData_h__

#include "BuiltinTopicKey_t.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "LatencyBudgetQosPolicy.h"
#include "LivelinessQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "UserDataQosPolicy.h"
#include "OwnershipQosPolicy.h"
#include "OwnershipStrengthQosPolicy.h"
#include "DestinationOrderQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PropertyList.h"
#include "PartitionQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "ZRSequence.h"
#include "TypeObject.h"
#ifdef _ZRDDSSECURITY
#include "DataTags.h"
#include "DDSBuiltinSecurityCommon.h"
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_PublicationBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   该结构体用于存储远程数据写者的信息。
 */

typedef struct DDS_PublicationBuiltinTopicData
{
    /** @brief   数据写者的唯一标识。 */
    DDS_BuiltinTopicKey_t key;
    /** @brief   数据写者所属域参与者的唯一标识。 */
    DDS_BuiltinTopicKey_t participant_key;
    /** @brief   数据写者关联的主题的主题名称。 */
    DDS_Char* topic_name;
    /** @brief   数据写者关联的主题关联的数据类型的名称。 */
    DDS_Char* type_name;
    /** @brief   数据写者的持久化配置。 */
    DDS_DurabilityQosPolicy durability;
    /** @brief   数据写者的持久化资源配置。 */
    DDS_DurabilityServiceQosPolicy durability_service;
    /** @brief   数据写者的属性列表。 */
    DDS_PropertyList property_list;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief   数据写者的截止时间配置。 */
    DDS_DeadlineQosPolicy deadline;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
    /** @brief   数据写者的延时优化配置。 */
    DDS_LatencyBudgetQosPolicy latency_budget;
#endif /* _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS */
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /** @brief   数据写者的存活性配置。 */
    DDS_LivelinessQosPolicy liveliness;
#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */
    /** @brief   数据写者可靠性的配置。 */
    DDS_ReliabilityQosPolicy reliability;
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
    /** @brief   数据写者数据有效期的配置。 */
    DDS_LifespanQosPolicy lifespan;
#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   数据写者的携带数据配置。 */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
    /** @brief   数据写者数据实例所有权配置。 */
    DDS_OwnershipQosPolicy ownership;
    /** @brief   数据写者数据实例所有权权值配置。 */
    DDS_OwnershipStrengthQosPolicy ownership_strength;
#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
    /** @brief   数据写者的样本顺序配置。 */
    DDS_DestinationOrderQosPolicy destination_order;
#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief   数据写者所属订阅者的数据表现配置。 */
    DDS_PresentationQosPolicy presention;
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief   数据写者所属发布者的分区配置。 */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
    /** @brief   数据写者关联的主题的携带数据配置。 */
    DDS_TopicDataQosPolicy topic_data;
#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief   数据写者所属订阅者的携带数据配置。 */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /** @brief   数据写者关联主题关联的数据类型的描述。 */
    TypeObject* type_object;
#endif
#ifdef _ZRDDSSECURITY
    /** @brief The data tags */
    DDS_DataTags data_tags;
    /** @brief 实体安全相关信息 */
    DDS_EndpointSecurityInfo security_info;
    /** @brief 发现过程是否需要被保护 */
    DDS_Boolean protected_discovery;
#endif /* _ZRDDSSECURITY */
}DDS_PublicationBuiltinTopicData;

DCPSDLL void DDS_PublicationBuiltinTopicDataInitial(DDS_PublicationBuiltinTopicData* self);

DCPSDLL void DDS_PublicationBuiltinTopicDataDestroy(DDS_PublicationBuiltinTopicData* self);

DCPSDLL DDS_Long DDS_PublicationBuiltinTopicDataCopy(DDS_PublicationBuiltinTopicData* dst, 
    const DDS_PublicationBuiltinTopicData* src);

/* 定义sequence结构*/
DDS_SEQUENCE_CPP(DDS_PublicationBuiltinTopicDataSeq, DDS_PublicationBuiltinTopicData);

#ifdef _ZRDDSSECURITY
typedef DDS_PublicationBuiltinTopicData DDS_PublicationBuiltinTopicDataSecure;
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
}
#endif

#endif /* PublicationBuiltinTopicData_h__*/
