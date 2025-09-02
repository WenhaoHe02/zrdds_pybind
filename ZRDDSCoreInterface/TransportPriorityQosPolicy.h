/**
 * @file:       TransportPriorityQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TransportPriorityQosPolicy_h__
#define TransportPriorityQosPolicy_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS

/**
 * @struct DDS_TransportPriorityQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   传输优先级配置。
 *
 * @details 配置当前主题数据的传输优先级。
 *          
 * @warning ZRDDS当前未实现该QoS。
 */

typedef struct DDS_TransportPriorityQosPolicy
{
    /** @brief   优先级别。 */
    DDS_Long value;
}DDS_TransportPriorityQosPolicy;

#endif /* _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS */

#endif /* TransportPriorityQosPolicy_h__*/
