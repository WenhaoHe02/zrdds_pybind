/**
 * @file:       RapidIOConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef RapidIOConfigQosPolicy_h__
#define RapidIOConfigQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_RIO

/**
 * @struct DDS_RapidIOControllerConfig
 *
 * @ingroup CoreQosStruct
 *
 * @brief RapidIO控制器配置。
 */
typedef struct DDS_RapidIOControllerConfig
{
    /** @brief 该配置针对的控制器号。 */
    DDS_Long rapidio_controller;
    /** @brief RapidIO设备地址。 */
    DDS_ULong rapidio_address;
    /** @brief RapidIO接收缓存映射的物理基地址。 */
    DDS_ULong receive_window_base_address;
    /** @brief RapidIO接收窗大小，作为每次开窗的大小，最大可设为4MB。 */
    DDS_Long receive_window_size;
    /** @brief 接收子窗口大小  
     * 
     * @details 默认的子窗口大小，接收窗会被划分成若干该长度子窗口，每个子窗口被分配给一对域参与者用于RapidIO通信。
     *          当没有空闲的子窗口时，自动从上次申请窗的地址后面继续申请接收窗大小的窗；
     *          发送端可以设置域参与者的DDS_PropertyQosPolicy，告知接收端对于该域参与者所需分配的子窗口大小。
     */
    DDS_Long receive_subwindow_size;
    /** @brief RapidIO接收窗限制最大开窗个数，最大为8 */
    DDS_ULong receive_window_limit;
    /** @brief RapidIO设备地址最大限制。 */
    DDS_ULong rapidio_address_limit;
}DDS_RapidIOControllerConfig;

#ifdef __cplusplus
extern "C"
{
#endif

DDS_SEQUENCE_CPP(DDS_RapidIOControllerConfigSeq, DDS_RapidIOControllerConfig);

#ifdef __cplusplus
}
#endif

/**
 * @struct DDS_RapidIOConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief RapidIO配置QoS。
 *
 * @details
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #controllers_config | 空 | 无 | 无 | 无 | 不可变
 */
typedef struct DDS_RapidIOConfigQosPolicy
{
    /** @brief RapidIO控制器配置序列。 */
    DDS_RapidIOControllerConfigSeq controllers_config;
}DDS_RapidIOConfigQosPolicy;

#endif /* _ZRDDS_RIO */

#endif /* RapidIOConfigQosPolicy_h__ */
