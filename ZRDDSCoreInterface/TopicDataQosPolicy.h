/**
 * @file:       TopicDataQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TopicDataQosPolicy_h__
#define TopicDataQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS

/**
 * @struct DDS_TopicDataQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   主题携带数据配置。
 *          
 * @details 该QoS作用在主题实体上，当用户创建数据读者或者数据写者时，该QoS的值将会被填充到代表数据写者以及数据读者的内置数据中，
 *          并通过内置发现协议发布到DDS网络中 DDS_SubscriptionBuiltinTopicData::topic_data 以及
 *          DDS_PublicationBuiltinTopicData::topic_data 。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #value | 长度为0的字节序列 | 无 | 无 | 无 | 可变
 *
 * @see DDS_UserDataQosPolicy DDS_GroupDataQosPolicy 。
 */

typedef struct DDS_TopicDataQosPolicy
{
    /** @brief   字节序列表示用户需要携带的内容。 */
    DDS_CharSeq value;
}DDS_TopicDataQosPolicy;

#endif /* _ZRDDS_INCLUDE_TOPIC_DATA_QOS */

#endif /* TopicDataQosPolicy_h__*/
