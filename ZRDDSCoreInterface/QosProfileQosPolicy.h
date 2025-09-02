/**
 * @file:       QosProfileQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef QosProfileQosPolicy_h__
#define QosProfileQosPolicy_h__

#include "ZROSDefine.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLQOSINTERFACE

/**
 * @struct DDS_QosProfileQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义与Qos配置文件有关的配置项。
 */
typedef struct DDS_QosProfileQosPolicy
{
    /**   
     * @brief   QoS配置文件加载路径列表。
     * 
     * @details DDS将从 #profile_paths 设置的路径中尝试读取Qos配置文件, 默认为空字符串序列。
     *          每个元素代表一个相对或者绝对路径。 
     */
    DDS_StringSeq profile_paths;
}DDS_QosProfileQosPolicy;

#endif /* _ZRXMLQOSINTERFACE */

#endif /* _ZRXMLINTERFACE */

#endif /* QosProfileQosPolicy_h__ */
