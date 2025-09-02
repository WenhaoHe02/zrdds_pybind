/**
 * @file:       DurabilityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DurabilityQosPolicy_h__
#define DurabilityQosPolicy_h__

#include "OsResource.h"

/**
 * @enum DDS_DurabilityQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据持久化类型。
 */

typedef enum DDS_DurabilityQosPolicyKind
{
    /**
     * @brief   无持久化。
     *
     * @ingroup CoreQosStruct
     *
     * @details 该类型为默认类型，数据写者设置为该类型表示该数据写者不存储已经发送完成（当前匹配的数据读者都收到）的数据样本，
     *          数据读者设置为该类型表示对于在该数据读者加入DDS网络之前的数据写者发布完成的历史数据不感兴趣。
     */
    DDS_VOLATILE_DURABILITY_QOS,

    /**
     * @brief   存活的数据写者在内存中持久化。
     *
     * @ingroup CoreQosStruct
     *
     * @details 数据写者设置为该类型表示该数据写者将在内存中存储已经发送完成（当前匹配的数据读者都收到），
     *          存储的数量受资源限制配置控制 DDS_ResourceLimitsQosPolicy ，在数据写者删除时，这些历史数据也会被同时删除。
     *          数据读者设置为该类型表示对于在该数据读者加入DDS网络之前且此时仍存活的数据写者发布完成的历史数据感兴趣。
     */
    DDS_TRANSIENT_LOCAL_DURABILITY_QOS,

    /**
     * @brief   所有数据写者（包括在数据读者加入DDS网络时已经被删除的数据写者）在内存中持久化。
     *
     * @ingroup CoreQosStruct
     *
     * @warning 该类型未实现。
     */
    DDS_TRANSIENT_DURABILITY_QOS,

    /**
     * @brief   所有数据写者（包括在数据读者加入DDS网络时已经被删除的数据写者）在持久化存储（文件、数据库）中持久化。
     *
     * @ingroup CoreQosStruct
     *
     * @warning 该类型未实现。
     */
    DDS_PERSISTENT_DURABILITY_QOS
}DDS_DurabilityQosPolicyKind;

/**
 * @struct DDS_DurabilityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   实体数据持久化配置。
 *
 * @details 在DDS通信模型中，数据写者和数据读者之间的连接关系解耦，即局域网中不存在匹配的数据读者，
 *          数据写者也可以发送数据。在数据读者加入DDS网络网前，与之匹配的数据写者可能已经发送了一定数量的样本，
 *          数据读者可能对这些“过时”而无法接收到的数据感兴趣。这种情况下，可以通过配置该QoS，
 *          使得数据读者可以在加入DDS网络通信时（创建并使能时）获取匹配的数据写者先前发送的“历史数据”。
 *          该QoS策略控制数据读者是否获取对应匹配的数据写者发送的“历史数据”以及数据的来源。
 *          数据读者可以通过设置该QoS来获取对应匹配的数据写者先前发送“历史数据”；
 *          在获取对应匹配的数据写者的“历史数据”的基础上，数据读者也可以通过设置该QoS来选择获取的来源，包括：
 *          - 数据读者只获取当前仍然存活的数据写者发送的“历史数据”；  
 *          - 数据读者获取发送端所有数据写者（包括已经被删除的数据写者）发送的“历史数据”。  
 *
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_VOLATILE_DURABILITY_QOS | 数据写者.#kind >= 数据读者.#kind | 无 | 无 | 不可变
 */

typedef struct DDS_DurabilityQosPolicy
{
    /** @brief   指明持久化类型，参见@ref DDS_DurabilityQosPolicyKind 。 */
    DDS_DurabilityQosPolicyKind kind;
}DDS_DurabilityQosPolicy;

#endif /* DurabilityQosPolicy_h__*/
