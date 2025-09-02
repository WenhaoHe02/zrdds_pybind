/**
 * @file:       OwnershipStrengthQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef OwnershipStrengthQosPolicy_h__
#define OwnershipStrengthQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS

/**
 * @struct DDS_OwnershipStrengthQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   所有权值配置。
 *
 * @details 该QoS在 DDS_OwnershipQosPolicy::kind == #DDS_EXCLUSIVE_OWNERSHIP_QOS 
 *          时设置数据写者的权值。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #value | 0 | 无 | #value >= 0 | 无 | 可变 
 */

typedef struct DDS_OwnershipStrengthQosPolicy
{
    /** @brief   指明权值，数值越大权值越高。 */
    DDS_Long value;
}DDS_OwnershipStrengthQosPolicy;

#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */

#endif /* OwnershipStrengthQosPolicy_h__*/
