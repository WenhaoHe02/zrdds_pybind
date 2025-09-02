/**
 * @file:       ReliabilityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ReliabilityQosPolicy_h__
#define ReliabilityQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @typedef enum DDS_ReliabilityQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief 可靠性配置类型。
 */
typedef enum DDS_ReliabilityQosPolicyKind
{
    /** @brief 尽力而为配置。 @ingroup CoreQosStruct */
    DDS_BEST_EFFORT_RELIABILITY_QOS = 1,
    /** @brief 可靠配置。 @ingroup CoreQosStruct */
    DDS_RELIABLE_RELIABILITY_QOS = 2
}DDS_ReliabilityQosPolicyKind;

/**
 * @struct DDS_ReliabilityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 可靠性配置。
 *
 * @details 当使用DDS进行数据传输时，可能因各种原因造成数据丢失（如非可靠网络传输等），DDS可以通过可靠性配置提升数据传输可靠性。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | 数据写者默认为 #DDS_RELIABLE_RELIABILITY_QOS 数据读者默认为 #DDS_BEST_EFFORT_RELIABILITY_QOS | 数据写者.#kind >= 数据读者.#kind  | 无 | 无 | 不可变
 *          #max_blocking_time | Duration_t{ 0, 100000000 } | 无 | 无 | 无 | 不可变
 *
 */
typedef struct DDS_ReliabilityQosPolicy
{
    /** @brief 可靠性配置类型。 */
    DDS_ReliabilityQosPolicyKind kind;
    /** @brief 可靠通信下，数据写者因资源不足而导致阻塞时的最长阻塞时长。 */
    DDS_Duration_t max_blocking_time;
}DDS_ReliabilityQosPolicy;

#endif /* ReliabilityQosPolicy_h__*/
