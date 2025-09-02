/**
 * @file:       BuiltinTopicKey_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_BUILTINTOPICKEY_T_H)
#define _BUILTINTOPICKEY_T_H

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_BuiltinTopicKey_t[4]
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   在内置数据类型中唯一标识该内置数据代表的远程实体（域参与者、数据读者、数据写者），本质上与远程实体的唯一标识
 *          DDS_InstanceHandle_t::value 值相同.
 */

typedef DDS_ULong DDS_BuiltinTopicKey_t[4];

#endif
