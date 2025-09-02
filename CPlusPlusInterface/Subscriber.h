/**
 * @file:       Subscriber.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SUBSCRIBER_H)
#define _SUBSCRIBER_H

#include "DomainEntity.h"
#include "ZRDDSCppWrapper.h"
#include "ZRBuiltinTypes.h"

namespace DDS {

class DataReader;
class TopicDescription;
class DataReaderListener;
class SubscriberListener;
class DomainParticipant;
class TypeSupport;
struct DataReaderSeq;

/**
 * @class   Subscriber
 *
 * @ingroup  CppSubscription
 *
 * @brief   ZRDDS提供的订阅者接口，应用创建订阅者表示自身想从指定的域内获取数据；
 *
 * @details 订阅者主要完成以下几个功能：
 *          - 实体功能；  
 *          - 作为数据读者的工厂；  
 *          - 统一处理数据读者的数据样本通知；
 */

class DCPSDLL Subscriber : public DomainEntity
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual DataReader* Subscriber::lookup_datareader_by_name( const Char* name)=0;
     *
     * @brief 按名字精确查找DataReader
     *
     * @param name The name
     *
     * @return null if it fails, else a DataReader*
    */
    virtual DataReader* lookup_datareader_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t Subscriber::lookup_named_datareaders( const Char* pattern, StringSeq& reader_names) = 0;
     *
     * @brief 查找名称符合pattern限定的数据读者。
     *
     * @param pattern               查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符。
     * @param [in,out] reader_names 查找得到的数据读者名字列表。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示查找成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_named_datareaders(
        const Char* pattern, StringSeq& reader_names) = 0;

    /**
     * @fn virtual DataReader* Subscriber::create_datareader_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML创建一个数据读者。
     *
     * @param xml_content 以XML字符串表示的数据读者。
     *
     * @return 非NULL表示创建成功，否则表示失败，失败的原因可能为：
     *          - 分配内存错误等未归类错误，详细参见日志。
     */
    virtual DataReader* create_datareader_from_xml_string(
        const Char* xml_content) = 0;
		
#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE
    /**
     * @fn virtual ReturnCode_t Subscriber::set_default_datareader_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库中获取数据读者QoS并将其设置为默认DataReaderQos
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_default_datareader_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t Subscriber::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库中获取订阅者QoS并将其设置到订阅者中
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
     * @fn virtual DataReader* Subscriber::create_datareader_with_qos_profile( TopicDescription *topic, const Char* library_name, const Char* profile_name, const Char* qos_name, DataReaderListener *dr_listener, StatusKindMask mask) = 0;
     *
     * @brief 从QoS仓库中获取数据读者QoS并用其创建数据读者。
     *
     * @param [in,out] topic    数据读者关联的主题。
     * @param library_name      QoS库的名字。
     * @param profile_name      QoS配置的名字。
     * @param qos_name          QoS的名字。
     * @param [in] dr_listener  为该订阅者设置的监听器，此参数可以为空。 ZRDDS不会接管监听器对象的内存管理，由用户负责释放。
     * @param   mask            设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return 非NULL表示创建成功，否则表示失败，失败的原因可能为：
     *          - @e a_topic 不是有效的主题对象；
     *          - @e a_topic 的父实体与该订阅者不属于一个域参与者实体；
     *          - @e library_name @e profile_name @e qos_name 指定的QoS中含有无效的QoS或者含有不一致的QoS配置；
     *          - 分配内存错误等未归类错误，详细参见日志。
     */
    virtual DataReader* create_datareader_with_qos_profile(
        TopicDescription *topic,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataReaderListener *dr_listener,
        StatusKindMask mask) = 0;

    /**
     * @fn  virtual DataReader* Subscriber::create_datareader_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataReaderListener *dr_listener, StatusKindMask mask) = 0;
     *
     * @brief   利用自动创建的用户订阅者，创建指定主题名称的数据读者，当主题名称关联的主题未创建时， 将自动创建，否则将利用已经创建的主题创建数据读者。
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

#endif // _ZRXMLQOSINTERFACE

#endif //_ZRXMLINTERFACE

    /**
     * @fn  virtual DataReader* Subscriber::create_datareader( TopicDescription *a_topic, const DataReaderQos &qoslist, DataReaderListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   该方法在订阅者下创建一个数据读者子实体，并设置关联的主题、QoS以及监听器。
     *          
     * @details 用户使用该数据读者从域内读取/获取指定主题数据，返回的数据读者对象为数据读者关联的用户数据类型相关的数据读者的父类指针，
     *          用户需要将返回值动态转化为用户数据类型的数据读者对象，具体代码参见 @ref subscription_example.cpp 。
     *
     * @param [in,out]  a_topic     关联的主题描述，用户可以关联主题以及基于内容过滤的主题，
     *                              该主题描述必须在调用该方法之前在同一个域参与者下调用 DDS::DomainParticipant::create_topic 
     *                              DDS::DomainParticipant::create_contentfilteredtopic 方法创建的主题的父类；
     * @param   qoslist             表示为该数据读者设置的QoS， DDS::DATAREADER_QOS_DEFAULT 表明使用订阅者中保存的默认的QoS。
     * @param [in,out]  a_listener  为该订阅者设置的监听器，此参数可以为空。 ZRDDS不会接管监听器对象的内存管理，由用户负责释放。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  非NULL表示创建成功，否则表示失败，失败的原因可能为：
     *          - @e a_topic 不是有效的主题对象；
     *          - @e a_topic 的父实体与该订阅者不属于一个域参与者实体；  
     *          - @e qoslist 中含有无效的QoS或者含有不一致的QoS配置；  
     *          - 分配内容错误等未归类错误，详细参见日志。
     */

    virtual DataReader* create_datareader(
        TopicDescription *a_topic,
        const DataReaderQos &qoslist,
        DataReaderListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::delete_datareader(DataReader *a_datareader) = 0;
     *
     * @brief   删除指定的数据读者。
     *
     * @param [in,out]  a_datareader    指明需要删除的数据读者。
     *
     * @details 被删除的数据读者应满足删除条件，主要包括：
     *          - 数据读者创建的所有“子实体”读取条件已经全部被删除；  
     *          - 通过该数据读者的 @ref read-take 系列方法租借给用户的空间已经全部回收成功；  
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK ：删除成功；
     *          - #DDS_RETCODE_BAD_PARAMETER ：参数指定的数据读者不是有效的数据读者对象；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ：  
     *              - 参数指定的数据读者不属于本；
     *              - 指定的数据读者不满足删除条件；
     */

    virtual ReturnCode_t delete_datareader(DataReader *a_datareader) = 0;

    /**
     * @fn  virtual DataReader* Subscriber::lookup_datareader(const Char* topic_name) = 0;
     *
     * @brief   根据主题名查找数据读者。
     *
     * @details 如果存在多个满足条件的数据读者，则返回数据读者地址最小的那个。
     *
     * @param   topic_name  查询的主题名。
     *
     * @return  返回空表示没有满足条件的数据读者，否则返回相应的数据读者。
     */

    virtual DataReader* lookup_datareader(const Char* topic_name) = 0;

#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS

    /**
     * @fn  virtual ReturnCode_t Subscriber::begin_access() = 0;
     *
     * @brief   数据读者端开启一致性访问。
     *
     * @details  此方法只有在订阅者 DDS_PresentationQosPolicy::access_scope == #DDS_GROUP_PRESENTATION_QOS
     *           时有效，该方法应与 #end_access 方法配合使用。
     *
     * @return  当前总是返回 #DDS_RETCODE_UNSUPPORTED 。
     *
     * @warning 该方法未实现。
     */

    virtual ReturnCode_t begin_access() = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::end_access() = 0;
     *
     * @brief   与 #begin_access 方法对应，表示数据访问结束。
     *
     * @return  当前总是返回 #DDS_RETCODE_UNSUPPORTED 。
     *
     * @warning 该方法未实现。
     */

    virtual ReturnCode_t end_access() = 0;

#endif //_ZRDDS_INCLUDE_PRESENTATION_QOS

    /**
     * @fn  virtual ReturnCode_t Subscriber::get_datareaders( DataReaderSeq &datareader, const SampleStateMask &sample_states, const ViewStateMask &view_states, const InstanceStateMask &instance_states) = 0;
     *
     * @brief   查找底层含有处于特定状态的数据样本的数据读者的结合。
     *
     * @param [in,out]  datareader  出口参数，用于存储满足条件的数据读者列表。
     * @param   sample_states       需要满足的样本状态条件。
     * @param   view_states         需要满足的视图状态条件。
     * @param   instance_states     需要满足的实例状态条件。
     *
     * @details  可以设置的条件包括 DDS_SampleStateKind 、DDS_ViewStateKind 、 DDS_InstanceStateKind 
     *           均通过掩码来表示状态的集合。数据读者中只要有一个样本满足则该数据读者符合条件。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK ：获取成功；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ：当@e datareader 提供的空间不足，且底层扩容失败；  
     *          - #DDS_RETCODE_NOT_ENABLED ：本订阅者尚未使能；  
     *          - #DDS_RETCODE_ERROR ：内部错误，详细参见日志；
     */

    virtual ReturnCode_t get_datareaders(
        DataReaderSeq &datareader,
        const SampleStateMask &sample_states,
        const ViewStateMask &view_states,
        const InstanceStateMask &instance_states) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::notify_datareaders() = 0;
     *
     * @brief   本方法将尝试调用所有处于 #DDS_DATA_AVAILABLE_STATUS 状态的数据读者关联的监听器的 
     *          DDS::DataReaderListener::on_data_available 方法。
     *
     * @details 当数据读者底层有新的数据到达时，将会处于 #DDS_DATA_AVAILABLE_STATUS 状态，当用户回调成功或者用户
     *          通过 @ref read-take 系列方法读取数据时清理这个状态，该方法通常在 
     *          DDS::SusbcriberListener::data_on_reader 回调函数中使用。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK ：通知成功；
     *          - #DDS_RETCODE_NOT_ENABLED ：本订阅者尚未使能；  
     *          - #DDS_RETCODE_ERROR ：内部错误，详细参见日志；
     */

    virtual ReturnCode_t notify_datareaders() = 0;

    /**
     * @fn  virtual DomainParticipant* Subscriber::get_participant() = 0;
     *
     * @brief   获得订阅者的父实体域参与者。
     *
     * @return  返回该订阅者的父实体的域参与者。
     */

    virtual DomainParticipant* get_participant() = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::delete_contained_entities() = 0;
     *
     * @brief   该方法删除该订阅者创建的所有实体。
     *
     * @details 该方法会对子实体进行递归调用 delete_contained_entities 方法，最终的删除的实体包括数据读者、读取条件等；
     *          该方法采取尽力而为的策略删除，即满足删除条件的实体进行删除，如果有不满足删除条件的实体，则返回特定的错误码。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示删除成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :表示有部分实体不满足删除条件，仅删除部分实体；
     *          - #DDS_RETCODE_ERROR :表示未归类错误，详细参见日志；
     */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::set_default_datareader_qos( const DataReaderQos &qoslist) = 0;
     *
     * @brief   该方法设置为数据读者保存的默认QoS配置。
     *
     * @details 默认的QoS在创建新的数据读者时指定QoS参数为 DDS::DATAREADER_QOS_DEFAULT 时使用的QoS配置，
     *          使用特殊的值 DDS::DATAREADER_QOS_DEFAULT 订阅者QoS中的各个配置的设置为默认值。
     *
     * @param   qoslist 指明QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示@e qoslist为空，或者@e qoslist 具有无效值；
     *          - #DDS_RETCODE_INCONSISTENT :表示@e qoslist 中具有不相容的配置；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t set_default_datareader_qos(
        const DataReaderQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::get_default_datareader_qos(DataReaderQos &qoslist) = 0;
     *
     * @brief   该方法获取为数据读者保存的默认QoS配置。
     *
     * @param [in,out]  qoslist 出口参数表示获取的结果.
     *
     * @return  当前的返回值类型：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t get_default_datareader_qos(DataReaderQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::copy_from_topic_qos( DataReaderQos &a_datareader_qos, const TopicQos &a_topic_qos) = 0;
     *
     * @brief   从主题QoS中构造相应的数据读者QoS。
     *
     * @param [in,out]  a_datareader_qos    出口参数，表示构造的结果数据读取QoS配置。
     * @param   a_topic_qos                 源主题QoS配置。
     *
     * @return  返回表示操作结果的返回码：
     *          - #DDS_RETCODE_OK ：构造成功；
     *          - #DDS_RETCODE_ERROR ：内部错误，具体参见日志文件，可能的原因为分配内存失败。
     */

    virtual ReturnCode_t copy_from_topic_qos(
        DataReaderQos &a_datareader_qos, 
        const TopicQos &a_topic_qos) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::set_qos(const SubscriberQos &qoslist) = 0;
     *
     * @brief   该方法设置为订阅者设置的QoS。
     *
     * @param   qoslist 表示用户想要设置的QoS配置。
     *
     * @details 可以使用特殊值 DDS::SUBSCRIBER_QOS_DEFAULT 表示使用存储在域参与者中的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示 @e qoslist 含有无效的QoS配置；
     *          - #DDS_RETCODE_INCONSISTENT :表示 @e qoslist 含有不兼容的QoS配置；
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :表示用户尝试修改使能后不可变的QoS配置；
     *          - #DDS_RETCODE_ERROR :表示未归类的错误，错误详细信息输出在日志中；
     */
    virtual ReturnCode_t set_qos(const SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::get_qos(SubscriberQos &qoslist) = 0;
     *
     * @brief   获取该订阅者的QoS配置。
     *
     * @param [in,out]  qoslist 出口参数，用于保存订阅者的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_ERROR :表示失败，原因可能为复制QoS时发生错误。
     */
    virtual ReturnCode_t get_qos(SubscriberQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t Subscriber::set_listener( SubscriberListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   设置该订阅者的监听器。
     *
     * @details  本方法将覆盖原有监听器，如果设置空对象表示清除原先设置的监听器。
     *
     * @param [in,out]  a_listener  为该订阅者设置的监听器对象。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示设置成功。
     */
    virtual ReturnCode_t set_listener(
        SubscriberListener *a_listener, const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual SubscriberListener* Subscriber::get_listener() = 0;
     *
     * @brief   该方法获取通过 #set_listener 方法或者创建时为订阅者设置的监听器对象。
     *
     * @return  当前可能的返回值：
     *          - NULL表示未设置监听器；
     *          - 非空表示应用通过 #set_listener 或者在创建时设置的监听器对象。
     */
    virtual SubscriberListener* get_listener() = 0;

protected:
    virtual ~Subscriber();
};

/**
 * @typedef Subscriber* SubscriberPtr
 *
 * @ingroup CppSubscription
 *
 * @brief   定义 DDS::Subscriber 指针的别名。
 */

typedef Subscriber* SubscriberPtr;

/**
 * @struct SubscriberSeq 
 *
 * @ingroup CppSubscription
 *
 * @brief   声明 DDS::SubscriberPtr 的序列类型，参见 #DDS_USER_SEQUENCE_CPP 。
 */

DDS_SEQUENCE_CPP(SubscriberSeq, SubscriberPtr);

} // namespace DDS

#endif  //_SUBSCRIBER_H
