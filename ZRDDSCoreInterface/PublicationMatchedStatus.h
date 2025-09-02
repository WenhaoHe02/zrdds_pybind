/**
 * @file:       PublicationMatchedStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_PUBLICATIONMATCHEDSTATUS_H)
#define _PUBLICATIONMATCHEDSTATUS_H

#include "InstanceHandle_t.h"

/**
 * @struct DDS_PublicationMatchedStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   数据写者端与数据读者的匹配状态。
 *
 * @details 数据写者端在与数据读者匹配成功或者解除与数据读者匹配会修改该状态，获取该状态的方式参见 #DDS_StatusKind 。
 */

typedef struct DDS_PublicationMatchedStatus
{
    /** @brief   数据写者与数据读者匹配总次数（包括已经解除匹配的数据读者）。 */
    DDS_Long total_count;
    /** @brief   从上一次获取该状态到本次获取本状态时间内匹配总次数的变化。 */
    DDS_Long total_count_change;
    /** @brief    当前数据写者与数据读者匹配的个数。 */
    DDS_Long current_count;
    /** @brief   从上一次获取该状态到本次获取本状态时间内当前匹配个数的变化。 */
    DDS_Long current_count_change;
    /** @brief   上一个引起该状态变化的远程数据读者的唯一标识。 */
    DDS_InstanceHandle_t last_subscription_handle;
}DDS_PublicationMatchedStatus;

#endif  /*_PUBLICATIONMATCHEDSTATUS_H*/
