/**
 * @file:       OsResource.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef OSRESOURCE_H
#define OSRESOURCE_H

#include "ZROSDefine.h"
#ifdef _REWORKS
#include <stdlib.h>
#include <reworks/types.h>
#ifdef __cplusplus
using namespace std;
#endif
#endif /* _REWORKS */

#ifndef __cplusplus
/**
 * @typedef bool ZR_BOOLEAN
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用bool类型。
 */
typedef char ZR_BOOLEAN;
#define false 0
#define true 1
#else

/**
 * @typedef bool ZR_BOOLEAN
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用bool类型。
 */

typedef bool ZR_BOOLEAN;
#endif

/**
 * @typedef char ZR_INT8
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的1个字节整型。
 */

typedef char ZR_INT8;

/**
 * @typedef unsigned char ZR_UINT8
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的1个字节无符号整型。
 */

typedef unsigned char ZR_UINT8;

/**
 * @typedef short ZR_INT16
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的2个字节整型。
 */

typedef short ZR_INT16;

/**
 * @typedef unsigned short ZR_UINT16
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的2个字节无符号整型。
 */

typedef unsigned short ZR_UINT16;

/**
 * @typedef int ZR_INT32
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的4个字节整型。
 */

typedef int ZR_INT32;

/**
 * @typedef unsigned int ZR_UINT32
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的4个字节无符号整型。
 */

typedef unsigned int ZR_UINT32;

/**
 * @typedef long long ZR_INT64
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的8个字节整型。
 */

typedef long long ZR_INT64;

/**
 * @typedef unsigned long long ZR_UINT64
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的8个字节无符号整型。
 */

typedef unsigned long long ZR_UINT64;

/**
 * @typedef float ZR_FLOAT32
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的4个字节单精度浮点型。
 */

typedef float ZR_FLOAT32;

/**
 * @typedef double ZR_DOUBLE64
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   为屏蔽平台差异，定义在接口中使用的8个字节双精度浮点型。
 */

typedef double ZR_DOUBLE64;

/**
 * @def MAX_USHORT_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   2字节无符号整型最大值。
 */

#define MAX_USHORT_VALUE 0xffff

/**
 * @def MAX_SHORT_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   2字节有符号整型最大值。
 */
#define MAX_SHORT_VALUE 0x7fff

/**
 * @def MAX_UINT32_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   4字节无符号整型最大值。
 */
#define MAX_UINT32_VALUE 0xffffffff

/**
 * @def MAX_INT32_VALUE
 *
 * @ingroup CoreMacro
 *
 * @brief   4字节有符号整型最大值。
 */
#define MAX_INT32_VALUE 0x7fffffff

/**
 * @def LENGTH_UNLIMITED
 *
 * @ingroup CoreMacro
 *
 * @brief   表明无限大，在不同的环境中取不同的值。
 */
#define LENGTH_UNLIMITED -1

/**
 * @typedef ZR_BOOLEAN DDS_Boolean
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的true/false类型。
 */

typedef ZR_BOOLEAN DDS_Boolean;


/**
 * @typedef ZR_UINT8 DDS_Octet
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的1字节无符号整型 
 */

typedef unsigned char DDS_Octet;

/**
 * @typedef ZR_INT8 DDS_Char
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的1字节整型。
 */

typedef char DDS_Char;

/**
 * @typedef ZR_INT16 DDS_Short
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的2字节整型。
 */

typedef ZR_INT16 DDS_Short;

/**
 * @typedef ZR_UINT16 DDS_UShort
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的2字节无符号整型。
 */

typedef ZR_UINT16 DDS_UShort;

/**
 * @typedef ZR_INT32 DDS_Long
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的4字节整型。
 */

typedef ZR_INT32 DDS_Long;

/**
 * @typedef ZR_UINT32 DDS_ULong
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的4字节无符号整型。
 */

typedef ZR_UINT32 DDS_ULong;

/**
 * @typedef ZR_INT64 DDS_LongLong
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的8字节长整型。
 */

typedef ZR_INT64 DDS_LongLong;

/**
 * @typedef ZR_UINT64 DDS_ULongLong
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的8字节无符号长整型。
 */

typedef ZR_UINT64 DDS_ULongLong;

/**
 * @typedef ZR_FLOAT32 DDS_Float
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的4字节单精度浮点型。
 */

typedef ZR_FLOAT32 DDS_Float;

/**
 * @typedef ZR_DOUBLE64 DDS_Double
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   ZRDDS内置的8字节双精度浮点型。
 */

typedef ZR_DOUBLE64 DDS_Double;

typedef struct ZRBuffer
{
    void* content;
    ZR_UINT32 length;
}ZRBuffer;

/**
 * 以下类型为兼容601测试使用。
 */
#ifdef _ZRDDS_INCLUDE_601_TYPE

/**
 * @typedef DDS_Octet DDS_UINT8
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Octet 的别名。
 */

typedef DDS_Octet DDS_UINT8;

/**
 * @typedef DDS_Char DDS_INT8
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Char 的别名。
 */

typedef DDS_Char DDS_INT8;

/**
 * @typedef DDS_Boolean DDS_BOOLEAN
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Boolean 的别名。
 */

typedef DDS_Boolean DDS_BOOLEAN;

/**
 * @typedef DDS_Short DDS_INT16
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Short 的别名。
 */

typedef DDS_Short DDS_INT16;

/**
 * @typedef DDS_UShort DDS_UINT16
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_UShort 的别名。
 */

typedef DDS_UShort DDS_UINT16;

/**
 * @typedef DDS_Long DDS_INT32
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Long 的别名。
 */

typedef DDS_Long DDS_INT32;

/**
 * @typedef DDS_ULong DDS_UINT32
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ULong 的别名。
 */

typedef DDS_ULong DDS_UINT32;

/**
 * @typedef DDS_Float DDS_FLOAT32
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Float 的别名。
 */

typedef DDS_Float DDS_FLOAT32;

/**
 * @typedef DDS_LongLong DDS_INT64
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_LongLong 的别名。
 */

typedef DDS_LongLong DDS_INT64;

/**
 * @typedef DDS_ULongLong DDS_UINT64
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_ULongLong 的别名。
 */

typedef DDS_ULongLong DDS_UINT64;

/**
 * @typedef DDS_Double DDS_DOUBLE64
 *
 * @ingroup CoreBuiltinTypes
 *
 * @brief   DDS_Double 的别名。
 */

typedef DDS_Double DDS_DOUBLE64;

#endif //_ZRDDS_INCLUDE_601_TYPE

#endif
