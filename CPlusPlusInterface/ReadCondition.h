/**
 * @file:       ReadCondition.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_READCONDITION_H)
#define _READCONDITION_H

#include "Condition.h"

struct ReadConditionImpl;

namespace DDS {

class ReadCondition;
#ifdef _ZRDDS_INCLUDE_READ_CONDITION

class DataReader;

/**
 * @class   ReadCondition
 *
 * @ingroup CppSubscription
 *
 * @brief   该类抽象ZRDDS中的读取条件@ref waitset-introduction 。
 *          
 * @details ZRDDS中数据读者为每个存储的数据样本均维护三个状态：
 *          - #DDS_SampleStateKind ;  
 *          - #DDS_ViewStateKind ;  
 *          - #DDS_InstanceStateKind ;
 *          
 *          满足读取条件 ReadCondition(sampleMask, viewMask, instanceMask)的数据样本，将同时满足以下三个条件：
 *          - #DDS_SampleStateKind 处于 sampleMask 所表示的状态集合中；
 *          - 且 #DDS_ViewStateKind 处于 viewMask 所表示的状态集合中；
 *          - 且 #DDS_InstanceStateKind 处于 instanceMask 所表示的状态集合中；
 *          读取条件用于同时表示这三种状态，读取条件主要在两个地方使用：
 *          1. 用于条件-等待模型@ref waitset-introduction 中，当数据读者中处于 DDS::ReadCondition 所指定状态的数据  
 *              样本集合不为空时，该条件被触发；  
 *          2. 用于 @ref read-take 系列方法，代替 sample_mask、view_mask、instance_mask，  
 *              参数，用于读取数据读者中处于 DDS::ReadCondition 所指定状态的数据样本集合。
 */

class DCPSDLL ReadCondition : public Condition
{
public:

    /**
     * @fn  virtual DataReader* ReadCondition::get_datareader() = 0;
     *
     * @brief   获取该读取条件所属的数据读者。
     *
     * @return  指向创建该读取条件的数据读者对象。
     */

    virtual DataReader* get_datareader() = 0;

    /**
     * @fn  virtual SampleStateMask ReadCondition::get_sample_state_mask() = 0;
     *
     * @brief   获取创建时传入的样本状态掩码。
     *
     * @return  该读取条件样本状态掩码。
     */

    virtual SampleStateMask get_sample_state_mask() = 0;

    /**
     * @fn  virtual ViewStateMask ReadCondition::get_view_state_mask() = 0;
     *
     * @brief   获取创建时传入的视图状态掩码。
     *
     * @return  该读取条件视图状态掩码。
     */

    virtual ViewStateMask get_view_state_mask() = 0;

    /**
     * @fn  virtual InstanceStateMask ReadCondition::get_instance_state_mask() = 0;
     *
     * @brief   获取创建时传入的实例状态掩码。
     *
     * @return  该读取条件实例状态掩码。
     */

    virtual InstanceStateMask get_instance_state_mask() = 0;
};

#endif //_ZRDDS_INCLUDE_READ_CONDITION

} // namespace DDS

#endif  //_READCONDITION_H
