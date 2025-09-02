/**
 * @file:       RapidIOControllerQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef RapidIOControllerQosPolicy_h__
#define RapidIOControllerQosPolicy_h__

#include "OsResource.h"

#ifdef _ZRDDS_RIO

/**
 * @typedef struct DDS_RapidIOControllerQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief RapidIO选择QoS，默认为0，不可变。
 */
typedef struct DDS_RapidIOControllerQosPolicy
{
    /** @brief 选用的RapidIO控制器号。 */
    DDS_Long controller_id;
}DDS_RapidIOControllerQosPolicy;

#endif /* _ZRDDS_RIO */

#endif /* RapidIOControllerQosPolicy_h__ */
