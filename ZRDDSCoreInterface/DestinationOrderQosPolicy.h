/**
 * @file:       DestinationOrderQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DestinationOrderQosPolicy_h__
#define DestinationOrderQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS

/**
 * @enum DDS_DestinationOrderQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   标识样本顺序类型。
 */

typedef enum DDS_DestinationOrderQosPolicyKind
{
    /**  
     * @brief   以数据读者接收到的顺序存储在数据读者的内部队列中。
     *
     * @ingroup CoreQosStruct
     *
     * @details 默认情况下选择该类型。数据会被以接收到的顺序提交给数据读者，这可能会导致不同的数据读者以不同的样本顺序接收数据。
     *          例如同一个主题下的数据写者DW1与DW2以及数据读者DR1与DR2，相互匹配，以顺序DW1(1)、DW2(1)、DW1(2)、DW2(2)发布主题数据，
     *          在该QoS条件下，DR1与DR2可能的接收顺序包括：
     *          - DW1(1)、DW2(1)、DW1(2)、DW2(2)  
     *          - DW1(1)、DW2(1)、DW2(2)、DW1(2)  
     *          - DW1(1)、DW1(2)、DW2(1)、DW2(2)  
     *          - DW2(1)、DW1(1)、DW1(2)、DW2(2)  
     *          - DW2(1)、DW1(1)、DW2(2)、DW1(2)  
     *          - DW2(1)、DW2(2)、DW1(1)、DW1(2)  
     */
    DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, 

    /**  
     * @brief   以样本数据的源时间戳顺序存储在数据读者的内部队列中。
     *
     * @ingroup CoreQosStruct
     *
     * @details 当数据写者设置为此类型时，发布一个数据的时间戳必须不小于前一个发布的数据的时间戳，否则发布数据会失败。
     *          当数据读者设置为此类型时，数据读者只会接收发送时间戳比上一个收到的数据发送时间戳大的数据。
     *          其他数据会被拒绝，但是不会影响 DDS_SAMPLE_REJECTED_STATUS 状态。
     *          
     *          例如同一个主题下的数据写者DW1与DW2以及数据读者DR1与DR2，相互匹配，假设DW1与DW2使用统一的时间系统
     *          以顺序DW1(1)、DW2(1)、DW1(2)、DW2(2)发布主题数据，
     *          在该QoS条件下，DR1与DR2可能的接收顺序包括：
     *          - DW1(1)、DW2(1)、DW1(2)、DW2(2)
     *          - DW1(1)、DW2(1)、DW2(2)
     *          - DW1(1)、DW1(2)、DW2(2)
     *          - DW2(1)、DW2(2)
     *          
     *          未收到的样本被数据读者根据时间戳拒绝。
     */
    DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
}DDS_DestinationOrderQosPolicyKind;

/**
 * @struct DDS_DestinationOrderQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   样本顺序配置。
 *
 * @details 该QoS决定数据读者在接收来自不同的数据写者发送的数据时的接收顺序。
 *          相同主题下的数据写者（不同发布者、域参与者、节点）向ZRDDS系统发布数据时，由于链路之间的速度等因素，
 *          ZRDDS无法保证来自多个数据写者的数据样本之间的接收顺序与其发送顺序一致。当数据写者停止发送数据时，不同
 *          数据读者收到的最后一包数据可能会不相同。
 *          该Qos可以用于创建要求结果一致性的系统。同一主题下多个数据读者收到的数据顺序的中间状态可能不一致，
 *          但是当数据写者停止发送数据时，所有数据读者接收到的最后一个状态将会相同。
 *          每个数据样本有两个时间戳，一个发送时间戳（由发送端提供或者默认为所属节点的系统时间）
 *          和一个接收时间戳（由网络层提交给数据读者存储的时间）。
 *          
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS | 数据写者.#kind >= 数据读者.#kind | 无 | 无 | 不可变
 */

typedef struct DDS_DestinationOrderQosPolicy
{
    /** @brief   指明样本顺序类型。 */
    DDS_DestinationOrderQosPolicyKind kind;
}DDS_DestinationOrderQosPolicy;

#endif /* _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS */

#endif /* DestinationOrderQosPolicy_h__*/
