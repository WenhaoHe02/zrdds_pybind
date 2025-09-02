/**
 * @file:       LivelinessQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef LivelinessQosPolicy_h__
#define LivelinessQosPolicy_h__

#include "OsResource.h"
#include "Duration_t.h"

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

/**
 * @enum DDS_LivelinessQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   指明数据写者声明存活性的类型。
 */

typedef enum DDS_LivelinessQosPolicyKind
{
    /**
     * @brief   由ZRDDS底层自动管理存活性声明。
     *
     * @ingroup CoreQosStruct
     *
     * @details 默认为该类型，ZRDDS内部负责自动地声明该类型数据写者，ZRDDS会至少以 DDS_LivelinessQosPolicy::lease_duration 
     *          的频率向其他域参与者声明该类数据写者的存活性，该设置是最方便的也是最不精确的声明数据写者存活性的方法。
     */
    DDS_AUTOMATIC_LIVELINESS_QOS,

    /**
     * @brief   通过域参与者手动管理存活性声明。
     *
     * @ingroup CoreQosStruct
     *
     * @details 假设数据写者设置该类型，则ZRDDS假设用户程序在 DDS_LivelinessQosPolicy::lease_duration 
     *          内声明了属于同一个域参与者下至少一个数据写者的存活性或域参与者自身的存活性，则该数据写者也是存活的。
     *          该设置允许用户代码通过声明同一个域参与者下任意一个数据写者或域参与者自身的存活性来代表整组数据写者的存活性的声明。
     */
    DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,

    /**
     * @brief   由数据写者手动管理存活性声明。
     *
     * @ingroup CoreQosStruct
     *
     * @details 只有用户程序明确的调用数据写者声明存活性的操作，该数据写者才会被认为是存活的。该设置强制用户程序声明
     *          数据写者的存活性，可以让用户程序更好地控制何时其他程序会认为数据写者变为不活跃的，但是会变得很不方便。
     */
    DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS
}DDS_LivelinessQosPolicyKind;

/**
 * @struct DDS_LivelinessQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据写者存活性声明与判定配置。
 *          
 * @details 该QoS用于数据读者判定数据写者是否存活，该QoS可与所有权配置 DDS_OwnershipQosPolicy 配合完成系统热备。
 *          - 手动声明数据写者存活性的方法：
 *              - 调用 DataWriter::write 系列方法 DataWriter::unregister_instance 系列方法   
 *                  DataWriter::dispose 系列方法；
 *              - 调用 DataWrite::assert_liveliness 方法。
 *          - 手动声明域参与者存活性的方法：
 *              - 调用 DomainParticipant::assert_liveliness 方法；  
 *          
 *          该QoS与实体状态 DDS_LivelinessChangedStatus 以及 DDS_LivelinessLostStatus 关联。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | #DDS_AUTOMATIC_LIVELINESS_QOS | 数据写者.#kind>=数据读者的.#kind  | 无 | 无 | 不可变
 *          #lease_duration | #INFINITE_DURATION | 数据写者.#lease_duration <= 数据读者.#lease_duration | #lease_duration > #ZERO_DURATION | 无 | 不可变 
 */

typedef struct DDS_LivelinessQosPolicy 
{
    /** @brief   指明数据写者声明存活性的类型。 */
    DDS_LivelinessQosPolicyKind kind;
    /**  
     * @brief   失活时间。 
     *
     * @details 对于数据写者以及数据读者的含义不同：
     *          - 对于数据写者来说该时间表示超过该时间段未声明存活就被认为非活动或者不存活；
     *          - 对于数据读者，该时间表明最大的时间段去检查匹配的数据写者的存活性。
     */
    DDS_Duration_t lease_duration;
}DDS_LivelinessQosPolicy;

#endif /* _ZRDDS_INCLUDE_LIVELINESS_QOS */

#endif /* LivelinessQosPolicy_h__*/
