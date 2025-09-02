/**
 * @file:       SubscriberListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_SUBSCRIBERLISTENER_H)
#define _SUBSCRIBERLISTENER_H

#include "DataReaderListener.h"

namespace DDS {

class Subscriber;
class DataReader;

/**
 * @class   SubscriberListener
 *
 * @ingroup CppListener
 *
 * @brief   该类作为订阅者监听器的父类。
 */

class DCPSDLL SubscriberListener : public DataReaderListener
{
public:
    virtual ~SubscriberListener(){}

    /**
     * @fn  virtual void SubscriberListener::on_data_on_readers(Subscriber *the_subscriber)
     *
     * @brief   回调 #DDS_DATA_ON_READERS_STATUS 状态。
     *
     * @details 当订阅者的子实体数据读者有新数据达到时，订阅者将处于此状态，以下情况将清楚该状态：
     *          - 订阅者监听器设置的关心的状态包含 #DDS_DATA_ON_READERS_STATUS ；  
     *          - 用户调用 DDS::Subscriber::notify_datareaders 函数；  
     *          - 用户成功调用 DDS::SubscriberListener::on_data_available 方法；  
     *          - 用户调用该域参与者中任意数据读者的 @ref read-take 系列方法。
     *
     * @param [in,out]  the_subscriber  该监听器所属的订阅者。
     */

    virtual void on_data_on_readers(Subscriber *the_subscriber)
    {
        ZRDDS_UNUSED_PARAM(the_subscriber);
    }
};

} // namespace DDS

#endif  //_SUBSCRIBERLISTENER_H
