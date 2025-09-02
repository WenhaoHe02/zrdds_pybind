/**
 * @file:       TypeConsistencyEnforcementQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeConsistencyEnforcementQosPolicy_h__
#define TypeConsistencyEnforcementQosPolicy_h__

/**
 * @enum DDS_TypeConsistencyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义兼容的类型，用于从预先定义的策略中选取。
 */

typedef enum DDS_TypeConsistencyKind 
{
    /**  @brief 数据写者与数据读者必须支持相同的数据类型。 @ingroup CoreQosStruct */
    DDS_DISALLOW_TYPE_COERCION,
    /**  @brief 只需要满足数据读者的类型 >= 数据写者的类型即可。 @ingroup CoreQosStruct */
    DDS_ALLOW_TYPE_COERCION
}DDS_TypeConsistencyKind;

/**
 * @struct  DDS_TypeConsistencyEnforcementQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   发布订阅数据类型兼容规则配置。
 *   
 * @details 成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_ALLOW_TYPE_COERCION | 无 | 无 | 无 | 不可变 
 *          注意，默认的值虽为 #DDS_ALLOW_TYPE_COERCION ,然而，若远端的发现信息中没有该信息，则认为远端为 #DDS_DISALLOW_TYPE_COERCION 类型。
 *
 * @warning 该QoS暂未实现。
 */

typedef struct DDS_TypeConsistencyEnforcementQosPolicy 
{
    /** @brief   指明兼容类型。 */
    DDS_TypeConsistencyKind kind;
}DDS_TypeConsistencyEnforcementQosPolicy;

#endif /* TypeConsistencyEnforcementQosPolicy_h__*/
