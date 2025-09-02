/**
 * @file:       RequestedDeadlineMissedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_REQUESTEDDEADLINEMISSEDSTATUS_H)
#define _REQUESTEDDEADLINEMISSEDSTATUS_H

#include "InstanceHandle_t.h"

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @struct DDS_RequestedDeadlineMissedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   数据读者端截止时间未满足状态。
 *         
 * @details 该状态在数据读者检测到数据实例的截止时间配置未满足时（ DDS_DeadlineQosPolicy ）数据读者修改该状态，
 *          获取该状态的方法参见 #DDS_StatusKind 。
 */

typedef struct DDS_RequestedDeadlineMissedStatus
{
    /** @brief   检测到违反截止时间的总次数。 */
    DDS_Long total_count;
    /** @brief   从上一次获取该状态到本次获取的时间段内，违反截止时间的次数。 */
    DDS_Long total_count_change;
    /** @brief   最近一次检测到违反截止时间的数据实例的标识。 */
    DDS_InstanceHandle_t last_instance_handle;
}DDS_RequestedDeadlineMissedStatus;

#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */

#endif  /*_REQUESTEDDEADLINEMISSEDSTATUS_H*/
