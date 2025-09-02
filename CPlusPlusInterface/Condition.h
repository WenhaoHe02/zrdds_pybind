/**
 * @file:       Condition.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_CONDITION_H)
#define _CONDITION_H

#include "ZRDDSCommon.h"
#include "ZRSequence.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

class Entity;
class GuardConditionCPlusPlusImpl;

/**
 * @class   Condition 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   ZRDDS中条件的基类。
 *
 * @details ZRDDS中提供条件-等待模型使得用户可以使用同步等待的模式获取ZRDDS底层的数据，@ref waitset-introduction 该类作为所有条件的基类。
 */

class DCPSDLL Condition
{
public:

    /**
     * @fn  virtual Boolean Condition::get_trigger_value() = 0;
     *
     * @brief   获取当前的触发状态。
     *
     * @return  true表示被触发，false表示该条件还未被触发。
     */

    virtual Boolean get_trigger_value() = 0;

    /**
     * @fn  virtual Condition::~Condition()
     *
     * @brief   析构函数。
     */

    virtual ~Condition(){}
};

/**
 * @class   StatusCondition 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   实体状态条件，该条件用于获取实体状态改变。
 *
 * @details 该条件用于等待实体中简单通信状态变化，由ZRDDS在用户创建实体时，自动创建与实体关联的该状态，用户通过接口
 *          DDS::Entity::get_statusconditon() 方法获取底层引用。
 */

class DCPSDLL StatusCondition : public Condition
{
public:

    /**
     * @fn  virtual ReturnCode_t StatusCondition::set_enabled_statuses(const StatusKindMask &mask) = 0;
     *
     * @brief   以掩码的方式设置用户关心的状态。
     *
     * @param   mask    掩码。
     *
     * @return  当前总是返回 #DDS_RETCODE_OK 。
     */

    virtual ReturnCode_t set_enabled_statuses(const StatusKindMask &mask) = 0;

    /**
     * @fn  virtual StatusKindMask StatusCondition::get_enabled_statuses() = 0;
     *
     * @brief   获取前一次用户通过 #set_enabled_statuses 方法设置的关心的状态。
     *
     * @return  掩码方式返回当前状态条件所关联的状态集合。
     */

    virtual StatusKindMask get_enabled_statuses() = 0;

    /**
     * @fn  virtual Entity* StatusCondition::get_entity() = 0;
     *
     * @brief   获取状态条件所属的实体。
     *
     * @return  NULL表示失败，否则指向关联的实体的基类，用户通过dynamic_cast转化为具体的实体类型。
     */

    virtual Entity* get_entity() = 0;
};

#ifdef _ZRDDS_INCLUDE_GUARD_CONDITION

/**
 * @class   GuardCondition 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   监视条件用于手动控制等待条件。
 *
 * @details 该类主要用于手动控制等待条件 DDS::WaitSet::wait 方法的阻塞，监视条件的生命周期完全由用户通过 new/delete 控制。
 */

class DCPSDLL GuardCondition : public Condition
{
public:

    /**
     * @fn  GuardCondition::GuardCondition();
     *
     * @brief   默认构造处于非触发状态的监视条件。
     */

    GuardCondition();

    /**
     * @fn  GuardCondition::~GuardCondition();
     *
     * @brief   析构函数。
     */

    ~GuardCondition();

    /**
     * @fn  virtual ReturnCode_t GuardCondition::set_trigger_value(Boolean value);
     *
     * @brief   手动设置监控类的触发状态。
     *
     * @param   value   true表示设置为触发状态，false表示设置为非触发状态。
     *
     * @return  总是返回 #DDS_RETCODE_OK 。
     */

    virtual ReturnCode_t set_trigger_value(Boolean value);

    /**
     * @fn  virtual Boolean GuardCondition::get_trigger_value();
     *
     * @brief   实现父类的抽象方法。
     *
     * @return  true表示被触发，false表示该条件还未被触发。
     */

    virtual Boolean get_trigger_value();

public:
    /** @brief   关联的实现对象。 */
    GuardConditionCPlusPlusImpl* m_impl;
};
#endif // _ZRDDS_INCLUDE_GUARD_CONDITION

/**
 * @typedef Condition* ConditionPtr
 *
 * @ingroup CppInfrastruct
 *
 * @brief   定义 DDS::Condition 指针的别名。
 */

typedef Condition* ConditionPtr;

/**
 * @struct ConditionSeq 
 *
 * @ingroup CppInfrastruct
 *
 * @brief   声明 DDS::ConditionPtr 的序列类型，参见 #DDS_USER_SEQUENCE_CPP 。
 */

typedef struct ConditionSeq ConditionSeq;
DDS_SEQUENCE_CPP(ConditionSeq, ConditionPtr);

} // namespace DDS

#endif  //_CONDITION_H
