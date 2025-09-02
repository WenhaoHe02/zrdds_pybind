/**
 * @file:       DomainParticipantFactory.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINPARTICIPANTFACTORY_H)
#define _DOMAINPARTICIPANTFACTORY_H

#include "ZRDDSCppWrapper.h" 

struct ZRDynamicData;
struct TypeCodeHeader;

namespace DDS {

class DomainListener;
class DomainParticipantListener;
class DomainParticipant;
class Entity;

/**
 * @class   DomainParticipantFactory
 *
 * @ingroup CppDomain
 *
 * @brief   域参与者工厂接口的核心功能在于是创建以及销毁域参与者实体，即作为域参与者实体的工厂，域参与者工厂是一个单例类。
 */

class DCPSDLL DomainParticipantFactory
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual DomainParticipant* DomainParticipantFactory::lookup_participant_by_name( const Char* name)=0;
     *
     * @brief 按名字精确查找Participant
     *
     * @param name Participant的名字，如果创建时以Application为根元素创建，该名字中必须包含Application名字，格式为/<ApplicationName>/<ParticipantName>
     *
     * @return null if it fails, else a DomainParticipant*
     */
    virtual DomainParticipant* lookup_participant_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual Entity* DomainParticipantFactory::lookup_entity_by_name( const Char* name)=0;
     *
     * @brief 按名字精确查找实体
     *
     * @param name 实体名字
     *
     * @return null if it fails, else an Entity*
     */
    virtual Entity* lookup_entity_by_name(
        const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::add_to_type_library_from_xml_string(const Char* xml_content) = 0;
     *
     * @brief 将XML描述的类型添加到类型库
     *
     * @param xml_content 以types为根的元素的XML字符串
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示添加成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *          - #DDS_RETCODE_ERROR :表示添加失败。
     */
    virtual ReturnCode_t add_to_type_library_from_xml_string(
        const Char* xml_content) = 0;

    /**
     * @fn virtual ZRDynamicData* DomainParticipantFactory::gen_dynamic_data(const Char* type_name, const Char* xml_content) = 0;
     *
     * @brief 从XML生成DynamicData
     *
     * @param type_name   在TypeLibrary添加过的类型名
     * @param xml_content 以XML描述的Data
     *
     * @return  当前可能的返回值如下：
     *          - 非空表明生成成功；
     *          - NULL表明生成失败。
     */
    virtual ZRDynamicData* gen_dynamic_data(
        const Char* type_name,
        const Char* xml_content) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_named_participants( const Char* pattern, StringSeq& participant_names) = 0;
     *
     * @brief 查找名称符合pattern限定的域参与者。
     *
     * @param pattern                    查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param [in,out] participant_names 查找得到的Participant名字列表
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示查找成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_named_participants(
        const Char* pattern,
        StringSeq& participant_names) = 0;

    /**
     * @fn virtual TypeCodeHeader* DomainParticipantFactory::lookup_type_by_name(const Char* name) = 0;
     *
     * @brief 按名字查找一个类型
     *
     * @param name 类型的名称，嵌套类型通过“::”分隔。
     *
     * @return 查找得到的类型对应的 #TypeCodeHeader
     */
    virtual TypeCodeHeader* lookup_type_by_name(const Char* name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_named_types(const Char* pattern, Long reference_depth, StringSeq& type_names) = 0;
     *
     * @brief 在类型库中查找名字符合pattern的类型
     *
     * @param pattern             查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param reference_depth     暂时无用，请填入-1
     * @param [in,out] type_names 查找得到类型名称列表
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示查找成功；
     *         - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_named_types(
        const Char* pattern,
        Long reference_depth,
        StringSeq& type_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::type_to_xml( const Char* type_name, const Char*& result) = 0;
     *
     * @brief 将指定名称的类型转换为XML
     *
     * @param type_name       类型库中的类型名称，嵌套类型通过“::”分隔。
     * @param [in,out] result 用于保存转换结果。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示转换成功；
     *         - #DDS_RETCODE_ERROR :表示转换失败。
     */
    virtual ReturnCode_t type_to_xml(
        const Char* type_name,
        const Char*& result) = 0;

    /**
     * @fn virtual DomainParticipant* DomainParticipantFactory::create_participant_from_xml_string( const Char* xml_content) = 0;
     *
     * @brief 从XML创建Participant，XML格式为domain_participant
     *
     * @param xml_content 以XML文本表示的域参与者。
     *
     * @return  当前可能的返回值如下：
     *          - 非空表示创建域参与者成功；
     *          - NULL表示创建失败。
     */
    virtual DomainParticipant* create_participant_from_xml_string(
        const Char* xml_content) = 0;

    static DomainParticipantFactory* new_instance(const DomainParticipantFactoryQos &qoslist);
    static ReturnCode_t delete_instance(DomainParticipantFactory* factory);

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn  DomainParticipantFactory* DomainParticipantFactory::get_instance_w_profile(const Char* qosFilePath, const Char* libName, const Char* profileName, const Char* qosName);
     *
     * @brief   以指定参数初始化DDS域参与者工厂。
     *
     * @param   qosFilePath qos配置文件路径，当为NULL时，将默认使用运行目录的 ZRDDS_QOS_PROFILES.xml 文件。
     * @param   libName     Qos库名称，不允许为NULL。
     * @param   profileName Qos配置名称，不允许为NULL。
     * @param   qosName     Qos名称，允许为空，将转化为default字符串。
     *
     * @return  NULL表示失败，否则返回单例指针。
     */

    static DomainParticipantFactory* get_instance_w_profile(const Char* qosFilePath, const Char* libName, const Char* profileName, const Char* qosName);

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::reload_qos_profiles() = 0;
     *
     * @brief 根据QosProfileQosPolicy（有关QoS配置的配置）配置重新加载QoS配置到库中，在DomainParticipantFactory初始化时隐式调用，
     *          异常处理逻辑：
     *          - 当配置的路径不存在时，忽略该条并提示用户，返回RETCODE_OK
     *          - 当配置的XML存在不可忽略的错误时（XML格式错误等）,提示用户，并返回RETCODE_ERROR
     *        其中的UserData、GroupData、TopicData可以支持使用String方式和Sequence方式设置
     *          - String方式为将字符串直接作为value节点的text
     *          - Sequence方式为将value当成Sequence使用（即设置其sequenceMaxLength属性），并将每个元素作为element写入
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功或配置的路径不存在；
     *         - #DDS_RETCODE_BAD_PARAMETER ：表示参数不正确导致的添加QoS库错误
     *         - #DDS_RETCODE_ERROR :表示XML存在错误导致QoS库添加失败；
     */
    virtual ReturnCode_t reload_qos_profiles() = 0;

    /**
     * @fn virtual void DomainParticipantFactory::unload_qos_profiles()=0;
     *
     * @brief 卸载所有的QoS配置
     */
    virtual void unload_qos_profiles() = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief 从QoS仓库获取QoS配置并设置到域参与者工厂
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
     * @fn virtual ReturnCode_t DomainParticipantFactory::set_default_participant_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief 从QoS仓库获取域参与者QoS并将其设为默认域参与者QoS
     *
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t set_default_participant_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::get_participant_factory_qos_from_profile( DomainParticipantFactoryQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name) = 0;
     *
     * @brief   从QoS仓库获取域参与者工厂QoS的配置
     *
     * @param [in,out]  qos     获取到的QoS
     * @param   library_name    QoS库的名字，不允许为NULL。
     * @param   profile_name    QoS配置的名字，不允许为NULL。
     * @param   qos_name        QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示设置成功；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */

    virtual ReturnCode_t get_participant_factory_qos_from_profile(
        DomainParticipantFactoryQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_participant_qos_from_profile( DomainParticipantQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取域参与者QoS的配置
     *
     * @param [in,out] qos 获取到的QoS
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t get_participant_qos_from_profile(
        DomainParticipantQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_publisher_qos_from_profile( PublisherQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取发布者QoS的配置
     *
     * @param [in,out] qos 获取到的QoS
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t get_publisher_qos_from_profile(
        PublisherQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_subscriber_qos_from_profile( SubscriberQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取订阅者QoS的配置
     *
     * @param [in,out] qos 获取到的QoS
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t get_subscriber_qos_from_profile(
        SubscriberQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_topic_qos_from_profile( TopicQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取主题QoS的配置
     *
     * @param [in,out] qos 获取到的QoS
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t get_topic_qos_from_profile(
        TopicQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_datawriter_qos_from_profile( DataWriterQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取数据写者QoS的配置
     *
     * @param [in,out] qos 获取到的QoS
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t get_datawriter_qos_from_profile(
        DataWriterQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::get_datareader_qos_from_profile( DataReaderQos& qos, const Char* library_name, const Char* profile_name, const Char* qos_name)=0;
     *
     * @brief 从QoS仓库获取数据读者QoS的配置
     *
     * @param [in,out] qos 获取到的QoS
     * @param library_name QoS库的名字，不允许为NULL。
     * @param profile_name QoS配置的名字，不允许为NULL。
     * @param qos_name     QoS的名字，允许为NULL，将转换为default字符串。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示设置成功；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的设置错误。
     */
    virtual ReturnCode_t get_datareader_qos_from_profile(
        DataReaderQos& qos,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name) = 0;

    /**
     * @fn virtual DomainParticipant* DomainParticipantFactory::create_participant_with_qos_profile( const DomainId_t domainId, const Char* library_name, const Char* profile_name, const Char* qos_name, DomainParticipantListener* listener, StatusKindMask mask) = 0;
     *
     * @brief 从QoS仓库获取QoS配置并用其创建域参与者
     *
     * @param domainId      域Id
     * @param library_name  QoS库的名字，不允许为NULL。
     * @param profile_name  QoS配置的名字，不允许为NULL。
     * @param qos_name      QoS的名字，允许为NULL，将转换为default字符串。
     * @param [in] listener 为该域参与者设置的监听器。
     * @param mask          设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  当前可能的返回值如下：
     *          - 非空表示创建域参与者成功；
     *          - NULL表示创建失败。
     */
    virtual DomainParticipant* create_participant_with_qos_profile(
        const DomainId_t domainId,
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name,
        DomainParticipantListener* listener,
        StatusKindMask mask) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::add_qos_library(const Char* xml_representation) = 0;
     *
     * @brief 添加一个QoS库
     *
     * @param xml_representation 以XML字符串表示的QoS库。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示添加成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示添加失败。
     */
    virtual ReturnCode_t add_qos_library(const Char* xml_representation) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::remove_qos_library(const Char* qos_library_name) = 0;
     *
     * @brief 删除一个QoS库
     *
     * @param qos_library_name 需要被移除的QoS库的名称
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示移除成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示移除失败。
     */
    virtual ReturnCode_t remove_qos_library(const Char* qos_library_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::add_qos_profile(const Char* qos_library_name, const Char* xml_representation) = 0;
     *
     * @brief 在指定QoS库中添加一个QoS配置
     *
     * @param qos_library_name   需要添加QoS配置的QoS库。
     * @param xml_representation 以XML表示的QoS配置内容。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示添加成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示添加失败。
     */
    virtual ReturnCode_t add_qos_profile(
        const Char* qos_library_name,
        const Char* xml_representation) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::remove_qos_profile(const Char* qos_library_name, const Char* qos_profile_name) = 0;
     *
     * @brief 从指定QoS库中移除一个QoS配置
     *
     * @param qos_library_name QoS库的名称。
     * @param qos_profile_name QoS配置的名称。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示移除成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示移除失败。
     */
    virtual ReturnCode_t remove_qos_profile(
        const Char* qos_library_name,
        const Char* qos_profile_name) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::qos_library_to_xml(const Char* qos_library_name, const Char*& result) = 0;
     *
     * @brief 将QoS库转换为XML
     *
     * @param qos_library_name QoS库的名称。
     * @param [in,out] result  转换得到的结果。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示转换成功；
     *         - #DDS_RETCODE_ERROR :表示转换失败。
     */
    virtual ReturnCode_t qos_library_to_xml(
        const Char* qos_library_name,
        const Char*& result) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::qos_profile_to_xml(const Char* qos_library_name, const Char* qos_profile_name, const Char*& result) = 0;
     *
     * @brief 将一个QoS配置转换为XML
     *
     * @param qos_library_name QoS库的名称。
     * @param qos_profile_name QoS配置的名称。
     * @param [in,out] result  转换得到的结果。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示转换成功；
     *         - #DDS_RETCODE_ERROR :表示转换失败。
     */
    virtual ReturnCode_t qos_profile_to_xml(
        const Char* qos_library_name,
        const Char* qos_profile_name,
        const Char*& result) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_qos_libraries( const Char* pattern, StringSeq& qos_library_names) = 0;
     *
     * @brief 查找名称符合pattern限定的QoS库
     *
     * @param pattern                    查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符。
     * @param [in,out] qos_library_names 查找得到的QoS库名字列表。
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示查找成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_qos_libraries(
        const Char* pattern,
        StringSeq& qos_library_names) = 0;

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::lookup_qos_profiles( const Char* qos_library_name, const Char* pattern, StringSeq& qos_profile_names) = 0;
     *
     * @brief 在指定QoS库中查找名字符合pattern的QoS配置
     *
     * @param qos_library_name           QoS库的名字，不允许为NULL。
     * @param pattern                    查找模式，可以支持*及?，*代表任意数量的任意字符，?代表任意单个字符
     * @param [in,out] qos_profile_names 查找得到的QoS配置名字列表
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示查找成功；
     *         - #DDS_RETCODE_BAD_PARAMETER :表示参数存在错误，如缺失参数；
     *         - #DDS_RETCODE_ERROR :表示查找失败。
     */
    virtual ReturnCode_t lookup_qos_profiles(
        const Char* qos_library_name,
        const Char* pattern,
        StringSeq& qos_profile_names) = 0;

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    /**
     * @fn  virtual DomainParticipant* DomainParticipantFactory::create_participant( const DomainId_t &domainId, const DomainParticipantQos &qoslist, DomainParticipantListener *a_listener, const StatusKindMask &mask) = 0;
     *
     * @brief   创建一个新的域参与者实体，并设置QoS以及监听器，域参与者的创建表明应用程序打算加入@e domainId 指定的域中进行通信。
     *
     * @param   domainId            表明需要加入的域号，取值范围为[0-232]。
     * @param   qoslist             表示为该域参与者设置的QoS，#DOMAINPARTICIPANT_QOS_DEFAULT 表明使用域参与者工厂中保存的默认的QoS。
     * @param [in,out]  a_listener  为该域参与者设置的监听器。
     * @param   mask                设置应用程序感兴趣的状态，只有应用程序感兴趣的状态发生变化时，才会通知应用程序。
     *
     * @return  创建成功指向创建成功的域参与者实体对象，否则返回NULL，失败的原因可能为：
     *          - 分配空间失败或者初始化资源失败，具体的错误信息参见日志；  
     *          - @e qoslist 含有无效值或者含有不一致的QoS。
     */

    virtual DomainParticipant* create_participant(
        const DomainId_t &domainId,
        const DomainParticipantQos &qoslist,
        DomainParticipantListener *a_listener,
        const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::delete_participant(DomainParticipant *a_dp) = 0;
     *
     * @brief   该方法删除指定的域参与者。在调用该方法之前需要保证该域参与者的所有子实体都已经被删除。否则将会返回错误
     *
     * @param [in,out]  a_dp    指明需要删除的域参与者实体。
     *
     * @return  可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示删除成功；  
     *          - #DDS_RETCODE_BAD_PARAMETER :用户提供的参数不是有效的域参与者对象，包括NULL值；  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :指明的域参与者不满足删除条件，即还有子实体未删除；  
     *          - #DDS_RETCODE_ERROR :指明的域参与者不是由工厂创建。
     */

    virtual ReturnCode_t delete_participant(DomainParticipant *a_dp) = 0;

    /**
     * @fn  static DomainParticipantFactory* DomainParticipantFactory::get_instance();
     *
     * @brief   获取域参与者工厂单例对象， #TheParticipantFactory 宏为该函数的简写。
     *
     * @return  当前可能的返回值：
     *          - NULL表示创建单例对象失败，可能的原因：  
     *              - 初始化资源失败，详细参见日志；  
     *              - Mac或者时间验证失败；
     *          - 获取成功的单例对象指针；   
     *
     * @note    该方法线程不安全，多个线程同时创建实例不安全，获取实例安全。
     */

    static DomainParticipantFactory* get_instance();

    /**
     * @fn  static DomainParticipantFactory* get_instance_w_qos(const DomainParticipantFactoryQos &qoslist);
     *
     * @brief   使用指定的DomainParticipantFactoryQos来获取域参与者工厂的单例对象.
     *
     * @param   qoslist 指定的DomainParticipantFactoryQos.
     *
     * @return  当前可能的返回值：
     *          - NULL表示创建单例对象失败，可能的原因：
     *              - 初始化资源失败，详细参见日志；
     *              - Mac或者时间验证失败；
     *          - 获取成功的单例对象指针；
     *          
     * @note    该方法线程不安全，多个线程同时创建实例不安全，获取实例安全。.
     */

    static DomainParticipantFactory* get_instance_w_qos(const DomainParticipantFactoryQos &qoslist);

    /**
     * @fn  static ReturnCode_t DomainParticipantFactory::finalize_instance();
     *
     * @brief   析构单例，该方法同样是线程不安全的，多个线程同时调用该函数，可能会出问题。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示析构成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :由该域参与者工厂创建的域参与者未删除完；
     */

    static ReturnCode_t finalize_instance();

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::delete_contained_entities() = 0;
     *
     * @brief   删除所有的域参与者及其子实体，该函数将尝试删除所有满足删除条件的子实体。
     *
     * @return  可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示删除成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :某些域参与者不满足删除条件，即还有子实体未删除；
     *          - #DDS_RETCODE_ERROR :指明的域参与者不是由工厂创建。
     */

    virtual ReturnCode_t delete_contained_entities() = 0;

    /**
     * @fn  virtual DomainParticipant* DomainParticipantFactory::lookup_participant(const DomainId_t &domainId) = 0;
     *
     * @brief   该方法在指定域@e domainId 下查找域参与者，如果有多个域参与者，则返回其中一个。
     *
     * @param   domainId    需要查找的域。
     *
     * @return  当前可能的返回值：
     *          - NULL表示查找失败，即本地在该域下当前没有域参与者；  
     *          - 非空表示查找的结果，返回的结果为该域下域参与者指针最小的域参与者。
     */

    virtual DomainParticipant* lookup_participant(const DomainId_t &domainId) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::set_default_participant_qos(const DomainParticipantQos &qoslist) = 0;
     *
     * @brief   该方法设置该工厂为域参与者保存的默认QoS配置。
     *          
     * @details 默认的QoS在创建新的域参与者时指定QoS参数为 DDS::DOMAINPARTICIPANT_QOS_DEFAULT 时使用的QoS配置，
     *          使用特殊的值 DDS::DOMAINPARTICIPANT_QOS_DEFAULT 域参与者QoS中的各个配置的设置为默认值。
     *
     * @param   qoslist 指明QoS配置。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示设置成功；  
     *          - #DDS_RETCODE_BAD_PARAMETER :表示@e qoslist为空，或者@e qoslist 具有无效值；   
     *          - #DDS_RETCODE_INCONSISTENT :表示@e qoslist 中具有不相容的配置；   
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t set_default_participant_qos(const DomainParticipantQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::get_default_participant_qos(DomainParticipantQos &qoslist) = 0;
     *
     * @brief   该方法获取该工厂为域参与者保存的默认QoS配置。
     *
     * @param [in,out]  qoslist 出口参数表示获取的结果.
     *
     * @return  当前的返回值类型：
     *          - #DDS_RETCODE_OK :表示设置成功；  
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t get_default_participant_qos(DomainParticipantQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::set_qos(const DomainParticipantFactoryQos &qoslist) = 0;
     *
     * @brief   该方法设置域参与者工厂本身的QoS，特殊的值 DDS::DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT 表示设置为默认值。
     *
     * @param   qoslist 指明目标QoS。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示设置成功；  
     *          - #DDS_RETCODE_BAD_PARAMETER :表示@e qoslist为空，或者@e qoslist 具有无效值；   
     *          - #DDS_RETCODE_INCONSISTENT :表示@e qoslist 中具有不相容的配置；   
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t set_qos(const DomainParticipantFactoryQos &qoslist) = 0;

    /**
     * @fn  virtual ReturnCode_t DomainParticipantFactory::get_qos(DomainParticipantFactoryQos &qoslist) = 0;
     *
     * @brief   该方法获取为域参与者工厂设置的QoS。
     *          
     * @details 如果调用该方法之前未调用过 #set_qos ，则返回系统默认的QoS配置，否则返回 #set_qos 的结果。
     *
     * @param [in,out]  qoslist 出口参数，存储获取的结果。
     *
     * @return  当前的返回值类型：
     *          - #DDS_RETCODE_OK :表示设置成功；  
     *          - #DDS_RETCODE_ERROR :表示失败，例如复制QoS时发生错误。
     */

    virtual ReturnCode_t get_qos(DomainParticipantFactoryQos &qoslist) = 0;

#ifdef _ZRDDSSECURITY

    /**
     * @fn virtual ReturnCode_t DomainParticipantFactory::load_security_plugin( const Char* plugin_name, const Char* file_name, const Char* retrieve_instance_func_name, const Char* finalize_instance_func_name) = 0;
     *
     * @brief 加载安全插件
     *
     * @details - 在Windows和Linux内核系统中，安全插件以动态库的形式提供（Windows：.dll，Linux：.so），
     *          可以在运行时通过调用该函数加载。
     *          - 在VxWorks和ReWorks中，安全插件以开发库的形式提供（.a），必须在开发应用时一同编译到应用中，  
     *          并在需要使用安全插件之前调用该函数。此时的调用 @e file_name 参数不起作用。
     *          注意：由于ReWorks的基础开发环境ReDe在编译时未被直接引用的符号会在编译过程中被删除，
     *          因此需要在使用安全插件的应用中放置一个函数，在函数中调用安全插件获取实例和删除实例的函数，
     *          避免这两个函数被编译器优化。
     *
     * @param plugin_name                 为当前加载的安全插件赋予的名称，用于在创建域参与者时引用安全插件。
     * @param file_name                   安全插件的文件名称，在Windows中是动态链接库（dll），Linux中是动态库（so），VxWorks和ReWorks中此参数不起作用。
     * @param retrieve_instance_func_name 安全插件中获取实例的函数名称，需要参考安全插件的使用手册获知。
     * @param finalize_instance_func_name 安全插件中删除实例的函数名称，需要参考安全插件的使用手册获知。
     *
     * @return 当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示加载成功；
     *          - #DDS_RETCODE_ERROR :表示加载失败，失败的原因包含：插件文件不存在、加载文件失败、获取安全插件中的函数失败、获取实例失败，详见运行时日志信息。
     */
    virtual ReturnCode_t load_security_plugin(
        const Char* plugin_name,
        const Char* file_name,
        const Char* retrieve_instance_func_name,
        const Char* finalize_instance_func_name) = 0;
#endif // _ZRDDSSECURITY
protected:

    virtual ~DomainParticipantFactory();
};

/**
 * @def TheParticipantFactory
 *
 * @ingroup CppDomain
 *
 * @brief   该宏作为 DDS::DomainParticipantFactory::get_instance 的缩写。
 */

#define TheParticipantFactory DomainParticipantFactory::get_instance()

} // namespace DDS

#endif  //_DOMAINPARTICIPANTFACTORY_H
