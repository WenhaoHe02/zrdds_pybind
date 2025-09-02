/**
 * @file:       DataReaderListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DATAREADERLISTENER_H)
#define _DATAREADERLISTENER_H

#include "Listener.h"
#include "ZRDDSCppWrapper.h"
#include <stdio.h>

namespace DDS {
    
class DataReader;

/**
 * @class   DataReaderListener
 *
 * @ingroup CppListener
 *
 * @brief   该类作为数据读者监听器的父类。
 *
 */

class DCPSDLL DataReaderListener : public Listener
{
public:
    virtual ~DataReaderListener(){}
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual void DataReaderListener::on_requested_deadline_missed(DataReader* reader, const RequestedDeadlineMissedStatus& status)
     *
     * @brief   底层 #DDS_REQUESTED_DEADLINE_MISSED_STATUS 状态的回调接口。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param   status          当前的状态值。
     */

    virtual void on_requested_deadline_missed(DataReader* reader, const RequestedDeadlineMissedStatus& status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
#endif //_ZRDDS_INCLUDE_DEADLINE_QOS

    /**
     * @fn  virtual void DataReaderListener::on_data_available(DataReader *reader)
     *
     * @brief   有新的样本存储到数据读者底层时回调。
     *
     * @details 该回调不包含新的数据样本的内容，用户需要通过 @ref read-take 系列方法按照要求获取数据样本的内容。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     */

    virtual void on_data_available(DataReader *reader)
    {
        ZRDDS_UNUSED_PARAM(reader);
    }

    /**
     * @fn  virtual void DataReaderListener::on_data_arrived(DataReader *reader, void* sample, const SampleInfo& info)
     *
     * @brief   直接通知数据到达，适用于best-effort等不需要数据读者缓存数据的场景。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param [in,out]  sample  样本数据。
     * @param   info            关联的样本信息。
     */

    virtual void on_data_arrived(DataReader *reader, void* sample, const SampleInfo& info)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(sample);
        ZRDDS_UNUSED_PARAM(info);
    }

    /**
     * @fn  virtual void DataReaderListener::on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status)
     *
     * @brief   底层 #DDS_SAMPLE_REJECTED_STATUS 状态的回调接口。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param   status          当前的状态值。
     */

    virtual void on_sample_rejected(DataReader *reader, const SampleRejectedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual void DataReaderListener::on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status)
     *
     * @brief   底层 #DDS_LIVELINESS_LOST_STATUS 状态的回调接口。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param   status          当前的状态值。
     */

    virtual void on_liveliness_changed(DataReader *reader, const LivelinessChangedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS

    /**
     * @fn  virtual void DataReaderListener::on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status)
     *
     * @brief   底层 #DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS 状态的回调接口。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param   status          当前的状态值。
     */

    virtual void on_requested_incompatible_qos(DataReader *reader, const RequestedIncompatibleQosStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }

    /**
     * @fn  virtual void DataReaderListener::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status)
     *
     * @brief   底层 #DDS_SUBSCRIPTION_MATCHED_STATUS 状态的回调接口。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param   status          当前的状态值。
     */

    virtual void on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }

    /**
     * @fn  virtual void DataReaderListener::on_sample_lost(DataReader *reader, const SampleLostStatus &status)
     *
     * @brief   底层 #DDS_SAMPLE_LOST_STATUS 状态的回调接口。
     *
     * @param [in,out]  reader  该监听器关联的数据读者。
     * @param   status          当前的状态值。
     */

    virtual void on_sample_lost(DataReader *reader, const SampleLostStatus &status)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(status);
    }
};

/**
 * @class   SimpleDataReaderListener
 *
 * @ingroup CppListener
 *
 * @brief   简单数据读者监听器基类，用于简化用户取出样本数据的过程。
 *
 * @tparam  T           监听器将处理的样本类型。
 * @tparam  TSeq        监听器将处理的样本类型序列。
 * @tparam  TDataReader 监听器将设置到的数据读者类型。
 */

template<typename T, typename TSeq, typename TDataReader>
class SimpleDataReaderListener : public DataReaderListener
{
public:

    /**
     * @fn  virtual void SimpleDataReaderListener::on_data_available(DataReader *reader)
     *
     * @brief   底层有数据到达时，典型取数据流程，将底层到达的样本全部取出，并以此调用 on_process_sample 方法。
     *
     * @param [in,out]  reader  有数据到达的数据读者指针。
     */

    virtual void on_data_available(DataReader *reader)
    {
        TSeq data_values;
        SampleInfoSeq sample_infos;
        /* 转化为类型安全接口 */
        TDataReader* typedReader = (TDataReader*)reader;
        ReturnCode_t retCode = typedReader->take(data_values, sample_infos,
            LENGTH_UNLIMITED, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
        if (RETCODE_OK != retCode)
        {
            printf("take failed(%d).\n", retCode);
            return;
        }
        /* 处理数据 */
        for (ZR_UINT32 i = 0; i < sample_infos._length; i++)
        {
            SampleInfo& info = sample_infos[i];
            /* 判断是否为有效的负载数据 */
            if (!info.valid_data)
            {
                continue;
            }
            T& sample = data_values[i];
            this->on_process_sample(reader, sample, info);
        }
        typedReader->return_loan(data_values, sample_infos);
    }

    /**
     * @fn  virtual void SimpleDataReaderListener::on_process_sample(DataReader* reader, const T& sample, const SampleInfo& info)
     *
     * @brief   样本处理函数，当有数据时调用，默认行为时打印一条语句，用户应重写覆盖该函数。
     *
     * @param [in,out]  reader  数据有效的数据读者指针。
     * @param   sample          数据样本。
     * @param   info            该样本关联的信息。
     */

    virtual void on_process_sample(DataReader* reader, const T& sample, const SampleInfo& info)
    {
        ZRDDS_UNUSED_PARAM(reader);
        ZRDDS_UNUSED_PARAM(sample);
        ZRDDS_UNUSED_PARAM(info);
        printf("data received on reader(%p)\n", reader);
    }
};

} // namespace DDS

#endif  //_DATAREADERLISTENER_H
