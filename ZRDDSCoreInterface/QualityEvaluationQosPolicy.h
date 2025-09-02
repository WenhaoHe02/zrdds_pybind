/**
 * @file:       QualityEvaluationQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QualityEvaluationQosPolicy_h__
#define QualityEvaluationQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"
#include "InstanceHandle_t.h"
#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_RTPS_MESSAGE_KIND
 *
 * @ingroup CoreQosStruct
 *
 * @brief   RTPS报文统计中的子消息类型。
 * 
 */
typedef enum DDS_RTPS_MESSAGE_KIND
{
    RTPS_MSG_ACKNACK = 0,
    RTPS_MSG_NACK,
    RTPS_MSG_GAP,
    RTPS_MSG_INFO_TS,
    RTPS_MSG_HEARTBEAT,
    RTPS_MSG_INFO_SRC,
    RTPS_MSG_INFO_REPLY_IP4,
    RTPS_MSG_INFO_DST,
    RTPS_MSG_INFO_REPLY,
    RTPS_MSG_NACK_FRAG,
    RTPS_MSG_HEARTBEAT_FRAG,
    RTPS_MSG_DATA,
    RTPS_MSG_RESEND_DATA,
    RTPS_MSG_DATA_FRAG,
    RTPS_MSG_RESEND_DATA_FRAG,
    RTPS_MSG_ACKNACK_BATCH,
    RTPS_MSG_DATA_BATCH,
    RTPS_MSG_RESEND_DATA_BATCH,
    RTPS_MSG_HEARTBEAT_BATCH,
    RTPS_MSG_UNKNOWN_SUBMSGKIND,
    RTPS_MSG_UNKNOWN_WRITER_DATA,
    RTPS_MSG_DUPLICATE_DATA,
    RTPS_MSG_MAX_SAMPLES_LIMITS_DATA,
    RTPS_MSG_MAX_INSTANCES_LIMITS_DATA,
    RTPS_MSG_MAX_SAMPLES_PER_INSTANCE_LIMITS_DATA,
    RTPS_MSG_FILTERED_DATA,
    RTPS_MSG_EARLY_TS_DATA,
    RTPS_DELIVERED_DATA,
    RTPS_MSG_NO_OWNERSHIP_DATA,
    RTPS_MSG_INVALID
}DDS_RTPS_MESSAGE_KIND;

#ifdef _ZRDDS_INCLUDE_QUALITY_EVALUATION

#define DDS_QUALITY_EVAL_LATENCY_RESERVED_NUM 16

/**
 * @struct DDS_LinkQualityEvaluationInfo
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义通信质量评估内置主题关联的数据类型，为支持扩展，该类型为 MUTABLE 类型。
 * 
 */
typedef struct DDS_LinkQualityEvaluationInfo
{
    /** @brief   结构版本信息。 */
    DDS_ULong version;
    /** @brief   连接的发送端，通常为数据写者的唯一标识。 */
    DDS_Octet writer_id[16];
    /** @brief   连接的接收端，通常为数据读者的唯一标识。 */
    DDS_Octet reader_id[16];
    /** @brief   该连接发送的rtps子消息累积统计。 */
    DDS_ULongLong rtps_smsg_recv_count[30];
    /** @brief   该连接传输的样本个数累积统计。 */
    DDS_ULongLong sample_count;
    /** @brief   该连接传输的样本累积大小，单位为字节。 */
    DDS_ULongLong sample_size;
    /** 
     *  @brief   从上一次发布评估数据后延迟统计信息，单位为us。
     *  
     *  @details    前16元素预留，当前分别为：个数、最小、最大、平均。
     *              后面的元素为发布上一个评估数据后前n个样本的延迟数据，n由DDS_QualityEvaluationQosPolicy::max_samples控制。 
     */
    DDS_LongSeq latency_infos;
}DDS_LinkQualityEvaluationInfo;

/**
 * @struct DDS_QualityEvaluationQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义通信质量评估QoS测试。
 * 
 * @details 启用通信质量评估QoS后，DDS会使用所属域参与者下的内置 DDS_BuiltinQualityEvaluationTopic 主题
 *          将关联的 DDS_QualityEvaluationInfo 类型样本以 @period 为周期发布，当前在数据读者端进行统计。
 */
typedef struct DDS_QualityEvaluationQosPolicy
{
    /** @brief   统计信息发布周期，默认为 DDS_DURATION_INFINITE_SEC 表示不开启统计。 */
    DDS_Duration_t period;
    /** @brief   合并发送的个数，默认为-1表示将所有连接数据合并发送。 */
    DDS_Long batch;
    /** @brief   是否采用内置的NTP对时调整时延。 */
    DDS_Boolean adjust_time;
    /** @brief   DDS_QualityEvaluationInfo::latency_infos 预分配的长度，避免在接收数据时动态分配空间，默认为1024。 */
    DDS_ULong initial_samples;
    /** @brief   统计周期内，统计的最大样本个数，默认为1024。 */
    DDS_ULong max_samples;
}DDS_QualityEvaluationQosPolicy;

#endif /* _ZRDDS_INCLUDE_QUALITY_EVALUATION */

#endif /* QualityEvaluationQosPolicy_h__*/
