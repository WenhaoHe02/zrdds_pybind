/**
 * @file:       UserDataQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef UserDataQosPolicy_h__
#define UserDataQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS

/**
 * @struct DDS_UserDataQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   实体携带数据。
 *
 * @details 该QoS为应用提供了一个能够存储额外的域参与组合、数据写者或数据读者信息的空间。
 *          这个信息在发现阶段在应用间使用内置的主题传递。如何使用这个信息由用户决定， 
 *          ZRDDS除了存储和将其发送到其他应用外不会做任何操作，一般用于应用间的识别、鉴定、授权和加密。 
 *          当用户创建以上实体时，该QoS的值将会被填充到代表域参与者、数据写者以及数据读者的内置数据中，
 *          并通过内置发现协议发布到DDS网络中 DDS_ParticipantBuiltinTopicData::user_data 
 *          DDS_SubscriptionBuiltinTopicData::user_data 以及 DDS_PublicationBuiltinTopicData::user_data 。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #value | 长度为0的字节序列 | 无 | 无 | 无 | 可变
 *
 * @see DDS_TopicDataQosPolicy DDS_GroupDataQosPolicy 。
 */

typedef struct DDS_UserDataQosPolicy
{
    /** @brief   字节序列表示用户需要携带的内容。 */
    DDS_CharSeq value;
}DDS_UserDataQosPolicy;

#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */

#endif /* UserDataQosPolicy_h__*/
