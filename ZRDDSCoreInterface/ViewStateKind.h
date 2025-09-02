/**
 * @file:       ViewStateKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ViewStateKind_h__
#define ViewStateKind_h__

/**
 * @typedef enum DDS_ViewStateKind
 *
 * @ingroup  CoreBaseStruct
 *
 * @brief   此枚举变量列举出了数据实例的视图状态，与 DDS_ViewStateMask 结合使用。
 *
 * @details  视图状态是数据读者为数据类型中的每个数据实例关联的一个状态信息，通过 DDS_SampleInfo::view_state 
 *           返回给用户。此状态信息会随着数据读者对该数据实例的数据以及该实例的生命周期变化而改变。
 */

typedef enum DDS_ViewStateKind
{
    /**
     * @brief   此状态表示数据读者尚未访问过此数据实例下的数据样本或这个数据实例发生了再现（从NOT_ALIVE状态重新变为ALIVE状态）。
     *
     * @ingroup CoreBaseStruct
     */
    DDS_NEW_VIEW_STATE = 0x0001 << 0,
    /**   
     * @brief   此状态表示数据读者访问过此实例的数据（且此实例未发生再现）。 
     *
     * @ingroup CoreBaseStruct
     */
     DDS_NOT_NEW_VIEW_STATE = 0x0001 << 1
}DDS_ViewStateKind;

#endif /* ViewStateKind_h__*/
