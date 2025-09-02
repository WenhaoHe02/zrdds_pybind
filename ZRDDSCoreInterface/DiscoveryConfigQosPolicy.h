/**
 * @file:       DiscoveryConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DiscoveryConfigQosPolicy_h__
#define DiscoveryConfigQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_DiscoveryConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   配置SPDP协议。
 *
 * @details 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #participant_liveliness_assert_period | DDS_Duration_t(30, 0) | 无 | 不能设置为 ::INFINITE_DURATION ::ZERO_DURATION ::INVALID_DURATION | #participant_liveliness_assert_period < #participant_liveliness_lease_duration | 不可变 
 *          #participant_liveliness_lease_duration | DDS_Duration_t(100, 0) | 无 | 不能设置为 ::ZERO_DURATION ::INVALID_DURATION |  #participant_liveliness_assert_period < #participant_liveliness_lease_duration | 不可变 
 */

typedef struct DDS_DiscoveryConfigQosPolicy
{
    /** @brief   ZRDDS以该时间为周期性向DDS组播中发送自身域参与者信息(Data(p)) */
    DDS_Duration_t participant_liveliness_assert_period;
    /** @brief   ZRDDS告知其他域参与者在该时间内未收到自身的Data(p)数据则认为本域参与者失去活性。*/
    DDS_Duration_t participant_liveliness_lease_duration;
}DDS_DiscoveryConfigQosPolicy;

#endif /* DiscoveryConfigQosPolicy_h__*/
