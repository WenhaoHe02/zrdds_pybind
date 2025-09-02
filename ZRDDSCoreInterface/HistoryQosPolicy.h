/**
 * @file:       HistoryQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef HistoryQosPolicy_h__
#define HistoryQosPolicy_h__

#include "OsResource.h"

/**
 * @enum DDS_HistoryQosPolicyKind
 *
 * @ingroup CoreQosStruct 
 *
 * @brief   样本数据保存类型。
 */

typedef enum DDS_HistoryQosPolicyKind
{
    /**
     * @brief   保存最新样本数据类型。
     *
     * @ingroup CoreQosStruct
     *
     * @details 该类型为默认类型。这种情况下，ZRDDS会尝试为每个实例保存最新的样本，当样本的数量达到 DDS_HistoryQosPolicy::depth 限制时，
     *          ZRDDS 会用最新的样本覆盖最旧的样本，当实体设置为该类型时，不能保证绝对的可靠。
     *          
     *          设置为该类型的数据写者的可靠性表现如下：
     *          - 当队列中一个数据实例下样本的数量 达到 depth 值，该数据实例下新的样本会替换队列中该实例中最旧的样本；  
     *          - 此时如果被覆盖的数据样本未被匹配的数据读者接收，则会造成数据样本丢失，数据读者的样本丢失状态会被触发  
     *              （DataReaderListener::on_sample_lost 以及 DataReader::get_sample_lost_status获取状态）。
     *          
     *          设置为该类型的数据读者的可靠性表现如下：
     *          - 当队列中一个数据实例下样本的数量 达到 depth 值，该数据实例下新的样本会替换队列中该实例中最旧的样本；  
     *          - 此时如果被替换的样本未被用户通过 DataReader::read/take系列方法访问时，用户将会丢失被替换样本。
     */
    DDS_KEEP_LAST_HISTORY_QOS,

    /**
     * @brief   尝试保存所有样本数据类型。
     *
     * @ingroup CoreQosStruct
     *
     * @details 以上描述中使用“尝试”一词是因为实际保存的数量受限于 DDS_ResourceLimitsQosPolicy 否则设置为该保存类型
     *          将导致内存资源耗尽，设置为该类型时， DDS_HistoryQosPolicy::depth 成员无效。
     *          
     *          设置为该类型的数据写者的可靠性表现如下：
     *          - 当队列中一个数据实例下样本的数量 达到 DDS_ResourceLimitsQosPolicy::max_samples_per_instance 值 ；  
     *          - 如果最旧的数据样本已经被所有数据读者接收时，数据实例下新的样本会替换该实例在发送队列中最旧的样本。   
     *          - 如果实例下最旧的样本没有被所有数据读者接收时，尝试写入一个该数据实例下的新样本的 DataWriter::write   
     *              操作会产生阻塞（时间由 DDS_ReliabilityQosPolicy::max_blocking_time 决定）。
     *
     *          设置为该类型的数据读者的可靠性表现如下：
     *          - 当队列中一个数据实例下样本的数量 达到 DDS_ResourceLimitsQosPolicy::max_samples_per_instance值 ；  
     *          - 该新的数据样本将被拒绝，此时数据读者的样本拒绝状态会被触发
     *              （ DataReaderListener::on_sample_reject 以及 DataReader::get_sample_reject_status 获取状态）。
     *              此时需要用户通过DataReader::take 系列方法腾出存储存储空间，使得新的样本能够提交给用户，
     *              注意此时不会造成丢包，因为被拒绝的样本会通过重传等机制重新尝试提交给用户。
     */
    DDS_KEEP_ALL_HISTORY_QOS
}DDS_HistoryQosPolicyKind;

/**
 * @struct DDS_HistoryQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   历史数据数据实例队列配置。
 *
 * @details 该QoS策略配置了数据写者以及数据读者在本地存储的历史样本数量。该QoS作用于每一个数据实例。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_KEEP_LAST_HISTORY_QOS | 无 | 无 | 无 | 不可变
 *          #depth | 1 | 无 | #depth > 0 | #depth <= DDS_ResourceLimitsQosPolicy::max_samples_per_instance | 不可变
 *          
 * @see DDS_ReliabilityQosPolicy DDS_ResourceLimitsQosPolicy 
 */

typedef struct DDS_HistoryQosPolicy 
{
    /** @brief   数据实例队列类型类型配置。 */
    DDS_HistoryQosPolicyKind kind;
    /** @brief   当 #kind == ::DDS_KEEP_LAST_HISTORY_QOS 数据实例队列的最大长度。 */
    DDS_Long depth;
}DDS_HistoryQosPolicy;

#endif /* HistoryQosPolicy_h__*/
