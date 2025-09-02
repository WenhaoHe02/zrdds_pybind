/**
 * @file:       ZRDDSCppWrapper.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSCppWrapper_h__
#define ZRDDSCppWrapper_h__

#include "AsynchronousPublisherQosPolicy.h"
#include "BatchQosPolicy.h"
#include "BuiltinTopicKey_t.h"
#include "CDRStream.h"
#include "ContentFilterProperty_t.h"
#include "DataReaderQos.h"
#include "DataRepresentationQosPolicy.h"
#include "DataWriterMessageModeQosPolicy.h"
#include "DataWriterProtocolQosPolicy.h"
#include "DataWriterQos.h"
#include "DataWriterResourceLimitsQosPolicy.h"
#include "DDSLogQosPolicy.h"
#include "DDSMsgStatisticsInfoQosPolicy.h"
#include "DeadlineQosPolicy.h"
#include "DefaultQos.h"
#include "DestinationOrderQosPolicy.h"
#include "DiscoveryConfigQosPolicy.h"
#include "DomainId_t.h"
#include "DomainParticipantFactoryQos.h"
#include "DomainParticipantQos.h"
#include "DurabilityQosPolicy.h"
#include "DurabilityServiceQosPolicy.h"
#include "Duration_t.h"
#include "EntityFactoryQosPolicy.h"
#include "GroupDataQosPolicy.h"
#include "HistoryQosPolicy.h"
#include "InconsistentTopicStatus.h"
#include "InstanceHandle_t.h"
#include "InstanceStateKind.h"
#include "InstanceStateMask.h"
#include "LatencyBudgetQosPolicy.h"
#include "LifespanQosPolicy.h"
#include "LivelinessChangedStatus.h"
#include "LivelinessLostStatus.h"
#include "LivelinessQosPolicy.h"
#include "OfferedDeadlineMissedStatus.h"
#include "OfferedIncompatibleQosStatus.h"
#include "OsResource.h"
#include "OwnershipQosPolicy.h"
#include "OwnershipStrengthQosPolicy.h"
#include "ParticipantBuiltinTopicData.h"
#include "PartitionQosPolicy.h"
#include "PresentationQosPolicy.h"
#include "PropertyList.h"
#include "PropertyQosPolicy.h"
#include "PublicationBuiltinTopicData.h"
#include "TopicBuiltinTopicData.h"
#include "PublicationMatchedStatus.h"
#include "PublicationSendStatus.h"
#include "PublisherQos.h"
#include "PublishModeQosPolicy.h"
#include "QosPolicyCount.h"
#include "QosPolicyId_t.h"
#include "RapidIOConfigQosPolicy.h"
#include "RapidIOControllerQosPolicy.h"
#include "ReaderDataLifecycleQosPolicy.h"
#include "ReceiverThreadConfigQosPolicy.h"
#include "ReliabilityQosPolicy.h"
#include "RequestedDeadlineMissedStatus.h"
#include "RequestedIncompatibleQosStatus.h"
#include "ResourceLimitsQosPolicy.h"
#include "ReturnCode_t.h"
#include "SampleInfo.h"
#include "SampleLostStatus.h"
#include "SampleRejectedStatus.h"
#include "SampleRejectedStatusKind.h"
#include "SampleStateKind.h"
#include "SampleStateMask.h"
#include "SequenceNumber_t.h"
#include "StatusKind.h"
#include "StatusKindMask.h"
#include "SubscriberQos.h"
#include "SubscriptionBuiltinTopicData.h"
#include "SubscriptionMatchedStatus.h"
#include "ThreadCoreAffinityQosPolicy.h"
#include "TimeBasedFilterQosPolicy.h"
#include "TopicDataQosPolicy.h"
#include "TopicQos.h"
#include "TransportConfigQosPolicy.h"
#include "TransportPriorityQosPolicy.h"
#include "TypeCodeKind.h"
#include "TypeConsistencyEnforcementQosPolicy.h"
#include "TypeObject.h"
#include "UserDataQosPolicy.h"
#include "ViewStateKind.h"
#include "ViewStateMask.h"
#include "WriterDataLifecycleQosPolicy.h"
#include "ZRDDSCommon.h"
#include "ZRDDSTypePlugin.h"
#include "ZRDynamicData.h"
#include "ZRMemPool.h"
#include "ZROSDefine.h"
#include "ZRBuiltinTypes.h"
#include "ZRSequence.h"
#include "ZRSleep.h"
#include "ZRUserLog.h"
#include "DDSSecurityPluginQosPolicy.h"
#ifdef _ZRDDS_INCLUDE_GATEWAY
#include "GatewayQosPolicy.h"
#endif // _ZRDDS_INCLUDE_GATEWAY

namespace DDS {

/**
 * @typedef DDS_Boolean Boolean
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的true/false类型。
 */

typedef DDS_Boolean Boolean;

/**
 * @typedef DDS_Octet Octet
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的1字节无符号整型 
 */

typedef DDS_Octet Octet;

/**
 * @typedef DDS_Char Char
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的1字节整型。
 */

typedef DDS_Char Char;

/**
 * @typedef DDS_Short Short
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的2字节整型。
 */

typedef DDS_Short Short;

/**
 * @typedef DDS_UShort UShort
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的2字节无符号整型。
 */

typedef DDS_UShort UShort;

/**
 * @typedef DDS_Long Long
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的4字节整型。
 */

typedef DDS_Long Long;

/**
 * @typedef DDS_ULong ULong
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的4字节无符号整型。
 */

typedef DDS_ULong ULong;

/**
 * @typedef DDS_LongLong LongLong
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的8字节长整型。
 */

typedef DDS_LongLong LongLong;

/**
 * @typedef DDS_ULongLong ULongLong
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的8字节无符号长整型。
 */

typedef DDS_ULongLong ULongLong;

/**
 * @typedef DDS_Float Float
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的4字节单精度浮点型。
 */

typedef DDS_Float Float;

/**
 * @typedef DDS_Double Double
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的8字节双精度浮点型。
 */

typedef DDS_Double Double;

/**
 * @typedef DDS_String String
 *
 * @ingroup CppCoreStruct
 *
 * @brief   ZRDDS内置的字符串类型。
 */

typedef DDS_String String;

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_KeyedString KeyedString
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_KeyedString 结构为C++接口。
 */

typedef DDS_KeyedString KeyedString;

/**
 * @typedef DDS_Bytes Bytes
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_Bytes 结构为C++接口。
 */

typedef DDS_Bytes Bytes;

/**
 * @typedef DDS_KeyedBytes KeyedBytes
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_KeyedBytes 结构为C++接口。
 */

typedef DDS_KeyedBytes KeyedBytes;

/**
 * @typedef DDS_ZeroCopyBytes ZeroCopyBytes
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_ZeroCopyBytes 结构为C++接口。
 */

typedef DDS_ZeroCopyBytes ZeroCopyBytes;

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_BooleanSeq BooleanSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_BooleanSeq 结构为C++接口。
 */

typedef DDS_BooleanSeq BooleanSeq;

/**
 * @typedef DDS_OctetSeq DDS_Octet
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_OctetSeq 结构为C++接口。
 */

typedef DDS_OctetSeq OctetSeq;

/**
 * @typedef DDS_CharSeq CharSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_CharSeq 结构为C++接口。
 */

typedef DDS_CharSeq CharSeq;

/**
 * @typedef DDS_ShortSeq ShortSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_ShortSeq 结构为C++接口。
 */

typedef DDS_ShortSeq ShortSeq;

/**
 * @typedef DDS_UShortSeq UShortSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UShortSeq 结构为C++接口。
 */

typedef DDS_UShortSeq UShortSeq;

/**
 * @typedef DDS_LongSeq LongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_LongSeq 结构为C++接口。
 */

typedef DDS_LongSeq LongSeq;

/**
 * @typedef DDS_ULongSeq ULongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_ULongSeq 结构为C++接口。
 */

typedef DDS_ULongSeq ULongSeq;

/**
 * @typedef DDS_LongLongSeq LongLongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_LongLongSeq 结构为C++接口。
 */

typedef DDS_LongLongSeq LongLongSeq;

/**
 * @typedef DDS_ULongLongSeq ULongLongSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_ULongLongSeq 结构为C++接口。
 */

typedef DDS_ULongLongSeq ULongLongSeq;

/**
 * @typedef DDS_FloatSeq FloatSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_FloatSeq 结构为C++接口。
 */

typedef DDS_FloatSeq FloatSeq;

/**
 * @typedef DDS_DoubleSeq DoubleSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_DoubleSeq 结构为C++接口。
 */

typedef DDS_DoubleSeq DoubleSeq;

/**
 * @typedef DDS_StringSeq StringSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_StringSeq 结构为C++接口。
 */

typedef DDS_StringSeq StringSeq;

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_KeyedStringSeq KeyedStringSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_KeyedStringSeq 结构为C++接口。
 */

typedef DDS_KeyedStringSeq KeyedStringSeq;

/**
 * @typedef DDS_BytesSeq BytesSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_BytesSeq 结构为C++接口。
 */

typedef DDS_BytesSeq BytesSeq;

/**
 * @typedef DDS_KeyedBytesSeq KeyedBytesSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_KeyedBytesSeq 结构为C++接口。
 */

typedef DDS_KeyedBytesSeq KeyedBytesSeq;

/**
 * @typedef DDS_ZeroCopyBytesSeq ZeroCopyBytesSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_ZeroCopyBytesSeq 结构为C++接口。
 */

typedef DDS_ZeroCopyBytesSeq ZeroCopyBytesSeq;

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

/**
 * @typedef DDS_DomainId_t DomainId_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DomainId_t 结构为C++接口。
 */
typedef DDS_DomainId_t DomainId_t;

/**
 * @typedef DDS_BuiltinTopicKey_t BuiltinTopicKey_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_BuiltinTopicKey_t 结构为C++接口。
 */
typedef DDS_BuiltinTopicKey_t BuiltinTopicKey_t;

/**
 * @typedef DDS_Duration_t Duration_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_Duration_t 结构为C++接口。
 */
typedef DDS_Duration_t Duration_t;

/**
 * @typedef DDS_Time_t Time_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_Time_t 结构为C++接口。
 */
typedef DDS_Time_t Time_t;

/** @brief 无穷秒  @ingroup   CppConstant */
DCPSDLL extern const Long DURATION_INFINITE_SEC;
/** @brief 0秒  @ingroup   CppConstant */
DCPSDLL extern const Long DURATION_ZERO_SEC;
/** @brief 无穷纳秒  @ingroup   CppConstant */
DCPSDLL extern const ULong DURATION_INFINITE_NSEC;
/** @brief 0纳秒  @ingroup   CppConstant */
DCPSDLL extern const ULong DURATION_ZERO_NSEC;
/** @brief  时间点为0。 @ingroup   CppConstant */
DCPSDLL extern const Time_t TIME_ZERO;
/** @brief  无效的时间点。 @ingroup   CppConstant */
DCPSDLL extern const Time_t TIME_INVALID;
/** @brief  无限长的时间点。 @ingroup   CppConstant */
DCPSDLL extern const Time_t TIME_INFINITE;

/**
 * @typedef DDS_InstanceHandle_t InstanceHandle_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_InstanceHandle_t 结构为C++接口。
 */
typedef DDS_InstanceHandle_t InstanceHandle_t;

/**
 * @brief   表示无效的 InstanceHandle_t 。
 *
 * @ingroup CppConstant
 */
DCPSDLL extern const InstanceHandle_t HANDLE_NIL_NATIVE;

/**
 * @typedef DDS_KeyHash_t KeyHash_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_KeyHash_t 结构为C++接口。
 */
typedef DDS_KeyHash_t KeyHash_t;

/**
 * @typedef DDS_InstanceHandleSeq InstanceHandleSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_InstanceHandleSeq 结构为C++接口。
 */
typedef DDS_InstanceHandleSeq InstanceHandleSeq;

/**
 * @typedef DDS_PublicationSendLocator PublicationSendLocator
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationSendLocator 结构为C++接口。
 */
typedef DDS_PublicationSendLocator PublicationSendLocator;

/**
 * @typedef DDS_PublicationSendLocatorSeq PublicationSendLocatorSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationSendLocatorSeq 结构为C++接口。
 */
typedef DDS_PublicationSendLocatorSeq PublicationSendLocatorSeq;

/**
 * @typedef DDS_PublicationSendStatus PublicationSendStatus
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationSendStatus 结构为C++接口。
 */
typedef DDS_PublicationSendStatus PublicationSendStatus;

/**
 * @typedef DDS_PublicationSendStatusSeq PublicationSendStatusSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationSendStatusSeq 结构为C++接口。
 */
typedef DDS_PublicationSendStatusSeq PublicationSendStatusSeq;

/**
 * @typedef DDS_ReturnCode_t ReturnCode_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ReturnCode_t 结构为C++接口。
 */
typedef DDS_ReturnCode_t ReturnCode_t;

/** @brief 执行成功。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_OK;
/** @brief 执行出错。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_ERROR;
/** @brief 不支持操作。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_UNSUPPORTED;
/** @brief 不正确的参数。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_BAD_PARAMETER;
/** @brief 调用操作的前置条件未满足。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_PRECONDITION_NOT_MET;
/** @brief 资源不够。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_OUT_OF_RESOURCES;
/** @brief 实体未使能，不能进行该操作。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_NOT_ENABLED;
/** @brief 试图修改使能后不能修改的Qos。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_IMMUTABLE_POLICY;
/** @brief 不一致的Qos。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_INCONSISTENT;
/** @brief 试图删除已经被删除的实体。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_ALREADY_DELETED;
/** @brief 操作超时。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_TIMEOUT;
/** @brief 在读数据的时候，没有有效的数据。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_NO_DATA;
/** @brief 非法的操作。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_ILLEGAL_OPERATION;
/** @brief 操作因安全原因被拒绝。 @ingroup CppConstant  */
DCPSDLL extern const ReturnCode_t RETCODE_NOT_ALLOWED_BY_SEC;

/**
 * @typedef DDS_SequenceNumber_t SequenceNumber_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SequenceNumber_t 结构为C++接口。
 */
typedef DDS_SequenceNumber_t SequenceNumber_t;

#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC
/**
 * @typedef DDS_ContentFilterProperty_t ContentFilterProperty_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ContentFilterProperty_t 结构为C++接口。
 */
typedef DDS_ContentFilterProperty_t ContentFilterProperty_t;

#endif //_ZRDDS_INCLUDE_CONTENTFILTER_TOPIC
// Qos
/**
 * @typedef DDS_AsynchronousPublisherQosPolicy AsynchronousPublisherQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_AsynchronousPublisherQosPolicy 结构为C++接口。
 */
typedef DDS_AsynchronousPublisherQosPolicy AsynchronousPublisherQosPolicy;

/**
 * @typedef DDS_BatchQosPolicy BatchQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_BatchQosPolicy 结构为C++接口。
 */
typedef DDS_BatchQosPolicy BatchQosPolicy;

/**
 * @typedef DDS_DataReaderQos DataReaderQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataReaderQos 结构为C++接口。
 */
typedef DDS_DataReaderQos DataReaderQos;

/**
 * @typedef DDS_DataRepresentationQosPolicy DataRepresentationQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataRepresentationQosPolicy 结构为C++接口。
 */
typedef DDS_DataRepresentationQosPolicy DataRepresentationQosPolicy;

/**
 * @typedef DDS_DataWriterMessageModeQosPolicy DataWriterMessageModeQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataWriterMessageModeQosPolicy 结构为C++接口。
 */
typedef DDS_DataWriterMessageModeQosPolicy DataWriterMessageModeQosPolicy;

/**
 * @typedef DDS_RtpsReliableWriterProtocol RtpsReliableWriterProtocol 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_RtpsReliableWriterProtocol 结构为C++接口。
 */
typedef DDS_RtpsReliableWriterProtocol RtpsReliableWriterProtocol;

/**
 * @typedef DDS_DataWriterProtocolQosPolicy DataWriterProtocolQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataWriterProtocolQosPolicy 结构为C++接口。
 */
typedef DDS_DataWriterProtocolQosPolicy DataWriterProtocolQosPolicy;

/**
 * @typedef DDS_DataWriterQos DataWriterQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataWriterQos 结构为C++接口。
 */
typedef DDS_DataWriterQos DataWriterQos;

/**
 * @typedef DDS_DataWriterResourceLimitsInstanceReplacementKind DataWriterResourceLimitsInstanceReplacementKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataWriterResourceLimitsInstanceReplacementKind 结构为C++接口。
 */
typedef DDS_DataWriterResourceLimitsInstanceReplacementKind DataWriterResourceLimitsInstanceReplacementKind;

/** @brief  只替换已注销的实例，映射核心常量 #DDS_UNREGISTERED_INSTANCE_REPLACEMENT 。 @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind UNREGISTERED_INSTANCE_REPLACEMENT;
/** @brief  只替换存活的实例，映射核心常量 #DDS_ALIVE_INSTANCE_REPLACEMENT 。 @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind ALIVE_INSTANCE_REPLACEMENT;
/** @brief  只替换已销毁的实例，映射核心常量 #DDS_DISPOSED_INSTANCE_REPLACEMENT 。 @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind DISPOSED_INSTANCE_REPLACEMENT;
/** @brief  优先替换存活的实例，若不存在则替换已注销的实例，映射核心常量 #ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT 。 @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT;
/** @brief  优先替换已销毁的实例，若不存在则替换存活的实例，映射核心常量 #DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT 。 @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT;
/** @brief  替换存活或者已注销的实例，映射核心常量 #ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT 。 @ingroup CppConstant */
DCPSDLL extern const DataWriterResourceLimitsInstanceReplacementKind ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT;

/**
 * @typedef DDS_DataWriterResourceLimitsQosPolicy DataWriterResourceLimitsQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataWriterResourceLimitsQosPolicy 结构为C++接口。
 */
typedef DDS_DataWriterResourceLimitsQosPolicy DataWriterResourceLimitsQosPolicy;

/**
 * @typedef DDS_LogType LogType 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LogType 结构为C++接口。
 */
typedef DDS_LogType LogType;

/**
 * @typedef DDS_LogQosPolicy LogQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LogQosPolicy 结构为C++接口。
 */
typedef DDS_LogQosPolicy LogQosPolicy;

/**
 * @typedef DDS_LogBackupKind LogBackupKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LogBackupKind 结构为C++接口。
 */
typedef DDS_LogBackupKind LogBackupKind;

#ifdef _ZRDDS_INCLUDE_GATEWAY
/**
 * @typedef DDS_GatewayQosPolicyKind GatewayQosPolicyKind
 *
 * @brief   映射核心数据 #DDS_GatewayQosPolicyKind 结构为C++接口.
 */
typedef DDS_GatewayQosPolicyKind GatewayQosPolicyKind;

/**
 * @typedef DDS_GatewayQosPolicy GatewayQosPolicy
 *
 * @brief   映射核心数据 #DDS_GatewayQosPolicy 结构为C++接口.
 */
typedef DDS_GatewayQosPolicy GatewayQosPolicy;

/**
 * @brief   无需子网网关参与转发。
 *
 * @ingroup CppConstant
 *
 * @details  参见核心常量 #DDS_NO_FORWARD_GATEWAY_QOS 。
 */
DCPSDLL extern const GatewayQosPolicyKind NO_FORWARD_GATEWAY_QOS;

/**
 * @brief   仅需要子网网关将Data(p)转发给已知的同一域号下的其它域参与者。
 *
 * @ingroup CppConstant
 *
 * @details  参见核心常量 #DDS_SPDP_FORWARD_GATEWAY_QOS 。
 */
DCPSDLL extern const GatewayQosPolicyKind SPDP_FORWARD_GATEWAY_QOS;

/**
 * @brief   需要子网网关协助打洞通信。
 *
 * @ingroup CppConstant
 *
 * @warning 该类型未实现 参见核心常量 #DDS_SEDP_FORWARD_GATEWAY_QOS 。
 */
DCPSDLL extern const GatewayQosPolicyKind SEDP_FORWARD_GATEWAY_QOS;

/**
 * @brief   需要子网网关转发所有的数据（包括内置数据以及用户数据）。
 *
 * @ingroup CppConstant
 *
 * @details  参见核心常量 #DDS_USER_FORWARD_GATEWAY_QOS 。
 */
DCPSDLL extern const GatewayQosPolicyKind USER_FORWARD_GATEWAY_QOS;

/**
 * @brief   需要子网网关协助打洞通信。
 *
 * @ingroup CppConstant
 *
 * @warning 该类型未实现 参见核心常量 #DDS_USER_FORWARD_ONLY_GATEWAY_QOS 。
 */
DCPSDLL extern const GatewayQosPolicyKind USER_FORWARD_ONLY_GATEWAY_QOS;

#endif // _ZRDDS_INCLUDE_GATEWAY

/**
 * @typedef DDS_Property_t Property_t
 *
 * @brief 扩展的Property_t.
 */
typedef DDS_Property_t Property_t;

/**
 * @typedef DDS_BinaryProperty_t BinaryProperty_t
 *
 * @brief 二值的键值对。
 */
typedef DDS_BinaryProperty_t BinaryProperty_t;

typedef DDS_PropertySeq PropertySeq;

typedef DDS_BinaryPropertySeq BinaryPropertySeq;

typedef DDS_PropertyQosPolicy PropertyQosPolicy;

typedef DDS_TypeConsistencyEnforcementQosPolicy TypeConsistencyEnforcementQosPolicy;

#ifdef _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
/**
 * @typedef DDS_MsgStatisticsInfoQosPolicy MsgStatisticsInfoQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_MsgStatisticsInfoQosPolicy 结构为C++接口。
 */
typedef DDS_MsgStatisticsInfoQosPolicy MsgStatisticsInfoQosPolicy;

#endif //_ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @typedef DDS_DeadlineQosPolicy DeadlineQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DeadlineQosPolicy 结构为C++接口。
 */
typedef DDS_DeadlineQosPolicy DeadlineQosPolicy;

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS
#ifdef _ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
/**
 * @typedef DDS_DestinationOrderQosPolicyKind DestinationOrderQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DestinationOrderQosPolicyKind 结构为C++接口。
 */
typedef DDS_DestinationOrderQosPolicyKind DestinationOrderQosPolicyKind;

/**
 * @brief   以数据读者接收到的顺序存储在数据读者的内部队列中。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS 。
 */
DCPSDLL extern const DestinationOrderQosPolicyKind BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
/**
 * @brief   以样本数据的源时间戳顺序存储在数据读者的内部队列中。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS 。
 */
DCPSDLL extern const DestinationOrderQosPolicyKind BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;

/**
 * @typedef DDS_DestinationOrderQosPolicy DestinationOrderQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DestinationOrderQosPolicy 结构为C++接口。
 */
typedef DDS_DestinationOrderQosPolicy DestinationOrderQosPolicy;

#endif //_ZRDDS_INCLUDE_DESTINATION_ORDER_QOS
/**
 * @typedef DDS_DiscoveryConfigQosPolicy DiscoveryConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DiscoveryConfigQosPolicy 结构为C++接口。
 */
typedef DDS_DiscoveryConfigQosPolicy DiscoveryConfigQosPolicy;

/**
 * @typedef DDS_DomainParticipantFactoryQos DomainParticipantFactoryQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DomainParticipantFactoryQos 结构为C++接口。
 */
typedef DDS_DomainParticipantFactoryQos DomainParticipantFactoryQos;

/**
 * @typedef DDS_DomainParticipantQos DomainParticipantQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DomainParticipantQos 结构为C++接口。
 */
typedef DDS_DomainParticipantQos DomainParticipantQos;

/**
 * @typedef DDS_DurabilityQosPolicyKind DurabilityQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DurabilityQosPolicyKind 结构为C++接口。
 */
typedef DDS_DurabilityQosPolicyKind DurabilityQosPolicyKind;

/**
 * @brief   无持久化。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_VOLATILE_DURABILITY_QOS 。
 */
DCPSDLL extern const DurabilityQosPolicyKind VOLATILE_DURABILITY_QOS;

/**
 * @brief   存活的数据写者在内存中持久化。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_TRANSIENT_LOCAL_DURABILITY_QOS 。
 */
DCPSDLL extern const DurabilityQosPolicyKind TRANSIENT_LOCAL_DURABILITY_QOS;

/**
 * @brief   所有数据写者（包括在数据读者加入DDS网络时已经被删除的数据写者）在内存中持久化。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_TRANSIENT_DURABILITY_QOS 。
 */
DCPSDLL extern const DurabilityQosPolicyKind TRANSIENT_DURABILITY_QOS;

/**
 * @brief   所有数据写者（包括在数据读者加入DDS网络时已经被删除的数据写者）在持久化存储（文件、数据库）中持久化。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_PERSISTENT_DURABILITY_QOS 。
 */
DCPSDLL extern const DurabilityQosPolicyKind PERSISTENT_DURABILITY_QOS;

/**
 * @typedef DDS_DurabilityQosPolicy DurabilityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DurabilityQosPolicy 结构为C++接口。
 */
typedef DDS_DurabilityQosPolicy DurabilityQosPolicy;

/**
 * @typedef DDS_DurabilityServiceQosPolicy DurabilityServiceQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DurabilityServiceQosPolicy 结构为C++接口。
 */
typedef DDS_DurabilityServiceQosPolicy DurabilityServiceQosPolicy;

/**
 * @typedef DDS_EntityFactoryQosPolicy EntityFactoryQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_EntityFactoryQosPolicy 结构为C++接口。
 */
typedef DDS_EntityFactoryQosPolicy EntityFactoryQosPolicy;

#ifdef _ZRXMLQOSINTERFACE
/**
 * @typedef DDS_QosProfileQosPolicy QosProfileQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_QosProfileQosPolicy 结构为C++接口。
 */
typedef DDS_QosProfileQosPolicy QosProfileQosPolicy;
#endif // _ZRXMLQOSINTERFACE

#ifdef _ZRDDS_INCLUDE_GROUP_DATA_QOS
/**
 * @typedef DDS_GroupDataQosPolicy GroupDataQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_GroupDataQosPolicy 结构为C++接口。
 */
typedef DDS_GroupDataQosPolicy GroupDataQosPolicy;

#endif //_ZRDDS_INCLUDE_GROUP_DATA_QOS
/**
 * @typedef DDS_HistoryQosPolicyKind HistoryQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_HistoryQosPolicyKind 结构为C++接口。
 */
typedef DDS_HistoryQosPolicyKind HistoryQosPolicyKind;

/**
 * @brief   保存最新样本数据类型。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_KEEP_LAST_HISTORY_QOS 。
 */
DCPSDLL extern const HistoryQosPolicyKind KEEP_LAST_HISTORY_QOS;
/**
 * @brief   尝试保存所有样本数据类型。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_KEEP_ALL_HISTORY_QOS 。
 */
DCPSDLL extern const HistoryQosPolicyKind KEEP_ALL_HISTORY_QOS;

/**
 * @typedef DDS_HistoryQosPolicy HistoryQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_HistoryQosPolicy 结构为C++接口。
 */
typedef DDS_HistoryQosPolicy HistoryQosPolicy;

#ifdef _ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
/**
 * @typedef DDS_LatencyBudgetQosPolicy LatencyBudgetQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LatencyBudgetQosPolicy 结构为C++接口。
 */
typedef DDS_LatencyBudgetQosPolicy LatencyBudgetQosPolicy;

#endif //_ZRDDS_INCLUDE_LATENCY_BUDGET_QOS
#ifdef _ZRDDS_INCLUDE_LIFESPAN_QOS
/**
 * @typedef DDS_LifespanQosPolicy LifespanQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LifespanQosPolicy 结构为C++接口。
 */
typedef DDS_LifespanQosPolicy LifespanQosPolicy;

#endif // _ZRDDS_INCLUDE_LIFESPAN_QOS
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
/**
 * @typedef DDS_LivelinessQosPolicyKind LivelinessQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LivelinessQosPolicyKind 结构为C++接口。
 */
typedef DDS_LivelinessQosPolicyKind LivelinessQosPolicyKind;

/**
 * @brief   由ZRDDS底层自动管理存活性声明。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_AUTOMATIC_LIVELINESS_QOS 。
 */
DCPSDLL extern const LivelinessQosPolicyKind AUTOMATIC_LIVELINESS_QOS;
/**
 * @brief   通过域参与者手动管理存活性声明。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_MANUAL_BY_PARTICIPANT_LIVELINESS_QOS 。
 */
DCPSDLL extern const LivelinessQosPolicyKind MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
/**
 * @brief   由数据写者手动管理存活性声明。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS 。
 */
DCPSDLL extern const LivelinessQosPolicyKind MANUAL_BY_TOPIC_LIVELINESS_QOS;

/**
 * @typedef DDS_LivelinessQosPolicy LivelinessQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LivelinessQosPolicy 结构为C++接口。
 */
typedef DDS_LivelinessQosPolicy LivelinessQosPolicy;

#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
#ifdef _ZRDDS_INCLUDE_OWNERSHIP_QOS
/**
 * @typedef DDS_OwnershipQosPolicyKind OwnershipQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_OwnershipQosPolicyKind 结构为C++接口。
 */
typedef DDS_OwnershipQosPolicyKind OwnershipQosPolicyKind;

/**
 * @brief   共享所有权类型。
 *
 * @ingroup CppConstant
 * 
 * @details 参见核心常量 #DDS_SHARED_OWNERSHIP_QOS 。
 */
DCPSDLL extern const OwnershipQosPolicyKind SHARED_OWNERSHIP_QOS;
/**
 * @brief   独占所有权类型。
 *
 * @ingroup CppConstant
 * 
 * @details 参见核心常量 #DDS_EXCLUSIVE_OWNERSHIP_QOS 。
 */
DCPSDLL extern const OwnershipQosPolicyKind EXCLUSIVE_OWNERSHIP_QOS;

/**
 * @typedef DDS_OwnershipQosPolicy OwnershipQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_OwnershipQosPolicy 结构为C++接口。
 */
typedef DDS_OwnershipQosPolicy OwnershipQosPolicy;

/**
 * @typedef DDS_OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_OwnershipStrengthQosPolicy 结构为C++接口。
 */
typedef DDS_OwnershipStrengthQosPolicy OwnershipStrengthQosPolicy;

#endif //_ZRDDS_INCLUDE_OWNERSHIP_QOS
#ifdef _ZRDDS_INCLUDE_PARTITION_QOS
/**
 * @typedef DDS_PartitionQosPolicy PartitionQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PartitionQosPolicy 结构为C++接口。
 */
typedef DDS_PartitionQosPolicy PartitionQosPolicy;

#endif //_ZRDDS_INCLUDE_PARTITION_QOS
#ifdef _ZRDDS_INCLUDE_PRESENTATION_QOS
/**
 * @typedef DDS_PresentationQosPolicyAccessScopeKind PresentationQosPolicyAccessScopeKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PresentationQosPolicyAccessScopeKind 结构为C++接口。
 */
typedef DDS_PresentationQosPolicyAccessScopeKind PresentationQosPolicyAccessScopeKind;

/** @brief  范围为数据实例，具体含义参见 PresentationQosPolicy @ingroup CppConstant */
DCPSDLL extern const PresentationQosPolicyAccessScopeKind INSTANCE_PRESENTATION_QOS;
/** @brief  范围为主题，具体含义参见 PresentationQosPolicy @ingroup CppConstant */
DCPSDLL extern const PresentationQosPolicyAccessScopeKind TOPIC_PRESENTATION_QOS;
/** @brief  范围为组，具体含义参见 PresentationQosPolicy @ingroup CppConstant */
DCPSDLL extern const PresentationQosPolicyAccessScopeKind GROUP_PRESENTATION_QOS;

/**
 * @typedef DDS_PresentationQosPolicy PresentationQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PresentationQosPolicy 结构为C++接口。
 */
typedef DDS_PresentationQosPolicy PresentationQosPolicy;

#endif //_ZRDDS_INCLUDE_PRESENTATION_QOS
/**
 * @typedef DDS_PublisherQos PublisherQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublisherQos 结构为C++接口。
 */
typedef DDS_PublisherQos PublisherQos;

/**
 * @typedef DDS_PublishModeQosPolicyKind PublishModeQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublishModeQosPolicyKind 结构为C++接口。
 */
typedef DDS_PublishModeQosPolicyKind PublishModeQosPolicyKind;

/** @brief  同步发送模式, 参见核心常量 #DDS_SYNCHRONOUS_PUBLISH_MODE_QOS 。 @ingroup CppConstant */
DCPSDLL extern const PublishModeQosPolicyKind SYNCHRONOUS_PUBLISH_MODE_QOS;
/** @brief  异步发送模式, 参见核心常量 #DDS_ASYNCHRONOUS_PUBLISH_MODE_QOS 。 @ingroup CppConstant */
DCPSDLL extern const PublishModeQosPolicyKind ASYNCHRONOUS_PUBLISH_MODE_QOS;

/**
 * @typedef DDS_PublishModeQosPolicy PublishModeQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublishModeQosPolicy 结构为C++接口。
 */
typedef DDS_PublishModeQosPolicy PublishModeQosPolicy;

/**
 * @typedef DDS_QosPolicyCount QosPolicyCount 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_QosPolicyCount 结构为C++接口。
 */
typedef DDS_QosPolicyCount QosPolicyCount;

/**
 * @typedef DDS_QosPolicyId_t QosPolicyId_t 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_QosPolicyId_t 结构为C++接口。
 */
typedef DDS_QosPolicyId_t QosPolicyId_t;

/** @brief  无效的标识。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t INVALID_QOS_POLICY_ID;
/** @brief  标识 UserDataQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t USERDATA_QOS_POLICY_ID;
/** @brief  标识 DurabilityQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DURABILITY_QOS_POLICY_ID;
/** @brief  标识 PresentationQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t PRESENTATION_QOS_POLICY_ID;
/** @brief  标识 DeadlineQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DEADLINE_QOS_POLICY_ID;
/** @brief  标识 LatencyBudgetQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t LATENCYBUDGET_QOS_POLICY_ID;
/** @brief  标识 OwnershipQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t OWNERSHIP_QOS_POLICY_ID;
/** @brief  标识 OwnershipStrengthQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t OWNERSHIPSTRENGTH_QOS_POLICY_ID;
/** @brief  标识 LivelinessQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t LIVELINESS_QOS_POLICY_ID;
/** @brief  标识 TimeBasedFilterQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TIMEBASEDFILTER_QOS_POLICY_ID;
/** @brief  标识 PartitionQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t PARTITION_QOS_POLICY_ID;
/** @brief  标识 ReliabilityQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t RELIABILITY_QOS_POLICY_ID;
/** @brief  标识 DestinationOrderQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DESTINATIONORDER_QOS_POLICY_ID;
/** @brief  标识 HistoryQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t HISTORY_QOS_POLICY_ID;
/** @brief  标识 ResourceLimitsQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t RESOURCELIMITS_QOS_POLICY_ID;
/** @brief  标识 EntityFactoryQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t ENTITYFACTORY_QOS_POLICY_ID;
/** @brief  标识 WriterDataLifeCycleQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t WRITERDATALIFECYCLE_QOS_POLICY_ID;
/** @brief  标识 ReaderDataLifeCycleQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t READERDATALIFECYCLE_QOS_POLICY_ID;
/** @brief  标识 TopicDataQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TOPICDATA_QOS_POLICY_ID;
/** @brief  标识 GroupDataQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t GROUPDATA_QOS_POLICY_ID;
/** @brief  标识 TransportPriorityQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TRANSPORTPRIORITY_QOS_POLICY_ID;
/** @brief  标识 LifespanQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t LIFESPAN_QOS_POLICY_ID;
/** @brief  标识 DurabilityServiceQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DURABILITYSERVICE_QOS_POLICY_ID;
/** @brief  标识 RepresentationQosPolicy 。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DATA_REPRESENTATION_QOS_POLICY_ID;
/** @brief  保留类型。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID;
/** @brief  保留类型。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t NETWORKCONFIG_QOS_POLICY_ID;
/** @brief  保留类型。 @ingroup CppConstant */
DCPSDLL extern const QosPolicyId_t DISCOVERYCONFIG_QOS_POLICY_ID;

/**
 * @typedef DDS_TransportKind TransportKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TransportKind 结构为C++接口。
 */
typedef DDS_TransportKind TransportKind;

/**
 * @typedef DDS_LocatorStatusKind LocatorStatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LocatorStatusKind 结构为C++接口。
 */
typedef DDS_LocatorStatusKind LocatorStatusKind;

#ifdef _ZRDDS_RIO
/**
 * @typedef DDS_RapidIOConfigQosPolicy RapidIOConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_RapidIOConfigQosPolicy 结构为C++接口。
 */
typedef DDS_RapidIOConfigQosPolicy RapidIOConfigQosPolicy;

/**
 * @typedef DDS_RapidIOControllerQosPolicy RapidIOControllerQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_RapidIOControllerQosPolicy 结构为C++接口。
 */
typedef DDS_RapidIOControllerQosPolicy RapidIOControllerQosPolicy;
#endif /* _ZRDDS_RIO */

/**
 * @typedef DDS_ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ReaderDataLifecycleQosPolicy 结构为C++接口。
 */
typedef DDS_ReaderDataLifecycleQosPolicy ReaderDataLifecycleQosPolicy;

/**
 * @typedef DDS_ReceiverThreadConfigQosPolicy ReceiverThreadConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ReceiverThreadConfigQosPolicy 结构为C++接口。
 */
typedef DDS_ReceiverThreadConfigQosPolicy ReceiverThreadConfigQosPolicy;

/**
 * @typedef DDS_ReceiverThreadKind ReceiverThreadKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ReceiverThreadKind 结构为C++接口。
 */
typedef DDS_ReceiverThreadKind ReceiverThreadKind;

/**
 * @brief  每个端口一个接收线程。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_THREAD_PER_PORT 。
 */
DCPSDLL extern const ReceiverThreadKind THREAD_PER_PORT;
/**
 * @brief  每个类型一个接收线程，内置的一个线程，用户的一个线程。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_THREAD_PER_KIND 。
 */
DCPSDLL extern const ReceiverThreadKind THREAD_PER_KIND;
/**
 * @brief  所有的端口都使用一个线程。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_THREAD_ALL_PORTS 。
 */
DCPSDLL extern const ReceiverThreadKind THREAD_ALL_PORTS;

/**
 * @typedef DDS_ReliabilityQosPolicyKind ReliabilityQosPolicyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ReliabilityQosPolicyKind 结构为C++接口。
 */
typedef DDS_ReliabilityQosPolicyKind ReliabilityQosPolicyKind;

/** @brief 尽力而为配置，参见核心常量 #DDS_BEST_EFFORT_RELIABILITY_QOS 。 @ingroup CppConstant */
DCPSDLL extern const ReliabilityQosPolicyKind BEST_EFFORT_RELIABILITY_QOS;
/** @brief 可靠配置，参见核心常量 #DDS_BEST_EFFORT_RELIABILITY_QOS 。@ingroup CppConstant */
DCPSDLL extern const ReliabilityQosPolicyKind RELIABLE_RELIABILITY_QOS;

/**
 * @typedef DDS_ReliabilityQosPolicy ReliabilityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ReliabilityQosPolicy 结构为C++接口。
 */
typedef DDS_ReliabilityQosPolicy ReliabilityQosPolicy;

/**
 * @typedef DDS_ResourceLimitsQosPolicy ResourceLimitsQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ResourceLimitsQosPolicy 结构为C++接口。
 */
typedef DDS_ResourceLimitsQosPolicy ResourceLimitsQosPolicy;

/**
 * @typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief   用于标识数据样本被拒绝的原因类型。
 */
typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind;

/** @brief   数据样本未被拒绝，参见核心常量 #DDS_NOT_REJECTED 。 @ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind NOT_REJECTED;
/** @brief   数据样本由于 ResourceLimitsQosPolicy::max_instances 原因被拒绝，参见核心常量 #DDS_REJECTED_BY_INSTANCE_LIMIT 。@ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind REJECTED_BY_INSTANCE_LIMIT;
/** @brief   数据样本由于 ResourceLimitsQosPolicy::max_samples 原因被拒绝，参见核心常量 #DDS_REJECTED_BY_SAMPLES_LIMIT 。 @ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind REJECTED_BY_SAMPLES_LIMIT;
/** @brief   数据样本由于 ResourceLimitsQosPolicy::max_samples_per_instance 原因被拒绝，参见核心常量 #DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT 。 @ingroup CppConstant */
DCPSDLL extern const SampleRejectedStatusKind REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT;

/**
 * @typedef DDS_SubscriberQos SubscriberQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SubscriberQos 结构为C++接口。
 */
typedef DDS_SubscriberQos SubscriberQos;

/**
 * @typedef DDS_ThreadCoreAffinityQosPolicy ThreadCoreAffinityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ThreadCoreAffinityQosPolicy 结构为C++接口。
 */
typedef DDS_ThreadCoreAffinityQosPolicy ThreadCoreAffinityQosPolicy;

#ifdef _ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
/**
 * @typedef DDS_TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TimeBasedFilterQosPolicy 结构为C++接口。
 */
typedef DDS_TimeBasedFilterQosPolicy TimeBasedFilterQosPolicy;

#endif //_ZRDDS_INCLUDE_TIME_BASED_FILTER_QOS
#ifdef _ZRDDS_INCLUDE_TOPIC_DATA_QOS
/**
 * @typedef DDS_TopicDataQosPolicy TopicDataQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TopicDataQosPolicy 结构为C++接口。
 */
typedef DDS_TopicDataQosPolicy TopicDataQosPolicy;

#endif //_ZRDDS_INCLUDE_TOPIC_DATA_QOS
/**
 * @typedef DDS_TopicQos TopicQos 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TopicQos 结构为C++接口。
 */
typedef DDS_TopicQos TopicQos;

/**
 * @typedef DDS_TransportConfigQosPolicy TransportConfigQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TransportConfigQosPolicy 结构为C++接口。
 */
typedef DDS_TransportConfigQosPolicy TransportConfigQosPolicy;

#ifdef _ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
/**
 * @typedef DDS_TransportPriorityQosPolicy TransportPriorityQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TransportPriorityQosPolicy 结构为C++接口。
 */
typedef DDS_TransportPriorityQosPolicy TransportPriorityQosPolicy;

#endif //_ZRDDS_INCLUDE_TRANSPORT_PRIORITY_QOS
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
/**
 * @typedef DDS_UserDataQosPolicy UserDataQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_UserDataQosPolicy 结构为C++接口。
 */
typedef DDS_UserDataQosPolicy UserDataQosPolicy;

#endif //_ZRDDS_INCLUDE_USER_DATA_QOS
/**
 * @typedef DDS_WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_WriterDataLifecycleQosPolicy 结构为C++接口。
 */
typedef DDS_WriterDataLifecycleQosPolicy WriterDataLifecycleQosPolicy;

/**
 * @brief   特殊的 DomainParticipantFactoryQos 表示使用ZRDDS默认的QoS。
 *
 * @ingroup CppCoreStruct
 *          
 * @details 参见核心常量 #DDS_DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_DomainParticipantFactoryQos& DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT;

/**
 * @brief   特殊的 DomainParticipantQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_DOMAINPARTICIPANT_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_DomainParticipantQos& DOMAINPARTICIPANT_QOS_DEFAULT;

/**
 * @brief   特殊的 PublisherQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CppCoreStruct
 *          
 * @details 参见核心常量 #DDS_PUBLISHER_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_PublisherQos& PUBLISHER_QOS_DEFAULT;

/**
 * @brief   特殊的 SubscriberQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_SUBSCRIBER_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_SubscriberQos& SUBSCRIBER_QOS_DEFAULT;

/**
 * @brief   特殊的 DataWriterQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_DATAWRITER_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_DataWriterQos& DATAWRITER_QOS_DEFAULT;

/**
 * @brief   特殊的 DataReaderQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_DATAREADER_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_DataReaderQos& DATAREADER_QOS_DEFAULT;

/**
 * @brief   特殊的 TopicQos 表示使用保存在父实体中的默认QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_TOPIC_QOS_DEFAULT 。
 */

DCPSDLL extern const DDS_TopicQos& TOPIC_QOS_DEFAULT;

/**
 * @brief   特殊的 DataWriterQos 表示使用数据写者关联主题的QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_DATAWRITER_QOS_USE_TOPIC_QOS 。
 */

DCPSDLL extern const DDS_DataWriterQos& DATAWRITER_QOS_USE_TOPIC_QOS;

/**
 * @brief   特殊的 DataReaderQos 表示使用数据读者关联主题的QoS。
 *
 * @ingroup CppCoreStruct
 *
 * @details 参见核心常量 #DDS_DATAREADER_QOS_USE_TOPIC_QOS 。
 */

DCPSDLL extern const DDS_DataReaderQos& DATAREADER_QOS_USE_TOPIC_QOS;

#if defined(_ZRDDSSECURITY)

/**
 * @typedef DDS_DataHolder DataHolder 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataHolder 结构为C++接口。
 */
typedef DDS_DataHolder DataHolder;

/**
 * @typedef DDS_DataHolderSeq DataHolderSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataHolderSeq 结构为C++接口。
 */
typedef DDS_DataHolderSeq DataHolderSeq;

/**
 * @typedef DDS_Tag Tag 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_Tag 结构为C++接口。
 */
typedef DDS_Tag Tag;

/**
 * @typedef DDS_TagSeq TagSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TagSeq 结构为C++接口。
 */
typedef DDS_TagSeq TagSeq;

/**
 * @typedef DDS_DataTags DataTags 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataTags 结构为C++接口。
 */
typedef DDS_DataTags DataTags;

/**
 * @typedef DDS_DataTagQosPolicy DataTagQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_DataTagQosPolicy 结构为C++接口。
 */
typedef DDS_DataTagQosPolicy DataTagQosPolicy;

/**
 * @typedef DDS_SecurityPluginType SecurityPluginType
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SecurityPluginType 结构为C++接口。
 */
typedef DDS_SecurityPluginType SecurityPluginType;

/**
 * @typedef DDS_SecurityPlugin SecurityPlugin
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SecurityPlugin 结构为C++接口。
 */
typedef DDS_SecurityPlugin SecurityPlugin;

/**
 * @typedef DDS_SecurityPluginSeq SecurityPluginSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SecurityPluginSeq 结构为C++接口。
 */
typedef DDS_SecurityPluginSeq SecurityPluginSeq;

/**
 * @typedef DDS_SecurityPluginQosPolicy SecurityPluginQosPolicy
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SecurityPluginQosPolicy 结构为C++接口。
 */
typedef DDS_SecurityPluginQosPolicy SecurityPluginQosPolicy;


/**
 * @typedef DDS_EndpointSecurityInfo EndpointSecurityInfo
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_EndpointSecurityInfo 结构为C++接口。
 */
typedef DDS_EndpointSecurityInfo EndpointSecurityInfo;

#endif

/**
 * @typedef DDS_SubscriptionMatchedStatus SubscriptionMatchedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SubscriptionMatchedStatus 结构为C++接口。
 */
typedef DDS_SubscriptionMatchedStatus SubscriptionMatchedStatus;

/**
 * @typedef DDS_InconsistentTopicStatus InconsistentTopicStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_InconsistentTopicStatus 结构为C++接口。
 */
typedef DDS_InconsistentTopicStatus InconsistentTopicStatus;

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
/**
 * @typedef DDS_LivelinessChangedStatus LivelinessChangedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LivelinessChangedStatus 结构为C++接口。
 */
typedef DDS_LivelinessChangedStatus LivelinessChangedStatus;

/**
 * @typedef DDS_LivelinessLostStatus LivelinessLostStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LivelinessLostStatus 结构为C++接口。
 */
typedef DDS_LivelinessLostStatus LivelinessLostStatus;

#endif //_ZRDDS_INCLUDE_LIVELINESS_QOS
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @typedef DDS_OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_OfferedDeadlineMissedStatus 结构为C++接口。
 */
typedef DDS_OfferedDeadlineMissedStatus OfferedDeadlineMissedStatus;

/**
 * @typedef DDS_RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_RequestedDeadlineMissedStatus 结构为C++接口。
 */
typedef DDS_RequestedDeadlineMissedStatus RequestedDeadlineMissedStatus;

#endif //_ZRDDS_INCLUDE_DEADLINE_QOS
/**
 * @typedef DDS_OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_OfferedIncompatibleQosStatus 结构为C++接口。
 */
typedef DDS_OfferedIncompatibleQosStatus OfferedIncompatibleQosStatus;

/**
 * @typedef DDS_PublicationMatchedStatus PublicationMatchedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationMatchedStatus 结构为C++接口。
 */
typedef DDS_PublicationMatchedStatus PublicationMatchedStatus;

/**
 * @typedef DDS_RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_RequestedIncompatibleQosStatus 结构为C++接口。
 */
typedef DDS_RequestedIncompatibleQosStatus RequestedIncompatibleQosStatus;

/**
 * @typedef DDS_QosPolicyCountSeq QosPolicyCountSeq
 *
 * @ingroup CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_QosPolicyCountSeq 结构为C++接口。 
 */

typedef DDS_QosPolicyCountSeq QosPolicyCountSeq;

/**
 * @typedef DDS_SampleLostStatus SampleLostStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleLostStatus 结构为C++接口。
 */
typedef DDS_SampleLostStatus SampleLostStatus;

/**
 * @typedef DDS_SampleRejectedStatus SampleRejectedStatus 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleRejectedStatus 结构为C++接口。
 */
typedef DDS_SampleRejectedStatus SampleRejectedStatus;

/**
 * @typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleRejectedStatusKind 结构为C++接口。
 */
typedef DDS_SampleRejectedStatusKind SampleRejectedStatusKind;

/**
 * @typedef DDS_TypeConsistencyKind TypeConsistencyKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TypeConsistencyKind 结构为C++接口。
 */
typedef DDS_TypeConsistencyKind TypeConsistencyKind;

DCPSDLL extern const TypeConsistencyKind DISALLOW_TYPE_COERCION;
DCPSDLL extern const TypeConsistencyKind ALLOW_TYPE_COERCION;

/**
 * @typedef DDS_RTPS_MESSAGE_KIND RTPS_MESSAGE_KIND 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_RTPS_MESSAGE_KIND 结构为C++接口。
 */
typedef DDS_RTPS_MESSAGE_KIND RTPS_MESSAGE_KIND;

// data
/**
 * @typedef DDS_Property Property
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_Property 结构为C++接口。
 */
typedef DDS_Property Property;

/**
 * @typedef DDS_PropertyList PropertyList 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PropertyList 结构为C++接口。
 */
typedef DDS_PropertyList PropertyList;

/**
 * @typedef DDS_ParticipantBuiltinTopicData ParticipantBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ParticipantBuiltinTopicData 结构为C++接口。
 */
typedef DDS_ParticipantBuiltinTopicData ParticipantBuiltinTopicData;

/**
 * @typedef DDS_PublicationBuiltinTopicData PublicationBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationBuiltinTopicData 结构为C++接口。
 */
typedef DDS_PublicationBuiltinTopicData PublicationBuiltinTopicData;

/**
 * @typedef DDS_SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SubscriptionBuiltinTopicData 结构为C++接口。
 */
typedef DDS_SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData;

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA
/**
 * @typedef DDS_TopicBuiltinTopicData TopicBuiltinTopicData 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_TopicBuiltinTopicData 结构为C++接口。
 */
typedef DDS_TopicBuiltinTopicData TopicBuiltinTopicData;

#endif //_ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

#if defined(_ZRDDSSECURITY)
/**
 * @typedef DDS_ParticipantBuiltinTopicDataSecure ParticipantBuiltinTopicDataSecure 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ParticipantBuiltinTopicDataSecure 结构为C++接口。
 */
typedef DDS_ParticipantBuiltinTopicDataSecure ParticipantBuiltinTopicDataSecure;

/**
 * @typedef DDS_PublicationBuiltinTopicDataSecure PublicationBuiltinTopicDataSecure 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_PublicationBuiltinTopicDataSecure 结构为C++接口。
 */
typedef DDS_PublicationBuiltinTopicDataSecure PublicationBuiltinTopicDataSecure;

/**
 * @typedef DDS_SubscriptionBuiltinTopicDataSecure SubscriptionBuiltinTopicDataSecure 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SubscriptionBuiltinTopicDataSecure 结构为C++接口。
 */
typedef DDS_SubscriptionBuiltinTopicDataSecure SubscriptionBuiltinTopicDataSecure;

#endif

/**
 * @typedef DDS_InstanceStateKind InstanceStateKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_InstanceStateKind 结构为C++接口。
 */
typedef DDS_InstanceStateKind InstanceStateKind;

/**
 * @typedef DDS_InstanceStateMask InstanceStateMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_InstanceStateMask 结构为C++接口。
 */
typedef DDS_InstanceStateMask InstanceStateMask;

/**
 * @brief   此掩码表示任意的实例状态 InstanceStateKind 。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_ANY_INSTANCE_STATE 。
 */
DCPSDLL extern const InstanceStateMask ANY_INSTANCE_STATE;
/**
 * @brief   此掩码表示非存活的实例状态 InstanceStateKind 。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_NOT_ALIVE_INSTANCE_STATE 。
 */
DCPSDLL extern const InstanceStateMask NOT_ALIVE_INSTANCE_STATE;
/**
 * @brief   此状态表示样本所属数据实例处于存活状态。
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_ALIVE_INSTANCE_STATE 。
 */
DCPSDLL extern const InstanceStateMask ALIVE_INSTANCE_STATE;
/**
 * @brief  此状态表示样本所属数据实例处于被销毁状态。  
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE 。
 */
DCPSDLL extern const InstanceStateMask NOT_ALIVE_DISPOSED_INSTANCE_STATE;
/**
 * @brief  此状态表示样本所属数据实例处于被注销状态。  
 *
 * @ingroup CppConstant
 *
 * @details 参见核心常量 #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE 。
 */
DCPSDLL extern const InstanceStateMask NOT_ALIVE_NO_WRITERS_INSTANCE_STATE;

/**
 * @typedef DDS_SampleInfo SampleInfo 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleInfo 结构为C++接口。
 */
typedef DDS_SampleInfo SampleInfo;

/**
 * @typedef DDS_SampleInfoValidMember SampleInfoValidMember 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleInfoValidMember 结构为C++接口。
 */
typedef DDS_SampleInfoValidMember SampleInfoValidMember;

/**
 * @typedef DDS_SampleInfoSeq SampleInfoSeq 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleInfoSeq 结构为C++接口。
 */
typedef DDS_SampleInfoSeq SampleInfoSeq;

/**
 * @typedef DDS_StatusKind StatusKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_StatusKind 结构为C++接口。
 */
typedef DDS_StatusKind StatusKind;

/** @brief QoS不匹配状态。 @ingroup CppConstant */
DCPSDLL extern const StatusKind INCONSISTENT_TOPIC_STATUS;
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
/** @brief 数据写者截止时间未满足状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind OFFERED_DEADLINE_MISSED_STATUS;
/** @brief 数据读者截止时间未满足状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind REQUESTED_DEADLINE_MISSED_STATUS;
#endif /* _ZRDDS_INCLUDE_DEADLINE_QOS */
/** @brief 数据写者端QoS不匹配状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind OFFERED_INCOMPATIBLE_QOS_STATUS;
/** @brief 数据读者端QoS不匹配状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind REQUESTED_INCOMPATIBLE_QOS_STATUS;
/** @brief 数据样本丢失状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind SAMPLE_LOST_STATUS;
/** @brief 数据样本拒绝状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind SAMPLE_REJECTED_STATUS;
/** @brief 订阅者数据到达状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind DATA_ON_READERS_STATUS;
/** @brief 数据读者数据到达状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind DATA_AVAILABLE_STATUS;
/** @brief 数据写者存活性状态丢失状态。 @ingroup CppConstant */
DCPSDLL extern const StatusKind LIVELINESS_LOST_STATUS;
/** @brief 数据写者存活性改变状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind LIVELINESS_CHANGED_STATUS;
/** @brief 数据写者匹配状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind PUBLICATION_MATCHED_STATUS;
/** @brief 数据读者匹配状态类型。 @ingroup CppConstant */
DCPSDLL extern const StatusKind SUBSCRIPTION_MATCHED_STATUS;

/**
 * @typedef DDS_StatusKindMask StatusKindMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_StatusKindMask 结构为C++接口。
 */
typedef DDS_StatusKindMask StatusKindMask;

/**
 * @ingroup  CppConstant
 *
 * @brief   此掩码表明所有类型的 #StatusKind 的集合。
 */
DCPSDLL extern const StatusKindMask STATUS_MASK_ALL;
/**
 * @ingroup  CppConstant
 *
 * @brief   此掩码表明空的 #StatusKind 的集合。
 */
DCPSDLL extern const StatusKindMask STATUS_MASK_NONE;

/**
 * @typedef DDS_SampleStateKind SampleStateKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleStateKind 结构为C++接口。
 */
typedef DDS_SampleStateKind SampleStateKind;

/**
 * @typedef DDS_SampleStateMask SampleStateMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_SampleStateMask 结构为C++接口。
 */
typedef DDS_SampleStateMask SampleStateMask;

/**
 * @ingroup  CppConstant
 *
 * @brief   此掩码表示任意的样本状态。
 */
DCPSDLL extern const SampleStateMask ANY_SAMPLE_STATE;
/**
 * @brief  该数据样本已经被用户访问过。
 *
 * @ingroup CppConstant
 *
 * @details 表示用户曾通过 DataReader::read 系列方法访问过此样本并且已经通过 DataReader::return_loan 方法归还。
 */
DCPSDLL extern const SampleStateMask READ_SAMPLE_STATE;
/**
 * @brief  该数据样本已经被用户访问过。
 *
 * @ingroup CppConstant
 *
 * @details 表示用户未曾通过 DataReader::read 系列方法访问过此样本或者还未通过 DataReader::return_loan 方法归还空间。
 */
DCPSDLL extern const SampleStateMask NOT_READ_SAMPLE_STATE;

/**
 * @typedef DDS_ViewStateKind ViewStateKind 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ViewStateKind 结构为C++接口。
 */
typedef DDS_ViewStateKind ViewStateKind;

/**
 * @typedef DDS_ViewStateMask ViewStateMask 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_ViewStateMask 结构为C++接口。
 */
typedef DDS_ViewStateMask ViewStateMask;

/**
 * @ingroup CppConstant
 *
 * @brief   此掩码表明所有类型的 #ViewStateKind 的集合。
 */
DCPSDLL extern const ViewStateMask ANY_VIEW_STATE;
/**
 * @brief   此状态表示数据读者尚未访问过此数据实例下的数据样本或这个数据实例发生了再现（从NOT_ALIVE状态重新变为ALIVE状态）。
 *
 * @ingroup CppConstant
 */
DCPSDLL extern const ViewStateMask NEW_VIEW_STATE;
/**
 * @brief   此状态表示数据读者访问过此实例的数据（且此实例未发生再现）。 
 *
 * @ingroup CppConstant
 */
DCPSDLL extern const ViewStateMask NOT_NEW_VIEW_STATE;

#ifdef _ZRDDS_INCLUDE_QUALITY_EVALUATION

/**
 * @typedef DDS_LinkQualityEvaluationInfo LinkQualityEvaluationInfo 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_LinkQualityEvaluationInfo 结构为C++接口。
 */
typedef DDS_LinkQualityEvaluationInfo LinkQualityEvaluationInfo;


/**
 * @typedef DDS_QualityEvaluationQosPolicy QualityEvaluationQosPolicy 
 *
 * @ingroup CppCoreStruct
 *
 * @brief 映射核心数据 #DDS_QualityEvaluationQosPolicy 结构为C++接口。
 */
typedef DDS_QualityEvaluationQosPolicy QualityEvaluationQosPolicy;

#endif // _ZRDDS_INCLUDE_QUALITY_EVALUATION

/**
 * 以下类型为兼容601测试使用。
 */
#ifdef _ZRDDS_INCLUDE_601_TYPE

/**
 * @typedef DDS_UINT8 UINT8
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT8 结构为C++接口。
 */

typedef DDS_UINT8 UINT8;

/**
 * @typedef DDS_INT8 INT8
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT8 结构为C++接口。
 */

typedef DDS_INT8 INT8;

/**
 * @typedef DDS_BOOLEAN BOOLEAN
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_BOOLEAN 结构为C++接口。
 */

typedef DDS_BOOLEAN BOOLEAN;

/**
 * @typedef DDS_INT16 INT16
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT16 结构为C++接口。
 */

typedef DDS_INT16 INT16;

/**
 * @typedef DDS_UINT16 UINT16
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT16 结构为C++接口。
 */

typedef DDS_UINT16 UINT16;

/**
 * @typedef DDS_INT32 INT32
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT32 结构为C++接口。
 */

typedef DDS_INT32 INT32;

/**
 * @typedef DDS_UINT32 UINT32
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT32 结构为C++接口。
 */

typedef DDS_UINT32 UINT32;

/**
 * @typedef DDS_FLOAT32 FLOAT32
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_FLOAT32 结构为C++接口。
 */

typedef DDS_FLOAT32 FLOAT32;

/**
 * @typedef DDS_INT64 INT64
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT64 结构为C++接口。
 */

typedef DDS_INT64 INT64;

/**
 * @typedef DDS_UINT64 UINT64
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT64 结构为C++接口。
 */

typedef DDS_UINT64 UINT64;

/**
 * @typedef DDS_DOUBLE64 DOUBLE64
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_DOUBLE64 结构为C++接口。
 */

typedef DDS_DOUBLE64 DOUBLE64;

/**
 * @typedef DDS_UINT8Seq UINT8Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT8Seq 结构为C++接口。
 */

typedef DDS_UINT8Seq UINT8Seq;

/**
 * @typedef DDS_INT8Seq INT8Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT8Seq 结构为C++接口。
 */

typedef DDS_INT8Seq INT8Seq;

/**
 * @typedef DDS_BOOLEANSeq BOOLEANSeq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_BOOLEANSeq 结构为C++接口。
 */

typedef DDS_BOOLEANSeq BOOLEANSeq;

/**
 * @typedef DDS_INT16Seq INT16Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT16Seq 结构为C++接口。
 */

typedef DDS_INT16Seq INT16Seq;

/**
 * @typedef DDS_UINT16Seq UINT16Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT16Seq 结构为C++接口。
 */

typedef DDS_UINT16Seq UINT16Seq;

/**
 * @typedef DDS_INT32Seq INT32Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT32Seq 结构为C++接口。
 */

typedef DDS_INT32Seq INT32Seq;

/**
 * @typedef DDS_UINT32Seq UINT32Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT32Seq 结构为C++接口。
 */

typedef DDS_UINT32Seq UINT32Seq;

/**
 * @typedef DDS_FLOAT32Seq FLOAT32Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_FLOAT32Seq 结构为C++接口。
 */

typedef DDS_FLOAT32Seq FLOAT32Seq;

/**
 * @typedef DDS_INT64Seq INT64Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_INT64Seq 结构为C++接口。
 */

typedef DDS_INT64Seq INT64Seq;

/**
 * @typedef DDS_UINT64Seq UINT64Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_UINT64Seq 结构为C++接口。
 */

typedef DDS_UINT64Seq UINT64Seq;

/**
 * @typedef DDS_DOUBLE64Seq DOUBLE64Seq
 *
 * @ingroup  CppCoreStruct
 *
 * @brief   映射核心数据 #DDS_DOUBLE64Seq 结构为C++接口。
 */

typedef DDS_DOUBLE64Seq DOUBLE64Seq;

#define DDS_BEST_EFFORT DDS_BEST_EFFORT_RELIABILITY_QOS
#define DDS_RELIABLE DDS_RELIABLE_RELIABILITY_QOS
#define DDS_BY_RECEPTION_TIMESTAMP DDS_BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS
#define DDS_BY_SOURCE_TIMESTAMP DDS_BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
#define DDS_TRANSIENT_LOCAL DDS_TRANSIENT_LOCAL_DURABILITY_QOS
#define DDS_VOLATILE DDS_VOLATILE_DURABILITY_QOS
#define DDS_KEEP_LAST DDS_KEEP_LAST_HISTORY_QOS
#define DDS_KEEP_ALL DDS_KEEP_ALL_HISTORY_QOS
#define DDS_SHARED DDS_SHARED_OWNERSHIP_QOS
#define DDS_EXCLUSIVE DDS_EXCLUSIVE_OWNERSHIP_QOS
#define DDS_RETCODE_INCONSISTENT_POLICY DDS_RETCODE_INCONSISTENT

#define DDS_DEFAULT_PARTICIPANT_QOS DDS_DOMAINPARTICIPANT_QOS_DEFAULT
#define DDS_DEFAULT_TOPIC_QOS DDS_TOPIC_QOS_DEFAULT
#define DDS_DEFAULT_PUBLISHER_QOS DDS_PUBLISHER_QOS_DEFAULT
#define DDS_DEFAULT_SUBSCRIBER_QOS DDS_SUBSCRIBER_QOS_DEFAULT
#define DDS_DEFAULT_DATAWRITER_QOS DDS_DATAWRITER_QOS_DEFAULT
#define DDS_DEFAULT_DATAREADER_QOS DDS_DATAREADER_QOS_DEFAULT

#define DDS_INCONSISTENT_TOPIC DDS_INCONSISTENT_TOPIC_STATUS
#define DDS_DATA_ON_READERS DDS_DATA_ON_READERS_STATUS
#define DDS_DATA_AVAILABLE DDS_DATA_AVAILABLE_STATUS
#define DDS_SAMPLE_REJECTED DDS_SAMPLE_REJECTED_STATUS
#define DDS_SAMPLE_LOST DDS_SAMPLE_LOST_STATUS
#define DDS_LIVELINESS_CHANGED DDS_LIVELINESS_CHANGED_STATUS
#define DDS_LIVELINESS_LOST DDS_LIVELINESS_LOST_STATUS
#define DDS_REQUESTED_DEADLINE_MISSED DDS_REQUESTED_DEADLINE_MISSED_STATUS 
#define DDS_REQUESTED_INCOMPATIBLE_QOS DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS
#define DDS_PUBLICATION_MATCHED DDS_PUBLICATION_MATCHED_STATUS
#define DDS_SUBSCRIPTION_MATCHED DDS_SUBSCRIPTION_MATCHED_STATUS
#define DDS_OFFERED_DEADLINE_MISSED DDS_OFFERED_DEADLINE_MISSED_STATUS
#define DDS_OFFERED_INCOMPATIBLE_QOS DDS_OFFERED_INCOMPATIBLE_QOS_STATUS

#define BEST_EFFORT BEST_EFFORT_RELIABILITY_QOS
#define RELIABLE RELIABLE_RELIABILITY_QOS
#define BY_RECEPTION_TIMESTAMP BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS
#define BY_SOURCE_TIMESTAMP BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
#define TRANSIENT_LOCAL TRANSIENT_LOCAL_DURABILITY_QOS
#define VOLATILE VOLATILE_DURABILITY_QOS
#define KEEP_LAST KEEP_LAST_HISTORY_QOS
#define KEEP_ALL KEEP_ALL_HISTORY_QOS
#define SHARED SHARED_OWNERSHIP_QOS
#define EXCLUSIVE EXCLUSIVE_OWNERSHIP_QOS
#define RETCODE_INCONSISTENT_POLICY RETCODE_INCONSISTENT

#define DEFAULT_PARTICIPANT_QOS DOMAINPARTICIPANT_QOS_DEFAULT
#define DEFAULT_TOPIC_QOS TOPIC_QOS_DEFAULT
#define DEFAULT_PUBLISHER_QOS PUBLISHER_QOS_DEFAULT
#define DEFAULT_SUBSCRIBER_QOS SUBSCRIBER_QOS_DEFAULT
#define DEFAULT_DATAWRITER_QOS DATAWRITER_QOS_DEFAULT
#define DEFAULT_DATAREADER_QOS DATAREADER_QOS_DEFAULT

#define INCONSISTENT_TOPIC INCONSISTENT_TOPIC_STATUS
#define DATA_ON_READERS DATA_ON_READERS_STATUS
#define DATA_AVAILABLE DATA_AVAILABLE_STATUS
#define SAMPLE_REJECTED SAMPLE_REJECTED_STATUS
#define SAMPLE_LOST SAMPLE_LOST_STATUS
#define LIVELINESS_CHANGED LIVELINESS_CHANGED_STATUS
#define LIVELINESS_LOST LIVELINESS_LOST_STATUS
#define REQUESTED_DEADLINE_MISSED REQUESTED_DEADLINE_MISSED_STATUS 
#define REQUESTED_INCOMPATIBLE_QOS REQUESTED_INCOMPATIBLE_QOS_STATUS
#define PUBLICATION_MATCHED PUBLICATION_MATCHED_STATUS
#define SUBSCRIPTION_MATCHED SUBSCRIPTION_MATCHED_STATUS
#define OFFERED_DEADLINE_MISSED OFFERED_DEADLINE_MISSED_STATUS
#define OFFERED_INCOMPATIBLE_QOS OFFERED_INCOMPATIBLE_QOS_STATUS

#endif //_ZRDDS_INCLUDE_601_TYPE
}

#endif // ZRDDSCppWrapper_h__
