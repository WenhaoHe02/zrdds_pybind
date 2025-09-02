/**
 * @file:       PublishModeQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PublishModeQosPolicy_h__
#define PublishModeQosPolicy_h__

/**
 * @enum DDS_PublishModeQosPolicyKind
 *
 * @ingroup CoreQosStruct
 * 
 * @brief 定义数据写者的发送模式类型。
 */
typedef enum DDS_PublishModeQosPolicyKind
{
    /** @brief  同步发送模式。 @ingroup CoreQosStruct */
    DDS_SYNCHRONOUS_PUBLISH_MODE_QOS,
    /** @brief  异步发送模式。 @ingroup CoreQosStruct */
    DDS_ASYNCHRONOUS_PUBLISH_MODE_QOS
}DDS_PublishModeQosPolicyKind;

/**
 * @struct DDS_PublishModeQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 数据写者发布模式配置。
 *
 * @details 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_SYNCHRONOUS_PUBLISH_MODE_QOS | 无 | 无 | 无 | 不可变
 *
 */
typedef struct DDS_PublishModeQosPolicy
{
    /** @brief 数据写者的发送模式类型。 */
    DDS_PublishModeQosPolicyKind kind;
}DDS_PublishModeQosPolicy;

#endif /* PublishModeQosPolicy_h__*/
