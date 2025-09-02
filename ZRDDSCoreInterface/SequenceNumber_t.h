/**
 * @file:       SequenceNumber_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SEQUENCENUMBER_H
#define SEQUENCENUMBER_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_SequenceNumber_t
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   64比特的序列号，seq_num = high * (2^32) + low.
 */

typedef struct DDS_SequenceNumber_t
{
    /** @brief 序列号的高位. */
    DDS_Long high;
    /** @brief 序列号的低位. */
    DDS_ULong low;
} DDS_SequenceNumber_t;

#ifdef __cplusplus
}
#endif

#endif
