/**
 * @file:       DataWriterResourceLimitsQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriterResourceLimitsQosPolicy_h__
#define DataWriterResourceLimitsQosPolicy_h__

#include "OsResource.h"

/**
 * @enum DDS_DataWriterResourceLimitsInstanceReplacementKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief 配置数据写者实例替换策略。
 */
typedef enum DDS_DataWriterResourceLimitsInstanceReplacementKind
{
    /** @brief  只替换已注销的实例。 @ingroup CoreQosStruct */
    DDS_UNREGISTERED_INSTANCE_REPLACEMENT,
    /** @brief  只替换存活的实例。 @ingroup CoreQosStruct */
    DDS_ALIVE_INSTANCE_REPLACEMENT,
    /** @brief  只替换已销毁的实例。 @ingroup CoreQosStruct */
    DDS_DISPOSED_INSTANCE_REPLACEMENT,
    /** @brief  优先替换存活的实例，若不存在则替换已注销的实例。 @ingroup CoreQosStruct */
    DDS_ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT,
    /** @brief  优先替换已销毁的实例，若不存在则替换存活的实例。 @ingroup CoreQosStruct */
    DDS_DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT,
    /** @brief  替换存活或者已注销的实例。 @ingroup CoreQosStruct */
    DDS_ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT
}DDS_DataWriterResourceLimitsInstanceReplacementKind;

/**
 * @struct DDS_DataWriterResourceLimitsQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 数据写者资源限制QoS配置。
 *
 * @details 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #initial_concurrent_blocking_threads | 1 | 无 | #initial_concurrent_blocking_threads >= 0 | 无 | 不可变
 *          #max_concurrent_blocking_threads | #LENGTH_UNLIMITED | 无 | #max_concurrent_blocking_threads >= #initial_concurrent_blocking_threads | 无 | 不可变
 *          #instance_replacement | #DDS_UNREGISTERED_INSTANCE_REPLACEMENT | 无 | 无 | 无 | 不可变
 *          #replace_empty_instances | false | 无 | 无 | 无 | 不可变
 *          #autoregister_instances | true | 无 | 无 | 无 | 不可变
 *          #max_batches | #LENGTH_UNLIMITED | 无 | #max_batches > 0 | 无 | 不可变
 *
 */
typedef struct DDS_DataWriterResourceLimitsQosPolicy
{
    /** @brief 配置当数据写者样本达到上限时，同时等待的线程初始数量，由于需要等待的线程占用一定资源，该QoS配置初始分配的资源量。 */
    DDS_Long initial_concurrent_blocking_threads;
    /** @brief 配置当数据写者样本达到上限时，同时等待的线程最大数量。 */
    DDS_Long max_concurrent_blocking_threads;
    /** @brief 配置数据写者实例替换策略。 */
    DDS_DataWriterResourceLimitsInstanceReplacementKind instance_replacement;
    /** @brief 配置当需要替换实例时是否替换空实例（即未发布过样本的实例） */
    DDS_Boolean replace_empty_instances;
    /** @brief 配置发布样本时，是否自动注册未注册的实例 */
    DDS_Boolean autoregister_instances;
    /** @brief 配置批量发送样本（Batch）的最大数量 */
    DDS_Long max_batches;
}DDS_DataWriterResourceLimitsQosPolicy;

#endif /* DataWriterResourceLimitsQosPolicy_h__*/
