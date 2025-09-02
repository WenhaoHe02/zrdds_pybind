/**
 * @file:       DomainParticipantListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINPARTICIPANTLISTENER_H)
#define _DOMAINPARTICIPANTLISTENER_H

#include "OsResource.h"
#include "PublisherListener.h"
#include "TopicListener.h"
#include "SubscriberListener.h"

namespace DDS {

/**
 * @class   DomainParticipantListener
 *
 * @ingroup CppListener
 *
 * @brief   该类作为域参与者监听器的父类。
 */

class DCPSDLL DomainParticipantListener :
    public PublisherListener,
    public TopicListener,
    public SubscriberListener
{
public:
    virtual ~DomainParticipantListener(){}

    /**
     * @fn  virtual void on_domain_received(ULong domainId)
     *
     * @brief   处理RTPX协议的回调，参见  DDS_DomainParticipantQos::domain_destination_addresses 。
     *
     * @param   domainId    表明收到 @e domainId 下域参与者的数据。
     */

    virtual void on_domain_received(ULong domainId)
    {
         ZRDDS_UNUSED_PARAM(domainId);
    }
};

} // namespace DDS

#endif  //_DOMAINPARTICIPANTLISTENER_H
