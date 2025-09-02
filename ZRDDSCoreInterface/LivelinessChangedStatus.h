/**
 * @file:       LivelinessChangedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_LIVELINESSCHANGEDSTATUS_H)
#define _LIVELINESSCHANGEDSTATUS_H

#include "InstanceHandle_t.h"

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

/**
 * @struct DDS_LivelinessChangedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   数据写者存活性变化状态。
 *          
 * @details ZRDDS会根据 DDS_LivelinessQosPolicy 检测数据写者的存活性信息。当数据读者检测到与之匹配的
 *          数据写者的存活性信息发生变化时，会维护自身的数据写者存活性变化状态，注意，当某个数据写者不再与该数据读者匹配时
 *          （被删除等情况），该数据写者的存活性不再统计的范围内，故而应注意区分数据写者失活以及被删除两种情况的差别。
 *          事件 | #alive_count 变化量 | #not_alive_count 变化量 | #alive_count_change 变化量 | #not_alive_count_change 变化量
 *          --- | --- | --- | --- | ---
 *          匹配新的数据写者 | 1 | 0 | 1 | 0
 *          已经匹配的数据写者从失活状态变为存活 | 1 | -1 | 1 | -1
 *          解除匹配数据写者 | -1 | 0 | -1 | 0
 *          已经匹配的数据写者从存活状态变为失活 | -1 | 1 | -1 | 1
 *          用户获取该状态的方式参见 ::DDS_StatusKind 。
 */

typedef struct DDS_LivelinessChangedStatus
{
    /** @brief   与该数据读者匹配的存活的数据写者的总量。 */
    DDS_Long alive_count;
    /** @brief   与该数据读者匹配的非存活的数据写者的总量。 */
    DDS_Long not_alive_count;
    /** @brief   从上一次获取该状态到本次事件段内与该数据读者匹配的存活的数据写者变为存活状态（或者新增数据写者）的个数。 */
    DDS_Long alive_count_change;
    /** @brief   从上一次获取该状态到本次事件段内与该数据读者匹配的存活的数据写者变为非存活状态（或者解除匹配数据写者）的个数。 */
    DDS_Long not_alive_count_change;
    /** @brief   最近一次影响上诉值的数据写者的唯一标识。 */
    DDS_InstanceHandle_t last_publication_handle;
}DDS_LivelinessChangedStatus;

#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */

#endif  /*_LIVELINESSCHANGEDSTATUS_H*/
