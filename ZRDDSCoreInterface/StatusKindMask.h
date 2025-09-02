/**
 * @file:       StatusKindMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_STATUSKINDMASK_H)
#define _STATUSKINDMASK_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @typedef DDS_ULong DDS_StatusKindMask
 *
 * @ingroup CoreStatusStruct
 *
 * @brief   #DDS_StatusKind 的掩码表示多个 #DDS_StatusKind 的状态的集合。
 * 
 * @details  例如：设置掩码为0x0003，由于0x0003 = 0x0001 | 0x0002，表明两个状态类型：
 *              #DDS_INCONSISTENT_TOPIC_STATUS (0x0001)或者 #DDS_OFFERED_DEADLINE_MISSED_STATUS (0x0002)。
 */

typedef DDS_ULong DDS_StatusKindMask;

/**
 * @def DDS_STATUS_MASK_ALL
 *
 * @ingroup  CoreMacro
 *
 * @brief   此掩码表明所有类型的 #DDS_StatusKind 的集合。
 */

#define DDS_STATUS_MASK_ALL 0xffffffff

/**
 * @def DDS_STATUS_MASK_NONE
 *
 * @ingroup  CoreMacro
 *
 * @brief   此掩码表明空的 #DDS_StatusKind 的集合。
 */

#define DDS_STATUS_MASK_NONE 0

#ifdef __cplusplus
}
#endif

#endif  /*_STATUSKINDMASK_H*/
