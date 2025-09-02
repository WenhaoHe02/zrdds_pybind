/**
 * @file:       ResourceLimitsQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ResourceLimitsQosPolicy_h__
#define ResourceLimitsQosPolicy_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

/**
 * @struct DDS_ResourceLimitsQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   资源限制配置。
 *
 * @details 对于 DDS_HistoryQosPolicy::kind == #DDS_KEEP_ALL_HISTORY_QOS 的实体该 Qos 决定了实体内部（
 *          数据写者、数据读者）用于存储数据的资源使用量，若没有该限制，则ZRDDS可能会导致内存的无限增长，
 *          引发内存不足的系统异常。
 *           成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #max_samples | #LENGTH_UNLIMITED | 无 | #max_samples > 0 | #max_samples >= #max_samples_per_instance | 不可变
 *          #max_instances | #LENGTH_UNLIMITED | 无 | #max_instances > 0 | 无 | 不可变
 *          #max_samples_per_instance | #LENGTH_UNLIMITED | 无 | #max_samples_per_instance > 0 | DDS_HistoryQosPolicy::depth <= #max_samples_per_instance < #max_samples | 不可变
 *          #initial_samples | 1 | 无 | #initial_samples >= 0 | 无 | 不可变
 */

typedef struct DDS_ResourceLimitsQosPolicy
{
    /**   
     * @brief   所有数据实例下存储的数据样本的最大数量。 
     *
     * @details 在数据读者端，收到底层的数据样本后，将首先检查底层存储的所有样本个数是否达到该值，如果未达到，则将保存
     *          到数据读者的待存储区（由于还未进行样本顺序以及其他资源限制的检查，还不能通知用户来获取该数据），并反馈数据写者
     *          该数据样本已收到，当存储的样本个数已经达到该值，则取决于 DDS_ReliabilityQosPolicy::kind 以及 
     *          DDS_HistoryQosPolicy::kind 的配置，底层将采取不同的行为。
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_ALL_HISTORY_QOS   
     *              - 样本被拒绝（ #DDS_REJECTED_BY_SAMPLES_LIMIT ）并且会请求数据写者端重新发送该样本，取决于数据写者的QoS设置，该样本最终可能重新被发送以及  
     *                  被通知已经在数据写者端被移除，导致该样本丢失。
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_LAST_HISTORY_QOS 
     *              - 数据读者以数据实例的唯一标识大小顺序尝试清理可用的空间，只要样本未被用户租借出去（DataReader::read/take系列方法）
     *                  即满足清理条件，如果清理失败，则拒绝该样本（ #DDS_REJECTED_BY_SAMPLES_LIMIT ）；
     *          -# #DDS_BEST_EFFORT_RELIABILITY_QOS 与上一种情况相同的处理方式。
     */
    DDS_Long max_samples;

    /**   
     * @brief   所有数据实例的最大数量。 
     *
     * @details 在数据读者端，在存储待存储区的数据样本时，将首先检查底层存储的所有数据实例的个数是否达到该值并且待存储
     *          的样本是否是新的数据实例，如果不满足上述两个条件，则未达到该限制，继续下一步，如果满足以上两个条件，
     *          数据读者将尝试清理已经存在的数据实例，数据实例清理的条件：
     *          - 数据实例的状态为 #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE ；  
     *          - 数据实例下的数据样本数量为0；
     *          
     *          如果清理数据实例失败，则由于该限制，数据读者将通知用户该样本被拒绝（ #DDS_REJECTED_BY_INSTANCE_LIMIT ）以及丢失，且该样本不会通过重传获得。
     *          
     * @note    不采用与 #max_samples_per_instance 不足时的处理方式（等待有数据实例空间时再存储并通知用户）
     *          的原因在于，#max_samples_per_instance 限制可以由数据读者操作主动解除，如：调用 DataReader::take 
     *          方法，而解除 #max_instances 的限制，必须由数据写者端发出状态报文或者与某个数据实例有关的数据写者变为
     *          非存活状态，如果采用相同的处理方式，则在到达 #max_samples 之后，会导致状态报文被拒绝，而永远无法解除限制。
     */
    DDS_Long max_instances;

    /**   
     * @brief   单个数据实例下存储的最大样本个数。
     *
     * @details 该值只有在 DDS_HistoryQosPolicy::kind == #DDS_KEEP_ALL_HISTORY_QOS 时有效，否则该值被设置成
     *          DDS_HistoryQosPolicy::depth 的值。 取决于DDS_HistoryQosPolicy::kind 的配置，底层将采取不同的行为。
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_ALL_HISTORY_QOS
     *              - 样本被拒绝（ #DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT ），并将数据存储在待存储区，等待下一次的尝试存储并通知用户；
     *          -# #DDS_RELIABLE_RELIABILITY_QOS && #DDS_KEEP_LAST_HISTORY_QOS
     *              - 数据读者端将尝试清理可用的空间，优先清理该数据所属的数据实例下的数据样本，如果未清理成功，则
     *                  扩大清理范围到所有的数据实例（以数据实例的唯一标识大小顺序），只要样本未被用户租借出去（
     *                  DataReader::read/take系列方法）即满足清理条件，如果清理样本失败则采取与上一步相同的处理逻辑；
     */
    DDS_Long max_samples_per_instance;

    /**   
     * @brief   样本池中的最少样本数量。
     *
     * @details 在数据读者端使用，为优化接收性能，ZRDDS底层维护样本池，避免重复的创建、删除样本，该成员配置样本池中最少的个数，在归还
     *          数据样本时，当池中样本个数大于该值时，数据样本所占空间将归还给操作系统，否则该数据样本归还到样本池中。
     */
    DDS_Long initial_samples;
    /** @brief   保留字段。 */
    DDS_Long max_prealloc_sample_size;
}DDS_ResourceLimitsQosPolicy;

#endif /* ResourceLimitsQosPolicy_h__*/
