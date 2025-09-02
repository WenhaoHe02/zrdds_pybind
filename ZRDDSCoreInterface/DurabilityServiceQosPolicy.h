/**
 * @file:       DurabilityServiceQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DurabilityServiceQosPolicy_h__
#define DurabilityServiceQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"
#include "HistoryQosPolicy.h"

/**
 * @struct DDS_DurabilityServiceQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   历史数据资源配置。
 *
 * @details 当 #DDS_DurabilityQosPolicyKind 取值为 ::DDS_TRANSIENT_DURABILITY_QOS
 *          ::DDS_PERSISTENT_DURABILITY_QOS 时，此时数据写者需要保存的历史数据的时间需要超过数据写者自身的生命周期，
 *          即数据写者被删除时，历史数据仍需要保存，此时需要一个特殊的持久化服务来为该数据写者保存历史数据，本QoS即控制该持久化
 *          服务为该数据写者保存的历史数据的资源限制。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #service_cleanup_delay | ::ZERO_DURATION | 无 | 无 | 无 | 不可变
 *          #history_kind | ::DDS_KEEP_LAST_HISTORY_QOS | 无 | 无 | 无 | 不可变
 *          #history_depth | 1 | 无 | #history_depth > 0 | 无 | 不可变
 *          #max_samples | #LENGTH_UNLIMITED | 无 | #max_samples > 0 | 无 | 不可变
 *          #max_instances | #LENGTH_UNLIMITED | 无 | #max_instances > 0 | 无 | 不可变
 *          #max_samples_per_instance | #LENGTH_UNLIMITED | 无 | #max_samples_per_instance > 0 | 无 | 不可变
 *          
 */

typedef struct DDS_DurabilityServiceQosPolicy
{
    /**  
     * @brief   控制何时删除持久化服务中保存的数据实例的信息。 
     *
     * @details 满足以下三个条件时删除：
     *          1. 数据实例被显示的dispose，即instance_state=NOT_ALIVE_DISPOSED；  
     *          2. 当在NOT_ALIVE_DISPOSED状态时，没有活着的DataWriter在写这个数据实例，即所有主题下的Writer要么注销了该数据实例，要么不再存活；  
     *          3. 在检测到前面两个条件满足后过了 #service_cleanup_delay 时间。
     */
    DDS_Duration_t service_cleanup_delay;
    /** @brief   为每个数据实例保存数据的类型。 */
    DDS_HistoryQosPolicyKind history_kind;
    /** @brief   当 #history_kind == ::DDS_KEEP_LAST_HISTORY_QOS 时，为每个数据实例保存最新的 #history_depth 个数据样本。*/
    DDS_Long history_depth;
    /** @brief   当 #history_kind == ::DDS_KEEP_ALL_HISTORY_QOS 时，为该主题保存的数据样本上限个数。 */
    DDS_Long max_samples;
    /** @brief   当 #history_kind == ::DDS_KEEP_ALL_HISTORY_QOS 时，为该主题下保存的数据实例上限个数。 */
    DDS_Long max_instances;
    /** @brief   当 #history_kind == ::DDS_KEEP_ALL_HISTORY_QOS 时，为该主题下每个数据实例保存的数据样本个数上限。 */
    DDS_Long max_samples_per_instance;
}DDS_DurabilityServiceQosPolicy;

#endif /* DurabilityServiceQosPolicy_h__*/
