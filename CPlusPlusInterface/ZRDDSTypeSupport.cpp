/**
 * @file:       ZRDDSTypeSupport.cpp
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#include <stdio.h>
#include "DomainParticipant.h"

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
#define ZRDDSOnSiteDeserilizeFunc(TType)                                                                            \
    result.m_noSerializingSupportedFunc = (TypePluginNoSerializingSupportedFunction)TType##NoSerializingSupported;  \
    result.m_fixedHeaderLengthFunc = (TypePluginFixedHeaderLengthFunction)TType##FixedHeaderLength;                 \
    result.m_onSiteDeserializeFunc = (TypePluginOnSiteDeserializeFunction)TType##OnSiteDeserialize;
#else
#define ZRDDSOnSiteDeserilizeFunc(TType)
#endif

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
#define ZRDDSNoDeserilizeFunc(TType)                                                                            \
    result.m_loanSampleBufFunc = (TypePluginLoanSampleBufFunction)TType##LoanSampleBuf;                         \
    result.m_returnSampleBufFunc = (TypePluginReturnSampleBufFunction)TType##ReturnSampleBuf;                   \
    result.m_loanDeserializeFunc = (TypePluginLoanDeserializeFunction)TType##LoanDeserialize;
#else
#define ZRDDSNoDeserilizeFunc(TType)
#endif

#define DDSTypeSupportImpl(TTypeSupport, TType, TTypeNameVar)   \
    TTypeSupport* TTypeSupport::m_instance = NULL;              \
    ZRDDSTypePlugin* TType##PluginNew() \
    {                                   \
        ZR_BOOLEAN initialized = false; \
        static ZRDDSTypePlugin result;  \
        if (initialized)                \
        {                               \
            return &result;             \
        }                               \
        result.m_createSampleFunc = (TypePluginCreateSampleFunction)TType##CreateSample;        \
        result.m_destroySampleFunc = (TypePluginDestroySampleFunction)TType##DestroySample;     \
        result.m_copySampleFunc = (TypePluginCopySampleFunction)TType##CopyEx;                  \
        result.m_getMaxSizeFunc = (TypePluginGetMaxSizeFunction)TType##GetSerializedSampleMaxSize;          \
        result.m_getSizeFunc = (TypePluginGetSizeFunction)TType##GetSerializedSampleSize;       \
        result.m_serializeFunc = (TypePluginSerializeFunction)TType##Serialize;                 \
        result.m_deserializeFunc = (TypePluginDeserializeFunction)TType##Deserialize;           \
        result.m_getMaxKeySizeFunc = (TypePluginGetMaxKeySizeFunction)TType##GetSerializedKeyMaxSize;       \
        result.m_getKeySizeFunc = (TypePluginGetKeySizeFunction)TType##GetSerializedKeySize;    \
        result.m_serializeKeyFunc = (TypePluginSerializeKeyFunction)TType##SerializeKey;        \
        result.m_deserializeKeyFunc = (TypePluginDeserializeKeyFunction)TType##DeserializeKey;  \
        result.m_getKeyHashFunc = (TypePluginGetKeyHashFunction)TType##GetKeyHash;              \
        result.m_hasKeyFunc = (TypePluginHasKeyFunction)TType##HasKey;                          \
        result.m_typecodeFunc = (TypePluginGetTypeCodeFunction)TType##GetInnerTypeCode;         \
        result.m_createDataReaderFunc = (TypePluginCreateDataReaderFunction)TType##DataReader::createI;     \
        result.m_destroyDataReaderFunc = (TypePluginDestroyDataReaderFunction)TType##DataReader::destroyI;  \
        result.m_createDataWriterFunc = (TypePluginCreateDataWriterFunction)TType##DataWriter::createI;     \
        result.m_destroyDataWriterFunc = (TypePluginDestroyDataWriterFunction)TType##DataWriter::destroyI;  \
        ZRDDSOnSiteDeserilizeFunc(TType)                                                        \
        ZRDDSNoDeserilizeFunc(TType)                                                            \
        initialized = true;                                                                     \
        return &result;                                                                         \
    }                                                                                           \
                                                    \
    const DDS::Char* TTypeSupport::get_type_name()  \
    {                                               \
        return TTypeNameVar;                        \
    }                                               \
                                                    \
    DDS::ReturnCode_t TTypeSupport::register_type(          \
        DDS::DomainParticipant *participant,                \
        const DDS::Char* type_name)                         \
    {                                                       \
        if (participant == NULL)                            \
        {                                                   \
            return DDS_RETCODE_BAD_PARAMETER;               \
        }                                                   \
        ZRDDSTypePlugin* plugin = TType##PluginNew();       \
        return participant->register_type(                  \
            type_name == NULL ? get_type_name() : type_name,\
            plugin);                                        \
    }                                                       \
                                                            \
    DDS::ReturnCode_t TTypeSupport::unregister_type(        \
        DDS::DomainParticipant *participant,                \
        const DDS::Char* type_name)                         \
    {                                                       \
        if (participant == NULL)                            \
        {                                                   \
            return DDS_RETCODE_BAD_PARAMETER;               \
        }                                                   \
        return participant->unregister_type(                \
            type_name == NULL ? get_type_name() : type_name);\
    }                                                       \
                                                            \
    TTypeSupport* TTypeSupport::get_instance()              \
    {                                                       \
        if (TTypeSupport::m_instance == NULL)               \
        {                                                   \
            TTypeSupport::m_instance = new TTypeSupport();  \
        }                                                   \
        return TTypeSupport::m_instance;                    \
    }                                                       \
                                                            \
    void TTypeSupport::finalize_instance()                  \
    {                                                       \
        if (TTypeSupport::m_instance)                       \
        {                                                   \
            delete TTypeSupport::m_instance;                \
            m_instance = NULL;                              \
        }                                                   \
    }                                                       \
                                                            \
    DDS::Boolean TTypeSupport::has_key()                    \
    {                                                       \
        return TType##HasKey();                             \
    }                                                       \
                                                            \
    TTypeSupport::TTypeSupport()                            \
    {                                                       \
                                                            \
    }                                                       \
                                                            \
    TTypeSupport::~TTypeSupport()                           \
    {                                                       \
                                                            \
    }
