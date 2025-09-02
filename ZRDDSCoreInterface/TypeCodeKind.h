/**
 * @file:       TypeCodeKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeCodeKind_h__
#define TypeCodeKind_h__

#include "OsResource.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TypeCodeHeader TypeCodeHeader;

/**
 * @typedef enum TCTypeKind
 *
 * @brief   四字节枚举类型，其中第一个字节的首位标识端序，1为小端编码，2为大端编码，该类型表示基础数据类型的TypeCode
 */

typedef enum TCTypeKind
{
    /** @brief  无效值 */
    DDS_TK_NULL = 0,
    /** @brief  基本数据类型short */
    DDS_TK_SHORT,
    /** @brief  基本数据类型int */
    DDS_TK_INT,
    /** @brief  基本数据类型ushort */
    DDS_TK_USHORT,
    /** @brief  基本数据类型uint */
    DDS_TK_UINT,
    /** @brief  基本数据类型float */
    DDS_TK_FLOAT,
    /** @brief  基本数据类型double */
    DDS_TK_DOUBLE,
    /** @brief  基本数据类型boolean */
    DDS_TK_BOOLEAN,
    /** @brief  基本数据类型char */
    DDS_TK_CHAR,
    /** @brief  基本数据类型uchar */
    DDS_TK_UCHAR,
    /** @brief  struct类型*/
    DDS_TK_STRUCT,
    /** @brief  union 类型*/
    DDS_TK_UNION,
    /** @brief  enum类型*/
    DDS_TK_ENUM,
    /** @brief  数据类型string */
    DDS_TK_STRING,
    /** @brief  数据类型sequence */
    DDS_TK_SEQUENCE,
    /** @brief  基本数据类型array */
    DDS_TK_ARRAY,
    /** @brief  基本数据类型(不支持) */
    DDS_TK_ALIAS,
    /** @brief  基本数据类型longlong */
    DDS_TK_LONGLONG,
    /** @brief  基本数据类型ulonglong */
    DDS_TK_ULONGLONG,
    /** @brief  继承的struct类型 */
    DDS_TK_VALUETYPE = 22,
    /** @brief  初始未知值 */
    DDS_TK_UNKNOWN = -1
}TCTypeKind;

/**
 * @typedef enum TypeCodeExceptionCode
 *
 * @brief   枚举型的TypeCodeException类型来存储TypeCode模块类型的返回值.
 */

typedef enum TypeCodeExceptionCode
{
    TC_EC_OK,
    TC_EC_ERROR
}TypeCodeExceptionCode;


typedef enum TypeCodeModifierKind
{
    DDS_MODIFIER_NONE
}TypeCodeModifierKind;

/**
 * @typedef enum ExtensibilityKind
 *
 * @brief   表示该类型的动态类型。
 */

typedef enum ExtensibilityKind
{
    /** @brief  表示类型需要兼容在后面添加成员。 */
    DDS_EXTENSIBLE_EXTENSIBILITY,
    /** @brief  表示类型已经确定，以后不打算扩展。 */
    DDS_FINAL_EXTENSIBILITY,
    /** @brief  表示该类型需要兼容增加、删除、交换位置的类型。 */
    DDS_MUTABLE_EXTENSIBILITY
}ExtensibilityKind;

#ifdef __cplusplus
}
#endif

#endif /* TypeCodeKind_h__*/
