/**
 * @file:       SubscriberQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SubscriberQos_h__
#define SubscriberQos_h__

#include "PresentationQosPolicy.h"
#include "PartitionQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "EntityFactoryQosPolicy.h"

/**
 * @struct DDS_SubscriberQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义订阅者的QoS配置。
 */

typedef struct DDS_SubscriberQos
{
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief   订阅者的数据展示配置。 */
    DDS_PresentationQosPolicy presentation;
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief   订阅者的分区配置。 */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief   订阅者的组携带数据配置。 */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
    /** @brief   订阅者的实体工厂配置。 */
    DDS_EntityFactoryQosPolicy entity_factory;
}DDS_SubscriberQos;

#endif /* SubscriberQos_h__*/
