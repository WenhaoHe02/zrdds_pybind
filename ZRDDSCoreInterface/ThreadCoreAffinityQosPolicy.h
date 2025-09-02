/**
 * @file:       ThreadCoreAffinityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ThreadCoreAffinityQosPolicy_h__
#define ThreadCoreAffinityQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"
#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_ThreadCoreAffinityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   线程依附性配置。
 *
 * @details 该QoS用于配置 ZRDDS 内部线程的CPU依赖性，在多核平台上通过该QoS配置线程运行在哪些CPU核上，配置以位掩码
 *          的形式设置该线程能够运行的CPU核心编号，例如0x01的第0字节为1，表示该线程可以运行在0号CPU核上，0xffff的低16位
 *          为1，表示该线程可以运行在0-15号CPU核上。
 *          一个域参与者的线程包含:
 *          - 若干个接收线程（ 个数由 DDS_ReceiverThreadConfigQosPolicy 配置）  
 *          - 一个定时器线程  
 *          - 若干个异步发送线程，数量等于使能异步传输的发布者的个数 DDS_PublishModeQosPolicy 
 *           成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #receive_thread_default_affinity_mask | #MAX_UINT32_VALUE | 无 | 无 | 无 | 不可变
 *          #user_data_receive_thread_affinity_mask | #MAX_UINT32_VALUE | 无 | 无 | 无 | 不可变
 *          #builtin_data_receive_thread_affinity_mask | #MAX_UINT32_VALUE | 无 | 无 | 无 | 不可变
 *          #timer_thread_affinity_mask | #MAX_UINT32_VALUE | 无 | 无 | 无 | 不可变
 *          #async_send_thread_affinity_mask | #MAX_UINT32_VALUE | 无 | 无 | 无 | 不可变
 */

typedef struct DDS_ThreadCoreAffinityQosPolicy
{
    /** @brief   接收线程默认使用的掩码值。 */
    DDS_ULong receive_thread_default_affinity_mask;
    /** @brief   用户数据接收线程使用的掩码值。 */
    DDS_ULong user_data_receive_thread_affinity_mask;
    /** @brief   内置数据接收线程使用的掩码值。 */
    DDS_ULong builtin_data_receive_thread_affinity_mask;
    /** @brief   定时器线程使用的掩码值。 */
    DDS_ULong timer_thread_affinity_mask;
    /** @brief   异步发送线程使用的掩码值。 */
    DDS_ULong async_send_thread_affinity_mask;
    /** @brief   当配置PER_PORT时，底层可能会创建多个用于接收TCP接收线程，此时按照序列号依次绑定线程。 */
    DDS_ULongSeq tcp_receive_thread_affinity_masks;
    /* @brief   默认情况下值为false，TCP接收线程按照序列号依次绑定tcp_receive_thread_affinity_masks所设置的核，
     *          tcp_receive_thread_affinity_masks所设置的值全部绑定后，其余接收线程不进行绑核。  
     *          当设置为true的情况下，接收线程循环绑定tcp_receive_thread_affinity_masks所设置的值*/
    ZR_BOOLEAN tcp_receive_thread_repeat_use_affinity_masks;
}DDS_ThreadCoreAffinityQosPolicy;

#endif /* ThreadCoreAffinityQosPolicy_h__*/
