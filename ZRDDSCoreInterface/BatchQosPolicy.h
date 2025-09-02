/**
 * @file:       BatchQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef BatchQosPolicy_h__
#define BatchQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_BatchQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   批量发送配置。
 *
 * @details 当用户发送大量长度较短的数据时，为了尽可能利用网络带宽，可以将多个小数据包合并成一个较大数据包发送，即批量发送。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #enable | false | 无 | 无 | 无 | 不可变
 *          #max_data_bytes | 1024 | 无 | DDS_BatchQosPolicy::max_data_bytes > 0 | 无 | 不可变
 *          #max_meta_data_bytes | #LENGTH_UNLIMITED | 无 | 无 | 无 | 不可变
 *          #max_samples | #LENGTH_UNLIMITED | 无 | DDS_BatchQosPolicy::max_samples > 0 | 无 | 不可变
 *          #max_flush_delay | #INFINITE_DURATION | 无 | 无 | !#enable OR #max_flush_delay == #INFINITE_DURATION OR !DDS_AsynchronousPublisherQosPolicy::disable_asynchronous_batch | 不可变
 *          #source_timestamp_resolution | #INFINITE_DURATION | 无 | 无 | 无 | 不可变
 *          #thread_safe_write | false | 无 | 无 | 无 | 不可变
 *
 */

typedef struct DDS_BatchQosPolicy
{
    /** @brief   是否使用批量发送。 */
    DDS_Boolean enable;
    /** @brief   批量发送时样本最大累计长度，积累样本长度达到该值时会触发刷新。 */
    DDS_Long max_data_bytes;
    /** @brief   暂未使用 */
    DDS_Long max_meta_data_bytes;
    /** @brief   批量发送中最大样本数量，积累样本数量达到该值时会触发刷新。 */
    DDS_Long max_samples;
    /** @brief   最大发送延迟，每当达到该时间时会触发刷新，当以其他方式刷新时，会重置刷新时间。 */
    DDS_Duration_t max_flush_delay;
    /** @brief   设置批量发送的源时间戳分辨率，当批量发送的数据包时间戳与前一个出现的时间戳小于该值时，数据包将不再包含独立的时间戳，否则会包含其独立的时间戳。 */
    DDS_Duration_t source_timestamp_resolution;
    /** @brief   暂未使用。 */
    DDS_Boolean thread_safe_write;
}DDS_BatchQosPolicy;

#endif /* BatchQosPolicy_h__*/
