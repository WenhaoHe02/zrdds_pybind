/**
 * @file:       ReaderDataLifecycleQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ReaderDataLifecycleQosPolicy_h__
#define ReaderDataLifecycleQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_ReaderDataLifecycleQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据读者数据实例的生命周期配置。
 *
 * @details 该配置控制数据读者何时清理非存活状态的数据实例所占的空间。正常情况下数据读者可以要求归还所有的为数据实例分配的资源，
 *          当所有的样本都被拿走的时候，数据读者还会为数据实例维护的最后一个样本（状态样本）即 
 *          DDS_SampleInfo::instance_state 为 #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE 或者 
 *          #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE 。如果没有该QoS，会导致这些非存活的数据实例所占的空间会无限期的残留在数据读者中。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #autopurge_nowriter_samples_delay | #INFINITE_DURATION | 无 | 无 | 无 | 可变
 *          #autopurge_disposed_samples_delay | #INFINITE_DURATION | 无 | 无 | 无 | 可变
 *          #purge_instance_with_not_read_samples | true | 无 | 无 | 无 | 可变
 */

typedef struct DDS_ReaderDataLifecycleQosPolicy
{
    /** @brief   表明当数据实例的状态变成 #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE 时数据读者维持该数据实例样本即信息的最大时间长度。 */
    DDS_Duration_t autopurge_nowriter_samples_delay;
    /** @brief   表明当数据实例的状态变成 #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE 时数据读者维持该数据实例样本即信息的最大时间长度。 */
    DDS_Duration_t autopurge_disposed_samples_delay;
    /**  
     *  @brief   是否清理存在未读样本的数据实例。当该值为false，在最大时间长度到达并尝试清理数据实例时，如果仍然存在未读样本，则暂不清除。  
     *             直至用户read/take并return_loan后才释放实例空间。默认为true。
     */
    DDS_Boolean purge_instance_with_not_read_samples;
}DDS_ReaderDataLifecycleQosPolicy;

#endif /* ReaderDataLifecycleQosPolicy_h__*/
