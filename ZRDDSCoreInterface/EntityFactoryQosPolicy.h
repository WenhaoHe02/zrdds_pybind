/**
 * @file:       EntityFactoryQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef EntityFactoryQosPolicy_h__
#define EntityFactoryQosPolicy_h__

#include "OsResource.h"

/**
 * @struct DDS_EntityFactoryQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   实体工厂配置。
 *
 * @details 当作为工厂创建其他实体的时候，是否自动使能其创建的实体，使能的详细规则参见 Entity::enable ,该QoS在
 *          设置监听器时设置为false，可以避免遗漏在创建域参与者之后设置内置数据读者的监听器之前的数据到达通知，
 *          遗漏的原因在于如果自动使能实体，则在实体创建完成后，可能已经收到了DDS网络中已经存在的实体内置信息，
 *          此时还未设置监听器，DDS将会忽略此内置数据的通知，设置的步骤参见用例 @ref CreateDisabledEntity.cpp 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #autoenable_created_entities | true | 无 | 无 | 无 | 可变
 */

typedef struct DDS_EntityFactoryQosPolicy
{
    /** @brief   控制是否自动使能子实体。 */
    DDS_Boolean autoenable_created_entities;
}DDS_EntityFactoryQosPolicy;

#endif /* EntityFactoryQosPolicy_h__ */
