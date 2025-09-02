/**
 * @file:       Publisher.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef Publisher_h__
#define Publisher_h__

#include "DomainEntity.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"
#include "ZRDDSCppWrapper.h"

struct PublisherImpl;

namespace DDS {

class DataWriter;
class Topic;
class DataWriterListener;
class PublisherListener;
class DomainParticipant;
class TypeSupport;


/**
 * @class   Publisher
 *
 * @ingroup  CppPublication
 *
 * @brief   ZRDDS提供的发布者接口，应用创建发布者表示自身想向指定的域内提供数据；
 *
 * @details 发布者主要完成以下几个功能：
 *          - 实体功能；  
 *          - 作为数据写者的工厂；  
 *          - 统一处理数据写者的数据样本发送；
 */
class Publisher : public DomainEntity
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual DataWriter* Publisher::lookup_datawriter_by_name( const Char* name)=0;
     *
     * @brief 按名字精确查找DataWriter
     *
     * @author Tim
     * @date 17/11/2
     *
     * @param name 待查找的数据写者名称。
     *
     * @return  可能的返回值如下：
     *           - NULL未查找到数据写者；
     *           - 查到到的首个数据写者。
     */
    virtual DataWriter* lookup_datawriter_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t Publisher::lookup_named_datawriters( const Char* pattern, StringSeq& writer_names) = 0;
     *
     * @brief 查找名称符合pattern限定的数据写者名称
     *
     * @param pattern               查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param [in,out] writer_names 查找得到数据写者名字列表
     *
     * @return   可能的返回值如下：
     *           - #DDS_RETCODE_BAD_PARAMETER 参数存在错误；
     *           - #DDS_RETCODE_OK 设置成功。
     */
    virtual ReturnCode_t lookup_named_datawriters(
        const Char* pattern, StringSeq& writer_names) = 0;

    /**
     * @fn virtual DataWriter* Publisher::create_datawriter_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML创建一个数据写者，XML根节点为data_writer
     *
     * @param xml_content XML字符串
     *
     * @return  可能的返回值如下：
     *           - NULL创建数据写者失败；
     *           - 创建的数据写者。
     */
    virtual DataWriter* create_datawriter_from_xml_string(
        const Char* xml_content) = 0;

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn virtual ReturnCode_t Publisher::set_default_datawriter_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库中获取数据写者QoS并将其设为默认数据写者QoS
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_default_datawriter_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t Publisher::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库中获取发布者QoS并将其设置到发布者中
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
     * @fn virtual DataWriter* Publisher::create_datawriter_with_qos_profile( Topic *topic, const Char* library_name, const Char* profile_name, const Char* qos_name, DataWriterListener *dw_listener, StatusKindMask mask) = 0;
     *
     * @brief 从QoS仓库中获取数据写者QoS并用其创建数据写者
     *
     * @param [in] topic        数据写者关联的主题
     * @param library_name      QoS库的名字，不允许为NULL。
     * @param profile_name      QoS配置的名字，不允许为NULL。
     * @param qos_name          QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in] dw_listener  用户提供的监听器对象
     * @param mask              状态掩码，指明需要被监听器捕获的状态
     *
     * @return  可能的返回值如下：
     *           - NULL创建数据写者失败；
     *           - 创建的数据写者。
     */
    virtual DataWriter* create_datawriter_with_qos_profile(
        Topic *topic,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DataWriterListener *dw_listener,
        StatusKindMask mask) = 0;

    /**
     * @fn  virtual DataWriter* Publisher::create_datawriter_with_topic_and_qos_profile( const Char* topicName, TypeSupport* typeSupport, const Char* library_name, const Char* profile_name, const Char* qos_name, DataWriterListener *dw_listener, StatusKindMask mask) = 0;
     *
     * @brief   创建指定主题名称的数据写者，当主题名称关联的主题未创建时，将自动创建， 否则将利用已经创建的主题创建数据写者。
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

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    /**
    * @fn   virtual DataWriter* Publisher::create_datawriter( Topic *the_topic, const DataWriterQos &qoslist, DataWriterListener *a_listener, const StatusKindMask &mask) = 0;
    *
    * @brief    创建DataWriter。
    *
    * @param    the_topic       用于关联DataWriter的Topic实例指针。
    * @param    qoslist         DataWriter的QoS配置。
    * @param    a_listener      需要安装到DataWriter的Listener。
    * @param    mask            状态掩码，指明需要被Listener捕获的状态。
    *
    * @return  可能的返回值如下：
    *           - NULL创建数据写者失败；
    *           - 创建的数据写者。
    */

    virtual DataWriter* create_datawriter(
        Topic *the_topic,
        const DataWriterQos &qoslist,
        DataWriterListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::delete_datawriter(DataWriter *a_writer) = 0;
    *
    * @brief    删除一个数据写者。
    *
    * @param    a_writer    需要被删除的数据写者。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_BAD_PARAMETER 传入的参数有误；
    *           - #DDS_RETCODE_PRECONDITION_NOT_MET 传入的数据写者有误；
    *           - #DDS_RETCODE_ERROR 未归类错误；
    *           - #DDS_RETCODE_OK 删除成功。
    */

    virtual ReturnCode_t delete_datawriter(DataWriter *a_writer) = 0;

    /**
    * @fn   virtual DataWriter* Publisher::lookup_datawriter( const Char* topic_name) = 0;
    *
    * @brief    根据主题名查找对应的数据写者。
    *
    * @param    topic_name  关联到数据写者主题的主题名称。
    *
    * @return   可能的返回值如下：
    *           - NULL未查找到数据写者；
    *           - 查到到的首个数据写者。
    */

    virtual DataWriter* lookup_datawriter(
        const Char* topic_name) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::suspend_publications() = 0;
    *
    * @brief    挂起数据发布。
    *
    * @details  当数据发布被挂起之后，该发布者创建的所有数据写者发布的数据都不再被发出。
    *           直到挂起被完全取消之后才会继续发出数据。
    *           该函数可以被多次调用，但是取消挂起也需要配对使用，亦即如果该函数被多次调用之后，必须取消相同次数才能重新开始发布数据。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_NOT_ENABLED 该发布者未被使能；
    *           - #DDS_RETCODE_OK 操作成功。
    */

    virtual ReturnCode_t suspend_publications() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::resume_publications() = 0;
    *
    * @brief    恢复数据发布，与 #suspend_publications 配对使用。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_NOT_ENABLED 该发布者未被使能；
    *           - #DDS_RETCODE_PRECONDITION_NOT_MET 该发布者未调用过 #suspend_publications ；
    *           - #DDS_RETCODE_OK 操作成功。
    */

    virtual ReturnCode_t resume_publications() = 0;

#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
    /**
    * @fn   virtual ReturnCode_t Publisher::begin_coherent_changes() = 0;
    *
    * @brief    开始进行“连续”的修改。
    *
    * @details  当该数据写者所属的发布者的QoS #DDS_PresentationQosPolicy::coherent_access == true，使用此函数开始进行“原子”操作。
    *           在该函数调用之后直到 #end_coherent_changes 被调用之前发布的所有数据会被接收端一次性访问到。
    *           亦即在 #end_coherent_changes 被调用之前，所有提交的数据对于接收端来说都是不可访问的。
    *           而在 #end_coherent_changes 调用之后，接收端会收到一批数据。
    *
    * @return	可能的返回值如下：
    *           - #DDS_RETCODE_NOT_ENABLED 发布者未使能；
    *           - #DDS_RETCODE_ERROR 未归类错误。
    */

    virtual ReturnCode_t begin_coherent_changes() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::end_coherent_changes() = 0;
    *
    * @brief    结束“连续”的修改，使接收端可以访问修改的值，必须在 #begin_coherent_changes 调用之后调用。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_NOT_ENABLED 发布者未使能。
    *           - #DDS_RETCODE_PRECONDITION_NOT_MET 发布者未调用过 #begin_coherent_changes 。
    *           - #DDS_RETCODE_ERROR 未归类错误。
    */

    virtual ReturnCode_t end_coherent_changes() = 0;

#endif //_ZRDDS_INCLUDE_PRESENTATION_QOS

    /**
    * @fn   virtual ReturnCode_t Publisher::wait_for_acknowledgments(const Duration_t &max_wait) = 0;
    *
    * @brief    阻塞调用该函数的线程直到该发布者创建的数据写者发送的所有数据都被接收端所响应或者超时。
    *
    * @param    max_wait    该函数的最长阻塞时间。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_NOT_ENABLED 发布者未使能。
    *           - #DDS_RETCODE_TIMEOUT 等待超时。
    *           - #DDS_RETCODE_ERROR 未归类错误。
    */

    virtual ReturnCode_t wait_for_acknowledgments(const Duration_t &max_wait) = 0;

    /**
    * @fn   virtual DomainParticipant* Publisher::get_participant() = 0;
    *
    * @brief    获取创建该发布者的域参与者。
    *
    * @return   可能的返回值如下：
    *           - 创建该Publisher的DomainParticipant。
    */

    virtual DomainParticipant* get_participant() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::delete_contained_entities() = 0;
    *
    * @brief    删除Publisher所包含的所有DataWriter。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_ERROR 未归类错误；
    *           - #DDS_RETCODE_OK 删除成功。
    */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::set_default_datawriter_qos(const DataWriterQos &qoslist) = 0;
    *
    * @brief    设置数据写者的默认QoS。
    *
    * @details  当创建数据写者时可以使用 DDS::DATAWRITER_QOS_DEFAULT 值作为DataWriterQoS传入。
    *           如果用户使用了 DDS::DATAWRITER_QOS_DEFAULT ，具体的QoS配置将由该函数调用时传入的QoS决定。
    *
    * @param    qoslist 需要设置的数据写者QoS，如果使用DEFAULT_DATAWRITER_QOS作为参数调用该函数，设置的默认QoS将被重置。
    *
    * @return   参见 #DDS::DataWriter::set_qos 。
    */

    virtual ReturnCode_t set_default_datawriter_qos(const DataWriterQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::get_default_datawriter_qos(DataWriterQos &qoslist) = 0;
    *
    * @brief    获取由 #set_default_datawriter_qos 设置的DataWriterQos。
    *
    * @param [in,out]   qoslist 获取到的数据写者QoS
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_ERROR 未归类错误；
    *           - #DDS_RETCODE_OK 获取成功。
    */

    virtual ReturnCode_t get_default_datawriter_qos(DataWriterQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::copy_from_topic_qos(DataWriterQos &a_datawriter_qos, const TopicQos &a_topic_qos) = 0;
    *
    * @brief    使用TopicQos中的对应项赋值DataWriterQos。
    *
    * @param    a_topic_qos                 主题QoS，作为拷贝的数据源。
    * @param [in,out]   a_datawriter_qos    数据写者QoS，保存拷贝结果。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_ERROR 未归类错误；
    *           - #DDS_RETCODE_OK 设置成功。
    */

    virtual ReturnCode_t copy_from_topic_qos(
        DataWriterQos &a_datawriter_qos, 
        const TopicQos &a_topic_qos) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::set_qos(const PublisherQos &qoslist) = 0;
    *
    * @brief    设置发布者QoS。
    *
    * @param    qoslist 待设置的发布者QoS，可以使用 DDS::PUBLISHER_QOS_DEFAULT 作为参数以使用在域参与者中保存的默认发布者QoS
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_IMMUTABLE_POLICY 不可在使能后修改的QoS；
    *           - #DDS_RETCODE_INCONSISTENT QoS存在冲突；
    *           - #DDS_RETCODE_BAD_PARAMETER QoS存在不合法的值；
    *           - #DDS_RETCODE_ERROR 未归类错误；
    *           - #DDS_RETCODE_OK 设置成功。
    */

    virtual ReturnCode_t set_qos(const PublisherQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::get_qos(PublisherQos &qoslist) = 0;
    *
    * @brief    获取发布者QoS。
    *
    * @param [in,out]   qoslist 保存获取到的发布者QoS值。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_OK 获取成功，
    *           - #DDS_RETCODE_ERROR 未归类错误。
    */

    virtual ReturnCode_t get_qos(PublisherQos &qoslist) = 0;

    /**
    * @fn   virtual ReturnCode_t Publisher::set_listener(PublisherListener *a_listener, const StatusKindMask &mask) = 0;
    *
    * @brief    设置发布者的监听器。
    *
    * @details  设置新的监听器不会使原有的监听器被释放，用户需要自己管理监听器对象的分配和释放。
    *
    * @param    a_listener  用户提供的监听器对象，可以传入NULL解除监听。
    * @param    mask        状态掩码，指明需要被监听器捕获的状态。
    *
    * @return   可能的返回值如下：
    *           - #DDS_RETCODE_OK 设置成功。
    */

    virtual ReturnCode_t set_listener(
        PublisherListener *a_listener, 
        const StatusKindMask &mask) = 0;

    /**
    * @fn   virtual PublisherListener* Publisher::get_listener() = 0;
    *
    * @brief    获取发布者当前的监听器。
    *
    * @return   可能的返回值如下：
    *           - NULL表示未设置监听器；
    *           - 非空表示应用通过 #set_listener 或者在创建时设置的监听器对象。
    */

    virtual PublisherListener* get_listener() = 0;

protected:
    virtual ~Publisher() {}
};

typedef Publisher* PublisherPtr;
// 声明PublisherSeq类
DDS_SEQUENCE_CPP(PublisherSeq, PublisherPtr);

} // namespace DDS

#endif // Publisher_h__
