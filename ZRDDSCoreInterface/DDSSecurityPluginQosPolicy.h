/**
 * @file:       DDSSecurityPluginQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSSecurityPluginQosPolicy_h__
#define DDSSecurityPluginQosPolicy_h__

#include "ZROSDefine.h"
#ifdef _ZRDDSSECURITY

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @enum DDS_SecurityPluginType
 *
 * @ingroup  CoreQosStruct
 *
 * @brief   定义安全插件的类型。
 */

typedef enum DDS_SecurityPluginType
{
    DDSSECURITY_EMPTY = 0,
    DDSSECURITY_AUTHENTICATION = 1,
    DDSSECURITY_ACCESSCONTROL = 2,
    DDSSECURITY_CRYPTOGRAPHIC = 4,
}DDS_SecurityPluginType;

typedef DDS_SecurityPluginType DDS_DDSSecurityPluginType;

/**
 * @typedef struct DDS_SecurityPlugin
 *
 * @ingroup  CoreQosStruct
 *
 * @brief   描述一项DDS安全插件的结构.
 */

typedef struct DDS_SecurityPlugin
{
    /** @brief 插件的名称，用于在域参与者中引用该插件 */
    DDS_CharSeq ref_name;
    /** @brief 插件库路径。 */
    DDS_CharSeq lib_path;
    /** @brief 插件库中包含的插件类型，使用 DDS_SecurityPluginType 掩码设定 */
    DDS_ULong types;
}DDS_SecurityPlugin;

typedef DDS_SecurityPlugin DDS_DDSSecurityPlugin;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

DDS_SEQUENCE_CPP(DDS_SecurityPluginSeq, DDS_SecurityPlugin);

typedef DDS_SecurityPluginSeq DDS_DDSSecurityPluginSeq;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
 * @struct DDS_SecurityPluginQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief 描述DDS安全插件集合的QoS配置项，可以配置一组DDS安全插件，然后通过名字进行区分。
 */

typedef struct DDS_SecurityPluginQosPolicy
{
    /** @brief   用户自定义安全插件列表，采用名称唯一标识。 */
    DDS_SecurityPluginSeq security_plugins;
}DDS_SecurityPluginQosPolicy;

#endif /* _ZRDDSSECURITY */

#endif /* DDSSecurityPluginQosPolicy_h__ */
