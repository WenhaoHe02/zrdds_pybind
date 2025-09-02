/**
 * @file:       CDRStream.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef CDRStream_h__
#define CDRStream_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

typedef struct MessageBlock MessageBlock;
typedef struct CDRSerializer CDRSerializer;
typedef struct CDRDeserializer CDRDeserializer;

#define PID_LIST_END 0x3f02

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus*/

/**
 * @fn  DCPSDLL CDRSerializer* CDRSerializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   用户提供原始缓存创建一个序列化器，使用该接口必须调用 ::CDRSerializerDestoryBuffer 回收资源。
 *
 * @param [in,out]  buffer  用户提供的空间。
 * @param   length          用户提供的空间长度。
 * @param   littleEndian    是否使用小端序列化，true表示小端，false表示大端。
 *
 * @return  NULL表示创建失败，否则指向新创建的序列化器。
 */

DCPSDLL CDRSerializer* CDRSerializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);

/**
 * @fn  DCPSDLL CDRDeserializer* CDRDeserializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   用户提供原始缓存创建一个反序列化器，使用该接口必须调用 ::CDRDeserializerDestoryBuffer 回收资源。
 *
 * @param [in,out]  buffer  用户提供的空间。
 * @param   length          用户提供的空间长度。
 * @param   littleEndian    是否使用小端序列化，true表示小端，false表示大端。
 *
 * @return  NULL表示失败，否则返回新创建的反序列化器。
 */

DCPSDLL CDRDeserializer* CDRDeserializerInitialWBuf(ZR_INT8* buffer, ZR_UINT32 length, ZR_BOOLEAN littleEndian);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetBufferSpace(CDRSerializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   获取指定序列化器还剩下的缓冲区大小。
 *
 * @param [in,out]  self    指明目标。
 *
 * @return  关联缓冲区的剩余空间大小。
 */

DCPSDLL ZR_UINT32 CDRSerializerGetBufferSpace(CDRSerializer* self);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRDeserializerGetBufferLength(CDRDeserializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   获取反序列化器关联的缓冲区的剩余数据长度。
 *
 * @param [in,out]  self    指明目标。
 *
 * @return  关联的缓冲区剩余数据长度。
 */

DCPSDLL ZR_UINT32 CDRDeserializerGetBufferLength(CDRDeserializer* self);

/**
 * @fn  DCPSDLL void CDRSerializerDestoryBuffer(CDRSerializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   回收由 ::CDRSerializerInitialWBuf 创建的内部空间。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void CDRSerializerDestoryBuffer(CDRSerializer* self);

/**
 * @fn  DCPSDLL void CDRDeserializerDestoryBuffer(CDRDeserializer* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   回收由 ::CDRDeserializerInitialWBuf 内部空间。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void CDRDeserializerDestoryBuffer(CDRDeserializer* self);

/**
 * @fn  void CDRSerializerInitial(CDRSerializer* self, MessageBlock* tgaMsgBlock, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化一个CDR序列化器。
 *
 * @param [in,out]  self        需要初始化的目标。
 * @param [in,out]  tgaMsgBlock 关联的目标缓存。
 * @param   littleEndian        使用的编码方式，true表示小端，false表示大端。
 */

DCPSDLL void CDRSerializerInitial(CDRSerializer* self, MessageBlock* tgaMsgBlock, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN CDRSerializerPutString(CDRSerializer* self, const ZR_INT8* value, const ZR_UINT32 length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   序列化字符串。
 *
 * @param [in,out]  self    目标序列化器。
 * @param   value           序列化目标值。
 * @param   length          序列化目标值长度，需要包括结尾符。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRSerializerPutString(CDRSerializer* self, const ZR_INT8* value, const ZR_UINT32 length);

/**
 * @fn  ZR_BOOLEAN CDRSerializerPutUntype(CDRSerializer* self, const ZR_UINT8* val, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   序列化基本数据类型。
 *
 * @param [in,out]  self    指明目标序列化器。
 * @param   val             需要序列化的值地址。
 * @param   typeSize        需要序列化的值的长度。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRSerializerPutUntype(CDRSerializer* self, const ZR_UINT8* val, ZR_UINT32 typeSize);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetUntypeSize(ZR_UINT32 typeSize, ZR_UINT32 currentAlignment);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   在指定对齐条件下，指定大小的数据类型序列化长度。
 *
 * @param   typeSize            指明类型长度。
 * @param   currentAlignment    当前的对齐偏移量。
 *
 * @return  考虑了对齐的序列化大小。
 */

DCPSDLL ZR_UINT32 CDRSerializerGetUntypeSize(ZR_UINT32 typeSize, ZR_UINT32 currentAlignment);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetUntypeArraySize(ZR_UINT32 typeSize, ZR_UINT32 arraySize, ZR_UINT32 currentAlignment);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   获取类型数组序列化长度的接口。
 *
 * @param   typeSize            指明类型长度。
 * @param   arraySize           指明数组规模。
 * @param   currentAlignment    当前对齐的偏移量。
 *
 * @return  考虑了对齐的序列化大小。
 */

DCPSDLL ZR_UINT32 CDRSerializerGetUntypeArraySize(ZR_UINT32 typeSize, ZR_UINT32 arraySize, ZR_UINT32 currentAlignment);

/**
 * @fn  DCPSDLL ZR_UINT32 CDRSerializerGetStringSize(ZR_UINT32 length, ZR_UINT32 currentAlignment);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   获取序列化string类型所需的长度。
 *
 * @param   length              字符串长度(包括\0)。
 * @param   currentAlignment    当前对齐的偏移量。
 *
 * @return  考虑了对齐的序列化大小。
 */

DCPSDLL ZR_UINT32 CDRSerializerGetStringSize(ZR_UINT32 length, ZR_UINT32 currentAlignment);

/**
 * @fn  ZR_BOOLEAN CDRSerializerPutUntypeArray(CDRSerializer* self, const ZR_UINT8* arrayVal, ZR_UINT32 arraySize, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   序列化基本类型数组。
 *
 * @param [in,out]  self    指明目标序列化器。
 * @param   arrayVal        需要序列化的数组首地址。
 * @param   arraySize       需要序列化的数组规模。
 * @param   typeSize        需要序列化的数组元素的长度。
 *
 * @return  true表示成功，false表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRSerializerPutUntypeArray(CDRSerializer* self, const ZR_UINT8* arrayVal, ZR_UINT32 arraySize, ZR_UINT32 typeSize);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRSerializerNoSerializingMode(CDRSerializer* self);
 *
 * @brief 是否启用无序列化模式，该模式由调用者设置
 *
 * @param [in] self If non-null, the self
 *
 * @return A ZR_BOOLEAN
 */

DCPSDLL ZR_BOOLEAN CDRSerializerNoSerializingMode(CDRSerializer* self);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRSerializerSetNoSerializingMode(CDRSerializer* self, ZR_BOOLEAN noSerializingMode);
 *
 * @brief 设置是否启用无序列化模式，该模式由调用者设置
 *
 * @param [in] self     If non-null, the self
 * @param noSerializingMode The no serializing mode
 *
 * @return A ZR_BOOLEAN
 */

DCPSDLL void CDRSerializerSetNoSerializingMode(CDRSerializer* self, ZR_BOOLEAN noSerializingMode);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRSerializerIsLittleEndian(CDRSerializer* self);
 *
 * @brief 获取当前CDRSerializer设置的端序，TRUE表示小端，FALSE表示大端
 *
 * @param [in] self If non-null, the self
 *
 * @return TRUE表示小端，FALSE表示大端
 */
DCPSDLL ZR_BOOLEAN CDRSerializerIsLittleEndian(CDRSerializer* self);

/**
 * @fn  void CDRDeserializerInitial(CDRDeserializer* self, MessageBlock* srcMsg, ZR_BOOLEAN useLittleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化一个CDR反序列化器。
 *
 * @param [in,out]  self    初始化目标。
 * @param [in,out]  srcMsg  指明反序列化源地址。
 * @param   useLittleEndian 指明解码方式。
 */

DCPSDLL void CDRDeserializerInitial(CDRDeserializer* self, MessageBlock* srcMsg, ZR_BOOLEAN useLittleEndian);

/**
 * @fn  ZR_BOOLEAN CDRDeserializerGetString(CDRDeserializer* self, ZR_INT8* value, ZR_UINT32* length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从缓冲区中获取字符串。
 *
 * @param [in,out]  self    指明反序列化器。
 * @param [in,out]  value   反序列化结果字符串首地址。
 * @param [in,out]  length  反序列化结果字符串长度。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerGetString(CDRDeserializer* self, ZR_INT8* value, ZR_UINT32* length);

/**
 * @fn  ZR_BOOLEAN CDRDeserializerGetUntype(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从缓冲区中获取基本数据类型。
 *
 * @param [in,out]  self    指明目标反序列化器。
 * @param [in,out]  value   反序列化结果存储地址。
 * @param   typeSize        指明反序列化类型长度。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerGetUntype(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32 typeSize);

/**
 * @fn  DCPSDLL ZR_INT8* CDRDeserializerLoanContiguousByte(CDRDeserializer* self, ZR_UINT32 length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从缓冲区中获取字符串，不拷贝。
 *
 * @param [in,out]  self    指明反序列化器。
 * @param   length          反序列化结果字符串长度。
 *
 * @return  NULL表示失败，否则指向头指针。
 */

DCPSDLL ZR_INT8* CDRDeserializerLoanContiguousByte(CDRDeserializer* self, ZR_UINT32 length);

/**
 * @fn  ZR_BOOLEAN CDRDeserializerGetUntypeArray(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32* arraySize, ZR_UINT32 typeSize);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从缓冲区中获取基本数据类型数组。
 *
 * @param [in,out]  self    指明目标反序列化器。
 * @param [in,out]  value   反序列化结果存储地址。
 * @param   arraySize   用户指明反序列化结果数组长度。
 * @param   typeSize        指明反序列化类型长度。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerGetUntypeArray(CDRDeserializer* self, ZR_UINT8* value, ZR_UINT32 arraySize, ZR_UINT32 typeSize);

/**
 * @fn  DCPSDLL ZR_BOOLEAN CDRDeserializerAheadLength(CDRDeserializer* self, ZR_UINT32 beginIndex, ZR_UINT32 length);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   跳过指定个数字符。
 *
 * @param [in,out]  self    指明目标反序列化器。
 * @param   beginIndex      起始位置。
 * @param   length          需要跳过的长度。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_BOOLEAN CDRDeserializerAheadLength(CDRDeserializer* self, ZR_UINT32 beginIndex, ZR_UINT32 length);

/**
 * @fn DCPSDLL ZR_BOOLEAN CDRDeserializerIsLittleEndian(CDRDeserializer* self);
 *
 * @brief 获取当前CDRDeserializer设置的端序，TRUE表示小端，FALSE表示大端
 *
 * @param [in] self If non-null, the self
 *
 * @return TRUE表示小端，FALSE表示大端
 */
DCPSDLL ZR_BOOLEAN CDRDeserializerIsLittleEndian(CDRDeserializer* self);

/**
 * @fn  DCPSDLL ZR_INT8* ParameterHeaderSerialize(CDRSerializer* cdr, ZR_BOOLEAN useExtended, ZR_BOOLEAN mustUnderstand, ZR_UINT32 memberId);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   序列化参数头，用于扩展CDR.
 *
 * @param [in,out]  cdr     指定序列化器。
 * @param   useExtended     是否使用PID_EXTENDED.
 * @param   mustUnderstand  是否必须理解该参数。
 * @param   memberId        参数对应的成员的memberId.
 *
 * @return  NULL表示失败，否则表示回填的长度的地址。
 */

DCPSDLL ZR_INT8* ParameterHeaderSerialize(CDRSerializer* cdr, ZR_BOOLEAN useExtended, ZR_BOOLEAN mustUnderstand, ZR_UINT32 memberId);

/**
 * @fn  void ParameterLenSerialize( CDRSerializer* cdr, ZR_INT8* lenAddr, ZR_UINT32 length, ZR_UINT16 lengthSize, ZR_BOOLEAN littleEndian);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   回填Parameter的长度。
 *
 * @param [in,out]  cdr     指明序列化器。
 * @param [in,out]  lenAddr 参数长度的地址。
 * @param   length          需要填的参数长度。
 * @param   lengthSize      参数长度的字节数。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL void ParameterLenSerialize(
    CDRSerializer* cdr,
    ZR_INT8* lenAddr,
    ZR_UINT32 length,
    ZR_UINT16 lengthSize);

/**
 * @fn  DCPSDLL ZR_INT32 ParameterHeaderDeserialize( CDRDeserializer* cdr, ZR_UINT32* memberId, ZR_UINT32* length, ZR_BOOLEAN* useExtend, ZR_BOOLEAN* mustUnderstand);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   反序列化参数头。
 *
 * @param [in,out]  cdr             指明反序列化器。
 * @param [in,out]  memberId        反序列化出来的memberId。
 * @param [in,out]  length          反序列化出来的length。
 * @param [in,out]  useExtend       反序列化出来是否使用的PID_EXTENDED.
 * @param [in,out]  mustUnderstand  反序列化出来是否必须理解该成员。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 ParameterHeaderDeserialize(
    CDRDeserializer* cdr,
    ZR_UINT32* memberId,
    ZR_UINT32* length,
    ZR_BOOLEAN* useExtend,
    ZR_BOOLEAN* mustUnderstand);

/**
 * @fn  DCPSDLL ZR_INT32 CDRSerializeGetKeyHash(CDRSerializer* cdr, ZR_UINT8* keyHash, ZR_BOOLEAN needMd5);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   获取关联的md5hash值。
 *
 * @param [in,out]  cdr     指明目标。
 * @param [in,out]  keyHash 获取的结果。
 * @param   needMd5         是否需要做MD5。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 CDRSerializeGetKeyHash(CDRSerializer* cdr, ZR_UINT8* keyHash, ZR_BOOLEAN needMd5);

/**
 * @fn  DCPSDLL void CDRDeserializerPushState(CDRDeserializer* cdr);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   保存反序列化器的状态。
 *
 * @param [in,out]  cdr 指明反序列化器。
 */

DCPSDLL void CDRDeserializerPushState(CDRDeserializer* cdr);

/**
 * @fn  DCPSDLL void CDRDeserializerPopState(CDRDeserializer* cdr);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   重新加载反序列化器的状态。
 *
 * @param [in,out]  cdr 指明反序列化器。
 */

DCPSDLL void CDRDeserializerPopState(CDRDeserializer* cdr);

/**
 * @fn  DCPSDLL void CDRSerializerAheadWrPtr(CDRSerializer* self, ZR_UINT32 length);
 *
 * @brief   手动调整CDR序列化器的写指针。
 *
 * @param [in,out]  self    指明目标。
 * @param   length          调整量。
 */

DCPSDLL void CDRSerializerAheadWrPtr(CDRSerializer* self, ZR_UINT32 length);

#ifdef _ZRDDS_INCLUDE_SPARE_TYPE
void* CDRDeserializerGetLastSample(CDRDeserializer* self);

void CDRDeserializerSetLastSample(CDRDeserializer* self, void* lastSample);

void* CDRSerializerGetLastSample(CDRSerializer* self);

void CDRSerializerSetLastSample(CDRSerializer* self, void* lastSample);
#endif //_ZRDDS_INCLUDE_SPARE_TYPE

#ifdef __cplusplus
}
#endif /* __cplusplus*/

#endif /* CDRStream_h__*/
