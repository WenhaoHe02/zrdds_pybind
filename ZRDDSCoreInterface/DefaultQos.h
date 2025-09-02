/**
 * @file:       DefaultQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DefaultQos_h__
#define DefaultQos_h__

#include "DomainParticipantFactoryQos.h"
#include "DomainParticipantQos.h"
#include "PublisherQos.h"
#include "SubscriberQos.h"
#include "DataWriterQos.h"
#include "DataReaderQos.h"
#include "TopicQos.h"
#include "ZRDDSCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   特殊的 DDS_DomainParticipantFactoryQos 表示使用ZRDDS默认的QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DomainParticipantFactoryQos DDS_DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_DomainParticipantQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DomainParticipantQos DDS_DOMAINPARTICIPANT_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_PublisherQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_PublisherQos DDS_PUBLISHER_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_SubscriberQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_SubscriberQos DDS_SUBSCRIBER_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_DataWriterQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataWriterQos DDS_DATAWRITER_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_DataReaderQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataReaderQos DDS_DATAREADER_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_TopicQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_TopicQos DDS_TOPIC_QOS_DEFAULT;

/**
 * @brief   特殊的 DDS_DataWriterQos 表示使用数据写者关联主题的QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataWriterQos DDS_DATAWRITER_QOS_USE_TOPIC_QOS;

/**
 * @brief   特殊的 DDS_DataReaderQos 表示使用数据读者关联主题的QoS。
 *
 * @ingroup CoreVar
 */

DCPSDLL extern DDS_DataReaderQos DDS_DATAREADER_QOS_USE_TOPIC_QOS;

/**
 * @fn  DCPSDLL void DDS_DefaultDomainParticipantFactoryQosInitial(DDS_DomainParticipantFactoryQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_DomainParticipantFactoryQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_DomainParticipantFactoryQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DefaultDomainParticipantFactoryQosInitial(DDS_DomainParticipantFactoryQos* self);

/**
 * @fn  DCPSDLL DDS_Long DDS_DefaultDomainParticipantQosInitial(DDS_DomainParticipantQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_DomainParticipantQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_DomainParticipantQos的指针。
 *
 * @param [in,out]  self    指明目标。
 *
 * @return  0表示初始化成功，否则表示初始化失败，原因可能为内存空间不足。
 */

DCPSDLL DDS_Long DDS_DefaultDomainParticipantQosInitial(DDS_DomainParticipantQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultPublisherQosInitial(DDS_PublisherQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_PublisherQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_PublisherQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DefaultPublisherQosInitial(DDS_PublisherQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultSubscriberQosInitial(DDS_SubscriberQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_PublisherQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_PublisherQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DefaultSubscriberQosInitial(DDS_SubscriberQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultDataWriterQosInitial(DDS_DataWriterQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_PublisherQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_PublisherQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DefaultDataWriterQosInitial(DDS_DataWriterQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultDataReaderQosInitial(DDS_DataReaderQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_PublisherQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_PublisherQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DefaultDataReaderQosInitial(DDS_DataReaderQos* self);

/**
 * @fn  DCPSDLL void DDS_DefaultTopicQosInitial(DDS_TopicQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化指定 DDS_PublisherQos 为DDS默认的值。
 *
 * @pre     self为有效的DDS_PublisherQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DefaultTopicQosInitial(DDS_TopicQos* self);

/**
 * @fn  DCPSDLL void DDS_DomainParticipantFactoryQosDestroy(DDS_DomainParticipantFactoryQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_DomainParticipantFactoryQos 的空间。
 *
 * @pre     self为有效的DDS_DomainParticipantFactoryQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DomainParticipantFactoryQosDestroy(DDS_DomainParticipantFactoryQos* self);

/**
 * @fn  DCPSDLL void DDS_DomainParticipantQosDestroy(DDS_DomainParticipantQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_DomainParticipantQos 的空间。
 *
 * @pre     self为有效的DDS_DomainParticipantQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DomainParticipantQosDestroy(DDS_DomainParticipantQos* self);

/**
 * @fn  DCPSDLL void DDS_PublisherQosDestroy(DDS_PublisherQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_PublisherQos 的空间。
 *
 * @pre     self为有效的DDS_PublisherQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_PublisherQosDestroy(DDS_PublisherQos* self);

/**
 * @fn  DCPSDLL void DDS_SubscriberQosDestroy(DDS_SubscriberQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_SubscriberQos 的空间。
 *
 * @pre     self为有效的DDS_SubscriberQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_SubscriberQosDestroy(DDS_SubscriberQos* self);

/**
 * @fn  DCPSDLL void DDS_DataWriterQosDestroy(DDS_DataWriterQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_DataWriterQos 的空间。
 *
 * @pre     self为有效的DDS_DataWriterQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DataWriterQosDestroy(DDS_DataWriterQos* self);

/**
 * @fn  DCPSDLL void DDS_DataReaderQosDestroy(DDS_DataReaderQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_DataReaderQos 的空间。
 *
 * @pre     self为有效的DDS_DataReaderQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_DataReaderQosDestroy(DDS_DataReaderQos* self);

/**
 * @fn  DCPSDLL void DDS_TopicQosDestroy(DDS_TopicQos* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   释放 DDS_TopicQos 的空间。
 *
 * @pre     self为有效的DDS_TopicQos的指针。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_TopicQosDestroy(DDS_TopicQos* self);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DomainParticipantFactoryQosAssign( DDS_DomainParticipantFactoryQos* self, const DDS_DomainParticipantFactoryQos* right);
 *
 * @brief   域参与者工厂QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN DomainParticipantFactoryQosAssign(DDS_DomainParticipantFactoryQos* self, const DDS_DomainParticipantFactoryQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DomainParticipantQosAssign(DDS_DomainParticipantQos* self, const DDS_DomainParticipantQos* right);
 *
 * @brief   域参与者QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN DomainParticipantQosAssign(DDS_DomainParticipantQos* self, const DDS_DomainParticipantQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN PublisherQosAssign(DDS_PublisherQos* self, const DDS_PublisherQos* right);
 *
 * @brief   发布者QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN PublisherQosAssign(DDS_PublisherQos* self, const DDS_PublisherQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN SubscriberQosAssign(DDS_SubscriberQos* self, const DDS_SubscriberQos* right);
 *
 * @brief   订阅者QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN SubscriberQosAssign(DDS_SubscriberQos* self, const DDS_SubscriberQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN TopicQosAssign(DDS_TopicQos* self, const DDS_TopicQos* right);
 *
 * @brief   主题QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN TopicQosAssign(DDS_TopicQos* self, const DDS_TopicQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DataWriterQosAssign(DDS_DataWriterQos* self, const DDS_DataWriterQos* right);
 *
 * @brief   数据写者QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN DataWriterQosAssign(DDS_DataWriterQos* self, const DDS_DataWriterQos* right);

/**
 * @fn  DCPSDLL ZR_BOOLEAN DataReaderQosAssign(DDS_DataReaderQos* self, const DDS_DataReaderQos* right);
 *
 * @brief   数据读者QoS赋值函数。
 *
 * @param [in,out]  self    赋值目的端。
 * @param   right           源端。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN DataReaderQosAssign(DDS_DataReaderQos* self, const DDS_DataReaderQos* right);

#ifdef __cplusplus
}
#endif

#endif /* DefaultQos_h__*/
