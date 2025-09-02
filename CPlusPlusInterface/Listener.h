/**
 * @file:       Listener.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_LISTENER_H)
#define _LISTENER_H

#include "ZRDDSCommon.h"

namespace DDS {

/**
 * @class   Listener
 *
 * @ingroup CppListener
 *
 * @brief   该类是所有监听器的基类，监听器是ZRDDS提供的一种异步回调机制，参见 @ref listener-introduction 
 */

class DCPSDLL Listener
{
public:
    virtual ~Listener() {}
};

} /*namespace DDS*/

#endif  //_LISTENER_H
