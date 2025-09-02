/**
 * @file:       DDSMsgStatisticsInfoQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSMsgStatisticsInfoQosPolicy_h__
#define DDSMsgStatisticsInfoQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS

/**
 * @struct DDS_MsgStatisticsInfoQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   实体报文统计信息发布配置。
 *
 * @details 为了更好地调试DDS系统，DDS系统提供精确到实体的报文以及用户样本发送、接收数量的统计，
 *          该功能需要与DDS管理监控器配合使用。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #enable | false | 无 | 无 | 无 | 可变
 *          #send_period | DDS_Duration_t(1, 0) | 无 | 无 | 无 | 可变
 */

typedef struct DDS_MsgStatisticsInfoQosPolicy 
{
    /** @brief   控制是否使能报文统计功能。*/
    DDS_Boolean enable;
    /** @brief   报文统计结果的发布周期。 */
    DDS_Duration_t send_period;
}DDS_MsgStatisticsInfoQosPolicy;

#endif /* _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS */

#endif /* DDSMsgStatisticsInfoQosPolicy_h__ */
