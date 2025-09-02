/**
 * @file:       StatusKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_STATUSKIND_H)
#define _STATUSKIND_H

#include "ZROSDefine.h"

/**
 * @enum    DDS_StatusKind
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   位域定义实体状态类型。
 *
 * @details 为获取ZRDDS底层的通信状态以及特定的事件，ZRDDS实体（数据写者、数据读者、主题等）均会维护一系列状态以通知上层用户。
 *          状态的分类及其关联的接口如下：
 *          状态 | 关联的实体 | 监听器接口 | 查询接口 | 关联的QoS
 *          --- | --- | --- | --- | ---
 *          #DDS_INCONSISTENT_TOPIC_STATUS | 主题 | DDS::TopicListener::on_inconsistent_topic | DDS::Topic::get_inconsistent_topic_status | 无
 *          #DDS_OFFERED_DEADLINE_MISSED_STATUS | 数据写者 | DDS::DataWriterListener::on_offered_deadline_missed | DDS::DataWriter::get_offered_deadline_missed_status | DDS_DeadlineQosPolicy
 *          #DDS_OFFERED_INCOMPATIBLE_QOS_STATUS | 数据写者 | DDS::DataWriterListener::on_offered_incompatible_qos | DDS::DataWriter::get_offered_incompatible_qos_status | 无
 *          #DDS_LIVELINESS_LOST_STATUS | 数据写者 | DDS::DataWriterListener::on_liveliness_lost | DDS::DataWriter::get_liveliness_lost_status | DDS_LivelinessQosPolicy
 *          #DDS_PUBLICATION_MATCHED_STATUS | 数据写者 | DDS::DataWriterListener::on_publication_matched | DDS::DataWriter::get_publication_matched_status | 无
 *          #DDS_REQUESTED_DEADLINE_MISSED_STATUS | 数据读者 | DDS::DataReaderListener::on_requested_deadline_missed | DDS::DataReader::get_requested_deadline_missed_status | DDS_DeadlineQosPolicy
 *          #DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS | 数据读者 | DDS::DataReaderListener::on_requested_incompatible_qos | DDS::DataReader::get_requested_incompatible_qos_status | 无
 *          #DDS_SAMPLE_LOST_STATUS | 数据读者 | DDS::DataReaderListener::on_sample_lost | DDS::DataReader::get_sample_lost_status | DDS_HistoryQosPolicy DDS_ResourceLimitsQosPolicy
 *          #DDS_SAMPLE_REJECTED_STATUS | 数据读者 | DDS::DataReaderListener::on_sample_rejected | DDS::DataReader::get_sample_rejected_status | DDS_HistoryQosPolicy DDS_ResourceLimitsQosPolicy
 *          #DDS_LIVELINESS_CHANGED_STATUS | 数据读者 | DDS::DataReaderListener::on_liveliness_changed | DDS::DataReader::get_liveliness_changed_status | DDS_LivelinessQosPolicy
 *          #DDS_SUBSCRIPTION_MATCHED_STATUS | 数据读者 | DDS::DataReaderListener::on_subscription_matched | DDS::DataReader::get_subscription_matched_status | 无
 *
 *          获取数据读者的非数据状态（除 #DDS_DATA_AVAILABLE_STATUS ）的方式如下：
 *          1. 用户通过数据读者监听器并设置想要获取的状态的掩码来监听该状态，ZRDDS在检测到该状态变化时将通过监听器的相应方法回调用户。
 *          2. 用户通过主动调用数据读者的相应方法查询该状态。
 *          3. 同步等待该状态：
 *              -# 用户调用 DDS::DataReader::get_status_condition 获取关联的 DDS::StatusCondition ；
 *              -# 调用 DDS::StatusCondition::set_enabled_statuses (想要获取的状态的掩码)方法设置关心该状态；
 *              -# 调用 DDS::WaitSet::attach_condition 方法将步骤a中获取到的 DDS::StatusCondition 附加到一个
 *               DDS::WaitSet 对象上，并调用 DDS::WaitSet::wait 方法阻塞等待该状态的发生;
 *              -# ZRDDS在检测到该状态变化时将解开 DDS::WaitSet::wait 方法阻塞，此时用户通过方法2获取该状态。
 *
 *          获取数据写者的状态的方式如下：
 *          1. 用户通过数据写者监听器并设置想要获取的状态的掩码来监听该状态，ZRDDS在检测到该状态变化时将通过监听器的相应方法回调用户。
 *          2. 用户通过主动调用数据写者的相应方法查询该状态。
 *          3. 同步等待该状态：
 *              -# 用户调用 DDS::DataWriter::get_status_condition 获取关联的 DDS::StatusCondition ；
 *              -# 调用 DDS::StatusCondition::set_enabled_statuses (想要获取的状态的掩码)方法设置关心该状态；
 *              -# 调用 DDS::WaitSet::attach_condition 方法将步骤a中获取到的 DDS::StatusCondition 附加到一个
 *               DDS::WaitSet 对象上，并调用 DDS::WaitSet::wait 方法阻塞等待该状态的发生;
 *              -# ZRDDS在检测到该状态变化时将解开 DDS::WaitSet::wait 方法阻塞，此时用户通过方法2获取该状态。
 */

typedef enum DDS_StatusKind
{
    /** @brief 主题不匹配状态。 @ingroup CoreStatusStruct */
    DDS_INCONSISTENT_TOPIC_STATUS = 0x0001 << 0,
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /** @brief 数据写者截止时间未满足状态类型。 @ingroup CoreStatusStruct */
    DDS_OFFERED_DEADLINE_MISSED_STATUS = 0x0001 << 1,
    /** @brief 数据读者截止时间未满足状态类型。 @ingroup CoreStatusStruct */
    DDS_REQUESTED_DEADLINE_MISSED_STATUS = 0x0001 << 2,
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
    /** @brief 数据写者端QoS不匹配状态类型。 @ingroup CoreStatusStruct */
    DDS_OFFERED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 5,
    /** @brief 数据读者端QoS不匹配状态类型。 @ingroup CoreStatusStruct */
    DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS = 0x0001 << 6,
    /** @brief 数据样本丢失状态类型。 @ingroup CoreStatusStruct */
    DDS_SAMPLE_LOST_STATUS = 0x0001 << 7,
    /** @brief 数据样本拒绝状态类型。 @ingroup CoreStatusStruct */
    DDS_SAMPLE_REJECTED_STATUS = 0x0001 << 8,
    /** @brief 订阅者数据到达状态类型。 @ingroup CoreStatusStruct */
    DDS_DATA_ON_READERS_STATUS = 0x0001 << 9,
    /** @brief 数据读者数据到达状态类型。 @ingroup CoreStatusStruct */
    DDS_DATA_AVAILABLE_STATUS = 0x0001 << 10,
    /** @brief 数据写者存活性状态丢失状态。 @ingroup CoreStatusStruct */
    DDS_LIVELINESS_LOST_STATUS = 0x0001 << 11,
    /** @brief 数据写者存活性改变状态类型。 @ingroup CoreStatusStruct */
    DDS_LIVELINESS_CHANGED_STATUS = 0x0001 << 12,
    /** @brief 数据写者匹配状态类型。 @ingroup CoreStatusStruct */
    DDS_PUBLICATION_MATCHED_STATUS = 0x0001 << 13,
    /** @brief 数据读者匹配状态类型。 @ingroup CoreStatusStruct */
    DDS_SUBSCRIPTION_MATCHED_STATUS = 0x0001 << 14
}DDS_StatusKind;

#endif  /* _STATUSKIND_H*/
