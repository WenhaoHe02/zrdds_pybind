/**
 * @file:       DynamicDataDataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DynamicDataReader_h__
#define DynamicDataReader_h__

#include "ZRDynamicData.h"
#include "ZRDDSDataReader.h"

#ifdef _ZRDDS_INCLUDE_DYNAMIC_DATA

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct ZRDynamicDataSeq ZRDynamicDataSeq;

typedef DDS::ZRDDSDataReader<ZRDynamicData, ZRDynamicDataSeq> ZRDynamicDataDataReader;

#ifdef __cplusplus
}
#endif
#endif // _ZRDDS_INCLUDE_DYNAMIC_DATA
#endif // DynamicDataReader_h__
