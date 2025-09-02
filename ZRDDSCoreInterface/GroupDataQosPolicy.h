/**
 * @file:       GroupDataQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef GroupDataQosPolicy_h__
#define GroupDataQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS

/**
 * @struct DDS_GroupDataQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   组携带数据。
 *
 * @details 该QoS作用在发布者以及订阅者实体上，当用户创建发布者或者订阅者时，该QoS的值将会被填充到代表数据写者以及数据读者的内置数据中，
 *          并通过内置发现协议发布到DDS网络中 DDS_SubscriptionBuiltinTopicData::group_data 以及 
 *          DDS_PublicationBuiltinTopicData::group_data 。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #value | 长度为0的字节序列 | 无 | 无 | 无 | 可变
 *          
 * @see DDS_UserDataQosPolicy DDS_TopicDataQosPolicy 。
 */

typedef struct DDS_GroupDataQosPolicy
{
    /** @brief   字节序列表示用户需要携带的内容。 */
    DDS_CharSeq value;
}DDS_GroupDataQosPolicy;

#endif /* _ZRDDS_INCLUDE_GROUP_DATA_QOS */

#endif /* GroupDataQosPolicy_h__*/
