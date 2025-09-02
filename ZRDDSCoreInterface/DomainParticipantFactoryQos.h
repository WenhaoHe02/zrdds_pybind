/**
 * @file:       DomainParticipantFactoryQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DomainParticipantFactoryQos_h__
#define DomainParticipantFactoryQos_h__

#include "OsResource.h"
#include "EntityFactoryQosPolicy.h"
#include "DDSLogQosPolicy.h"
#include "RapidIOConfigQosPolicy.h"
#include "QosProfileQosPolicy.h"
#ifdef _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE
#include "PropertyQosPolicy.h"
#endif // _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE

/**
 * @struct DDS_DomainParticipantFactoryQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义域参与者工厂的QoS。
 */

typedef struct DDS_DomainParticipantFactoryQos
{
    /** @brief   实体工厂配置。 */
    DDS_EntityFactoryQosPolicy entity_factory;
    /** @brief   日志系统配置。 */
    DDS_LogQosPolicy dds_log;
    /**   
     * @brief   超过该值使用DMA代替memcpy函数拷贝存储空间。
     *
     * @note    仅在华睿处理平台上使用。
     */
    DDS_ULong min_dma_copy_size;
#ifdef _ZRDDS_RIO
    /** @brief   RapidIO配置。 */
    DDS_RapidIOConfigQosPolicy rapidio_config;
#endif /* _ZRDDS_RIO */
#ifdef _ZRXMLINTERFACE
#ifdef _ZRXMLQOSINTERFACE
    /** @brief   QoS配置文件路径配置。 */
    DDS_QosProfileQosPolicy qos_profile;
#endif // _ZRXMLQOSINTERFACE
#endif /* _ZRXMLINTERFACE */
#ifdef _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE
    DDS_PropertyQosPolicy property;
#endif /* _ZRDDS_INCLUDE_ENABLE_SYSTEM_CONFIGURE */
}DDS_DomainParticipantFactoryQos;

#endif /* DomainParticipantFactoryQos_h__*/
