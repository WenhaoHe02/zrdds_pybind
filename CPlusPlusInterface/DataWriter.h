/**
 * @file:       DataWriter.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataWriter_h__
#define DataWriter_h__

#include "DomainEntity.h"
#include "Topic.h"
#include "DataWriterListener.h"
#include "ZRDDSCppWrapper.h"

struct DataWriterImpl;
struct DataWriterListenerImpl;
struct ZRDynamicData;

namespace DDS {

class Publisher;

/**
 * @class DataWriter
 *
 * @ingroup CppPublication
 *
 * @brief DDS��׼�е����ݶ��߽ӿڡ�
 *
 * @details ���ݶ�д��Ҫ����洢Ϊ�û��ṩ�������ݵĹ��ܣ����ݶ�д�ӿڰ�������ӿڣ�
 *          - �û����������޹ؽӿڣ����༴��������Щ���û������޹صĽӿڣ���Ϊ�û����͵�����д�ߵĸ��ࡣ
 *          - �û�����������ؽӿڣ�ͨ����ģ��ʵ�֣� DDS::ZRDDSDataWriter
 */
class DCPSDLL DataWriter : public DomainEntity
{
public:
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn virtual ReturnCode_t DataWriter::parse_write_sample_info_xml( const Char* xml_content, SampleInfo* sample_info, SampleInfoValidMember* valid_sample_info_member);
     *
     * @brief ������XML��ʾ��SampleInfo��XML��ʽΪwrite_sample_info
     *
     * @param xml_content                       ��XML��ʾ��SampleInfo��XML��ʽΪwrite_sample_info
     * @param [in,out] sample_info              �����SampleInfo�ṹ�������Ľ���ᱻ�����ڸýṹ��
     * @param [in,out] valid_sample_info_member �����SampleInfoValidMember�ṹ��ָ����������sample_info��������Щ��Ա��Ч
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ�����ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĽ�������
     */
    virtual ReturnCode_t parse_write_sample_info_xml(
        const Char* xml_content,
        SampleInfo* sample_info,
        SampleInfoValidMember* valid_sample_info_member);

    /**
     * @fn virtual ReturnCode_t DataWriter::parse_write_sample_xml( const Char* xml_content, ZRDynamicData*& data);
     *
     * @brief ������XML��ʾ����������������DynamicData��XML��ʽΪdata
     *
     * @param xml_content   ��XML��ʾ���������������������봴����Writer��Topic���������ͱ���ƥ��
     * @param [in,out] data [in,out] ��XML������DynamicData
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ�����ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĽ�������
     */
    virtual ReturnCode_t parse_write_sample_xml(
        const Char* xml_content,
        ZRDynamicData*& data);

    /**
     * @fn virtual ReturnCode_t DataWriter::return_xml_sample( ZRDynamicData* data);
     *
     * @brief ���ٴ� #DataWriter::return_xml_sample ��ȡ��������������
     *
     * @param [in,out] data �����ٵ�����������
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���ٳɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ٴ���
     */
    virtual ReturnCode_t return_xml_sample(
        ZRDynamicData* data);

    /**
     * @fn virtual ReturnCode_t DataWriter::to_xml(const Char*& result, Boolean containedQos);
     *
     * @brief ��Writerת����XML��XML���ڵ�Ϊdata_writer
     *
     * @param [in,out] result ���ɵ�XML
     * @param containedQos    �����Ƿ����QoS
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾת���ɹ���
     *         - #DDS_RETCODE_OUT_OF_RESOURCES :��ȡ��Դʧ�ܣ�һ��Ϊ�ڴ治�㵼�£�
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ�ת������
     */
    virtual ReturnCode_t to_xml(const Char*& result, Boolean containedQos = true);

    /**
     * @fn virtual const Char* DataWriter::get_entity_name();
     *
     * @brief ��ȡEntity������
     *
     * @return ����д�����ơ�
     */
    virtual const Char* get_entity_name();

    /**
     * @fn virtual Entity* DataWriter::get_factory();
     *
     * @brief ��ȡ����ָ�룬��������ָ��
     *
     * @return ��ȡ���Ĺ���ָ�롣
     */
    virtual Entity* get_factory();

#endif // _ZRXMLENTITYINTERFACE

#ifdef _ZRXMLQOSINTERFACE

    /**
     * @fn virtual ReturnCode_t DataWriter::set_qos_with_profile( const Char* library_name, const Char* profile_name, const Char* qos_name);
     *
     * @brief ��QoS�ֿ��ȡQoS���ò����õ�����д�ߡ�
     *
     * @param library_name QoS������֣�������ΪNULL��
     * @param profile_name QoS���õ����֣�������ΪNULL��
     * @param qos_name     QoS�����֣�����ΪNULL����ת��Ϊdefault�ַ�����
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���óɹ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µ����ô���
     */
    virtual ReturnCode_t set_qos_with_profile(
        const Char* library_name,
        const Char* profile_name,
        const Char* qos_name);

#endif // _ZRXMLQOSINTERFACE

#endif // _ZRXMLINTERFACE

    DataWriter(DataWriter *dw);

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    /**
     * @fn  virtual ReturnCode_t DataWriter::get_liveliness_lost_status( LivelinessLostStatus &status);
     *
     * @brief   ��ȡ����д�߹����� #DDS_LIVELINESS_LOST_STATUS ״̬��
     *
     * @param [in,out]  status  ��ȡ����LIVELINESS_LOST��ͨ��״̬��
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */

    virtual ReturnCode_t get_liveliness_lost_status(
        LivelinessLostStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataWriter::assert_liveliness();
     *
     * @brief   ���������Ĵ����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ�����ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_NOT_ENABLED :����д��δʹ�ܣ�
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µ���������
     */

    virtual ReturnCode_t assert_liveliness();
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    /**
     * @fn  virtual ReturnCode_t DataWriter::get_offered_deadline_missed_status( OfferedDeadlineMissedStatus &status);
     *
     * @brief   ��ȡ����д�߹����� #DDS_OFFERED_DEADLINE_MISSED_STATUS ״̬��
     *
     * @param [in,out]  status  ��ȡ����OFFERED_DEADLINE_MISSED״̬��
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */

    virtual ReturnCode_t get_offered_deadline_missed_status(
        OfferedDeadlineMissedStatus &status);

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_offered_incompatible_qos_status( OfferedIncompatibleQosStatus &status);
     *
     * @brief   ��ȡ����д�߹����� #DDS_OFFERED_INCOMPATIBLE_QOS_STATUS ״̬��
     *
     * @param [in,out]  status  ��ȡ����INCOMPATIBLE_QOS״̬��
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */

    virtual ReturnCode_t get_offered_incompatible_qos_status(
        OfferedIncompatibleQosStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_publication_matched_status( PublicationMatchedStatus &status);
     *
     * @brief   ��ȡ����д�߹����� #DDS_PUBLICATION_MATCHED_STATUS ״̬��
     *
     * @param [in,out]  status  ��ȡ��������д��ƥ��״̬��
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */

    virtual ReturnCode_t get_publication_matched_status(
        PublicationMatchedStatus &status);

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_matched_subscriptions( InstanceHandleSeq &handles);
     *
     * @brief   ��ȡ��ƥ����û�б����ԵĶ����߾���б���
     *
     * @param [in,out]  handles ��ȡ������ƥ����û�б����ԵĶ����߾���б���
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_NOT_ENABLED :����д��δʹ�ܣ�
     *         - #DDS_RETCODE_OUT_OF_RESOURCES :��ȡ��Դʧ�ܣ�һ��Ϊ�ڴ治�㵼�£�
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */

    virtual ReturnCode_t get_matched_subscriptions(
        InstanceHandleSeq &handles);

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_matched_subscription_data( SubscriptionBuiltinTopicData &subscription_data, const InstanceHandle_t& a_handle);
     *
     * @brief   ��ȡָ������ƥ�䶩���ߵ���ϸ��Ϣ��
     *
     * @param [in,out]  subscription_data   ���涩������ϸ��Ϣ�Ľṹ.
     * @param   a_handle                    �� #get_matched_subscriptions ��ȡ���Ķ����߾����
     *
     * @return  ��ǰ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *          - #DDS_RETCODE_NOT_ENABLED :����д��δʹ�ܣ�
     *          - #DDS_RETCODE_ERROR :��ʾδ֪�����µĶ�ȡ����
     */

    virtual ReturnCode_t get_matched_subscription_data(
        SubscriptionBuiltinTopicData &subscription_data,
        const InstanceHandle_t& a_handle);

    /**
     * @fn  virtual ReturnCode_t DataWriter::wait_for_acknowledgments(const Duration_t &max_wait);
     *
     * @brief   �Կɿ�������д�ߵ��ô˺��������µ����ߵ�������ֱ�������ѷ��������ݱ�Ӧ����ߵȴ���ʱ��
     *
     * @param   max_wait    ��ȴ�ʱ�䡣
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ���������������Ѿ��������ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_NOT_ENABLED :����д��δʹ�ܣ�
     *         - #DDS_RETCODE_TIMEOUT :��ʾ�ȴ���ʱ��
     *         - #DDS_RETCODE_ERROR :��ʾδ֪�����µĵȴ�����
     */

    virtual ReturnCode_t wait_for_acknowledgments(const Duration_t &max_wait);

    /**
     * @fn  virtual Topic* DataWriter::get_topic();
     *
     * @brief   ��ȡ������д�������������⡣
     *
     * @return  ��������д�߹��������⡣
     */

    virtual Topic* get_topic();

    /**
     * @fn  virtual Publisher* DataWriter::get_publisher();
     *
     * @brief   ��ȡ������DataWriter��Publisher��
     *
     * @return  ������DataWriter��Publisher��
     */

    virtual Publisher* get_publisher();

    /**
     * @fn  virtual ReturnCode_t DataWriter::set_qos(const DataWriterQos &qoslist);
     *
     * @brief   ����DataWriterQoS��
     *
     * @details QoSӰ��DataWriter����Ϊ������QoSֻ����DataWriterʹ��֮ǰ�޸ġ�
     *          �û����뱣֤QoS����ȷ�ԣ�������ڳ�ͻ�����ý���ʧ�ܡ�
     *          ����ļ����б�����QoS�ĵ���
     *
     * @param   qoslist ���������Ҫ�����QoS��
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ���óɹ���
     *          - #DDS_RETCODE_IMMUTABLE_POLICY ������ʹ�ܺ��޸ĵ�QoS��
     *          - #DDS_RETCODE_INCONSISTENT QoS���ڳ�ͻ��
     *          - #DDS_RETCODE_BAD_PARAMETER �����������⡣
     *          - #DDS_RETCODE_ERROR δ�������
     */

    virtual ReturnCode_t set_qos(const DataWriterQos &qoslist);

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_qos(DataWriterQos &qoslist);
     *
     * @brief   ��ȡ��ǰ����д�ߵ�QoS��
     *
     * @param [in,out]  qoslist �����ȡ����QoS��
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ��ȡ�ɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER �����������⡣
     *          - #DDS_RETCODE_ERROR δ�������
     */

    virtual ReturnCode_t get_qos(DataWriterQos &qoslist);

    /**
     * @fn  virtual ReturnCode_t DataWriter::set_listener( DataWriterListener* a_listener, const StatusKindMask &mask);
     *
     * @brief   ��������д�߼�������
     *
     * @param   a_listener  �û��ṩ�ļ��������󣬿��Դ���NULL���������
     * @param   mask        ״̬���룬ָ����Ҫ�������������״̬��
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ���óɹ���
     */

    virtual ReturnCode_t set_listener(
        DataWriterListener* a_listener,
        const StatusKindMask &mask);

    /**
     * @fn  virtual DataWriterListener* DataWriter::get_listener();
     *
     * @brief   ��ȡ��ǰ����д�ߵļ�������
     *
     * @return  ���ܵķ���ֵ���£�
     *          - NULL��ʾδ���ü�������
     *          - �ǿձ�ʾӦ��ͨ�� #set_listener �����ڴ���ʱ���õļ���������
     */

    virtual DataWriterListener* get_listener();

    /**
     * @fn  StatusCondition* DataWriter::get_statuscondition();
     *
     * @brief   ʵ�ָ��� DDS::Entity �ķ��������ظ�����д�߹�����״̬������
     *
     * @return  �ײ��Զ�������״̬������
     */

    StatusCondition* get_statuscondition();

    /**
     * @fn   virtual StatusKindMask DataWriter::get_status_changes();
     *
     * @brief    ʵ�ָ��� DDS::Entity �ķ�������ȡ��ʵ�����һ�λ�ȡ����״̬���״̬�仯��
     *
     * @return   ����״̬�ĸı����롣
     */

    virtual StatusKindMask get_status_changes();

    /**
     * @fn  virtual ReturnCode_t DataWriter::enable();
     *
     * @brief   �ֶ�ʹ�ܸ�����д�ߡ�
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ʹ�ܳɹ���
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ����д�������ķ����߻�δʹ�ܡ�
     *          - #DDS_RETCODE_ERROR δ�������
     */

    virtual ReturnCode_t enable();

    /**
     * @fn virtual InstanceHandle_t DataWriter::get_instance_handle();
     *
     * @brief ʵ�ָ��� DDS::Entity �ķ�������ȡ������д�ߵ�Ψһ��ʶ��
     *
     * @return ����д�ߵ�Ψһ��ʶ��
     */
    virtual InstanceHandle_t get_instance_handle();

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_send_status(PublicationSendStatusSeq &status);
     *
     * @brief   ��ȡ����ƥ����û�б����Ե����ݶ���֮��ͨ��״̬�б���
     *
     * @param [in,out]  status ��ȡ��������ƥ����û�б����Ե����ݶ���֮��ͨ��״̬�б���
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_NOT_ENABLED :����д��δʹ�ܣ�
     *         - #DDS_RETCODE_OUT_OF_RESOURCES :��ȡ��Դʧ�ܣ�һ��Ϊ�ڴ治�㵼�£�
     */

    virtual ReturnCode_t get_send_status(PublicationSendStatusSeq &status);

    /**
     * @fn  virtual ReturnCode_t DataWriter::print_send_status(PublicationSendStatusSeq &status);
     *
     * @brief   ��ӡ�����ݶ���֮��ͨ��״̬�б���
     *
     * @param   status ͨ�� #get_send_status ��ȡ��������ƥ����û�б����Ե����ݶ���֮��ͨ��״̬�б���
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     */

    virtual ReturnCode_t print_send_status(PublicationSendStatusSeq &status);

    /**
     * @fn  virtual ReturnCode_t DataWriter::get_send_status_w_handle(PublicationSendStatus &status, const InstanceHandle_t* dstGuid);
     *
     * @brief   ��ȡ��ָ�������ݶ���֮��ͨ��״̬��
     *
     * @param [in,out]  status ��ȡ������ָ�������ݶ���֮��ͨ��״̬��
     * @param   dstGuid ָ�������ݶ��ߵ�Ψһ��ʶ��
     *
     * @return ��ǰ���ܵķ���ֵ���£�
     *         - #DDS_RETCODE_OK :��ʾ��ȡ�ɹ���
     *         - #DDS_RETCODE_BAD_PARAMETER :�����д��ڴ���
     *         - #DDS_RETCODE_NOT_ENABLED :����д��δʹ�ܣ�
     *         - #DDS_RETCODE_OUT_OF_RESOURCES :��ȡ��Դʧ�ܣ�һ��Ϊ�ڴ治�㵼�£�
     */

    virtual ReturnCode_t get_send_status_w_handle(PublicationSendStatus &status, const InstanceHandle_t* dstGuid);

#ifdef _ZRDDS_INCLUDE_BATCH
    /**
     * @fn virtual ReturnCode_t DataWriter::flush();
     *
     * @brief �ֶ�ˢ���������ͣ�����������ǰ��������д��������͵��������������
     *
     * @return  ���ܵķ���ֵ���£�
     *          - #DDS_RETCODE_OK ʹ�ܳɹ���
     *          - #DDS_RETCODE_BAD_PARAMETER �������ڴ���
     *          - #DDS_RETCODE_NOT_ENABLED ����д��δʹ�ܡ�
     *          - #DDS_RETCODE_ERROR δ������󣬾������ݼ�¼����־�ļ��С�
     */
    virtual ReturnCode_t flush();
#endif // _ZRDDS_INCLUDE_BATCH

    DataWriter* get_impl()
    {
        return m_impl;
    }
    virtual InstanceHandle_t register_instance_untype(const void *instance, const Time_t* timestamp);
    virtual ReturnCode_t unregister_instance_untype(const void *instance, const InstanceHandle_t& handle, const Time_t* timestamp);
    virtual ReturnCode_t get_key_value_untype(void *key_holder, const InstanceHandle_t& handle);
    virtual InstanceHandle_t lookup_instance_untype(const void *key_holder);
    virtual ReturnCode_t write_untype_w_dst(const void *data, const InstanceHandle_t& handle, const Time_t* timestamp, const InstanceHandle_t* dstGuid);
    virtual ReturnCode_t dispose_untype(const void *instance, const InstanceHandle_t& handle, const Time_t* timestamp);

protected:
    virtual ~DataWriter() {}

    DataWriter *m_impl;
};

} // namespace DDS

#endif // DataWriter_h__
