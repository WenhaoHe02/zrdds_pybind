/**
 * @file:       OwnershipQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef OwnershipQosPolicy_h__
#define OwnershipQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS

/**
 * @enum DDS_OwnershipQosPolicyKind
 *
 * @ingroup CoreQosStruct 
 *
 * @brief   指明数据实例所有权类型。
 */

typedef enum DDS_OwnershipQosPolicyKind
{
    /**
     * @brief   共享所有权类型。
     *
     * @ingroup CoreQosStruct
     * 
     * @details 默认为该类型，允许多个数据写者去更新同一个数据实例，即数据读者会通知用户所有匹配数据写者发布的数据。
     */
    DDS_SHARED_OWNERSHIP_QOS,

    /**
     * @brief   独占所有权类型。
     *
     * @ingroup CoreQosStruct
     * 
     * @details 设置为该类型表示每个数据实例只能被拥有该数据实例所有权的数据写者修改，即数据读者仅会通知用户该数据写者发布的数据。
     *          在数据读者端数据实例的所有权属于满足以下条件的数据写者：
     *          1. DDS_OwnershipStrengthQosPolicy::value 最大的数据写者；  
     *          2. 数据写者必须处于存活状态 DDS_LivelinessQosPolicy ；  
     *          3. 数据写者未违反 DDS_DeadlineQosPolicy ；  
     *          4. 数据读者收到该数据写者的数据；
     *          
     *          以下几个方面会导致所有权的变化：
     *          - 系统中具有更大 DDS_OwnershipStrengthQosPolicy::value 值的数据写者发布了该数据实例下的数据；  
     *          - 拥有该数据实例的数据写者的 DDS_OwnershipStrengthQosPolicy::value 值改变且不再为最大；  
     *          - 拥有该数据实例的数据写者的存活性发生了变化 DDS_LivelinessQosPolicy ；
     *              - 从alive变为not_alive时，该数据写者失去了拥有权；
     *              - 从not_alive变为alive时，并且重新发布了数据，该数据写者重新获取拥有权；
     *          - 拥有该数据实例的数据写者违反了 DDS_DeadlineQosPolicy 的约定；  
     *              - 当违反了截止时间约定时，该数据写者失去拥有权；
     */
    DDS_EXCLUSIVE_OWNERSHIP_QOS
}DDS_OwnershipQosPolicyKind;

/**
 * @struct DDS_OwnershipQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据实例所有权配置。
 *
 * @details 控制是否允许多个数据写者去更新同一个数据实例，与@ref DDS_OwnershipStrengthQosPolicy 
 *          常用于构建存在冗余节点的系统，用于热备容错。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_SHARED_OWNERSHIP_QOS | 数据写者.#kind == 数据读者.#kind | 无 | 无 | 不可变
 */

typedef struct DDS_OwnershipQosPolicy 
{
    /** @brief   指明数据实例的所有权类型。 */
    DDS_OwnershipQosPolicyKind kind;
}DDS_OwnershipQosPolicy;

#endif /* _ZRDDS_INCLUDE_OWNERSHIP_QOS */

#endif /* OwnershipQosPolicy_h__*/
