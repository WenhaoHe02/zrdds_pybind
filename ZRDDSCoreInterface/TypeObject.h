/**
 * @file:       TypeObject.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeObject_h__
#define TypeObject_h__

#include "OsResource.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"
#include "TypeCodeKind.h"

#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TypeObject TypeObject;

#define TypeObjectSize 64

/**
 * @fn  TypeObjectImpl* TypeObjectFactoryCloneTypeObject(const TypeObjectImpl* typeObject);
 *
 * @brief   深度拷贝TypeObject。
 *
 * @author  Hzy
 * @date    2017/1/10
 *
 * @param   typeObject  原始TypeObject。
 *
 * @return  NULL表示失败，否则指向拷贝出来的TypeObject。
 */

DCPSDLL TypeObject* TypeObjectFactoryCloneTypeObject(const TypeObject* typeObject);

/**
 * @fn  DDS_Long TypeObjectFactoryDeleteTypeObject(TypeObjectImpl* typeObject);
 *
 * @brief   清理TypeObject的空间。
 *
 * @author  Hzy
 * @date    2017/1/5
 *
 * @param [in,out]  typeObject  清理TypeObject的空间。
 *
 * @return  0表示成功，-1表示失败。
 */

DCPSDLL DDS_Long TypeObjectFactoryDeleteTypeObject(TypeObject* typeObject);

/**
 * @fn  DDS_Long TypeObjectAssignableFrom(const TypeObjectImpl* type1, const TypeObjectImpl* type2);
 *
 * @brief   是否满足type1 is-assignable-from type2.
 *
 * @param   type1   类型1.
 * @param   type2   类型2.
 *
 * @return  0表示满足，小于0表示不满足。
 */

DCPSDLL DDS_Long TypeObjectAssignableFrom(const TypeObject* type1, const TypeObject* type2);

/**
 * @fn  DDS_Char* GetTypeObjectPrintableString(const TypeObject* typeObject);
 *
 * @brief   获取一个TypeObject等价的IDL文件描述。
 *
 * @param   typeObject  指明目标。
 *
 * @return  NULL表示失败，否则指向文件内容,需要调用ReleaseTypeObjectPrintableString，否则造成内存泄漏。
 */

DCPSDLL DDS_Char* GetTypeObjectPrintableString(const TypeObject* typeObject);

/**
 * @fn  DCPSDLL void ReleaseTypeObjectPrintableString(DDS_Char* buffer);
 *
 * @brief   清理交给用户的空间。
 *
 * @param [in,out]  buffer  GetTypeObjectPrintableString返回的空间。
 */

DCPSDLL void ReleaseTypeObjectPrintableString(DDS_Char* buffer);

#ifdef _ZRDDS_INCLUDE_TYPECODE

/**
 * @fn  TypeObject TypeObjectFactoryCreateFromTypeCode(TypeObjectImpl* typeObject, struct TypeCodeImpl* typeCode);
 *
 * @brief   从TypeCode创建等价的TypeObject。
 *
 * @param [in,out]  typeCode    源TypeCode。
 *
 * @return  NULL表示转化失败，否则表示转化结果。
 */

DCPSDLL TypeObject* TypeObjectFactoryCreateFromTypeCode(struct TypeCodeHeader* typeCode);

/**
 * @fn  DCPSDLL TypeCodeHeader* TypeObjectToTypeCode(const TypeObject* typeObject);
 *
 * @brief   从TypeObject转化为TypeCode.
 *
 * @param   typeObject  指明目标。
 *
 * @return  NULL表示失败，否则表示转化结果。
 */

DCPSDLL TypeCodeHeader* TypeObjectToTypeCode(const TypeObject* typeObject);

#endif /*_ZRDDS_INCLUDE_TYPECODE */

#ifdef __cplusplus
}
#endif

#endif /* _ZRDDS_INCLUDE_TYPE_OBJECT */

#endif /* TypeObject_h__*/
