/**
 * @file:       DataWriterListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DATAWRITERLISTENER_H)
#define _DATAWRITERLISTENER_H

#include "Listener.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class DataWriter;

/**
 * @class DataWriterListener
 *
 * @ingroup CppListener
 *
 * @brief 该类作为数据写者监听器的父类。
 *
 */
class DCPSDLL DataWriterListener : public Listener
{
public:
    virtual ~DataWriterListener(){}
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn virtual void DataWriterListener::on_liveliness_lost(DataWriter *the_writer, const LivelinessLostStatus &status)
     *
     * @brief 底层 #DDS_LIVELINESS_LOST_STATUS 状态的回调接口。
     *
     * @param [in,out] the_writer 该监听器关联的数据写者。
     * @param status              当前的状态值。
     */
    virtual void on_liveliness_lost(DataWriter *the_writer, const LivelinessLostStatus &status)
    {
        ZRDDS_UNUSED_PARAM(the_writer);
        ZRDDS_UNUSED_PARAM(status);
    }
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn virtual void DataWriterListener::on_offered_deadline_missed(DataWriter *the_writer, const OfferedDeadlineMissedStatus &status)
     *
     * @brief 底层 #DDS_OFFERED_DEADLINE_MISSED_STATUS 状态的回调接口。
     *
     * @param [in,out] the_writer 该监听器关联的数据写者。
     * @param status              当前的状态值。
     */
    virtual void on_offered_deadline_missed(DataWriter *the_writer, const OfferedDeadlineMissedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(the_writer);
        ZRDDS_UNUSED_PARAM(status);
    }
#endif //_ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn virtual void DataWriterListener::on_offered_incompatible_qos(DataWriter *the_writer, const OfferedIncompatibleQosStatus &status)
     *
     * @brief 底层 #DDS_OFFERED_INCOMPATIBLE_QOS_STATUS 状态的回调接口。
     *
     * @param [in,out] the_writer 该监听器关联的数据写者。
     * @param status              当前的状态值。
     */
    virtual void on_offered_incompatible_qos(DataWriter *the_writer, const OfferedIncompatibleQosStatus &status)
    {
        ZRDDS_UNUSED_PARAM(the_writer);
        ZRDDS_UNUSED_PARAM(status);
    }

    /**
     * @fn virtual void DataWriterListener::on_publication_matched(DataWriter *the_writer, const PublicationMatchedStatus &status)
     *
     * @brief 底层 #DDS_PUBLICATION_MATCHED_STATUS 状态的回调接口。
     *
     * @param [in,out] the_writer 该监听器关联的数据写者。
     * @param status              当前的状态值。
     */
    virtual void on_publication_matched(DataWriter *the_writer, const PublicationMatchedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(the_writer);
        ZRDDS_UNUSED_PARAM(status);
    }
};

} // namespace DDS

#endif  //_DATAWRITERLISTENER_H
