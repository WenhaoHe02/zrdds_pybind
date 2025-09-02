/**
 * @file:       ZRDDSTypePlugin.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSTypePlugin_h__
#define ZRDDSTypePlugin_h__

#include "OsResource.h"
#include "InstanceHandle_t.h"
#include "ZRMemPool.h"
#include "TypeCodeKind.h"
#include "CDRStream.h"

typedef void* (*TypePluginCreateSampleFunction)(
    ZRMemPool* pool,
    ZR_BOOLEAN allocMutable,
    const void* typeSupport);

typedef void(*TypePluginDestroySampleFunction)(
    ZRMemPool* mempool,
    void* sample, 
    const void* typeSupport);

typedef ZR_BOOLEAN(*TypePluginCopySampleFunction)(
    void* dst, 
    const void* src, 
    ZRMemPool* pool,
    const void* typeSupport);

typedef ZR_UINT32(*TypePluginGetMaxSizeFunction)(
    const void* typeSupport);

typedef ZR_UINT32(*TypePluginGetSizeFunction)(
    const void* sample, 
    ZR_UINT32 currentAlignment, 
    const void* typeSupport);

typedef ZR_INT32(*TypePluginSerializeFunction)(
    const void* sample, 
    CDRSerializer* cdr, 
    const void* typeSupport);

typedef ZR_INT32(*TypePluginDeserializeFunction)(
    void* sample, 
    CDRDeserializer* cdr,
    ZRMemPool* pool,
    const void* typeSupport);

typedef ZR_UINT32(*TypePluginGetMaxKeySizeFunction)(
    const void* typeSupport);

typedef ZR_UINT32(*TypePluginGetKeySizeFunction)(
    const void* sample, 
    ZR_UINT32 currentAlignment, 
    const void* typeSupport);

typedef ZR_INT32(*TypePluginSerializeKeyFunction)(
    const void* sample, 
    CDRSerializer* cdr, 
    const void* typeSupport);

typedef ZR_INT32(*TypePluginDeserializeKeyFunction)(
    void* sample, 
    CDRDeserializer* cdr,
    ZRMemPool* pool,
    const void* typeSupport);

typedef ZR_INT32(*TypePluginGetKeyHashFunction)(
    const void* sample,
    CDRSerializer* cdr,
    DDS_KeyHash_t* result,
    const void* typeSupport);

typedef ZR_BOOLEAN(*TypePluginHasKeyFunction)(
    const void* typeSupport);

typedef void* (*TypePluginCreateDataReaderFunction)(
    void* impl, 
    const void* typeSupport);

typedef ZR_INT32 (*TypePluginDestroyDataReaderFunction)(
    void* reader, 
    const void* typeSupport); 

typedef void* (*TypePluginCreateDataWriterFunction)(
    void* impl, 
    const void* typeSupport);

typedef ZR_INT32 (*TypePluginDestroyDataWriterFunction)(
    void* writer, 
    const void* typeSupport);

typedef TypeCodeHeader* (*TypePluginGetTypeCodeFunction)(
    const void* typeSupport);

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE

typedef ZR_INT8* (*TypePluginLoanSampleBufFunction)(
    void* sample,
    ZR_BOOLEAN takeBuffer,
    const void* typeSupport);

typedef void (*TypePluginReturnSampleBufFunction)(
    ZR_INT8* sampleBuf,
    const void* typeSupport);

typedef ZR_INT32 (*TypePluginLoanDeserializeFunction)(
    void* sample,
    CDRDeserializer* cdr,
    ZR_UINT32 curIndex,
    ZR_UINT32 totalNum,
    ZR_INT8* base,
    ZR_UINT32 offset,
    ZR_UINT32 space,
    ZR_UINT32 fixedHeaderLen);
#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE

typedef ZR_BOOLEAN(*TypePluginNoSerializingSupportedFunction)(
    const void* typeSupport);

typedef ZR_UINT32(*TypePluginFixedHeaderLengthFunction)(
    const void* typeSupport);

typedef ZR_INT32(*TypePluginOnSiteDeserializeFunction)(
    CDRDeserializer* cdr,
    void* sample,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

typedef ZR_INT32(*TypePluginLoanContiguousDeserializeFunction)(
    CDRDeserializer* cdr,
    void* sample);

#endif //_ZRDDS_INCLUDE_ONSITE_DESERILIZE

typedef struct ZRDDSTypePlugin
{
    TypePluginCreateSampleFunction m_createSampleFunc;
    TypePluginDestroySampleFunction m_destroySampleFunc;
    TypePluginCopySampleFunction m_copySampleFunc;
    TypePluginGetMaxSizeFunction m_getMaxSizeFunc;
    TypePluginGetSizeFunction m_getSizeFunc;
    TypePluginSerializeFunction m_serializeFunc;
    TypePluginDeserializeFunction m_deserializeFunc;
    TypePluginGetMaxKeySizeFunction m_getMaxKeySizeFunc;
    TypePluginGetKeySizeFunction m_getKeySizeFunc;
    TypePluginSerializeKeyFunction m_serializeKeyFunc;
    TypePluginDeserializeKeyFunction m_deserializeKeyFunc;
    TypePluginGetKeyHashFunction m_getKeyHashFunc;
    TypePluginHasKeyFunction m_hasKeyFunc;
    TypePluginCreateDataReaderFunction m_createDataReaderFunc;
    TypePluginDestroyDataReaderFunction m_destroyDataReaderFunc;
    TypePluginCreateDataWriterFunction m_createDataWriterFunc;
    TypePluginDestroyDataWriterFunction m_destroyDataWriterFunc;
    TypePluginGetTypeCodeFunction m_typecodeFunc;
#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    TypePluginOnSiteDeserializeFunction m_onSiteDeserializeFunc;
    TypePluginFixedHeaderLengthFunction m_fixedHeaderLengthFunc;
    TypePluginNoSerializingSupportedFunction m_noSerializingSupportedFunc;
    TypePluginLoanContiguousDeserializeFunction m_loanCongitiousDeserializeFunc;
#endif
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    TypePluginLoanSampleBufFunction m_loanSampleBufFunc;
    TypePluginReturnSampleBufFunction m_returnSampleBufFunc;
    TypePluginLoanDeserializeFunction m_loanDeserializeFunc;
#endif //_ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    void* m_typeSupport;
}ZRDDSTypePlugin;

#endif /* ZRDDSTypePlugin_h__*/
