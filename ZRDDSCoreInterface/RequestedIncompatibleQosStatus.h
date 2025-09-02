/**
 * @file:       RequestedIncompatibleQosStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_REQUESTEDINCOMPATIBLEQOSSTATUS_H)
#define _REQUESTEDINCOMPATIBLEQOSSTATUS_H

#include "OsResource.h"
#include "QosPolicyId_t.h"
#include "QosPolicyCount.h"

/**
 * @struct DDS_RequestedIncompatibleQosStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   数据读者端QoS不匹配状态。
 *
 * @details 数据读者在试图与远端的数据写者匹配时检测到订阅者所需求的QoS与远端的数据写者不兼容时会改变本状态，
 *          ZRDDS对QoS的兼容性检查参见每个QoS的详细描述，用户获取该状态的方式参见 #DDS_StatusKind 。
 */

typedef struct DDS_RequestedIncompatibleQosStatus
{
    /** @brief   数据读者检测到数据写者QoS不兼容的总次数。 */
    DDS_Long total_count;
    /** @brief   自从上一次获取该状态开始到本次获取该状态时间内数据写者检测到数据读者QoS不兼容的次数。 */
    DDS_Long total_count_change;
    /** @brief   最近一次引起不匹配QoS状态的QoS标识。 */
    DDS_QosPolicyId_t last_policy_id;
    /** @brief   对于每个类型的Qos类型分别统计引起不兼容QoS的总次数。 */
    DDS_QosPolicyCountSeq policies;
}DDS_RequestedIncompatibleQosStatus;

#endif  /*_REQUESTEDINCOMPATIBLEQOSSTATUS_H*/
