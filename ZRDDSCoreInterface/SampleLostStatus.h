/**
 * @file:       SampleLostStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SAMPLELOSTSTATUS_H)
#define _SAMPLELOSTSTATUS_H

#include "OsResource.h"
#include "SequenceNumber_t.h"
#include "InstanceHandle_t.h"

/**
 * @struct DDS_SampleLostStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   样本丢失状态。
 *
 * @details 当数据读者检测到数据样本丢失时修改此状态，造成该状态的可能的原因如下，获取该状态的方式参见 @ref #DDS_StatusKind ：
 *          - 在 DDS_RelialibityQosPolicy::kind == DDS_BEST_EFFORT_RELIABILITY 条件下：  
 *              - 底层传输协议的乱序将导致延后的数据样本被丢失；  
 *              - 由于 DDS_ResourceLimitQosPolicy::max_instances 的限制；
 *              - 由于 DDS_ResourceLimitQosPolicy::max_samples_per_instance 的限制；
 *          - 在 DDS_RelialibityQosPolicy::kind == DDS_RELIABLE_RELIABILITY 条件下：
 *              - 在请求重传时（原因可能为底层的传输协议丢包或者由于资源限制数据读者主动丢弃），请求的样本已经被数据写者删除（QoS配置）；
 *              - 由于 DDS_ResourceLimitQosPolicy::max_instances 的限制；
 *              - 由于 DDS_ResourceLimitQosPolicy::max_samples_per_instance 的限制；
 *              - 在数据读者使能后，与之匹配的数据写者已经发送完成的数据；
 */

typedef struct DDS_SampleLostStatus
{
    /** @brief   该数据读者累计所有数据实例丢失的数据样本的个数。 */
    DDS_Long total_count;
    /** @brief   从上一次获取该状态到本次获取该状态时间内，数据读者检测到的数据样本丢失的数据个数。 */
    DDS_Long total_count_change;
    /** @brief   丢失样本的来源信息。 */
    DDS_InstanceHandle_t writer_handle;
    /** @brief   丢失样本的序列号信息，[start_seq, end_seq]区间的样本标记为丢失。*/
    DDS_SequenceNumber_t start_seq;
    /** @brief   丢失样本的序列号信息，[start_seq, end_seq]区间的样本标记为丢失。*/
    DDS_SequenceNumber_t end_seq;
}DDS_SampleLostStatus;

#endif  /*_SAMPLELOSTSTATUS_H*/
