/**
 * @file:       LatencyBudgetQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef LatencyBudgetQosPolicy_h__
#define LatencyBudgetQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS

/**
 * @struct DDS_LatencyBudgetQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   延时优化配置。
 *
 * @details 表明最大可接受的数据延迟，即接收端应用被通知的时间-发布端发布该数据的时间。只是一个给ZRDDS底层的提示，
 *          用于优化操作，例如，可以让 #duration 小的链路的数据优先级变高。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #duration | ::ZERO_DURATION | 数据写者.#duration &lt;= 数据读者.#duration | #duration &gt;= #ZERO_DURATION | 无 | 可变
 *
 * @warning ZRDDS暂未实现该QoS，配置该QoS无效，但会对该QoS进行检查。
 */

typedef struct DDS_LatencyBudgetQosPolicy
{
    /** @brief   表明最大可接受的数据延迟。 */
    DDS_Duration_t duration;
}DDS_LatencyBudgetQosPolicy;

#endif //_ZRDDS_INCLUDE_LATENCY_BUDGET_QOS

#endif /* LatencyBudgetQosPolicy_h__*/
