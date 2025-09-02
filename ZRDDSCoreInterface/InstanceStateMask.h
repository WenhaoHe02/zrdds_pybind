/**
 * @file:       InstanceStateMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef InstanceStateMask_h__
#define InstanceStateMask_h__

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_InstanceStateMask
 *
 * @ingroup CoreBaseStruct
 *          
 * @brief   ::DDS_InstanceStateKind 的掩码表示多个 ::DDS_InstanceStateKind 的状态。
 */
typedef DDS_ULong DDS_InstanceStateMask;

/**
 * @brief   此掩码表示任意的实例状态 ::DDS_InstanceStateKind 。
 *
 * @ingroup CoreMacro
 */
#define DDS_ANY_INSTANCE_STATE 0xffffffff

/**
 * @brief   此掩码表示非存活的实例状态 ::DDS_InstanceStateKind 。
 *
 * @ingroup CoreMacro
 */
#define  DDS_NOT_ALIVE_INSTANCE_STATE 0x00000006

#endif /* InstanceStateMask_h__*/
