/**
 * @file:       DataWriterMessageModeQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */


#ifndef DataWriterMessageModeQosPolicy_h__
#define DataWriterMessageModeQosPolicy_h__

#include "OsResource.h"

/**
 * @struct DDS_DataWriterMessageModeQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 提供控制DataWriter消息处理的功能。
 *
 * @details 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #without_timestamp | false | 无 | 无 | DDS_DataWriterQos::destination_order::kind == #DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS && ! #without_timestamp | 不可变
 *          #without_inlineQos | false | 无 | 无 | 无 | 不可变
 *          #disallow_message_coalesce | false | 无 | 无 | 无 | 不可变
 *          #message_header_coalesce | false | 无 | 无 | 无 | 不可变
 *          #enable_raw_transfer | false | 无 | 无 | 无 | 不可变
 *
 */
typedef struct DDS_DataWriterMessageModeQosPolicy
{
    /** @brief DataWriter发送的数据包是否包含时间戳。 */
    DDS_Boolean without_timestamp;
    /** @brief DataWriter发送的数据包是否包含InlineQos，注意：即使关闭了InlineQos，仍会包含一些必要的InlineQos。 */
    DDS_Boolean without_inlineQos;
    /** @brief DataWriter是否允许合并数据包。当发送Nack反馈时，DataWriter会尝试将多个小的数据包合并到同一个网络包中发送，若有特殊情况不允许合并，可以使用该QoS关闭此功能。 */
    DDS_Boolean disallow_message_coalesce;
    /** @brief DataWriter发送样本时，是否预留空间将子消息头（包含Timestamp）和用户数据写入同一块缓存。当使用零拷贝类型（ DDS_ZeroCopyBytes ）时会直接启用该选项。 */
    DDS_Boolean message_header_coalesce;
#ifdef _ZRDDS_ENABLE_RAW_TRANSFER
    /** @brief 启用无协议数据传输，当开启该选项时，传出的数据将不再包含RTPS数据头，从而减少构造数据头的开销。此时DataReader必须使用Raw地址配置（见 DDS_TransportConfigQosPolicy ）。
     *         若DataReader启用了Raw地址配置而DataWriter未启用该配置，会使得DataReader配置的Raw地址无效，若DataReader未配置其他地址将导致无法正常接收数据。
     *         同时启用该选项意味着放弃RTPS协议所提供的可靠传输功能，除传输信道可能造成的数据丢失外，若发送速度高于接收速度，可能在接收方出现数据覆盖的问题。 
     */
    DDS_Boolean enable_raw_transfer;
#endif // _ZRDDS_ENABLE_RAW_TRANSFER
}DDS_DataWriterMessageModeQosPolicy;

#endif /* DataWriterMessageModeQosPolicy_h__*/
