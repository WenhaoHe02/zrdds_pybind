/**
 * @file:       TimeBasedFilterQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TimeBasedFilterQosPolicy_h__
#define TimeBasedFilterQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS

/**
 * @struct DDS_TimeBasedFilterQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   基于时间过滤配置。
 *
 * @details 使得数据读者在 #minimum_separation 时间内最多存储并通知用户同一个数据实例一个数据样本，注意作用域为数据实例。
 *          该过滤是在订阅端完成，被过滤的数据通过网络等方式从发布端传输到订阅端，该过滤动作在检查 
 *          DDS_ResourceLimitQosPolicy::max_samples 之后，检查其他资源限制之前，且不过滤状态样本。
 *          应用场景：
 *          - 异构环境中发布端远远大于订阅端速度速度时， 订阅端利用该QoS来过滤数据以匹配自身的处理速度。
 *          - 不同的数据读者利用该QoS来匹配自身的处理速度。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #minimum_separation | #ZERO_DURATION | 无 | #minimum_separation >= #ZERO_DURATION | DDS_DeadlineQosPolicy::period >= #minimum_separation | 可变
 */

typedef struct DDS_TimeBasedFilterQosPolicy
{
    /** @brief   指明同一数据实例下数据样本的最小时间间隔。 */
    DDS_Duration_t minimum_separation;
}DDS_TimeBasedFilterQosPolicy;

#endif /* _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS */

#endif /* TimeBasedFilterQosPolicy_h__*/
