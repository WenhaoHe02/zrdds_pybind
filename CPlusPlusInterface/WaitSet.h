/**
 * @file:       WaitSet.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_WAITSET_H)
#define _WAITSET_H

#include "Condition.h"
#include "ZRDDSCppWrapper.h"

typedef struct WaitSetImpl WaitSetImpl;

#ifdef _ZRDDS_INCLUDE_WAITSET

namespace DDS {

/**
 * @class   WaitSet
 *
 * @ingroup CppInfrastructure
 *
 * @brief   该类型抽象等待条件 @ref waitset-introduction 。
 */

class DCPSDLL WaitSet
{
public:

    /**
     * @fn  WaitSet::WaitSet();
     *
     * @brief   默认构造函数，构造集合为空的集合。
     */

    WaitSet();

    /**
     * @fn  WaitSet::~WaitSet();
     *
     * @brief   析构函数，将自动解开阻塞。
     */

    ~WaitSet();

    /**
     * @fn  ReturnCode_t WaitSet::attach_condition(Condition *a_condition);
     *
     * @brief   将指定的条件加入到该等待集合中。
     *          
     * @details 如果添加的条件的触发状态为true，将会解开阻塞。
     *
     * @param [in,out]  a_condition 指明需要添加的条件。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :添加成功；  
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :分配内存失败；  
     *          - #DDS_RETCODE_BAD_PARAMETER :参数不是有效的条件。
     */

	ReturnCode_t attach_condition(Condition *a_condition);

    /**
     * @fn  ReturnCode_t WaitSet::detach_condition(Condition *a_condition);
     *
     * @brief   从等待集合中移除指定的条件。
     *
     * @param [in,out]  a_condition 指明需要删除的条件。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :添加成功；  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :指定的条件不在该等待集合中；  
     *          - #DDS_RETCODE_BAD_PARAMETER :参数不是有效的条件。
     */

	ReturnCode_t detach_condition(Condition *a_condition);

    /**
     * @fn  ReturnCode_t WaitSet::wait(const ConditionSeq &active_condition, const Duration_t &timeout);
     *
     * @brief   阻塞等待等待集合中的条件处于触发状态。
     *          
     * @details 应用线程等待某些条件的发生，堵塞调用线程， 当调用成功时，@e active_condition 中存放触发的条件，
     *          不允许多个线程等待同一个等待条件。
     *
     * @param   active_condition    出口参数，用于存储处于触发状态的条件。
     * @param   timeout             指明最长等待时间。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :出口参数有效，表明处于触发状态的条件；  
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :在多个线程上等待条件；    
     *          - #DDS_RETCODE_BAD_PARAMETER / #DDS_RETCODE_ERROR ：用户提供的空间不足，且底层扩容失败；  
     *          - #DDS_RETCODE_TIMEOUT : 在指定的时间内没有条件处于触发状态。
     */

    ReturnCode_t wait(ConditionSeq &active_condition, const Duration_t &timeout);

    /**
     * @fn  ReturnCode_t WaitSet::get_conditions(ConditionSeq &attached_conditions);
     *
     * @brief   获取当前该等待集合中已有的条件。
     *
     * @param [in,out]  attached_conditions 出口参数，用于存储当前集合中的条件。
     *
     * @return  当前可能的返回值：
     *          - #DDS_RETCODE_OK :出口参数有效，表明处于触发状态的条件；  
     *          - #DDS_RETCODE_BAD_PARAMETER / #DDS_RETCODE_ERROR ：用户提供的空间不足，且底层扩容失败；  
     */

    ReturnCode_t get_conditions(ConditionSeq &attached_conditions);
private:
    /** @brief   The conditions. */
    WaitSetImpl* m_cWaitSet;
};

} // namespace DDS

#endif //_ZRDDS_INCLUDE_WAITSET

#endif  //_WAITSET_H
