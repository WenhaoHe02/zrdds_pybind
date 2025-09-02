/**
 * @file:       ZRSleep.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRSLEEP_H
#define ZRSLEEP_H

#include "ZROSDefine.h"
#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @fn  void DCPSDLL ZRSleep(DDS_ULong ms);
 *
 * @ingroup CoreUtilityFunction
 *
 * @brief   跨平台延时函数。
 *
 * @param   ms  延时的毫秒数。
 */

void DCPSDLL ZRSleep(DDS_ULong ms);

/**
 * @fn  void DCPSDLL ZRUSleep(DDS_ULong us);
 *
 * @ingroup CoreUtilityFunction
 *
 * @brief   跨平台延时函数。
 *
 * @param   us  延时的微秒数。
 */

void DCPSDLL ZRUSleep(DDS_ULong us);

/**
 * @fn  void DCPSDLL ZRSyncSleep(DDS_ULong us);
 *
 * @brief   同步sleep。
 *
 * @param   us  微秒。
 */

void DCPSDLL ZRSyncSleep(DDS_ULong us);

/**
 * @fn  void DCPSDLL ZRSyncSleep(DDS_ULong us);
 *
 * @brief   使用for循环同步sleep。
 *
 * @param   count  循环次数。
 */

void DCPSDLL ZRForSleep(DDS_ULong count);

#ifdef __cplusplus
}
#endif

#endif
