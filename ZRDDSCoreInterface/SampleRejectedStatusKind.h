/**
 * @file:       SampleRejectedStatusKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SAMPLEREJECTEDSTATUSKIND_H)
#define _SAMPLEREJECTEDSTATUSKIND_H

/**
 * @enum DDS_SampleRejectedStatusKind
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   用于标识数据样本被拒绝的原因类型。
 */

typedef enum DDS_SampleRejectedStatusKind
{
    /** @brief   数据样本未被拒绝。 @ingroup CoreBaseStruct */
    DDS_NOT_REJECTED,
    /** @brief   数据样本由于 DDS_ResourceLimitsQosPolicy::max_instances 原因被拒绝。 @ingroup CoreBaseStruct */
    DDS_REJECTED_BY_INSTANCE_LIMIT,
    /** @brief   数据样本由于 DDS_ResourceLimitsQosPolicy::max_samples 原因被拒绝。 @ingroup CoreBaseStruct */
    DDS_REJECTED_BY_SAMPLES_LIMIT,
    /** @brief   数据样本由于 DDS_ResourceLimitsQosPolicy::max_samples_per_instance 原因被拒绝。 @ingroup CoreBaseStruct */
    DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
}DDS_SampleRejectedStatusKind;

#endif  /*_SAMPLEREJECTEDSTATUSKIND_H*/
