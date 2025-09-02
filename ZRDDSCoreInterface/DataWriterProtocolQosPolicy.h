/**
 * @file:       DataWriterProtocolQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriterProtocolQosPolicy_h__
#define DataWriterProtocolQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

/**
 * @struct DDS_RtpsReliableWriterProtocol
 *
 * @ingroup CoreQosStruct
 *
 * @brief 控制可靠数据写者的相关行为。
 */
typedef struct DDS_RtpsReliableWriterProtocol
{
    /** @brief DataWriter定时发送心跳的间隔。 */
    DDS_Duration_t heartbeat_period;
    /** @brief 当设置为reliability/keep_all时，当存在未反馈的样本且正在等待空间时，底层将以该时间周期发送HB消息。 */
    DDS_Duration_t fastheartbeat_period;
    /** @brief 暂未使用 */
    DDS_Long max_heartbeat_retries;
    /** 
     * @brief 控制数据写者数据包中包含心跳包的包数间隔。
     *        
     * @details 数据写者数据包中可以同时携带心跳包，使用该QoS时，每隔max_samples/heartbeats_per_max_samples个数据包时会携带一个心跳包。
     *        其中max_samples值为当前DataWriter的最大缓存样本数量，当DDS_HistoryQosPolicy::kind为DDS_KEEP_LAST_HISTORY_QOS时，取DDS_HistoryQosPolicy::depth，
     *        当DDS_HistoryQosPolicy::kind为DDS_KEEP_ALL_HISTORY_QOS时，取DDS_ResourceLimitsQosPolicy::max_samples_per_instance。当该值取0时，与取1效果相同，不允许取负值。 
     */
    DDS_Long heartbeats_per_max_samples;
}DDS_RtpsReliableWriterProtocol;

/**
 * @struct DDS_DataWriterProtocolQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 数据写者中与RTPS协议相关的行为配置。
 *
 * @details
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #push_on_write | false | 无 | 无 | 无 | 不可变
 *          DDS_RtpsReliableWriterProtocol::heartbeat_period | DDS_Duration_t{3,0} | 无 | 无 | 无 | 不可变
 *          DDS_RtpsReliableWriterProtocol::fastheartbeat_period | DDS_Duration_t{0, 100 * 1000 * 1000} | 无 | 无 | 无 | 不可变
 *          DDS_RtpsReliableWriterProtocol::max_heartbeat_retries | #LENGTH_UNLIMITED | 无 | 无 | 无 | 不可变
 *          DDS_RtpsReliableWriterProtocol::heartbeats_per_max_samples | 8 | 无 | DDS_RtpsReliableWriterProtocol::heartbeats_per_max_samples >= 0 | 无 | 不可变
 *
 */
typedef struct DDS_DataWriterProtocolQosPolicy
{
    /** @brief 当使用TCP传输时，用于控制数据传输SOCKET的TCP_NODELAY选项，设置为true时，底层将设置该选项。 */
    DDS_Boolean push_on_write;
    /** @brief 控制可靠数据写者的相关行为。 */
    DDS_RtpsReliableWriterProtocol rtps_reliable_writer;
}DDS_DataWriterProtocolQosPolicy;

#endif /* DataWriterProtocolQosPolicy_h__*/
