/**
 * @file:       Topic.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TOPIC_H)
#define _TOPIC_H

#include "DomainEntity.h"
#include "TopicDescription.h"
#include "TopicListener.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief	内置域参与者信息数据读者关联的主题名称。@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_PARTICIPANT_TOPIC_NAME;
/** @brief	内置数据写者者信息数据读者关联的主题名称。@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_PUBLICATION_TOPIC_NAME;
/** @brief	内置数据读者信息数据读者关联的主题名称。@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_SUBSCRIPTION_TOPIC_NAME;
#if defined(_ZRDDSSECURITY)
/** @brief	内置数据写者者信息数据读者关联的主题名称。@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_PUBLICATION_SECURE_TOPIC_NAME;
/** @brief	内置数据读者信息数据读者关联的主题名称。@ingroup   CoreVar */
DCPSDLL extern const Char* BUILTIN_SUBSCRIPTION_SECURE_TOPIC_NAME;
#endif // _ZRDDSSECURITY

#ifdef __cplusplus
}
#endif

/**
 * @class   Topic
 *
 * @ingroup CppTopic
 *
 * @brief   主题是发布订阅模型中数据基本的抽象。
 *          
 * @details 主题由主题名标识，主题名在域内唯一，并且通过关联的类型名称定义主题下数据的数据结构。
 *          数据写者与数据读者通过关联主题进行通信。
 */

class DCPSDLL Topic :
    virtual public DomainEntity,
    virtual public TopicDescription
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn  virtual ReturnCode_t set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief   从QoS仓库中获取主题QoS并将其设置到主题中
     *
     * @param   library_name    QoS库的名字，不允许为NULL。
     * @param   profile_name    QoS配置的名字，不允许为NULL。
     * @param   qos_name        QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return  当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */

    virtual ReturnCode_t set_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    /**
     * @fn  virtual ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus &status) = 0;
     *
     * @brief   获取该主题关联的 #DDS_INCONSISTENT_TOPIC_STATUS 状态.
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus &status) = 0;

    /**
     * @fn  virtual ReturnCode_t set_qos(const TopicQos &qoslist) = 0;
     *
     * @brief   设置主题实体的QoS。
     *
     * @details  可以使用特殊值 DDS::TOPIC_QOS_DEFAULT 。
     *
     * @param   qoslist 表示用户想要设置的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示 @e qoslist 含有无效的QoS配置；
     *          - #DDS_RETCODE_INCONSISTENT :表示 @e qoslist 含有不兼容的QoS配置；
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :表示用户尝试修改使能后不可变的QoS配置；
     *          - #DDS_RETCODE_ERROR :表示未归类的错误，错误详细信息输出在日志中；.
     */

    virtual ReturnCode_t set_qos(const TopicQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t get_qos(TopicQos &qoslist) = 0;
     *
     * @brief   获取该主题的QoS配置。
     *
     * @param [in,out]  qoslist 出口参数，用于保存该主题的的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_ERROR :表示失败，原因可能为复制QoS时发生错误。
     */

    virtual ReturnCode_t get_qos(TopicQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t set_listener(TopicListener *a_listener, StatusKindMask mask) = 0;
     *
     * @brief   设置该主题的的监听器。
     *
     * @details  本方法将覆盖原有监听器，如果设置空对象表示清除原先设置的监听器。
     *
     * @param [in,out]  a_listener  为该主题设置的监听器对象。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示设置成功。
     */

    virtual ReturnCode_t set_listener(TopicListener *a_listener, StatusKindMask mask) = 0;

    /**
     * @fn  virtual TopicListener* get_listener() = 0;
     *
     * @brief   该方法获取通过 #set_listener 方法或者创建时为主题设置的监听器对象。
     *
     * @return  当前可能的返回值：
     *          - NULL表示未设置监听器；
     *          - 非空表示应用通过 #set_listener 或者在创建时设置的监听器对象。
     */

    virtual TopicListener* get_listener() = 0;
protected:
    Topic(){}
    virtual ~Topic(){}
};

} // namespace DDS

#endif  //_TOPIC_H
