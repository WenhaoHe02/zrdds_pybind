/**
 * @file:       MultiTopic.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_MULTITOPIC_H)
#define _MULTITOPIC_H

#include "TopicDescription.h"
#include "ZRBuiltinTypes.h"

namespace DDS {
    
class DomainParticipant;
/**
 * @class   MultiTopic
 *
 * @ingroup CppTopic
 *
 * @brief   合并接收多个主题。
 *
 * @details 指明一个订阅者可以接受由同一类型创建的多个主题，并可以通过指明的方式进行过滤和重新排序。
 *          过滤和重排的表达式格式类似于SQL语句。详细的语法规则见DDS规范。
 *
 * @warning ZRDDS当前未实现该功能。
 */

class DCPSDLL MultiTopic :
    public TopicDescription
{
public:
    virtual ReturnCode_t get_expression_parameters(StringSeq &exp_paras) = 0;
    virtual ReturnCode_t set_expression_parameters(const StringSeq &exp_paras) = 0;
protected:
    virtual ~MultiTopic() {}
};

} // namespace DDS

#endif  //_MULTITOPIC_H
