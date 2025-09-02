/**
 * @file:       ZRDynamicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDynamicData_h__
#define ZRDynamicData_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "ReturnCode_t.h"
#include "ZRBuiltinTypes.h"
#include "TypeCodeKind.h"
#include "CDRStream.h"
#include "TypeCodeKind.h"

#ifdef _ZRDDS_INCLUDE_DYNAMIC_DATA

#ifdef __cplusplus
extern "C"
{
#endif

#define DYNAMIC_DATA_PROPERTY_INITIALIZER { 0, 256, 16 }

#define DYNAMIC_DATA_MEMBER_INITIALIZER { DDS_TK_NULL, false, -1, 0, NULL, { 0 }, NULL }

#define DYNAMIC_DATA_BUFFER_INITIALIZER { NULL, 0, 0, true, DYNAMIC_DATA_PROPERTY_INITIALIZER}

#define DYNAMIC_DATA_MEMBER_ID_UNSPECIFIED -1

#define DYNAMIC_DATA_BUFFER_MEMBER_FIXED_PART_SIZE 64
#define DYNAMIC_DATA_BUFFER_MEMBER_MAX_STRING_LENGTH 256
#define DYNAMIC_DATA_BUFFER_MEMBER_SIZE sizeof(DDS_Long)*  2 + DYNAMIC_DATA_BUFFER_MEMBER_FIXED_PART_SIZE + 4 

typedef struct ZRDynamicDataProperty_t
{
    /** @brief   初始化的成员个数。*/
    DDS_Long _initialMemberCount;
    /** @brief   最大的成员个数。*/
    DDS_Long _maxMemberCount;
    /** @brief   每次成员个数的增量。*/
    DDS_Long _incrementCount;
}ZRDynamicDataProperty_t;

extern const ZRDynamicDataProperty_t DEFAULT_DYNAMIC_DATA_PROPERTY;

typedef struct ZRDynamicDataMemberInfo
{
    /** @brief   成员Id。*/
    DDS_Long _memberId;
    /** @brief   成员名称。*/
    const DDS_Char* _memberName;
    /** @brief   成员类型。*/
    TCTypeKind _memberKind;
    /** @brief   元素个数。*/
    DDS_ULong _elementCount;
    /** @brief   元素类型。*/
    TCTypeKind _elementKind;
}ZRDynamicDataMemberInfo;

typedef struct ZRDynamicDataMember
{
    /** @brief   成员类型。*/
    TCTypeKind _memberType;
    /** @brief   是否属于键域。*/
    DDS_Boolean _isKey;
    /** @brief   存储内容的长度。*/
    DDS_Long _memberSize;
    /** @brief   变长空间长度。*/
    DDS_Long _variablePartSize;
    /** @brief   复杂数据关联的DynamicData。*/
    struct ZRDynamicData* _relatedData;
    /** @brief   缓冲区。*/
    DDS_Char _fixedPart[DYNAMIC_DATA_BUFFER_MEMBER_FIXED_PART_SIZE];
    /** @brief   缓冲区空间不足时，额外申请空间。*/
    DDS_Char* _variablePart;
}ZRDynamicDataMember;

typedef struct ZRDynamicDataBuffer
{
    /** @brief   成员内容。*/
    ZRDynamicDataMember* _membersBuffer;
    /** @brief   已使用的成员个数。*/
    DDS_Long _usedCount;
    /** @brief   已申请成员的个数。*/
    DDS_Long _ownedCount;
    /** @brief   是否拥有此空间。*/
    DDS_Boolean _ownedBuffer;
    /** @brief   DynamicData存储属性。*/
    ZRDynamicDataProperty_t _properties;
}ZRDynamicDataBuffer;

typedef struct ZRDynamicData
{
    /** @brief   数据类型。*/
    const TypeCodeHeader* _type;
    /** @brief 是否已经初始化*/
    DDS_Boolean _init;
    /** @brief   是否拥有此类型。*/
    DDS_Boolean _ownedType;
    /** @brief   是否绑定复杂的类型。*/
    DDS_Boolean _boundMember;
    /** @brief   此类型的在父结构中的索引。*/
    DDS_Long _boundIndex;
    /** @brief   父结构的指针。*/
    struct ZRDynamicData* _parent;
    /** @brief   DynamicData数据。*/
    ZRDynamicDataBuffer _buffer;
}ZRDynamicData;

DCPSDLL DDS_Boolean ZRDynamicDataInitialize(
    ZRDynamicData* self,
    const TypeCodeHeader* type,
    const ZRDynamicDataProperty_t* property);

DCPSDLL DDS_Boolean ZRDynamicDataIsValid(const ZRDynamicData* self);

DCPSDLL ZRDynamicData* ZRDynamicDataNew(
    const TypeCodeHeader* type,
    const ZRDynamicDataProperty_t* property);

DCPSDLL void ZRDynamicDataFinalize(ZRDynamicData* self);

DCPSDLL void ZRDynamicDataDelete(ZRDynamicData* self);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataCopy(
    ZRDynamicData* self,
    const ZRDynamicData* src);

DCPSDLL DDS_Boolean ZRDynamicDataEqual(
    const ZRDynamicData* self,
    const ZRDynamicData* other);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataClearAllMembers(ZRDynamicData* self);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataClearMember(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataEnsureBufferSize(
    ZRDynamicData* self,
    DDS_Long requiredSize);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataPrint(
    const ZRDynamicData* self,
    DDS_ULong maxLength);

DCPSDLL DDS_Char* ZRDynamicDataGetPrintableString(const ZRDynamicData* self);

DCPSDLL void ZRDynamicDataReleasePrintableString(DDS_Char* buffer);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSerialize(
    const ZRDynamicData* self,
    CDRSerializer* cdr);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataDeserialize(
    ZRDynamicData* self,
    CDRDeserializer* cdr);

DCPSDLL DDS_Long ZRDynamicDataGetMaxSerializeSize(
    const TypeCodeHeader* tc,
    DDS_Long offset);

DCPSDLL DDS_Long ZRDynamicDataGetSerializeSize(
    const ZRDynamicData* self,
    DDS_Long offset);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSerializeKey(
    const ZRDynamicData* self,
    CDRSerializer* cdr);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataDeserializeKey(
    ZRDynamicData* self,
    CDRDeserializer* cdr);

DCPSDLL DDS_Long ZRDynamicDataGetMaxSerializeKeySize(
    const TypeCodeHeader* tc,
    DDS_Long offset);

DCPSDLL DDS_Long ZRDynamicDataGetSerializeKeySize(
    const ZRDynamicData* self,
    DDS_Long offset);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataBindType(
    ZRDynamicData* self,
    const TypeCodeHeader* type);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataUnbindType(ZRDynamicData* self);

DCPSDLL ZRDynamicData* ZRDynamicDataBindComplexMember(
    const ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long memberID);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataUnbindComplexMember(ZRDynamicData* self);

DCPSDLL const TypeCodeHeader* ZRDynamicDataGetType(const ZRDynamicData* self);

DCPSDLL TCTypeKind ZRDynamicDataGetTypeKind(const ZRDynamicData* self);

DCPSDLL DDS_ULong ZRDynamicDataGetMemberCount(const ZRDynamicData* self);

DCPSDLL DDS_Boolean ZRDynamicDataMemberExists(
    const ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_Boolean ZRDynamicDataMemberExistsInType(
    const ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetMemberInfo(
    const ZRDynamicData* self,
    ZRDynamicDataMemberInfo* info,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetMemberInfoByIndex(
    const ZRDynamicData* self,
    ZRDynamicDataMemberInfo* info,
    DDS_ULong index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetMemberType(
    const ZRDynamicData* self,
    const TypeCodeHeader** type,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataIsMemberKey(
    const ZRDynamicData* self,
    DDS_Boolean* isKey,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetParentData(
    const ZRDynamicData* self,
    ZRDynamicData** parentData);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetParentDataConst(
    const ZRDynamicData* self,
    const ZRDynamicData** parentData);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt8(
    const ZRDynamicData* self,
    DDS_Char* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt8(
    const ZRDynamicData* self,
    DDS_Octet* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt16(
    const ZRDynamicData* self,
    DDS_Short* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt16(
    const ZRDynamicData* self,
    DDS_UShort* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt32(
    const ZRDynamicData* self,
    DDS_Long* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt32(
    const ZRDynamicData* self,
    DDS_ULong* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetEnum(
    const ZRDynamicData* self,
    DDS_ULong* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetEnumString(
    const ZRDynamicData* self,
    const DDS_Char** enumStr,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetFloat32(
    const ZRDynamicData* self,
    DDS_Float* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetDouble64(
    const ZRDynamicData* self,
    DDS_Double* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetBoolean(
    const ZRDynamicData* self,
    DDS_Boolean* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt64(
    const ZRDynamicData* self,
    DDS_LongLong* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt64(
    const ZRDynamicData* self,
    DDS_ULongLong* value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetString(
    const ZRDynamicData* self,
    DDS_Char** value,
    DDS_ULong* size,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetStringConst(
    const ZRDynamicData* self,
    const DDS_Char** value,
    DDS_ULong* size,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetComplexMember(
    const ZRDynamicData* self,
    ZRDynamicData** value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetComplexMemberConst(
    const ZRDynamicData* self,
    const ZRDynamicData** value,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetPrimitiveTypeArray(
    const ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong elementSize,
    DDS_ULong offset,
    const DDS_Char** dataAddr,
    DDS_ULong* elementNum);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt8Array(
    const ZRDynamicData* self,
    DDS_Char* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt8ArrayConst(
    const ZRDynamicData* self,
    const DDS_Char** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt8Array(
    const ZRDynamicData* self,
    DDS_Octet* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt8ArrayConst(
    const ZRDynamicData* self,
    const DDS_Octet** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt16Array(
    const ZRDynamicData* self,
    DDS_Short* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt16ArrayConst(
    const ZRDynamicData* self,
    const DDS_Short** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt16Array(
    const ZRDynamicData* self,
    DDS_UShort* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt16ArrayConst(
    const ZRDynamicData* self,
    const DDS_UShort** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt32Array(
    const ZRDynamicData* self,
    DDS_Long* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt32ArrayConst(
    const ZRDynamicData* self,
    const DDS_Long** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt32Array(
    const ZRDynamicData* self,
    DDS_ULong* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt32ArrayConst(
    const ZRDynamicData* self,
    const DDS_ULong** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt64Array(
    const ZRDynamicData* self,
    DDS_LongLong* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt64ArrayConst(
    const ZRDynamicData* self,
    const DDS_LongLong** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt64Array(
    const ZRDynamicData* self,
    DDS_ULongLong* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt64ArrayConst(
    const ZRDynamicData* self,
    const DDS_ULongLong** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetFloat32Array(
    const ZRDynamicData* self,
    DDS_Float* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetFloat32ArrayConst(
    const ZRDynamicData* self,
    const DDS_Float** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetDouble64Array(
    const ZRDynamicData* self,
    DDS_Double* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetDouble64ArrayConst(
    const ZRDynamicData* self,
    const DDS_Double** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetBooleanArray(
    const ZRDynamicData* self,
    DDS_Boolean* array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetBooleanArrayConst(
    const ZRDynamicData* self,
    const DDS_Boolean** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetStringArray(
    const ZRDynamicData* self,
    DDS_Char** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetComplexMemberArray(
    const ZRDynamicData* self,
    ZRDynamicData** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetComplexMemberArrayConst(
    const ZRDynamicData* self,
    const ZRDynamicData** array,
    DDS_ULong* length,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt8Seq(
    const ZRDynamicData* self,
    DDS_CharSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt8Seq(
    const ZRDynamicData* self,
    DDS_OctetSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt16Seq(
    const ZRDynamicData* self,
    DDS_ShortSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt16Seq(
    const ZRDynamicData* self,
    DDS_UShortSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt32Seq(
    const ZRDynamicData* self,
    DDS_LongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt32Seq(
    const ZRDynamicData* self,
    DDS_ULongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt64Seq(
    const ZRDynamicData* self,
    DDS_LongLongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt64Seq(
    const ZRDynamicData* self,
    DDS_ULongLongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetFloat32Seq(
    const ZRDynamicData* self,
    DDS_FloatSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetDouble64Seq(
    const ZRDynamicData* self,
    DDS_DoubleSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetBooleanSeq(
    const ZRDynamicData* self,
    DDS_BooleanSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetStringSeq(
    const ZRDynamicData* self,
    DDS_StringSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt8SeqConst(
    const ZRDynamicData* self,
    DDS_CharSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt8SeqConst(
    const ZRDynamicData* self,
    DDS_OctetSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt16SeqConst(
    const ZRDynamicData* self,
    DDS_ShortSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt16SeqConst(
    const ZRDynamicData* self,
    DDS_UShortSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt32SeqConst(
    const ZRDynamicData* self,
    DDS_LongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt32SeqConst(
    const ZRDynamicData* self,
    DDS_ULongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetInt64SeqConst(
    const ZRDynamicData* self,
    DDS_LongLongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetUInt64SeqConst(
    const ZRDynamicData* self,
    DDS_ULongLongSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetFloat32SeqConst(
    const ZRDynamicData* self,
    DDS_FloatSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetDouble64SeqConst(
    const ZRDynamicData* self,
    DDS_DoubleSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataGetBooleanSeqConst(
    const ZRDynamicData* self,
    DDS_BooleanSeq* seq,
    const DDS_Char* memberName,
    DDS_Long index);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt8(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Char value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt8(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Octet value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt16(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Short value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt16(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_UShort value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt32(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Long value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt32(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt64(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_LongLong value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt64(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULongLong value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetFloat32(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Float value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetDouble64(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Double value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetBoolean(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_Boolean value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetString(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_Char* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetComplexMember(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const ZRDynamicData* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt8Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Char* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt8Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Octet* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt16Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Short* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt16Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_UShort* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt32Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Long* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt32Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_ULong* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt64Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_LongLong* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt64Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_ULongLong* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetFloat32Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Float* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetDouble64Array(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Double* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetBooleanArray(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Boolean* array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetStringArray(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const DDS_Char** array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetComplexMemberArray(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const ZRDynamicData** array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetComplexMemberSequence(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    DDS_ULong length,
    const ZRDynamicData** array);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt8Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_CharSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt8Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_OctetSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt16Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_ShortSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt16Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_UShortSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt32Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_LongSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt32Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_ULongSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetInt64Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_LongLongSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetUInt64Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_ULongLongSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetFloat32Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_FloatSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetDouble64Seq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_DoubleSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetBooleanSeq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_BooleanSeq* value);

DCPSDLL DDS_ReturnCode_t ZRDynamicDataSetStringSeq(
    ZRDynamicData* self,
    const DDS_Char* memberName,
    DDS_Long index,
    const DDS_StringSeq* value);

ZR_INT32 ZRDynamicDataGetSerializeSizeEx(
    const ZRDynamicData* self,
    ZR_INT32 offset,
    ZR_BOOLEAN fixLen);

DDS_ReturnCode_t ZRDynamicDataDeserializeEx(
    ZRDynamicData* self,
    CDRDeserializer* cdr,
    ZR_INT32 elementCount,
    ZR_UINT32 offset,
    ZR_UINT32 totalSize,
    ZR_INT8* payload,
    ZR_UINT32 payloadLen,
    ZR_UINT32 fixedHeaderLen);

DDS_SEQUENCE_CPP(ZRDynamicDataSeq, ZRDynamicData);


DDS_ReturnCode_t ZRDynamicDataGetPrintRow(
    const ZRDynamicData* self,
    DDS_Char **typeBuffer,
    DDS_Char **dataBuffer);

void ZRDynamicDataReleasePrintRow(
    DDS_Char *typeBuffer,
    DDS_Char *dataBuffer);

#ifdef __cplusplus
}
#endif

#endif /* _ZRDDS_INCLUDE_DYNAMIC_DATA */

#endif /* ZRDynamicData_h__*/
