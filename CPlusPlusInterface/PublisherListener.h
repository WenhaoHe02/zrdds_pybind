/**
 * @file:       PublisherListener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_PUBLISHERLISTENER_H)
#define _PUBLISHERLISTENER_H

#include "DataWriterListener.h"

namespace DDS {

/**
 * @class   PublisherListener
 *
 * @ingroup CppListener
 *
 * @brief   作为发布者监听器的父类。
 */

class DCPSDLL PublisherListener : public DataWriterListener
{
public:
    virtual ~PublisherListener(){}
};

} // namespace DDS

#endif  //_PUBLISHERLISTENER_H
