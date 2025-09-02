/**
 * @file:       SampleStateMask.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SampleStateMask_h__
#define SampleStateMask_h__

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_SampleStateMask
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   ::DDS_SampleStateKind 的掩码表示多个 ::DDS_SampleStateKind 的状态。
 */

typedef DDS_ULong DDS_SampleStateMask;

/**
 * @def DDS_ANY_SAMPLE_STATE
 *
 * @ingroup  CoreMacro
 *
 * @brief   此掩码表示任意的样本状态。
 */

#define  DDS_ANY_SAMPLE_STATE 0xffffffff

#endif /* SampleStateMask_h__*/
