/**
 * @file:       LifespanQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef LifespanQosPolicy_h__
#define LifespanQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS

/**
 * @struct DDS_LifespanQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据有效期配置。
 *
 * @details 该QoS策略用于数据写者指明自身发布的数据的有效期，超过该有效期的数据样本将从数据读者历史数据队列中移除。
 *          过期时间 = #duration + 数据样本的源时间戳（由底层获取系统时间或者由 DataWriter::write_w_timestamp 提供）。
 *          使用该QoS的发布端以及接收端要求时钟有效地同步。如果未同步并且底层可以检测到，数据读者使用接收到的时间戳来代替源时间戳来计算过期时间。
 *          该Qos可以用于控制数据读者样本存储队列中存储的数据数量。尽管 DDS_HistoryQosPolicy::kind == 
 *          #DDS_KEEP_ALL_HISTORY_QOS ， 由于该QoS的限制超过有效期的数据还是会被清理干净，
 *          即数据读者底层仅存储对象数据写者最近 #duration 时间的数据样本。
 *          该QoS在数据写者使能后可变，改变之后的有效期仅适用于改变后发布的样本，而不影响该QoS改变之前数据读者已收到的数据样本。 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #duration | #INFINITE_DURATION | 无 | #duration > #ZERO_DURATION | 无 | 可变
 */

typedef struct DDS_LifespanQosPolicy 
{
    /** @brief   指明数据写者的数据有效期。 */
    DDS_Duration_t duration;
}DDS_LifespanQosPolicy;

#endif /* _ZRDDS_INCLUDE_LIFESPAN_QOS */

#endif /* LifespanQosPolicy_h__*/
