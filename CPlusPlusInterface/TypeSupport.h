/**
 * @file:       TypeSupport.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_TYPESUPPORT_H)
#define _TYPESUPPORT_H

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "ZRDDSCppWrapper.h"
#include <stdlib.h>

namespace DDS {

class DomainParticipant;
class DataWriter;
class DataReader;

/**
 * @class   TypeSupport
 *
 * @ingroup CppTopic
 *
 * @brief   类型支持接口，用于向ZRDDS注册用户自定义数据类型。
 *
 * @details 应用自定义的数据类型必须实现该接口，ZRDDS通过编译器自动生成与用户数据类型关联的类型支持接口。
 *          应用自定义的数据类型需要向域参与者注册成功后，才能用来与主题相关联，向ZRDDS注册的过程主要是告知ZRDDS如何
 *          管理样本的生命周期以及序列化、反序列化等操作。 
 */

class DCPSDLL TypeSupport
{
public:

    virtual ~TypeSupport(){}

    /**
     * @fn  virtual const Char* TypeSupport::get_type_name() = 0;
     *
     * @brief   获取类型名称。
     *
     * @return  获取到的类型名称。
     */

    virtual const Char* get_type_name() = 0;

    /**
     * @fn  virtual ReturnCode_t TypeSupport::register_type( DomainParticipant *participant, const Char* type_name);
     *
     * @brief   注册数据类型，子类必须实现的接口。
     *          
     * @details 该方法用于向域参与者注册类型，注册的结果是使得通信中间件能够管理样本对象（创建、删除、拷贝）、
     *          获取数据类型描述、序列化以及反序列化样本。在同一个域参与者下给不同的类型支持对象注册相同的类型名会
     *          返回 #DDS_RETCODE_PRECONDITION_NOT_MET ，允许给类型支持接口多次注册相同的或者不同的类型名称，
     *          效果是覆盖注册。
     *
     * @param [in,out]  participant 注册的目的域参与者。
     * @param   type_name           用户指定的为该类型支持对象注册的类型名，允许为NULL，通信中间件使用 #get_type_name 
     *                              方法的结果注册，该类型名用于在域参与者内唯一标识关联的数据类型，用于创建主题等。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :注册成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :已有相同的类型名被注册，且类型支持对象不同；
     *          - #DDS_RETCODE_BAD_PARAMETER ：participant参数为空；
     *          - #DDS_RETCODE_ERROR :内部未知错误。
     */

    virtual ReturnCode_t register_type(
        DomainParticipant *participant,
        const Char* type_name) = 0;

    /**
     * @fn  virtual ReturnCode_t TypeSupport::unregister_type(DomainParticipant *participant, const Char* type_name) = 0;
     *
     * @brief   从指定域参与者中注销类型。
     *
     * @param [in,out]  participant 指明目标域参与者。
     * @param   type_name           指明注销类型名称。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :表示注销成功；  
     *          - #DDS_RETCODE_BAD_PARAMETER ：参数为空；  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ：  
     *              - 参数指定的类型名称不存在；  
     *              - 不满足注销条件，底层还有主题与该数据类型关联；
     */

    virtual ReturnCode_t unregister_type(DomainParticipant *participant,
                                         const Char* type_name) = 0;
protected:

    TypeSupport(){}
};

} // namespace DDS

#endif  //_TYPESUPPORT_H
