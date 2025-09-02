/**
 * @file:       DeadlineQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DeadlineQosPolicy_h__
#define DeadlineQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

/**
 * @struct DDS_DeadlineQosPolicy
 *
 * @ingroup CoreQosStruct 
 *
 * @brief   截止时间配置。
 * 
 * @details 该Qos可以在希望周期性的发布一个主题下每个实例的数据时使用。
 *          - 在发布端，在用户的设计中，每个数据实例在 #period 时间内至少被更新一次，通过设置该QoS，  
 *            如果在实际运行中发布端不满足该要求，DDS将会通知用户（ DDS_OfferedDeadlineMissedStatus ），
 *            用户来处理该实际运行与设计不相符的异常。
 *          - 在订阅端，在用户的设计中，每个数据实例在 #period 时间内都会收到一个数据，通过设置该QoS，  
 *            如果在实际运行中订阅端不满足该要求，DDS将会通知用户（ DDS_RequestedDeadlineMissedStatus ），
 *            用户来处理该实际运行与设计不相符的异常。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #period | #INFINITE_DURATION | 数据写者.#period <= 数据读者.#period | 无 | #period >= DDS_TimeBasedFilterQosPolicy::minimum_separation | 可变
 */

typedef struct DDS_DeadlineQosPolicy 
{
    /** @brief   每个实例数据的最小发布周期。 */
    DDS_Duration_t period;
} DDS_DeadlineQosPolicy;

#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */

#endif /* DeadlineQosPolicy_h__*/
