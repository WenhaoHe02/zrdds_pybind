/**
 * @file:       InstanceStateKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef InstanceStateKind_h__
#define InstanceStateKind_h__

/**
 * @enum    DDS_InstanceStateKind
 *          
 * @ingroup CoreBaseStruct
 *
 * @brief   此枚举变量列举出一系列的实例状态，与 DDS_InstanceStateMask 结合使用。
 *          
 * @details 实例状态是数据读者为主题中的每个实例关联的一个状态信息，每个样本均包含该状态，参见
 *          DDS_SampleInfo::instance_state 。此状态信息会随着实例的生命周期发生变化而改变。
 */
typedef enum DDS_InstanceStateKind
{
    /**
     * @brief   此状态表示样本所属数据实例处于存活状态。
     *
     * @ingroup CoreBaseStruct
     *          
     * @details 当数据读者接收到了该数据实例的数据样本后，样本所属的数据实例会转变为此状态，不通知用户。
     *          样本包括两种类型：
     *          - 包含主题数据的样本，称为数据样本；  
     *          - 不包含主题数据的样本，称为状态样本，其中：  
     *              - 由 DataWriter::unregister_instance 产生注销状态样本；  
     *              - 由 DataWriter::dispose 产生销毁状态样本。
     */
    DDS_ALIVE_INSTANCE_STATE = 0x0001 << 0,

    /** @brief  此状态表示样本所属数据实例处于被销毁状态。  
     *
     * @ingroup CoreBaseStruct
     *
     * @details 当数据读者接收到了销毁状态样本时：
     *          - 如果原本为 ::DDS_ALIVE_INSTANCE_STATE 状态样本所属的数据实例会转变为此状态，并通知用户，  
     *              用户通过 DataReader::read/take 方法可以获取该事件；
     *          - 如果原本为 ::DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE 状态样本所属的数据实例会转变为此状态，不通知用户。  
     *          - 如果原本为 ::DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE 状态样本所属的数据实例状态不会改变，不通知用户。  
     */
    DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE = 0x0001 << 1,

    /** @brief  此状态表示样本所属数据实例处于被注销状态。  
     *
     * @ingroup CoreBaseStruct
     *
     * @details 当数据读者接收到了注销状态样本时：
     *          - 如果原本为 ::DDS_ALIVE_INSTANCE_STATE 并且此数据写者为最后一个与该数据实例关联的数据写者，  
     *              则状态样本所属的数据实例会转变为此状态，并通知用户， 若还有数据写者与该数据实例关联，则不改变状态，
     *              数据写者与数据实例关联是指：数据实例发布过该数据实例下的样本数据，并且最后的样本不是状态样本。 
     *          - 如果原本为 ::DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE 状态样本所属的数据实例状态不会改变，不通知用户。  
     *          - 如果原本为 ::DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE 状态样本所属的数据实例状态不会改变，不通知用户。  
     */
    DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE = 0x0001 << 2
}DDS_InstanceStateKind;

#endif /* InstanceStateKind_h__*/
