/**
 * @file:       DataTags.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataTags_h__
#define DataTags_h__

#include "ZROSDefine.h"
#ifdef _ZRDDSSECURITY

#include "ZRSequence.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct DDS_Tag
{
    DDS_Char* name;
    DDS_Char* value;
}DDS_Tag;

DDS_SEQUENCE_CPP(DDS_TagSeq, DDS_Tag);

typedef struct DDS_DataTags
{
    DDS_TagSeq tags;
}DDS_DataTags;

typedef DDS_DataTags DDS_DataTagQosPolicy;

#ifdef __cplusplus
}
#endif
#endif /* _ZRDDSSECURITY */

#endif /* DataTags_h__ */
