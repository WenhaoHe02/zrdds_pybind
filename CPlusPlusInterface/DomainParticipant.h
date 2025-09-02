/**
 * @file:       DomainParticipant.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINPARTICIPANT_H)
#define _DOMAINPARTICIPANT_H

#include "Entity.h"
#include "Publisher.h"
#include "Subscriber.h"
#include "ContentFilteredTopic.h"
#include "MultiTopic.h"
#include "DomainParticipantListener.h"
#include "ZRDDSCppWrapper.h"
#include "TypeSupport.h"

namespace DDS {

/**
 * @class   DomainParticipant
 *
 * @ingroup CppDomain
 *
 * @brief   该类抽象域参与者实体。
 *      
 * @details 域参与者主要提供以下接口功能：
 *          - 实体功能；  
 *          - 作为其他实体工厂；  
 *              - 作为发布者实体工厂；  
 *              - 作为订阅者实体工厂；  
 *              - 作为主题实体工厂；
 *          - 内置实体管理；  
 *          - 通信管理；  
 *          - 域信息查询；  
 *          - 存活性管理；
 */

class DCPSDLL DomainParticipant : public Entity
{
public:

#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual Subscriber* DomainParticipant::lookup_subscriber_by_name( const Char* name)=0;
     *
     * @brief 按名字精确查找Subscriber
     *
     * @param name The name
     *
     * @return null if it fails, else a Subscriber*
     */
    virtual Subscriber* lookup_subscriber_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual Publisher* DomainParticipant::lookup_publisher_by_name( const Char* name)=0;
     *
     * @brief 按名字精确查找Publisher
     *
     * @param name The name
     *
     * @return null if it fails, else a Publisher*
     */
    virtual Publisher* lookup_publisher_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual Topic* DomainParticipant::lookup_topic_by_name( const Char* name) = 0;
     *
     * @brief 按名字精确查找Topic
     *
     * @param name The name
     *
     * @return null if it fails, else a Topic*
     */
    virtual Topic* lookup_topic_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::register_type_from_type_library( const Char* type_name, const Char* registered_name) = 0;
     *
     * @brief 从TypeLibrary注册类型。
     *
     * @param type_name       类型库中的类型名称。
     * @param registered_name 类型被注册的名称，该名称用于创建主题时引用类型。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示注册成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示添加失败。
     */
    virtual ReturnCode_t register_type_from_type_library(
        const Char* type_name,
        const Char* registered_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::unregister_type_from_type_library( const Char* registered_name) = 0;
     *
     * @brief 注销指定的数据类型。
     *
     * @param registered_name 待注销类型的名称，对应注册时的名称。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示注册成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :指定类型未注册；
     *          - #DDS_RETCODE_ERROR :表示添加失败。
     */
    virtual ReturnCode_t unregister_type_from_type_library(
        const Char* registered_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::register_type_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML字符串注册类型。
     *
     * @details 此处只能指定类型引用而不能定义类型，被引用的类型必须已经存在于类型库中
     *
     * @param xml_content 以XML字符串表示的类型。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示注册成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示注册失败，可能为指定的类型不存在。
     */
    virtual ReturnCode_t register_type_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::lookup_named_publishers( const Char* pattern, StringSeq& publisher_names) = 0;
     *
     * @brief 查找名称符合pattern限定的发布者。
     *
     * @param pattern                  查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param [in,out] publisher_names 查找得到的发布者名字列表
     *
     * @return 当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示查找成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_named_publishers(
        const Char* pattern, StringSeq& publisher_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::lookup_named_subscribers( const Char* pattern, StringSeq& subscriber_names) = 0;
     *
     * @brief 查找名称符合pattern限定的订阅者。
     *
     * @param pattern                   查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param [in,out] subscriber_names 查找得到的订阅者名字列表
     *
     * @return 当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示查找成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_named_subscribers(
        const Char* pattern, StringSeq& subscriber_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::lookup_named_topics( const Char* pattern, StringSeq& topic_names) = 0;
     *
     * @brief 查找名称符合pattern限定的主题。
     *
     * @param pattern              查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param [in,out] topic_names 查找得到的主题名字列表
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示查找成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_named_topics(
        const Char* pattern, StringSeq& topic_names) = 0;

    /**
     * @fn virtual Publisher* DomainParticipant::create_publisher_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML字符串创建发布者。
     *
     * @details 其中的DataWriterQos的UserData、PublisherQos的GroupData可以支持使用String方式和Sequence方式设置
     *          - String方式为将字符串直接作为value节点的text
     *          - Sequence方式为将value当成Sequence使用（即设置其sequenceMaxLength属性），并将每个元素作为item写入
     *
     * @param xml_content 以XML字符串表示的发布者。
     *
     * @return 创建成功指向创建成功的发布者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - QoS有无效值或者含有不一致的QoS。
     */
    virtual Publisher* create_publisher_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual Subscriber* DomainParticipant::create_subscriber_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML字符串创建订阅者。
     *
     * @details 其中的DataReaderQos的UserData、SubscriberQos的GroupData可以支持使用String方式和Sequence方式设置
     *          - String方式为将字符串直接作为value节点的text
     *          - Sequence方式为将value当成Sequence使用（即设置其sequenceMaxLength属性），并将每个元素作为item写入
     *
     * @param xml_content 以XML字符串表示的订阅者。
     *
     * @return 创建成功指向创建成功的订阅者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - QoS有无效值或者含有不一致的QoS。
     */
    virtual Subscriber* create_subscriber_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual Topic* DomainParticipant::create_topic_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML字符串创建主题。
     *
     * @details 其中的 #TopicQos::topic_data 可以支持使用String方式和Sequence方式设置
     *          - String方式为将字符串直接作为value节点的text
     *          - Sequence方式为将value当成Sequence使用（即设置其sequenceMaxLength属性），并将每个元素作为item写入
     *
     * @param xml_content 以XML字符串表示的主题。
     *
     * @return 创建成功指向创建成功的订阅者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - QoS有无效值或者含有不一致的QoS。
     */
    virtual Topic* create_topic_from_xml_string(
        const Char* xml_content) = 0;
#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE
    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取QoS配置并设置到域参与者
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_default_topic_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取主题QoS并将其设为默认主题QoS
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_default_topic_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_default_publisher_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取发布者QoS并将其设为默认发布者QoS
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_default_publisher_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipant::set_default_subscriber_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取订阅者QoS并将其设为默认订阅者QoS
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_default_subscriber_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual Publisher* DomainParticipant::create_publisher_with_qos_profile( const Char* library_name, const Char* profile_name, const Char* qos_name, PublisherListener* listener, StatusKindMask mask) = 0;
     *
     * @brief 从QoS仓库中获取发布者QoS并用其创建发布者。
     *
     * @param library_name  QoS库的名字，不允许为NULL。
     * @param profile_name  QoS配置的名字，不允许为NULL。
     * @param qos_name      QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in] listener 为该发布者设置的监听器。
     * @param mask          设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return 创建成功指向创建成功的发布者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - 未找到指定的QoS等。
     */
    virtual Publisher* create_publisher_with_qos_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        PublisherListener* listener,
        StatusKindMask mask) = 0;

    /**
     * @fn virtual Subscriber* DomainParticipant::create_subscriber_with_qos_profile( const Char* library_name, const Char* profile_name, const Char* qos_name, SubscriberListener* listener, StatusKindMask mask) = 0;
     *
     * @brief 从QoS仓库中获取订阅者QoS并用其创建订阅者
     *
     * @param library_name  QoS库的名字，不允许为NULL。
     * @param profile_name  QoS配置的名字，不允许为NULL。
     * @param qos_name      QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in] listener 为该订阅者设置的监听器。
     * @param mask          设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return 创建成功指向创建成功的订阅者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - 未找到指定的QoS等。
     */
    virtual Subscriber* create_subscriber_with_qos_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        SubscriberListener* listener,
        StatusKindMask mask) = 0;

    /**
     * @fn virtual Topic* DomainParticipant::create_topic_with_qos_profile( const Char* topic_name, const Char* type_name, const Char* library_name, const Char* profile_name, const Char* qos_name, TopicListener* listener, StatusKindMask mask) = 0;
     *
     * @brief 从QoS仓库中获取主题QoS并用其创建主题。
     *
     * @param topic_name    主题的名称。
     * @param type_name     关联的类型名称。
     * @param library_name  QoS库的名字，不允许为NULL。
     * @param profile_name  QoS配置的名字，不允许为NULL。
     * @param qos_name      QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in] listener 为该主题设置的监听器。
     * @param mask          设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return 创建成功指向创建成功的主题实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - 未找到指定的QoS等。
     */
    virtual Topic* create_topic_with_qos_profile(
        const Char* topic_name,
        const Char* type_name,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        TopicListener* listener,
        StatusKindMask mask) = 0;

#ifdef _ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB

    /**
     * @fn  virtual DataWriter* DomainParticipant::create_datawriter_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataWriterListener *dw_listener, StatusKindMask mask) = 0;
     *
     * @brief   利用自动创建的用户发布者，创建指定主题名称的数据写者，当主题名称关联的主题未创建时，将自动创建，
     *          否则将利用已经创建的主题创建数据写者，调用该函数等价于 get_auto_created_publisher()->create_datawriter_with_topic_and_qos_profile 。
     *
     * @param   topicName           数据写者关联的主题名称。
     * @param [in,out]  typeSupport 数据写者关联的数据类型的类型支持单例，例如零拷贝类型： ZeroCopyBytesTypeSupport::get_instance() 。
     * @param   library_name        QoS库的名字，不允许为NULL。
     * @param   profile_name        QoS配置的名字，不允许为NULL。
     * @param   qos_name            QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in,out]  dw_listener 数据写者的监听器。
     * @param   mask                监听器掩码。
     *
     * @return  NULL表示失败，否则返回数据写者指针。
     */

    virtual DataWriter* create_datawriter_with_topic_and_qos_profile(
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataWriterListener *dw_listener,
        StatusKindMask mask) = 0;

    /**
     * @fn  virtual DataReader* DomainParticipant::create_datareader_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataReaderListener *dr_listener, StatusKindMask mask) = 0;
     *
     * @brief   利用自动创建的用户订阅者，创建指定主题名称的数据读者，当主题名称关联的主题未创建时，
     *          将自动创建，否则将利用已经创建的主题创建数据读者。调用该函数等价于 get_auto_created_subscriber()->create_datareader_with_topic_and_qos_profile 。
     *
     * @param   topicName           数据读者关联的主题名称。
     * @param [in,out]  typeSupport 数据读者关联的数据类型的类型支持单例，例如零拷贝类型： ZeroCopyBytesTypeSupport::get_instance() 。
     * @param   library_name        QoS库的名字，不允许为NULL。
     * @param   profile_name        QoS配置的名字，不允许为NULL。
     * @param   qos_name            QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in,out]  dr_listener 数据读者的监听器。
     * @param   mask                监听器掩码。
     *
     * @return  NULL表示失败，否则返回数据读者指针。
     */

    virtual DataReader* create_datareader_with_topic_and_qos_profile(
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataReaderListener *dr_listener,
        StatusKindMask mask) = 0;

#endif //_ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

#ifdef _ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB

    /**
     * @fn  virtual Publisher* DomainParticipant::get_auto_created_publisher() = 0;
     *
     * @brief   为简化用户操作，域参与者创建时将使用默认QoS自动创建用户使用的发布者，该接口为获取该自动创建的发布者。
     *
     * @return  成功返回自动创建的发布者指针，失败返回NULL。
     */

    virtual Publisher* get_auto_created_publisher() = 0;

    /**
     * @fn  virtual Subscriber* DomainParticipant::get_auto_created_subscriber() = 0;
     *
     * @brief   为简化用户操作，域参与者创建时将使用默认QoS自动创建用户使用的订阅者，该接口为获取该自动创建的订阅者，
     *          自动创建的订阅者与内置订阅者不同，内置订阅者用于管理内置的Reader实体，用于发现过程。
     *
     * @return  成功返回自动创建的订阅者指针，失败返回NULL。
     */

    virtual Subscriber* get_auto_created_subscriber() = 0;

#endif //_ZRDDS_INCLUDE_AUTO_CREATED_PUB_SUB
    /**
     * @fn  virtual Subscriber* DomainParticipant::get_builtin_subscriber() = 0;
     *
     * @brief   获取用户实体发现的内置订阅者。
     *          
     * @details 内置实体是指负责DDS中间件内部数据交互（发现信息、存活性信息）的主题、数据写者以及数据读者。
     *          为了能够获取“发现信息”，域参与者提供访问内部订阅者的接口，用户再通过该内置订阅者的功能获取想要的发现信息，
     *          内置实体由域参与者自动创建，并通过该接口配合 DDS::Subscriber::lookup_datareader 接口获取内置的
     *          数据读者，使用内置的数据读者除了其生命周期与用户自定义数据读者不同之外，其他操作与用户自定义数据读者一致。
     *          提供给用户使用的内置数据读者及其关联的主题名称及其关联的数据类型参见下表：
     *          内置数据读者 | 主题名称 | 数据类型
     *          --- | --- | ---
     *          DDS::ParticipantBuiltinTopicDataDataReader | #BUILTIN_PARTICIPANT_TOPIC_NAME | DDS_ParticipantBuiltinTopicData
     *          DDS::PublicationBuiltinTopicDataDataReader | #BUILTIN_PUBLICATION_TOPIC_NAME | DDS_PublicationBuiltinTopicData
     *          DDS::SubscriptionBuiltinTopicDataDataReader | #BUILTIN_SUBSCRIPTION_TOPIC_NAME | DDS_SubscriptionBuiltinTopicData
     *          获取到的内置实体不应该删除，否则造成系统异常，具体使用的例子参见 @ref SetBuiltinListenerExample.cpp 。
     *
     * @return  内置订阅者的指针，ZRDDS的实现中，只要域参与者未被删除，那么返回值一定有效。
     */

    virtual Subscriber* get_builtin_subscriber() = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_participants(InstanceHandleSeq &discoved_handleList) = 0;
     *
     * @brief   获取该域参与者发现的远程（逻辑上，也有可能在同一个节点，甚至在同一个应用程序中）域参与者的标识列表。
     *
     * @details 在ZRDDS中，当域参与者使能后，会通过发现协议自动感知同一个域下的域参与者，并与之交换当前实体的信息，
     *          以建立发布/订阅关系。域参与者发现远程域参与者的条件包括：
     *          - 两者在同一个域内；  
     *          - 未调用 #ignore_participant 手动忽略远程域参与者；
     *          
     *          用户可以通过两种方式获取当前域参与者已经发现的其他域参与者信息：
     *          - 同步方式，用户在需要该信息时按如下步骤获取：    
     *              - 用户调用本接口获取发现的域参与者标识；  
     *              - 调用 #get_discovered_participant_data 通过上一步中获取的标识查看远程域参与者的详细信息；
     *          - 异步回调方式  
     *              - 通过设置内置数据读者（ DDS::ParticipantBuiltinTopicDataDataReader ）的监听器。  
     *              - 在监听器中获取发现远程域参与者的详细信息；
     *          同步方式优点在于比较简单，缺点在于不同及时的获取最新的状态，或者说想要获取及时的状态的代价较高（
     *          通过高频率的轮询）。
     *          异步回调方式，使用相对复杂，但能够及时的获取最新的发现状态。
     *
     * @param [in,out]  discoved_handleList 出口参数，用于存储已发现的域参与者标识，当用户提供的空间不足时，
     *                  底层将尝试对序列进行扩容。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；  
     *          - #DDS_RETCODE_NOT_ENABLED :当前域参与者未使能；
     *          - #DDS_RETCODE_ERROR :获取失败，扩容失败；
     *
     * @see get_discovered_participant_data
     */

    virtual ReturnCode_t get_discovered_participants(InstanceHandleSeq &discoved_handleList) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_participant_data( ParticipantBuiltinTopicData &a_pd, const InstanceHandle_t& a_handle) = 0;
     *
     * @brief   该方法查询指定标识的域参与者的详细信息。
     *
     * @param [in,out]  a_pd    出口参数，用于存储获取到的详细信息。
     * @param   a_handle        指明域参与者的唯一标识，该标识可以从以下几个地方获取：
     *                          - #get_discovered_participants   
     *                          - 内置数据读者中读取出来的内置数据样本中的 DDS_ParticipantBuiltinTopicData::_key   
     *                              或者 DDS_SampleInfo::instance_handle
     *                          - 远程域参与者的 #get_instance_handle 方法的结果；
     *
     * @return  - #DDS_RETCODE_OK :表示出口参数中的详细信息有效，即获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :该域参与者未使能；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :提供的标识无效；  
     *          - #DDS_RETCODE_ERROR :表示获取失败，例如拷贝内置数据失败；
     *
     * @see get_discovered_participants
     */

    virtual ReturnCode_t get_discovered_participant_data(
        ParticipantBuiltinTopicData &a_pd, 
        const InstanceHandle_t& a_handle) = 0;

    /**
     * @fn  virtual DomainId_t DomainParticipant::get_domain_id() = 0;
     *
     * @brief   获取该域参与者所属的域。
     *
     * @return  域参与者所属域值。
     */

    virtual DomainId_t get_domain_id() = 0;

    /**
     * @fn  virtual DomainParticipantListener* DomainParticipant::get_listener() = 0;
     *
     * @brief   该方法获取通过 #set_listener 方法或者创建时为域参与者设置的监听器对象。
     *
     * @return  当前可能的返回值：
     *          - NULL表示未设置监听器；
     *          - 非空表示应用通过 #set_listener 或者在创建时设置的监听器对象。
     */

    virtual DomainParticipantListener* get_listener() = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_qos(DomainParticipantQos &qoslist) = 0;
     *
     * @brief   获取该域参与者的QoS配置。
     *
     * @param [in,out]  qoslist 出口参数，用于保存域参与者的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_ERROR :表示失败，原因可能为复制QoS时发生错误。
     */

    virtual ReturnCode_t get_qos(DomainParticipantQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_participant(const InstanceHandle_t &handle) = 0;
     *
     * @brief   该方法用于忽略指定的域参与者，即如同未发现该域参与者，忽略该域参与者下的所有订阅、发布信息。
     *
     * @details 通信管理功能的常见使用场景为访问控制，即通过域参与者详细信息判断该域参与者或者数据写者、数据读者是否具备
     *          相应的权限（例如：域参与者携带的数据是否满足要求），如果已经发现了指定域参与者，则将解开与该域参与者的匹配。
     *
     * @param   handle  用户标识远端的域参与者，来源参见 #get_discovered_participant_data 。
     *
     * @return  是否忽略成功。
     */

    virtual ReturnCode_t ignore_participant(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_listener( DomainParticipantListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   设置该域参与者的监听器。
     *
     * @details  本方法将覆盖原有监听器，如果设置空对象表示清除原先设置的监听器。
     *
     * @param [in,out]  a_listener  为该域参与者设置的监听器对象。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示设置成功。
     */

    virtual ReturnCode_t set_listener(
        DomainParticipantListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_qos(const DomainParticipantQos& qoslist) = 0;
     *
     * @brief   该方法设置为域参与者设置的QoS。
     *
     * @param   qoslist 表示用户想要设置的QoS配置。
     *
     * @details 可以使用特殊值 DDS::DOMAINPARTICIPANT_QOS_DEFAULT 表示使用存储在域参与者工厂中的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示 @e qoslist 含有无效的QoS配置；
     *          - #DDS_RETCODE_INCONSISTENT :表示 @e qoslist 含有不兼容的QoS配置；
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :表示用户尝试修改使能后不可变的QoS配置；
     *          - #DDS_RETCODE_ERROR :表示未归类的错误，错误详细信息输出在日志中；
     */

    virtual ReturnCode_t set_qos(const DomainParticipantQos& qoslist) = 0;

    /**
     * @fn  virtual Publisher* DomainParticipant::create_publisher( const PublisherQos &qoslist, PublisherListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   该方法在域参与者下创建一个发布者子实体，并设置QoS以及监听器，表明应用想要向该域内发布数据。
     *
     * @param   qoslist             表示为该发布者设置的QoS，#PUBLISHER_QOS_DEFAULT 表明使用该域参与者中保存的默认的QoS。
     * @param [in,out]  a_listener  为该发布者设置的监听器。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  创建成功指向创建成功的发布者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - @e qoslist 含有无效值或者含有不一致的QoS。
     */

    virtual Publisher* create_publisher(
        const PublisherQos &qoslist,
        PublisherListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_publisher(Publisher *a_pub) = 0;
     *
     * @brief   删除指定的发布者实体。
     *
     * @param [in,out]  a_pub   指定的发布者。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_BAD_PARAMETER :表示传入的参数无效，即无效的发布者指针； 
     *              - 有效的发布者指针，但是不属于该域参与者创建出来的。
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :  
     *              - 表示该发布者不满足删除条件，及还有子实体数据写者未删除；  
     *              - 传入的发布者不由该域参与者创建。
     *          - #DDS_RETCODE_OK ：表示删除成功；  
     *          - #DDS_RETCODE_ERROR ：未归类的错误，详细信息参见日志。
     */

    virtual ReturnCode_t delete_publisher(Publisher *a_pub) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_publishers( PublisherSeq &publisherList) = 0;
     *
     * @brief   获取当前未被删除的由该域参与者创建的发布者列表。
     *
     * @param [in,out]  publisherList   出口参数，用于填充发布者实体对象。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :出口参数有效，表示获取成功；  
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ：表示用户提供的空间不足且扩容失败；
     */

    virtual ReturnCode_t get_publishers(
        PublisherSeq &publisherList) = 0;

    /**
     * @fn  virtual Subscriber* DomainParticipant::create_subscriber( const SubscriberQos &qoslist, SubscriberListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   该方法在域参与者下创建一个订阅者子实体，并设置QoS以及监听器，表明应用想要向该域内订阅数据。
     *
     * @param   qoslist             表示为该订阅者设置的QoS，#SUBSCRIBER_QOS_DEFAULT 表明使用该域参与者中保存的默认的QoS。
     * @param [in,out]  a_listener  为该订阅者设置的监听器。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  创建成功指向创建成功的订阅者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；
     *          - @e qoslist 含有无效值或者含有不一致的QoS。
     */

    virtual Subscriber* create_subscriber(
        const SubscriberQos &qoslist,
        SubscriberListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_subscriber(Subscriber *a_sub) = 0;
     *
     * @brief   删除指定的订阅者实体。
     *
     * @param [in,out]  a_sub   指定的订阅者。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_BAD_PARAMETER :表示传入的参数无效，即无效的发布者指针；
     *              - 有效的订阅者指针，但是不属于该域参与者创建出来的。
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :
     *              - 表示该订阅者不满足删除条件，及还有子实体数据读者未删除；
     *              - 传入的订阅者不由该域参与者创建。
     *          - #DDS_RETCODE_OK ：表示删除成功；
     *          - #DDS_RETCODE_ERROR ：未归类的错误，详细信息参见日志。
     */

    virtual ReturnCode_t delete_subscriber(Subscriber *a_sub) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_subscribers( SubscriberSeq &subscriberList) = 0;
     *
     * @brief   获取当前未被删除的由该域参与者创建的订阅者列表。
     *
     * @param [in,out]  subscriberList   出口参数，用于填充订阅者实体对象。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :出口参数有效，表示获取成功；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ：表示用户提供的空间不足且扩容失败；
     */

    virtual ReturnCode_t get_subscribers(
        SubscriberSeq &subscriberList) = 0;

    /**
     * @fn  virtual Topic* DomainParticipant::create_topic( const Char* topic_name, const Char* type_name, const TopicQos &qoslist, TopicListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   该方法在域参与者下创建一个主题子实体，并设置域内唯一的名称、关联的数据类型、QoS以及监听器，用于抽象域内的数据。
     *
     * @param   topic_name          新创建的主题的名称，保证本域参与者者内唯一。
     * @param   type_name           新创建的主题关联的类型的名称，该类型名称必须是向该域参与者注册的类型名称（
     *                              注意区分注册的名称以及类型本身的名称），注册的方法为使用编译器生成的支持接口 
     *                              DDS::FooTypeSupport::get_instance().register_type 。
     * @param   qoslist             新创建的主题的QoS配置。
     * @param [in,out]  a_listener  主题消息回调接口。
     * @param   mask                回调消息类型掩码。
     *
     * @return  创建成功则指向创建成功的主题对象，否则返回NULL，原因可能如下：
     *          - 分配空间失败；  
     *          - 传入的参数非法（ @e topic_name == NULL @e type_name == NULL）；  
     *          - 传入的QoS含有无效值或者QoS中含有不一致的配置；  
     *          - 传入的参数未注册；  
     *          - 该域参与者中已有相同主题名的主题；  
     *          - 未归类错误，详细参见日志；
     */

    virtual Topic* create_topic(
        const Char* topic_name,
        const Char* type_name,
        const TopicQos &qoslist,
        TopicListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual Topic* DomainParticipant::create_topic_w_type_support( const Char* topic_name, TypeSupport* type_support, const TopicQos &qoslist, TopicListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   该方法与 create_topic 相同，在创建主题之前将会以默认的类型名自动注册关联的类型。
     *
     * @param   topic_name              新创建的主题的名称，保证本域参与者者内唯一。
     * @param [in,out]  type_support    新创建的主题关联的数据类型的类型支持单例，例如零拷贝类型： ZeroCopyBytesTypeSupport::get_instance() 。
     * @param   qoslist                 新创建的主题的QoS配置。
     * @param [in,out]  a_listener      主题消息回调接口。
     * @param   mask                    回调消息类型掩码。
     *
     * @return  创建成功则指向创建成功的主题对象，否则返回NULL，原因可能如下：
     *          - 分配空间失败；  
     *          - 传入的参数非法（ @e topic_name == NULL @e type_support == NULL）；  
     *          - 传入的QoS含有无效值或者QoS中含有不一致的配置；  
     *          - 传入的参数未注册；  
     *          - 该域参与者中已有相同主题名的主题；  
     *          - 未归类错误，详细参见日志；
     */

    virtual Topic* create_topic_w_type_support(
        const Char* topic_name,
        TypeSupport* type_support,
        const TopicQos &qoslist,
        TopicListener *a_listener,
        const StatusKindMask &mask) = 0;
    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_topic(Topic *a_topic) = 0;
     *
     * @brief   删除指定主题。
     *          
     * @details 在调用该方法之前需要保证与主题关联的所有子实体（数据写者、数据读者、基于内过滤的主题）都已经被删除，
     *          此外该主题的引用次数为0次，用户通过 #find_topic 方法会增加主题的引用次数。
     *          如果不满足上述条件将会返回错误 #DDS_RETCODE_PRECONDITION_NOT_MET 。
     *
     * @param [in,out]  a_topic 指定的主题对象。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示删除成功。  
     *          - #DDS_RETCODE_BAD_PARAMETER :@e a_topic 不是有效的主题对象；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET   
     *              - 表示指定主题不是由该域参与者创建的；  
     *              - 不满足删除条件；  
     */

    virtual ReturnCode_t delete_topic(Topic *a_topic) = 0;

    /**
     * @fn  virtual Topic* DomainParticipant::find_topic(const Char* topic_name, const Duration_t& timeout) = 0;
     *
     * @brief   根据主题名字阻塞查找本地主题。
     *          
     * @details 若满足条件的主题已经存在，则直接返回，否则等待，直到超时或者满足条件的主题被创建，注意查找成功时，
     *          将增加查找成功的主题的引用数，应调用 #delete_topic 删除引用数。
     *
     * @param   topic_name  主题名称。
     * @param   timeout     最长等待时间。
     *
     * @return  当前可能的返回值：
     *          - NULL表示查找失败，指定的时间内没有满足条件的主题。   
     *          - 非NULL表示查找到的满足条件的指针对象。
     */

    virtual Topic* find_topic(const Char* topic_name, const Duration_t& timeout) = 0;

    /**
     * @fn  virtual TopicDescription* DomainParticipant::lookup_topicdescription(const Char* name) = 0;
     *
     * @brief   根据主题名字查找本地创建的主题，包括主题以及基于内容过滤的主题。
     *
     * @param   name    指明需要查找的主题名称。
     *
     * @return  当前可能的返回值：
     *          - NULL表示查找失败，本地尚未创建指定主题名的主题。
     *          - 非NULL表示查找到的满足条件的父类指针。
     */

    virtual TopicDescription* lookup_topicdescription(const Char* name) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_topic(const InstanceHandle_t &handle) = 0;
     *
     * @brief   忽略指定标识表示的主题关联的所有订阅/发布。
     *          
     * @details 对象是数据读者以及数据写者，忽略所有对该主题的订阅或者发布的匹配，如果已经匹配了则断开被忽略的数据写者以及数据读者匹配。
     *
     * @param   handle  标识指定的主题。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_NOT_ENABLED :表示未使能。
     *          - #DDS_RETCODE_ERROR :表示忽略错误。  
     *          - #DDS_RETCODE_OK :表示忽略成功。
     *
     * @warning ZRDDS当前未实现该接口。
     */

    virtual ReturnCode_t ignore_topic(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_publication(const InstanceHandle_t &handle) = 0;
     *
     * @brief   忽略指定数据写者，即不与本地数据读者匹配。
     *          
     * @details 忽略发布是对于本地的数据读者来说的，在该方法被调用之后，该域参与者下的所有数据读者均不会收到来自该数据写者的数据，
     *          通常的做法是，调用 DDS::DataReader::get_matched_publications 来获取已经配对的远程数据写者的
     *          唯一标识或者通过内置监听器获取远端数据写者的唯一标识，再调用该函数来设置忽略。
     *
     * @param   handle  标识需要被忽略的数据写者。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示忽略成功，包括@e handle 指定的数据写者不存在的情况；
     *          - #DDS_RETCODE_BAD_PARAMETER :@e handle 不是有效的数据写者标识。
     *          - #DDS_RETCODE_NOT_ENABLED :表示本域参与者未使能。
     *          - #DDS_RETCODE_ERROR :未归类错误，详细参见日志信息。
     */

    virtual ReturnCode_t ignore_publication(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::ignore_subscription(const InstanceHandle_t &handle) = 0;
     *
     * @brief   忽略指定数据读者，即不与本地数据写者匹配。
     *
     * @details 忽略订阅是对于本地的数据写者来说的，在该方法被调用之后，该域参与者下的所有数据写者均不会向该数据读者发送数据，
     *          通常的做法是，调用 DDS::DataWriter::get_matched_subscriptions 来获取已经配对的远程数据读者的
     *          唯一标识或者通过内置监听器获取远端数据读者的唯一标识，再调用该函数来设置忽略。
     *
     * @param   handle  标识需要被忽略的数据读者。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示忽略成功，包括@e handle 指定的数据读者不存在的情况；
     *          - #DDS_RETCODE_BAD_PARAMETER :@e handle 不是有效的数据读者标识。
     *          - #DDS_RETCODE_NOT_ENABLED :表示本域参与者未使能。
     *          - #DDS_RETCODE_ERROR :未归类错误，详细参见日志信息。
     */

    virtual ReturnCode_t ignore_subscription(const InstanceHandle_t &handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_contained_entities() = 0;
     *
     * @brief   该方法删除域参与者创建的所有实体。
     *          
     * @details 包括发布者、订阅者、主题、基于内容过滤的主题。并且对子实体进行递归调用 delete_contained_entities 
     *          方法，最终的删除的实体包括数据写者、数据读者、读取条件等，删除的实体不包括内置实体。
     *          该方法采取尽力而为的策略删除，即满足删除条件的实体进行删除，如果有不满足删除条件的实体，则返回特定的错误码。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示删除成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :表示有部分实体不满足删除条件，仅删除部分实体；
     *          - #DDS_RETCODE_ERROR :表示未归类错误，详细参见日志；
     */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
     * @fn  virtual bool DomainParticipant::contains_entity(const InstanceHandle_t &a_handle) = 0;
     *
     * @brief   该方法用于测试实体是否是域参与者的子实体。
     *          
     * @details 该方法会递归测试，即可测试的实体包括发布者、订阅者、主题、数据读者、数据写者。
     *
     * @param   a_handle    需要测试的实体标识。
     *
     * @return  true表示属于该域参与者的子实体，false表示不属于。
     */

    virtual bool contains_entity(const InstanceHandle_t &a_handle) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_default_subscriber_qos(const SubscriberQos &qoslist) = 0;
     *
     * @brief   该方法设置为订阅者保存的默认QoS配置。
     *
     * @details 默认的QoS在创建新的订阅者时指定QoS参数为 DDS::SUBSCRIBER_QOS_DEFAULT 时使用的QoS配置，
     *          使用特殊的值 DDS::SUBSCRIBER_QOS_DEFAULT 订阅者QoS中的各个配置的设置为默认值。
     *
     * @param   qoslist 指明QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示@e qoslist为空，或者@e qoslist 具有无效值；
     *          - #DDS_RETCODE_INCONSISTENT :表示@e qoslist 中具有不相容的配置；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t set_default_subscriber_qos(const SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_default_publisher_qos(const PublisherQos &qoslist) = 0;
     *
     * @brief   该方法设置为发布者保存的默认QoS配置。
     *
     * @details 默认的QoS在创建新的订阅者时指定QoS参数为 DDS::PUBLISHER_QOS_DEFAULT 时使用的QoS配置，
     *          使用特殊的值 DDS::PUBLISHER_QOS_DEFAULT 发布者QoS中的各个配置的设置为默认值。
     *
     * @param   qoslist 指明QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示@e qoslist为空，或者@e qoslist 具有无效值；
     *          - #DDS_RETCODE_INCONSISTENT :表示@e qoslist 中具有不相容的配置；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t set_default_publisher_qos(const PublisherQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::set_default_topic_qos(const TopicQos &qoslist) = 0;
     *
     * @brief   该方法设置为主题保存的默认QoS配置。
     *
     * @details 默认的QoS在创建新的主题时指定QoS参数为 DDS::TOPIC_QOS_DEFAULT 时使用的QoS配置，
     *          使用特殊的值 DDS::TOPIC_QOS_DEFAULT 主题QoS中的各个配置的设置为默认值。
     *
     * @param   qoslist 指明QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示@e qoslist为空，或者@e qoslist 具有无效值；
     *          - #DDS_RETCODE_INCONSISTENT :表示@e qoslist 中具有不相容的配置；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t set_default_topic_qos(const TopicQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_default_subscriber_qos(SubscriberQos &qoslist) = 0;
     *
     * @brief   该方法获取为订阅者保存的默认QoS配置。
     *
     * @param [in,out]  qoslist 出口参数表示获取的结果.
     *
     * @return  当前的返回值类型：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t get_default_subscriber_qos(SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_default_publisher_qos(PublisherQos &qoslist) = 0;
     *
     * @brief   该方法获取为发布者保存的默认QoS配置。
     *
     * @param [in,out]  qoslist 出口参数表示获取的结果.
     *
     * @return  当前的返回值类型：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t get_default_publisher_qos(PublisherQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_default_topic_qos(TopicQos &qoslist) = 0;
     *
     * @brief   该方法获取为主题保存的默认QoS配置。
     *
     * @param [in,out]  qoslist 出口参数表示获取的结果.
     *
     * @return  当前的返回值类型：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t get_default_topic_qos(TopicQos &qoslist) = 0;    

#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC

    /**
     * @fn  virtual ContentFilteredTopic* DomainParticipant::create_contentfilteredtopic( const Char* name, const Topic *related_topic, const Char* filter_exp, const StringSeq& exp_para) = 0;
     *
     * @brief   创建基于内容过滤的主题。
     *
     * @param   name            基于内容过滤的主题名称，该主题名称不会通过内置数据传递到远程，仅在本地使用，name
     *                          应该保证本域参与者内唯一（包括普通主题的名称）。
     * @param   related_topic   关联的基本主题。
     * @param   filter_exp      过滤表达式，语法规则参见 @ref expression-grammer 。
     * @param   exp_para        过滤参数，与过滤表达式配合使用。
     *
     * @return  非NULL表示创建成功，NULL表示创建失败，失败的原因可能为：
     *          - 本地已存在同名的主题；  
     *          - 关联的基础主题不存在；  
     *          - 过滤表达式或者过滤参数不合法；
     *          - 分配内存失败。
     */

    virtual ContentFilteredTopic* create_contentfilteredtopic(
        const Char* name,
        const Topic *related_topic,
        const Char* filter_exp,
        const StringSeq& exp_para) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_contentfilteredtopic( ContentFilteredTopic *a_topic) = 0;
     *
     * @brief   删除指定基于内容过滤的主题。
     *
     * @param [in,out]  a_topic 指明目标。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK ：删除成功；
     *          - #DDS_RETCODE_BAD_PARAMETER ：参数无效或者不是由该域参与者创建；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ：不满足删除的条件，还有与该主题关联的数据读者尚未删除；
     *          - #DDS_RETCODE_ERROR ：删除错误，详细参见日志；
     */

    virtual ReturnCode_t delete_contentfilteredtopic(
        ContentFilteredTopic *a_topic) = 0;

#endif // _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC

    /**
     * @fn  virtual MultiTopic* DomainParticipant::create_multitopic( const Char* name, const Char* type_name, const Char* sub_exp, const Char** exp_para) = 0;
     *
     * @brief   创建合并主题。
     *
     * @param   name        主题名称。
     * @param   type_name   类型名称。
     * @param   sub_exp     订阅表达式。
     * @param   exp_para    表示式参数。
     *
     * @return  当前总是返回NULL。
     *  
     * @warning 当前未实现 DDS::MultiTopic 。
     */

    virtual MultiTopic* create_multitopic(
        const Char* name,
        const Char* type_name,
        const Char* sub_exp,
        const Char** exp_para) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::delete_multitopic(MultiTopic *a_topic) = 0;
     *
     * @brief   删除合并主题。
     *
     * @param [in,out]  a_topic 指明目标。
     *
     * @return  当前总是返回 #DDS_RETCODE_ERROR 。
     *  
     * @warning 当前未实现 DDS::MultiTopic 。
     */

    virtual ReturnCode_t delete_multitopic(MultiTopic *a_topic) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_topics(InstanceHandleSeq &discoved_handleList) = 0;
     *
     * @brief   获取已经被发现且没有被忽略的其他主题的标识。
     *
     * @param [in,out]  discoved_handleList 获取的结果列表。
     *
     * @return  当前总是返回 #DDS_RETCODE_UNSUPPORTED 。
     *  
     * @warning 当前未实现。
     */

    virtual ReturnCode_t get_discovered_topics(InstanceHandleSeq &discoved_handleList) = 0;

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA
    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_discovered_topic_data( TopicBuiltinTopicData &data, const InstanceHandle_t& a_handle) = 0;
     *
     * @brief   获取已经被发现且没有被忽略的主题的详细信息
     *
     * @param [in,out]  data    获取到的详细信息。
     * @param   a_handle        标识需要发送获取的主题。
     *
     * @return  当前总是返回 #DDS_RETCODE_UNSUPPORTED 
     *          
     * @warning 当前未实现。
     */

    virtual ReturnCode_t get_discovered_topic_data(
        TopicBuiltinTopicData &data,
        const InstanceHandle_t& a_handle) = 0;
#endif //_ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::get_current_time(Time_t &cur_time) = 0;
     *
     * @brief   获取ZRDDS内部使用的时间系统的当前时间戳。
     *
     * @param [in,out]  cur_time    出口参数，当前的时间戳。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 。
     */

    virtual ReturnCode_t get_current_time(Time_t &cur_time) = 0;

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual ReturnCode_t DomainParticipant::assert_liveliness() = 0;
     *
     * @brief   该方法用于手动声明域参与者的存活性，当存活性策略设置为 #DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS 时有用。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示声明存活性成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示本域参与者未使能。
     *          - #DDS_RETCODE_ERROR :内部未归类错误，详细参见日志。
     */

    virtual ReturnCode_t assert_liveliness() = 0;
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

    virtual ReturnCode_t register_type(
        const Char* type_name,
        ZRDDSTypePlugin* type_plugin) = 0;

    virtual ReturnCode_t unregister_type(const Char* type_name) = 0;

protected:

    /**
     * @brief   工厂模式创建实体，私有的构造函数禁止用户自己创建。
     */

    DomainParticipant(){}

    virtual ~DomainParticipant(){}
};

} // namespace DDS

#endif  //_DOMAINPARTICIPANT_H
