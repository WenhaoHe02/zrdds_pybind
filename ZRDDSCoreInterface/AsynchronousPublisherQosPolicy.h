/**
 * @file:       AsynchronousPublisherQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef AsynchronousPublisherQosPolicy_h__
#define AsynchronousPublisherQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_AsynchronousPublisherQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   配置Publisher是否使用异步发送数据或异步批量发送的QoS。
 *
 * @details 默认情况下，DDS发布数据时会使用用户调用发送接口的线程直接将数据发送到传输协议中，
 *          当数据包较大时，可能造成用户线程的长时间阻塞。为了避免此种情况发生，可以使用异步发送。
 *          当启动异步发送时，发布者会开启新线程发送数据。
 *          当用户发送大量长度较短的数据时，为了尽可能利用网络带宽，可以将多个小数据包合并成一个较大数据包发送，即批量发送。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #disable_asynchronous_write | false | 无 | 无 | DDS_PublishModeQosPolicy::kind == DDS_SYNCHRONOUS_PUBLISH_MODE_QOS | 不可变
 *          #disable_asynchronous_batch | false | 无 | 无 | DDS_BatchQosPolicy::enable == false OR DDS_BatchQosPolicy::max_flush_delay == #INFINITE_DURATION | 不可变
 *
 */

typedef struct DDS_AsynchronousPublisherQosPolicy
{
    /** @brief   是否禁用异步发送模式。 */
    DDS_Boolean disable_asynchronous_write;
#ifdef _ZRDDS_INCLUDE_BATCH
    /** @brief   是否禁用异步批量发送模式。 */
    DDS_Boolean disable_asynchronous_batch;
#endif // _ZRDDS_INCLUDE_BATCH
}DDS_AsynchronousPublisherQosPolicy;

#endif /* AsynchronousPublisherQosPolicy_h__*/
