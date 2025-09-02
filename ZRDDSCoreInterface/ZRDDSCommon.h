/**
 * @file:       ZRDDSCommon.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSCommon_h__
#define ZRDDSCommon_h__

#include "ZROSDefine.h"

#if defined(_WIN32)
#if defined(_ZRDDSDLLEXPORT)
    #define DCPSDLL __declspec(dllexport)
    #define CEXPORT extern "C" __declspec(dllexport)
#elif defined(_ZRDDSDLLIMPORT)
    #define DCPSDLL __declspec(dllimport)
    #define CEXPORT extern "C" __declspec(dllimport)
#else
    #define DCPSDLL
    #define CEXPORT extern "C"
#endif
#if defined(_MSC_VER)
/* 模版实例未导出warning */
#pragma warning(disable: 4251)
/* sprintf的warning */
#pragma warning(disable: 4996)
/* this用于初始化列表的warning */
#pragma warning(disable: 4355)
#endif
#elif defined(_LINUX)
    #define DCPSDLL __attribute__ ((visibility("default")))
    #define CEXPORT __attribute__ ((visibility("default")))
#else
    #define DCPSDLL
    #define CEXPORT
#endif

#define ZRDDS_UNUSED_PARAM(x)    (void)x;

#endif /* ZRDDSCommon_h__*/
