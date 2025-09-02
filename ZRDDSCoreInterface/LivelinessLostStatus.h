/**
 * @file:       LivelinessLostStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_LIVELINESSLOSTSTATUS_H)
#define _LIVELINESSLOSTSTATUS_H

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

/**
 * @struct DDS_LivelinessLostStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   数据写者存活性丢失状态。
 *
 * @details 当数据写者的 DDS_LivelinessQosPolicy::kind 设置为 
 *          #DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS 或者 #DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS 时，
 *          数据写者会检测用户的行为（是否在规定的时间周期内调用 DataWriter::write等方法来声明自身的存活性）
 *          是否满足 DDS_LivelinessQosPolicy 的设置，如果检测到不满足则会修改自身的存活性丢失状态
 *          ，获取方法参见 #DDS_StatusKind 。
 */

typedef struct DDS_LivelinessLostStatus
{
    /** @brief   检测到存活性丢失的总次数。 */
    DDS_Long total_count;
    /** @brief   从上一次获取该状态到本次事件段内检测到存活性丢失的次数。 */
    DDS_Long total_count_change;
}DDS_LivelinessLostStatus;

#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */

#endif  /*_LIVELINESSLOSTSTATUS_H*/
