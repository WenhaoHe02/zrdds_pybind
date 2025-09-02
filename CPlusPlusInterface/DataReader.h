/**
 * @file:       DataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DATAREADER_H)
#define _DATAREADER_H

#include "ZRDDSCommon.h"
#include "DomainEntity.h"
#include "ReadCondition.h"
#include "QueryCondition.h"
#include "ZRSequence.h"
#include <stdlib.h>
#include "ZRDDSCppWrapper.h"
#include "DataReaderReadOrTakeParams.h"

typedef struct DataReaderImpl DataReaderImpl;
typedef struct DataReaderListenerImpl DataReaderListenerImpl;
struct ZRDynamicData;

namespace DDS {

class Subscriber;
class TopicDescription;
class DataReaderListener;

/**
 * @class   DataReader
 *          
 * @ingroup CppSubscription
 *
 * @brief   DDS标准中的数据读者接口。
 *          
 * @details 数据读者主要负责存储从发布端获取到的数据以及提供接口给上层应用获取接收到的数据，数据读者接口同样包含两类接口：
 *          - 用户数据类型无关接口，该类即定义了这些与用户类型无关的接口，作为用户类型的数据读者的父类。
 *          - 用户数据类型相关接口，通过类模板实现， DDS::ZRDDSDataReader 
 */
class DCPSDLL DataReader : public DomainEntity
{
public:

#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE
    /**
     * @fn virtual ReturnCode_t DataReader::sample_to_xml_string( ZRDynamicData* data, const Char*& result);
     *
     * @brief 将DynamicData转换到XML，XML格式为data
     *
     * @param [in] data       用户传入的DynamicData，必须与创建Reader的Topic关联的类型匹配
     * @param [in,out] result 生成的XML
     *
     * @return A ReturnCode_t
     */
    virtual ReturnCode_t sample_to_xml_string(
        ZRDynamicData* data,
        const Char*& result);

    /**
     * @fn virtual ReturnCode_t DataReader::read_sample_info_to_xml_string( SampleInfo* sample_info, SampleInfoValidMember* valid_sample_info_member, const Char*& result);
     *
     * @brief 将SampleInfo转换到XML，XML格式为read_sample_info
     *
     * @param [in] sample_info              用户传入的SampleInfo
     * @param [in] valid_sample_info_member 指明传入的sample_info中哪些成员是有效的
     * @param [in,out] result               生成的XML
     *
     * @return The sample information to XML string
     */
    virtual ReturnCode_t read_sample_info_to_xml_string(
        SampleInfo* sample_info,
        SampleInfoValidMember* valid_sample_info_member,
        const Char*& result);

    /**
     * @fn virtual ReturnCode_t DataReader::to_xml(const Char*& result, Boolean containedQos = true);
     *
     * @brief 将Reader转换到XML，XML格式为data_reader
     *
     * @param [in,out] result 生成的结果
     * @param containedQos    生成是否包含QoS
     *
     * @return result as a ReturnCode_t
     */
    virtual ReturnCode_t to_xml(const Char*& result, Boolean containedQos = true);

    /**
     * @fn virtual const Char* DataReader::get_entity_name();
     *
     * @brief 获取Entity的名称
     *
     * @return null if it fails, else the entity name
     */
    virtual const Char* get_entity_name();

    virtual Entity* get_factory();

#ifdef _ZRDDS_INCLUDE_READ_CONDITION
    virtual ReadCondition* create_named_readcondition(
        const Char* name,
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask);

    virtual ReadCondition* get_named_read_condition(const Char* name);

    virtual ReturnCode_t delete_named_readcondition(const Char* name);

#ifdef _ZRDDS_INCLUDE_QUERY_CONDITION
    virtual QueryCondition* create_named_querycondition(
        const Char* name,
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask,
        const Char* query_expression,
        const StringSeq &query_parameters);
#endif //_ZRDDS_INCLUDE_QUERY_CONDITION

#endif //_ZRDDS_INCLUDE_READ_CONDITION

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn virtual ReturnCode_t DataReader::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name);
     *
     * @brief 从QoS仓库获取QoS配置并设置到数据读者
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
        const Char* qos_name);

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    virtual ~DataReader(){}
#ifdef _ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  virtual ReadCondition* DataReader::create_readcondition( const SampleStateMask &sample_mask, const ViewStateMask &view_mask, const InstanceStateMask &instance_mask);
     *
     * @brief   创建一个与该数据读者绑定的读取条件。
     *
     * @param   sample_mask     用于指定样本状态集合的掩码。
     * @param   view_mask       用于指定视图状态集合的掩码。
     * @param   instance_mask   用户指定数据实例状态集合掩码。
     *
     * @return  创建成功返回读取条件的对象指针，否则返回空，失败的原因可能为分配内存失败。
     */

    virtual ReadCondition* create_readcondition(
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask);

#ifdef _ZRDDS_INCLUDE_QUERY_CONDITION

    /**
     * @fn  virtual QueryCondition* DataReader::create_querycondition( const SampleStateMask &sample_mask, const ViewStateMask &view_mask, const InstanceStateMask &instance_mask, const Char* query_expression, const StringSeq &query_parameters);
     *
     * @brief   创建一个绑定到该订阅者上的查询条件。
     *
     * @param   sample_mask         样本状态掩码。
     * @param   view_mask           视图状态掩码。
     * @param   instance_mask       实例状态掩码。
     * @param   query_expression    查询表达式。
     * @param   query_parameters    查询的参数。
     *
     * @return  创建成功返回得到 DDS::QueryCondition ，否则返回空。
     *          
     *          @warning 暂未实现。.
     */

    virtual QueryCondition* create_querycondition(
        const SampleStateMask &sample_mask,
        const ViewStateMask &view_mask,
        const InstanceStateMask &instance_mask,
        const Char* query_expression,
        const StringSeq &query_parameters);

#endif //_ZRDDS_INCLUDE_QUERY_CONDITION

    /**
     * @fn  virtual ReturnCode_t DataReader::delete_readcondition(ReadCondition *a_condition);
     *
     * @brief   删除指定的读取条件。
     *
     * @param   a_condition 指明读取条件。
     *
     * @details 删除读取条件时，若该条件加入了等待集合中，则将自动从等待集合中删除该条件。
     *
     * @return  可能返回的值如下：
     *          - #DDS_RETCODE_OK 表示删除成功；
     *          - #DDS_RETCODE_ERROR 表示删除失败，失败的原因可能为：
     *              - @e a_condition 不是有效的 DDS::ReadCondition 对象，包括NULL；
     *              - @e a_condition 不是由该数据读者创建；
     */
    virtual ReturnCode_t delete_readcondition(ReadCondition *a_condition);

    /**
     * @fn  virtual ReturnCode_t DataReader::delete_contained_entities();
     *
     * @brief   删除该数据读者创建的所有读取条件(包括查询条件)，删除读取条件时，将自动从所有加入的等待集合中删除该条件。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示删除成功。
     */

    virtual ReturnCode_t delete_contained_entities();
#endif //_ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  virtual ReturnCode_t DataReader::wait_for_historical_data(const Duration_t &max_wait);
     *
     * @brief   等待历史数据。
     *
     * @details 当该数据读者的持久化配置类型 > DDS_VOLATILE_DURABILITY_QOS 时，即该数据读者需要接收在该数据读者
     *          加入网络前，与之匹配的数据写者已经发送的历史数据，调用此函数以等待历史数据接收完成或者超时。
     *
     * @param   max_wait    最长的等待时间。
     *
     * @return  可能返回的值如下：
     *          - #DDS_RETCODE_OK :表示所有的历史数据均已接收完成，或者不需要接收历史数据；
     *          - #DDS_RETCODE_NOT_ENABLED :表示本数据读者尚未使能；
     *          - #DDS_RETCODE_TIMEOUT :表示在 @e max_wait 时间内未完成历史数据的接收。
     */
    virtual ReturnCode_t wait_for_historical_data(const Duration_t &max_wait);

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual ReturnCode_t DataReader::get_liveliness_changed_status( LivelinessChangedStatus &status);
     *
     * @brief   获取该数据读者关联的 #DDS_LIVELINESS_CHANGED_STATUS 状态。
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_liveliness_changed_status(
        LivelinessChangedStatus &status);
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual ReturnCode_t DataReader::get_requested_deadline_missed_status( RequestedDeadlineMissedStatus &status);
     *
     * @brief   获取该数据读者关联的 #DDS_REQUESTED_DEADLINE_MISSED_STATUS 状态。
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_requested_deadline_missed_status(
        RequestedDeadlineMissedStatus &status);

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual ReturnCode_t DataReader::get_requested_incompatible_qos_status( RequestedIncompatibleQosStatus &status);
     *
     * @brief   获取该数据读者关联的 #DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS 状态。
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_requested_incompatible_qos_status(
        RequestedIncompatibleQosStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_sample_lost_status(SampleLostStatus &status);
     *
     * @brief   获取该数据读者关联的 #DDS_SAMPLE_LOST_STATUS 状态。
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_sample_lost_status(SampleLostStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_sample_rejected_status( SampleRejectedStatus &status);
     *
     * @brief   获取该数据读者关联的 #DDS_SAMPLE_REJECTED_STATUS 状态。
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_sample_rejected_status(
        SampleRejectedStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_subscription_matched_status( SubscriptionMatchedStatus &status);
     *
     * @brief   获取该数据读者关联的 #DDS_SUBSCRIPTION_MATCHED_STATUS 状态。
     *
     * @param [in,out]  status  出口参数表示当前的状态。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示获取成功。
     */

    virtual ReturnCode_t get_subscription_matched_status(
        SubscriptionMatchedStatus &status);

    /**
     * @fn  virtual TopicDescription* DataReader::get_topicdescription();
     *
     * @brief   获取该数据读者所关联的主题。
     *
     * @return  由于数据读者可以关联以下几种主题，故而返回值为主题的父类对象，用户通过动态转换转化为子类主题对象。
     *          1. 基本主题类型 DDS::Topic ;
     *          2. 基于内容过滤的主题类型 DDS::ContentFilteredTopic ;
     */

    virtual TopicDescription* get_topicdescription();

    /**
     * @fn  virtual Subscriber* DataReader::get_subscriber();
     *
     * @brief   获取该数据读者所属的订阅者对象。
     *
     * @return  该数据读者所属订阅者对象指针。
     */

    virtual Subscriber* get_subscriber();

    /**
     * @fn  virtual ReturnCode_t DataReader::get_matched_publication_data( PublicationBuiltinTopicData &publication_data, const InstanceHandle_t &publication_handle);
     *
     * @brief   该方法查询指定标识的数据写者的内置数据。
     *
     * @param [in,out]  publication_data    出口参数，用于保存通信中间件存储的内置数据；
     * @param   publication_handle          数据写者的唯一标识：可从以下方式获取：
     *                                      - 从内置数据读者数据中获取；
     *                                      - #get_matched_publications 中方法；
     *                                      - 远程数据写者的 DDS::DataWriter::get_instance_handle 获取。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示该数据读者尚未使能；
     *          - #DDS_RETCODE_BAD_PARAMETER :传入的 @e publication_handle 未与该数据读者匹配；
     *          - #DDS_RETCODE_ERROR :表示在拷贝出口参数时发生错误。
     */

    virtual ReturnCode_t get_matched_publication_data(
        PublicationBuiltinTopicData &publication_data,
        const InstanceHandle_t &publication_handle);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_matched_publications( InstanceHandleSeq &publication_handles);
     *
     * @brief   查询已经匹配的远程数据写者的标识列表。
     *
     * @details 返回的列表中不包括通过方法 DomainParticipant::ignore_participant 、
     *          DomainParticipant::ignore_publication 忽略的数据读者，当传入的序列 @e publication_handles
     *          的最大长度小于需要返回的结果时，底层将对 @e publication_handles 进行扩容。
     *
     * @param [in,out]  publication_handles 出口参数，用于保存数据写者的标识。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示该数据读者尚未使能；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :表示分配内存失败。
     */

    virtual ReturnCode_t get_matched_publications(
        InstanceHandleSeq &publication_handles);

    /**
     * @fn  virtual ReturnCode_t DataReader::set_qos(const DataReaderQos &qoslist);
     *
     * @brief   该方法设置为数据读者设置的QoS。
     *
     * @param   qoslist 表示用户想要设置的QoS配置。
     *
     * @details 可以使用特殊值 DDS::DATAREADER_QOS_DEFAULT 以及 DDS::DATAREADER_QOS_USE_TOPIC_QOS 。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示 @e qoslist 含有无效的QoS配置；
     *          - #DDS_RETCODE_INCONSISTENT :表示 @e qoslist 含有不兼容的QoS配置；
     *          - #DDS_RETCODE_IMMUTABLE_POLICY :表示用户尝试修改使能后不可变的QoS配置；
     *          - #DDS_RETCODE_ERROR :表示未归类的错误，错误详细信息输出在日志中；
     */
    virtual ReturnCode_t set_qos(const DataReaderQos &qoslist);

    /**
     * @fn  virtual ReturnCode_t DataReader::get_qos(DataReaderQos &qoslist);
     *
     * @brief   获取该数据读者的QoS配置。
     *
     * @param [in,out]  qoslist 出口参数，用于保存该数据读者的QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_ERROR :表示失败，原因可能为复制QoS时发生错误。
     */

    virtual ReturnCode_t get_qos(DataReaderQos &qoslist);

    /**
     * @fn  virtual ReturnCode_t DataReader::set_listener( DataReaderListener *a_listener, const StatusKindMask &mask);
     *
     * @brief   设置该数据读者的监听器。
     *
     * @details  本方法将覆盖原有监听器，如果设置空对象表示清除原先设置的监听器。
     *
     * @param [in,out]  a_listener  为该数据读者设置的监听器对象。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 表示设置成功。
     */

    virtual ReturnCode_t set_listener(
        DataReaderListener *a_listener,
        const StatusKindMask &mask);

    /**
     * @fn  virtual DataReaderListener* DataReader::get_listener();
     *
     * @brief   该方法获取通过 #set_listener 方法或者创建时为数据读者设置的监听器对象。
     *
     * @return  当前可能的返回值：
     *          - NULL表示未设置监听器；
     *          - 非空表示应用通过 #set_listener 或者在创建时设置的监听器对象。
     */

    virtual DataReaderListener* get_listener();

    /**
     * @fn  virtual StatusCondition* DataReader::get_statuscondition();
     *
     * @brief   实现父类 DDS::Entity 的方法，返回该数据读者关联的状态条件。
     *
     * @return  底层自动创建的状态条件。
     */

    virtual StatusCondition* get_statuscondition();

    /**
     * @fn  virtual StatusKindMask DataReader::get_status_changes();
     *
     * @brief   实现父类 DDS::Entity 的方法，获取该实体从上一次获取任意状态后的状态变化。
     *
     * @return  返回状态的改变掩码。
     */
    virtual StatusKindMask get_status_changes();

    /**
     * @fn  InstanceHandle_t DataReader::get_instance_handle();
     *
     * @brief   实现父类 DDS::Entity 的方法，获取该数据读者的唯一标识。
     *
     * @return  数据读者的唯一标识。
     */
    virtual InstanceHandle_t get_instance_handle();

    /**
     * @fn  virtual ReturnCode_t DataReader::enable();
     *
     * @brief   手动使能该数据读者，参见@ref entity-enable 。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK ，表示获取成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ，表示所属的订阅者尚未使能。
     */

    virtual ReturnCode_t enable();

    /**
     * @fn  virtual ReturnCode_t DataReader::get_data_instance(InstanceHandleSeq &data_seq,
     *      SampleStateMask sampleMask,
     *      ViewStateMask viewMask,
     *      InstanceStateMask  instanceMask);
     *
     * @brief   查询满足条件的数据实例标识。
     *
     * @param [in,out]  data_seq    出口参数，用于存储满足条件的数据实例。
     * @param   sampleMask          样本掩码。
     * @param   viewMask            view掩码。
     * @param   instanceMask        实例状态掩码。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK ，表示获取成功；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES ，表示分配内存失败。
     */
    virtual ReturnCode_t get_data_instance(
        InstanceHandleSeq& data_seq,
        SampleStateMask sampleMask,
        ViewStateMask viewMask,
        InstanceStateMask instanceMask);

    virtual DataReader* get_impl();

    virtual ReturnCode_t read_or_take_untype(DataReaderReadOrTakeParams& result);

    virtual ReturnCode_t read_or_take_next_sample_untype(
        Char* dataValue,
        SampleInfo* sampleInfo,
        Boolean isTake);

    virtual ReturnCode_t return_loan_untype(
        void** dataSeqBuffer,
        Long dataSeqMaxLen,
        SampleInfoSeq* sampleInfos);

    virtual ReturnCode_t return_recv_buffer_untype(
        SampleInfo* sampleInfo);

    virtual ReturnCode_t loan_recv_buffer_untype(
        SampleInfo* sampleInfo);

#ifdef _ZRDDS_INCLUDE_BREAKPOINT_RESUME
    /**
    * @fn  ReturnCode_t DataReader::record_data();
    *
    * @brief   当使用此接口时,数据读者会将已处理数据序列号以及相关读写者Guid记录到运行目录下的zrdds.customer.xml文件中
    *          当数据读者意外下线后重新上线，将读取zrdds.customer.xml文件，根据内容通知数据写者从所记录的未处理数据处开始重传
    *          使用此接口时需注意：
    *             a)数据读者与数据写者的Guid不能改变，需与zrdds.customer.xml文件记录一致(可通过指定实体ID实现)  
    *             b)需设置断点重传 breakpoint_resume = true
    *
    * @param [in]  sample_infos  数据的信息。
    * 
    * @param [in]  finish  数据是否全部消费完成，
    *        true表示数据该类数据全部消费完成，会删除已经记录的用户数据序列号；
    *        false表示数据未全部消费，将会为用户保存数据序列号。
    *
    * @return  数据读者的唯一标识。
    */
    virtual ReturnCode_t record_data(
        SampleInfoSeq &sample_infos,
        ZR_BOOLEAN finish);
#endif//_ZRDDS_INCLUDE_BREAKPOINT_RESUME

    virtual ReturnCode_t get_key_value_untype(
        void* keyHolder,
        const InstanceHandle_t* handle);

    virtual InstanceHandle_t lookup_instance_untype(
        const void* instance);

protected:

    DataReader(DataReader* impl);

protected:
    DataReader* m_cppImpl;
};

typedef DataReader* DataReaderPtr;

// 声明DataReaderPtrSeq类
DDS_SEQUENCE_CPP(DataReaderSeq, DataReaderPtr);

} // namespace DDS

#endif  //_DATAREADER_H
