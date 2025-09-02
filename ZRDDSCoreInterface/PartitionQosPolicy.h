/**
 * @file:       PartitionQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PartitionQosPolicy_h__
#define PartitionQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_PARTITION_QOS

/**
 * @struct DDS_PartitionQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   分区QoS配置。
 *
 * @details 在一个域内构成逻辑分区（通信平面的概念），由一个字符串序列组成，每个字符串表示一个分区的名称。名字中可以含有通配符，
 *          通配符 | 含义 | 举例
 *          --- | --- | ---
 *          * | 表示匹配0-多个字符； | a*bc 可以匹配 adddbc/abc等
 *          ? | 匹配单个任意字符； | a?bc 可以匹配 aabc a bc等
 *          [ ] | 表示匹配括号内单个字符 | a[a-z]bc 可以匹配 aabc azbc等
 *          [^] | 表示排除括号内单个字符 | a[^b-x]bc 可以匹配 aabc azbc等
 *
 *          该QoS的默认值是一个长度为0的列表，并且把该长度为0的列表看成是“包含一个空串元素的列表”。数据写者与数据读者
 *          匹配的条件如下：
 *          - 数据写者与数据读者所属的域参与者处于同一个域。
 *          - 数据写者与数据读者关联的主题名称以及主题关联的数据类型相同；
 *          - 数据写者与数据读者及其所属的发布者以及订阅者的QoS满足匹配规则；
 *          - 数据写者和数据读者及其所属的工厂没有调用 ignore 方法忽略对端；
 *          - 数据写者所属的发布者与数据读者所属的订阅者至少有一个分区名称匹配，分区匹配的规则如下：
 *              - 字符串相等的分区名称匹配；  
 *              - 两个均含有通配符的分区名称不匹配；  
 *              - 两个长度为0的序列认为是匹配的；  
 *              - 长度为0的序列与分区名称""匹配；  
 *              - 通配符匹配；
 *          
 *          该QoS与域隔离的主要区别：
 *          - 不同域完全隔离，连DDS本身都不知道其他域的信息。
 *          - 实体只能属于一个域，但是可以属于多个分区。
 *          - 不同域内的实体不能引用同一个数据实例，但是同一个数据实例可以在一个或者多个分区中发布或者订阅。
 *          使用场景：
 *          - 基于地理位置的分区：在交通管制系统中存在一系列的主题：TrafficAlert、AccidentReport、CongestionStatus。  
 *              应用程序可能需要控制主题的可见性基于实际上那些信息应用的地理位置，此时发布者可以利用地理位置构造分区名称例如
 *              /USA/California/Santa Clara，订阅者可以选择看哪些城市的信息例如/USA/California/ *表示接收整个加利福尼亚的数据。
 *          - 基于访问控制组的分区：发布者的分区名称代表哪些组可以访问自身数据，订阅者分区名称代表自己属于哪些组。
 *          - 基于目的的分区：假设应用程序包含用于多种目的的子系统，例如训练、模拟、真实使用。可以很方面的从模拟子系统转化到真实子系统。  
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #name | 长度为0的序列 | 无 | 无 | 无 | 可变
 *
 * @note    由于该QoS导致不能匹配不认为是不兼容的QoS，不触发 DDS_OfferedIncompatibleQosStatus 或者 
 *          DDS_RequestedIncompatibleQosStatus 状态。
 */

typedef struct DDS_PartitionQosPolicy
{
    /** @brief   字符串序列。 */
    DDS_StringSeq name;
}DDS_PartitionQosPolicy;

#endif /* _ZRDDS_INCLUDE_PARTITION_QOS */

#endif /* PartitionQosPolicy_h__*/
