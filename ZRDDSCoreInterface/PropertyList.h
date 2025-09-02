/**
 * @file:       PropertyList.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef PropertyList_h__
#define PropertyList_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"

/**
 * @typedef struct DDS_Property
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   <名称-值>键值对，用来在发现阶段存储节点信息。
 * 
 * @details 现阶段支持的名称有:
 *          - "dds.sys_info.hostname": 表示DDS程序所在主机名称
 *          - "dds.sys_info.username": 表示运行DDS程序的用户
 *          - "dds.sys_info.process_id": 表示DDS程序的进程ID
 *          - "dds.sys_info.host_ip": 表示DDS程序所在主机IP
 *          - "dds.sys_info.executable_filepath": 表示DDS程序的可执行程序完整路径
 */

typedef struct DDS_Property
{
    /** @brief   名称，由厂商自己约定。 */
    DDS_Char* name;
    /** @brief   名称对应的值。 */
    DDS_Char* value;
}DDS_Property;

#define BUFFERED_PROPERTY_NUM 16

/**
 * @struct DDS_PropertyList
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   <名称-值>键值对列表封装。
 */

typedef struct DCPSDLL DDS_PropertyList
{
    /** @brief   列表中Property个数。*/
    DDS_ULong size;
    /** @brief   列表内容数组。*/
    DDS_Property buffer[BUFFERED_PROPERTY_NUM];
    /** @brief   当缓冲区用满时，申请额外的空间。*/
    DDS_Property* values;
#ifdef _ZRDDSCPPINTERFACE
    DDS_PropertyList();
#endif
}DDS_PropertyList;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyInitial(DDS_Property* self, const DDS_Char* name, const DDS_Char* value);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化属性键值对，申请空间。
 *
 * @param [in,out]  self    指明目标。
 * @param   name            名称。
 * @param   value           值。
 *
 * @return  0表示成功，-1表示失败。
 */

DCPSDLL DDS_Long DDS_PropertyInitial(DDS_Property* self, const DDS_Char* name, const DDS_Char* value);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyClear(DDS_Property* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   清理键值对空间。
 *
 * @param [in,out]  self    指明目标。
 *
 * @return  总是返回0表示成功。
 */

DCPSDLL DDS_Long DDS_PropertyClear(DDS_Property* self);

/**
 * @fn  DCPSDLL void DDS_PropertyListInitial(DDS_PropertyList* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化一个空的列表。
 *
 * @param [in,out]  self    指明目标。
 */

DCPSDLL void DDS_PropertyListInitial(DDS_PropertyList* self);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyListInsert(DDS_PropertyList* self, const DDS_Char* name, const DDS_Char* value, DDS_Property* newPro);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   插入指定参数的Property到列表中。
 *
 * @param [in,out]  self    指定插入目标。
 * @param   name            Property字符串型的名称，以NULL结尾。
 * @param   value           Property缓冲区型的值，可以不以NULL结尾。
 * @param [in,out]  newPro  新的Property的空间，为空时使用name/value指定。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL DDS_Long DDS_PropertyListInsert(DDS_PropertyList* self,
    const DDS_Char* name,
    const DDS_Char* value,
    DDS_Property* newPro);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyListCopy(DDS_PropertyList* self, const DDS_PropertyList* right);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   拷贝PropertyList。
 *
 * @param [in,out]  self    指明目标,会清除原有的内容。
 * @param   right           指明拷贝源。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL DDS_Long DDS_PropertyListCopy(DDS_PropertyList* self,
    const DDS_PropertyList* right);

/**
 * @fn  DCPSDLL DDS_Property* DDS_PropertyListGet(DDS_PropertyList* self, const char* name);;
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   查找Property。
 *
 * @param [in,out]  self    指明目标。
 * @param   name            需要查找的属性名。
 *
 * @return  成功返回查找的Property，否则返回NULL。
 */

DCPSDLL DDS_Property* DDS_PropertyListGet(DDS_PropertyList* self,
    const char* name);

/**
 * @fn  DCPSDLL DDS_Long DDS_PropertyListClear(DDS_PropertyList* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   清空列表并回收空间。
 *
 * @param [in,out]  self    指定目标。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL DDS_Long DDS_PropertyListClear(DDS_PropertyList* self);

/**
 * @fn  DCPSDLL DDS_Property* DDS_PropertyListAt(DDS_PropertyList* self, DDS_ULong index);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   下标操作函数。
 *
 * @param [in,out]  self    指明目标。
 * @param   index           指明下标。
 *
 * @return  NULL表示超出范围，否则为有效的属性列表。
 */

DCPSDLL DDS_Property* DDS_PropertyListAt(DDS_PropertyList* self, DDS_ULong index);

#ifdef __cplusplus
}
#endif

#endif /* PropertyList_h__*/
