/**
 * @file:       PropertyQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PropertyQosPolicy_h__
#define PropertyQosPolicy_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "ZRSequence.h"
#include "ZRBuiltinTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @typedef struct DDS_Property_t
 *
 * @brief   扩展的DDS_Property_t.
 */

typedef struct DDS_Property_t
{
    /** @brief   名称，由厂商自己约定。 */
    DDS_Char* name;
    /** @brief   名称对应的值。 */
    DDS_Char* value;
    /** @brief   是否需要传递给对端。 */
    DDS_Boolean propagate;
    /** @brief   区分内存空间是否由内部分配，true表明DDS内部管理内存空间，否则表明用户管理内存空间。 */
    DDS_Boolean owned;
}DDS_Property_t;

DDS_SEQUENCE_CPP(DDS_PropertySeq, DDS_Property_t);

/**
 * @struct  DDS_BinaryProperty_t
 *
 * @brief   二值的键值对。
 *
 * @author  Hzy
 * @date    2018/1/30
 */

typedef struct DDS_BinaryProperty_t
{
    /** @brief   名称，由厂商自己约定。 */
    DDS_Char* name;
    /** @brief   名称对应的值。 */
    DDS_OctetSeq value;
    /** @brief   是否需要传递给对端。 */
    DDS_Boolean propagate;
    /** @brief   区分内存空间是否由内部分配，true表明DDS内部管理内存空间，否则表明用户管理内存空间。 */
    DDS_Boolean owned;
}DDS_BinaryProperty_t;

DDS_SEQUENCE_CPP(DDS_BinaryPropertySeq, DDS_BinaryProperty_t);

/**
 * @struct DDS_PropertyQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   属性配置。
 *
 * @details 
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #value | 空 | 无 | 无 | 无 | 不可变
 *          #binary_value | 空 | 无 | 无 | 无 | 不可变
 *
 */
typedef struct DDS_PropertyQosPolicy 
{
    /** @brief   字符串值。 */
    DDS_PropertySeq value;
    /** @brief   缓冲区值。 */
    DDS_BinaryPropertySeq binary_value;
}DDS_PropertyQosPolicy;

/**
 * @fn  DDS_Boolean DDS_PropertyQos_AppendProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name, const DDS_Char* value, DDS_Boolean propagate);
 *
 * @brief   在PropertyQos中增加字符串值属性键值对.
 *
 * @param [in,out]  propertyQos 指定PropertyQos对象.
 * @param   name                字符串值属性名称.
 * @param   value               字符串值属性值.
 * @param   propagate           是否需要传递给对端.
 *
 * @return  A DDS_Boolean.      若成功，返回true，否则返回false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_AppendProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name,
    const DDS_Char* value,
    DDS_Boolean propagate);

/**
 * @fn  DDS_Boolean DDS_PropertyQos_AppendBinaryProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name, const DDS_OctetSeq* value, DDS_Boolean propagate);
 *
 * @brief   在PropertyQos中增加缓冲区值属性键值对.
 *
 * @param [in,out]  propertyQos 指定PropertyQos对象.
 * @param   name                缓冲区值属性名称.
 * @param   value               缓冲区值属性值.
 * @param   propagate           是否需要传递给对端.
 *
 * @return  A DDS_Boolean.      若成功，返回true，否则返回false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_AppendBinaryProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name,
    const DDS_OctetSeq* value,
    DDS_Boolean propagate);

/**
 * @fn  DDS_Boolean DDS_PropertyQos_RemoveProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name);
 *
 * @brief   在PropertyQos中移除指定名称的字符串值属性.调用此函数，会将所有同名属性移除.
 *
 * @param [in,out]  propertyQos 指定PropertyQos对象.
 * @param   name                需要移除的属性名称.
 *
 * @return  A DDS_Boolean.      若成功，返回true，否则返回false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_RemoveProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name);

/**
 * @fn  DDS_Boolean DDS_PropertyQos_RemoveBinaryProperty(DDS_PropertyQosPolicy * propertyQos, const DDS_Char* name);
 *
 * @brief   在PropertyQos中移除指定名称的缓冲区值属性.调用此函数，会将所有同名属性移除.
 *
 * @param [in,out]  propertyQos 指定PropertyQos对象.
 * @param   name                需要移除的属性名称.
 *
 * @return  A DDS_Boolean.      若成功，返回true，否则返回false.
 */

DCPSDLL DDS_Boolean DDS_PropertyQos_RemoveBinaryProperty(DDS_PropertyQosPolicy * propertyQos,
    const DDS_Char* name);

#ifdef _ZRDDS_INCLUDE_DATA_COMPRESSION

/**
* @fn  int CompressionFunc(const char* src, char* dst, int src_size, int dst_size);
*
* @brief   CompressionFunc.
*
* @param   src         原数据
* @param   src_size    原始数据大小
* @param   [in,out]dst 存储压缩后数据.
* @param   dst_size    存储压缩后数据的空间大小.
*
* @return   返回0表示失败，否则返回正数.
*/
typedef int(*CompressionFunc)(
    const char* src,
    char* dst,
    int src_size,
    int dst_size);

/**
* @fn  int DeCompressionFunc(const char* src, char* dst, int compressed_size, int dst_capacity);
*
* @brief   DeCompressionFunc.
*
* @param   src             需要解压的数据.
* @param   [in,out] dst    存储解压后数据的位置.
* @param   compressed_size 需要解压的数据大小.
* @param   dst_capacity    存储解压后数据的空间大小.
*
* @return  解压成功返回压缩前数据大小，如果dst空间不够，则数据错误码（负数）.
*/

typedef int(*DeCompressionFunc)(
    const char* src,
    char* dst,
    int compressed_size,
    int dst_capacity);

/**
* @fn  ZR_INT32 SetDataWriterCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, void* get_name_func, void* compression_func);
*
* @brief   设置数据写者压缩.
*
* @param [in,out]  property            数据写者的PropertyQosPolicy.
* @param [in]      dll_name            使用的DLL名字（动态加载填动态库名字，静态加载填NULL，使用默认值填NULL）.
* @param [in]      conpression_name    使用的压缩算法名称（使用默认函数填NULL）.
* @param [in]      compression_func    压缩函数（动态加载填函数名，静态加载填函数地址，使用默认函数填NULL）.
*
* @return  成功返回0，失败返回-1.
*/

DCPSDLL ZR_INT32 SetDataWriterCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, ZR_INT8* compression_name, void* compression_func);

/**
* @fn  ZR_INT32 SetDataReaderCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, void* get_name_func, void* decompression_func);
*
* @brief   设置数据读者压缩.
*
* @param [in,out]  property              数据读者的PropertyQosPolicy.
* @param [in]      dll_name              使用的DLL名字（动态加载填动态库名字，静态加载填NULL，使用默认值填NULL）.
* @param [in]      conpression_name      使用的压缩算法名称（使用默认函数填NULL）.
* @param [in]      decompression_func    解压函数（动态加载填函数名，静态加载填函数地址，使用默认函数填NULL）.
*
* @return  成功返回0，失败返回-1.
*/

DCPSDLL ZR_INT32 SetDataReaderCompression(DDS_PropertyQosPolicy* property, ZR_INT8* dll_name, ZR_INT8* compression_name, void* decompression_func);

#endif // _ZRDDS_INCLUDE_DATA_COMPRESSION


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PropertyQosPolicy_h__ */
