/**
 * @file:       PresentationQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PresentationQosPolicy_h__
#define PresentationQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS

/**
 * @enum DDS_PresentationQosPolicyAccessScopeKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   表明数据展现控制域类型。
 */

typedef enum DDS_PresentationQosPolicyAccessScopeKind
{
    /** @brief  范围为数据实例，具体含义参见 DDS_PresentationQosPolicy @ingroup CoreQosStruct */
    DDS_INSTANCE_PRESENTATION_QOS,
    /** @brief  范围为主题，具体含义参见 DDS_PresentationQosPolicy @ingroup CoreQosStruct */
    DDS_TOPIC_PRESENTATION_QOS,
    /** @brief  范围为组，具体含义参见 DDS_PresentationQosPolicy @ingroup CoreQosStruct */
    DDS_GROUP_PRESENTATION_QOS
}DDS_PresentationQosPolicyAccessScopeKind;

/**
 * @struct DDS_PresentationQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据展示配置。
 *
 * @details 该QoS配置ZRDDS呈现接收到的数据给数据读者的方式，其中 #coherent_access 控制一致性访问，
 *          #ordered_access 控制按序访问，数据样本呈现给用户的顺序。
 *          “一致性集合”数据是指必须被一起提交用户的数据样本集合，只有在集合中所有的数据样本都存储到数据读者后，
 *          用户才能通过 DataReader::read/take 方法访问数据，且整个集合中的数据均会通过接口返回给用户。
 *          设置 #coherent_access = true 只有在数据读者和数据写者设置为可靠通信时才有效。
 *          发送程序使用 Publisher::begin_coherent_changes() 以及 Publisher::end_coherent_changes()
 *          发送一组连续的数据样本。此时 #access_scope 控制打包成一致性集合的数据样本的范围，包括：
 *          - #DDS_INSTANCE_PRESENTATION_QOS ，表明只有同一个数据写者以及属于一个数据实例的数据能够打包到一个一致性集合中，
 *          - #DDS_TOPIC_PRESENTATION_QOS ，表明同一个数据写者的数据可以打包到一个一致性集合中；
 *          
 *          按序访问是指用户通过 DataReader::read/take 方法访问数据样本时，ZRDDS返回结果时，数据样本的顺序：
 *          - #DDS_INSTANCE_PRESENTATION_QOS ，表明返回的顺序为按数据实例的顺序；
 *          - #DDS_TOPIC_PRESENTATION_QOS ，表明返回的顺序为按照主题的顺序；  
 *          例如：DW1分别发送数据实例1以及数据实例2下的数据样本，顺序为 data(1,1)、data(2,1)、data(1,2)、data(2,2)，
 *          其中括号内第一个数字表示数据实例的标识，第二个数字表示该数据实例下的样本编号，在数据读者端调用 DataReader::read/take
 *          的结果如下：
 *          - #DDS_INSTANCE_PRESENTATION_QOS ，data(1,1)、data(1,2)、data(2,1)、data(2,2)
 *          - #DDS_TOPIC_PRESENTATION_QOS ，data(1,1)、data(2,1)、data(1,2)、data(2,2)
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #access_scope | DDS_INSTANCE_PRESENTATION_QOS | 发布者.#access_scope >= 订阅端.#access_scope | 无 | 无 | 不可变 
 *          #coherent_access | false | 发布者.#coherent_access >= 订阅端.#coherent_access (true > false) | 无 | 无 | 不可变 
 *          #ordered_access | false | 发布者.#ordered_access >= 订阅端.#ordered_access (true > false) | 无 | 无 | 不可变 
 *
 * @warning 访问域为 #DDS_GROUP_PRESENTATION_QOS 类型的一致性访问以及按序访问均暂未实现。
 */

typedef struct DDS_PresentationQosPolicy
{
    /** @brief  控制访问的范围，#coherent_access 以及 #ordered_access 含义不同。 */
    DDS_PresentationQosPolicyAccessScopeKind access_scope;
    /** @brief 开启一致性访问。 */
    DDS_Boolean coherent_access;
    /** @brief 开启按序访问。 */
    DDS_Boolean ordered_access;
}DDS_PresentationQosPolicy;

#endif /* _ZRDDS_INCLUDE_PRESENTATION_QOS */

#endif /* PresentationQosPolicy_h__*/
