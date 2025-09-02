/**
 * @file:       TopicListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TOPICLISTENER_H)
#define _TOPICLISTENER_H

#include "Listener.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class Topic;

/**
 * @class   TopicListener 
 *
 * @ingroup CppListener
 *
 * @brief   该类作为主题监听器的父类。
 */

class DCPSDLL TopicListener : public Listener
{
public:
    virtual ~TopicListener(){}

    /**
     * @fn  virtual void TopicListener::on_inconsistent_topic(Topic *the_topic, const InconsistentTopicStatus &status)
     *
     * @brief   底层 #DDS_INCONSISTENT_TOPIC_STATUS 状态的回调接口。
     *
     * @param [in,out]  the_topic  该监听器关联的主题。
     * @param   status          当前的状态值。
     */

    virtual void on_inconsistent_topic(Topic *the_topic, const InconsistentTopicStatus &status)
    {
        ZRDDS_UNUSED_PARAM(the_topic);
        ZRDDS_UNUSED_PARAM(status);
    }
};

} // namespace DDS

#endif  //_TOPICLISTENER_H
