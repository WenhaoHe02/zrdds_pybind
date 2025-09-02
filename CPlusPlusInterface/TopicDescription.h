/**
 * @file:       TopicDescription.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TOPICDESCRIPTION_H)
#define _TOPICDESCRIPTION_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

namespace DDS {

class DomainParticipant;

/**
 * @class	TopicDescription
 *
 * @ingroup	CppTopic
 *
 * @brief	抽象主题的基本属性信息。
 *
 * @details	与主题相关的信息包括关联的一个已存在的数据类型（由数据类型名和 DDS::TypeSupport 类描述），
 * 			主题名称以及与该主题关联的 DDS::DomainParticipant 。这些描述信息包含于该类的对象中并可通过该类的对象获取。
 */

class DCPSDLL TopicDescription
{
public:

    /**
     * @fn  virtual DomainParticipant* TopicDescription::get_participant() = 0;
     *
     * @brief   获取创建该主题所属的域参与者。
     *
     * @return  返回该主题所属的域参与者对象。
     */

    virtual DomainParticipant* get_participant() = 0;

    /**
     * @fn  virtual const Char* TopicDescription::get_type_name() = 0;
     *
     * @brief   获取与该主题关联的数据类型在域参与者中注册的名称。
     *
     * @return  数据类型的名称。
     */

    virtual const Char* get_type_name() = 0;

    /**
     * @fn  virtual const Char* TopicDescription::get_name() = 0;
     *
     * @brief   获取该主题的名称。
     *
     * @return  主题名称。
     */

    virtual const Char* get_name() = 0;
protected:

    TopicDescription(){}

    virtual ~TopicDescription(){}
};

} // namespace DDS

#endif  //_TOPICDESCRIPTION_H
