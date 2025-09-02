/**
 * @file:       OfferedDeadlineMissedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_OFFEREDDEADLINEMISSEDSTATUS_H)
#define _OFFEREDDEADLINEMISSEDSTATUS_H

#include "InstanceHandle_t.h"

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

/**
 * @struct DDS_OfferedDeadlineMissedStatus
 * 
 * @ingroup CoreStatusStruct
 *
 * @brief   数据写者端截止时间未满足状态。
 *
 * @details 该状态在发布端检测到截止时间未满足时（ DDS_DeadlineQosPolicy ）数据写者修改该状态
 *          ，获取该状态的方法参见 #DDS_StatusKind 。
 */

typedef struct DDS_OfferedDeadlineMissedStatus
{
    /** @brief   检测到违反截止时间的总次数。 */
    DDS_Long total_count;
    /** @brief   从上一次获取该状态到本次获取的时间段内，违反截止时间的次数。 */
    DDS_Long total_count_change;
    /** @brief   最近一次检测到违反截止时间的数据实例的标识。 */
    DDS_InstanceHandle_t last_instance_handle;
}DDS_OfferedDeadlineMissedStatus;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */

#endif  /*_OFFEREDDEADLINEMISSEDSTATUS_H*/
