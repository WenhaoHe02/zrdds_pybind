/**
 * @file:       ContentFilteredTopic.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_CONTENTFILTEREDTOPIC_H)
#define _CONTENTFILTEREDTOPIC_H

#include "ZRDDSCommon.h"
#include "DomainEntity.h"
#include "TopicDescription.h"
#include "ZRBuiltinTypes.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class DomainParticipant;
class Topic;

/**
 * @class   ContentFilteredTopic
 *
 * @ingroup  CppTopic
 *
 * @brief   抽象基于内容过滤的主题。
 *
 * @details  基于内容的过滤主题是更复杂的主题抽象，表明订阅端不需要主题下的所有数据，而只关心满足一定条件的数据。
 *           基于内容过滤的主题可以用来限制订阅端需要处理的数据量，以及减少网络内发送的数据量（发布端过滤）。
 *           通过过滤表达式以及过滤参数来表示订阅端需要的数据。过滤表达式与SQL语句中的WHERE块类似，
 *           而过滤参数则提供值给过滤表达式中的参数（使用%n表示），提供的过滤参数的个数需与过滤表达式中要求的参数一致。
 *           过滤表达式以及过滤参数的语法参见 @ref expression-grammer 。
 *
 *           注意： ZRDDS该版本的过滤在订阅端应用，故而基于内容过滤的主题不会减少网络带宽，反而会增加接收端的负载（每个样本
 *           均需要应用用户设置的过滤规则）。
 */

class DCPSDLL ContentFilteredTopic :
    public TopicDescription
{
public:

    /**
     * @fn  virtual Topic* ContentFilteredTopic::get_related_topic() = 0;
     *
     * @brief   获取该基于内容过滤主题的基础主题，在使用 DomainParticipant::create_contentfilertopic 创建时指定。
     *
     * @return  指向该基于内容过滤的主题关联的基础主题。
     */

    virtual Topic* get_related_topic() = 0;

    /**
     * @fn  virtual ReturnCode_t ContentFilteredTopic::get_expression_parameters(StringSeq &exp_paras) = 0;
     *
     * @brief   该方法获取关联的过滤参数，在创建基于内容过滤的主题时传入或者通过 #set_expression_parameters 方法设置。
     *
     * @param [in,out]  exp_paras   出口参数，用于保存通信中间件维护的过滤参数。
     *
     * @return  如下的可能返回值：
     *          - #DDS_RETCODE_OK :表示成功； 
     *          - #DDS_RETCODE_ERROR :未知的错误表示失败，例如拷贝参数失败。
     */

    virtual ReturnCode_t get_expression_parameters(StringSeq &exp_paras) = 0;

    /**
     * @fn  virtual ReturnCode_t ContentFilteredTopic::set_expression_parameters(const StringSeq &exp_paras) = 0;
     *
     * @brief   该方法用于重新设置过滤参数。
     *
     * @param   exp_paras   指明新的过滤参数。
     *
     * @return  如下的可能返回值：
     *          - #DDS_RETCODE_OK :表示成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示过滤参数个数或者类型与过滤表达式不匹配；  
     *          - #DDS_RETCODE_ERROR :未知的错误表示失败，例如拷贝参数失败。
     */

    virtual ReturnCode_t set_expression_parameters(const StringSeq &exp_paras) = 0;

    /**
     * @fn  virtual Char* ContentFilteredTopic::get_filter_expression() const = 0;
     *
     * @brief   获取当前基于内容过滤的主题关联的过滤表达式。
     *
     * @return  过滤表达式字符串。
     */

    virtual Char* get_filter_expression() const = 0;
protected:
    virtual ~ContentFilteredTopic(){}
};

} // namespace DDS

#endif  //_CONTENTFILTEREDTOPIC_H
