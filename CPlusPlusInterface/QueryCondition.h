/**
 * @file:       QueryCondition.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_QUERYCONDITION_H)
#define _QUERYCONDITION_H

#include "ReadCondition.h"
#include "ZRBuiltinTypes.h"

namespace DDS {

class QueryCondition;

#ifdef _ZRDDS_INCLUDE_QUERY_CONDITION

/**
 * @class   QueryCondition
 *
 * @ingroup CppSubscription
 *
 * @brief   查询条件。
 *
 * @warning ZRDDS当前未实现该功能。
 */

class DCPSDLL QueryCondition : public ReadCondition
{
public:
    virtual ReturnCode_t set_query_argument(const StringSeq &query_parameters) = 0;
    virtual ReturnCode_t get_query_argument(StringSeq &query_parameters) = 0;
    virtual const Char* get_query_expression() = 0;
};

#endif //_ZRDDS_INCLUDE_QUERY_CONDITION

} // namespace DDS

#endif  //_QUERYCONDITION_H
