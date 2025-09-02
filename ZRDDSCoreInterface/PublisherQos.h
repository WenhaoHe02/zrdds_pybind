/**
 * @file:       PublisherQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PublisherQos_h__
#define PublisherQos_h__

#include "PresentationQosPolicy.h"
#include "PartitionQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "EntityFactoryQosPolicy.h"
#include "AsynchronousPublisherQosPolicy.h"
#include "TransportConfigQosPolicy.h"

/**
 * @struct DDS_PublisherQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief 发布者QoS配置
 */
typedef struct DDS_PublisherQos
{
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /** @brief 数据展示配置。 */
    DDS_PresentationQosPolicy presentation;
#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
    /** @brief 分区QoS配置。 */
    DDS_PartitionQosPolicy partition;
#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */
#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
    /** @brief 组携带数据。 */
    DDS_GroupDataQosPolicy group_data;
#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */
    /** @brief 实体工厂配置。 */
    DDS_EntityFactoryQosPolicy entity_factory;
    /* 扩展QoS */
    /** @brief 配置Publisher是否使用异步发送数据或异步批量发送的QoS。 */
    DDS_AsynchronousPublisherQosPolicy asynchronous_publisher;
#ifdef _ZRDDS_PORT_LIMIT
    /*指定用户发送数据使用的端口和地址*/
    DDS_TransportConfigQosPolicy send_addresses;
    /* 是否使用单端口，直接复用dp的端口和地址 */
    ZR_BOOLEAN single_port;
#endif /*_ZRDDS_PORT_LIMIT*/
}DDS_PublisherQos;

#endif /* PublisherQos_h__*/
