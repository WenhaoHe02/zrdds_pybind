/**
 * @file:       WriterDataLifecycleQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef WriterDataLifecycleQosPolicy_h__
#define WriterDataLifecycleQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_WriterDataLifecycleQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 数据写者样本生命周期配置。
 *
 * @details 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #autodispose_unregistered_instances | true | 无 | 无 | 无 | 不可变
 *          #autopurge_unregistered_instance_delay | #DDS_TIME_INFINITE | 无 | 无 | 无 | 不可变
 *          #autopurge_disposed_instance_delay | #DDS_TIME_INFINITE | 无 | 无 | 无 | 不可变
 *
 */
typedef struct DDS_WriterDataLifecycleQosPolicy
{
    /** @brief 配置是否自动销毁已经注销的实例。 */
    DDS_Boolean autodispose_unregistered_instances;
    /** @brief 配置已注销实例回收资源的延迟时间。 */
    DDS_Duration_t autopurge_unregistered_instance_delay;
    /** @brief 配置已销毁实例回收资源的延迟时间。 */
    DDS_Duration_t autopurge_disposed_instance_delay;
}DDS_WriterDataLifecycleQosPolicy;

#endif /* WriterDataLifecycleQosPolicy_h__*/
