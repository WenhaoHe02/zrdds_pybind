/**
 * @file:       InconsistentTopicStatus.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef InconsistentTopicStatus_h__
#define InconsistentTopicStatus_h__

#include "OsResource.h"

/**
 * @struct DDS_InconsistentTopicStatus
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   描述名称同一个域中主题名相同但关联的类型不同的主题状态。
 *          
 * @details ZRDDS要求在同一个域中具有相同主题名称的主题与相同的主题名称绑定，否则该主题关联的数据写者和数据读者将不能匹配，
 *          进而不能进行数据交互，ZRDDS在发现同一个域中具有相同主题名但类型名不同的主题时（通过发现主题关联的数据写者或
 *          数据读者，ZRDDS不会单独发现主题）将会触发本地具备该主题名的主题的主题不一致状态，获取方法参见 ::DDS_StatusKind 。
 */

typedef struct DDS_InconsistentTopicStatus
{
    /** @brief   从该主题创建开始，触发主题不一致状态的总次数。 */
    DDS_ULong total_count;
    /** @brief   从上一次获取此状态到本次获取时间段内触发主题不一致状态的增量。 */
    DDS_ULong total_count_change;
}DDS_InconsistentTopicStatus;

#endif /* InconsistentTopicStatus_h__*/
