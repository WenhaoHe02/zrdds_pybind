/**
 * @file:       ZRTimeUtility.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRTimeUtility_h__
#define ZRTimeUtility_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef _ZRDDS_INCLUDE_TIMEUTILITY

#if defined(_WIN32)
#include <windows.h>
#elif defined(_LINUX)
#include <time.h>
#include <unistd.h>
#elif defined(_VXWORKS)
#include <unistd.h>
#include <timers.h>
#include <drv/timer/timerDev.h>
#elif defined(_REWORKS)
#include <cpu.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define ZR_TIME_MAX_BUFFER 1024

struct TimeRecord
{
	ZR_UINT32 param;
	ZR_DOUBLE64 time;
};

extern struct TimeRecord g_timeBuffer[ZR_TIME_MAX_BUFFER];

extern ZR_UINT32 g_timeCount;

DCPSDLL ZR_DOUBLE64 ZRGetFrequence();

DCPSDLL ZR_UINT64 ZRStartCount();

DCPSDLL ZR_UINT64 ZRGetCurrentCount(ZR_BOOLEAN bufferd, ZR_UINT32 param);

DCPSDLL ZR_DOUBLE64 ZRGetNanoSecFromPeriod(ZR_UINT64 startCount, ZR_UINT64 endCount);

DCPSDLL ZR_DOUBLE64 ZRGetNanoSecFromCount(ZR_INT64 startCount);

DCPSDLL void ZRPrintBufferedTime();

#ifdef __cplusplus
}
#endif

#endif /* _ZRDDS_INCLUDE_TIMEUTILITY */

#endif /* ZRTimeUtility_h__*/
