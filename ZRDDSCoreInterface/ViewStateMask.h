/**
 * @file:       ViewStateMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ViewStateMask_h__
#define ViewStateMask_h__

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_ViewStateMask
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   #DDS_ViewStateKind 的掩码表示多个 #DDS_ViewStateKind 的状态的集合。
 */

typedef DDS_ULong DDS_ViewStateMask;

/**
 * @def DDS_ANY_VIEW_STATE
 *
 * @ingroup CoreMacro
 *
 * @brief   此掩码表明所有类型的 #DDS_ViewStateKind 的集合。
 */

#define DDS_ANY_VIEW_STATE 0xffffffff

#endif /* ViewStateMask_h__*/
