/**
 * @file:       SampleRejectedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SAMPLEREJECTEDSTATUS_H)
#define _SAMPLEREJECTEDSTATUS_H

#include "OsResource.h"
#include "SampleRejectedStatusKind.h"
#include "InstanceHandle_t.h"

/**
 * @struct DDS_SampleRejectedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief  数据样本被拒绝状态。
 *
 * @details 当数据读者检测到数据样本被拒绝时修改此状态，造成该状态的可能的原因如下，获取该状态的方式参见 @ref #DDS_StatusKind ：
 *          - 由于 DDS_ResourceLimitQosPolicy::max_samples 的限制；
 *          - 由于 DDS_ResourceLimitQosPolicy::max_instances 的限制；
 *          - 由于 DDS_ResourceLimitQosPolicy::max_samples_per_instance 的限制；
 */

typedef struct DDS_SampleRejectedStatus
{
    /** @brief   数据样本被拒绝的总次数（需要区分总个数，同一个样本可能被拒绝多次）。*/
    DDS_Long total_count;
    /** @brief   从上一次获取该状态到本次获取该状态时间内，数据读者检测到的数据样本被拒绝的次数。 */
    DDS_Long total_count_change;
    /** @brief   最近一次引发该状态的的原因。 */
    DDS_SampleRejectedStatusKind last_reason;
    /** @brief   最近一次引发该状态的数据样本所属数据实例的唯一标识。 */
    DDS_InstanceHandle_t last_instance_handle;
}DDS_SampleRejectedStatus;

#endif  /*_SAMPLEREJECTEDSTATUS_H*/
