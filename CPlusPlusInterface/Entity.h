/**
 * @file:       Entity.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_ENTITY_H)
#define _ENTITY_H

#include "ZRDDSCommon.h"
#include "ZRBuiltinTypes.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class StatusCondition;

/**
 * @class   Entity
 *
 * @ingroup CppInfrastruct
 *
 * @brief   实体（@ref entity-introduction) 作为所有实体（包括域参与者、主题、发布者、订阅者、数据读者、数据写者）的基类，抽象实体的基本属性以及操作。
 */

class DCPSDLL Entity
{
public:
    virtual ~Entity();

    /**
     * @fn  virtual StatusCondition* Entity::get_statuscondition() = 0;
     *
     * @brief   返回该实体关联的状态条件。
     *
     * @return  底层自动创建的状态条件。
     */

    virtual StatusCondition* get_statuscondition() = 0;

    /**
     * @fn  virtual StatusKindMask Entity::get_status_changes() = 0;
     *
     * @brief   获取该实体从上一次获取任意状态后的状态变化。
     *
     * @return  返回状态的改变掩码。
     */

    virtual StatusKindMask get_status_changes() = 0;

    /**
     * @fn  virtual ReturnCode_t Entity::enable() = 0;
     *
     * @brief   手动使能该实体，参见@ref entity-enable 。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK ，表示获取成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET ，表示所属的父实体尚未使能。
     */

    virtual ReturnCode_t enable() = 0;

    /**
     * @fn  virtual InstanceHandle_t Entity::get_instance_handle() = 0;
     *
     * @brief   获取该实体的唯一标识。
     *
     * @return  实体唯一标识。
     */

    virtual InstanceHandle_t get_instance_handle() = 0;
#ifdef _ZRXMLINTERFACE

#ifdef _ZRXMLENTITYINTERFACE

    /**
     * @fn  virtual const Char* Entity::get_entity_name() = 0;
     *
     * @brief   获取实体的名称。
     *
     * @return  NULL表示获取失败，否则为实体的名称。
     */

    virtual const Char* get_entity_name() = 0;

    /**
     * @fn  virtual Entity* Entity::get_factory() = 0;
     *
     * @brief   获取该实体的工厂实体。
     *
     * @return  该实体的父工厂实体。
     */

    virtual Entity* get_factory() = 0;

    /**
     * @fn virtual ReturnCode_t Entity::to_xml(const Char*& result, Boolean containedQos = true) = 0;
     *
     * @brief 将实体转换为XML文本
     *
     * @param [in,out] result 转换得到的XML文本。
     * @param containedQos    转换的XML中是否需要包含实体的QoS。
     *
     * @return 当前可能的返回值：
     *          - #DDS_RETCODE_OK ，表示转换成功；
     *          - #DDS_RETCODE_ERROR ，表示转换失败。
     */
    virtual ReturnCode_t to_xml(const Char*& result, Boolean containedQos = true) = 0;

#endif // _ZRXMLENTITYINTERFACE

#endif // _ZRXMLINTERFACE
protected:
    // 构造函数
    Entity();
    StatusCondition* m_statusCondition;
};

} // namespace DDS

#endif  //_ENTITY_H
