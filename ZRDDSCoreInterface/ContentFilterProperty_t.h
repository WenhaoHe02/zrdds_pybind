/**
 * @file:       ContentFilterProperty_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ContentFilterProperty_t_h__
#define ContentFilterProperty_t_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

#ifdef _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC

/**
 * @struct DDS_ContentFilterProperty_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   封装在 DDS_SubscriptionBuiltinTopicData 中的基于内容过滤的主题属性。
 */

typedef struct DDS_ContentFilterProperty_t{
    /** @brief    基于内容过滤主题的名称(ContentFilterTopic的名称)。 */
    DDS_Char* contentFilteredTopicName;
    /** @brief    相关联的普通主题的名称（Topic的名称）。 */
    DDS_Char* relatedTopicName;
    /** @brief    过滤类型，当前ZRDDS仅支持"DDSSQL"。 */
    DDS_Char* filterClassName;
    /** @brief    过滤表达式，在创建基于内容过滤的主题时用户指定的参数。 */
    DDS_Char* filterExpression;
    /** @brief    过滤参数，在创建基于内容过滤的主题时用户指定的参数。 */
    DDS_StringSeq expressionParameters;
} DDS_ContentFilterProperty_t;

#endif /* _ZRDDS_INCLUDE_CONTENTFILTER_TOPIC */

#endif /* ContentFilterProperty_t_h__*/
