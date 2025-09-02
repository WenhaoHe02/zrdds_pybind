/**
 * @file:       SampleInfo.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SampleInfo_h__
#define SampleInfo_h__

#include "SampleStateKind.h"
#include "ViewStateKind.h"
#include "InstanceStateKind.h"
#include "Duration_t.h"
#include "InstanceHandle_t.h"
#include "ZRSequence.h"
#include "SequenceNumber_t.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_SampleInfo
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   数据读者为每一个接收到的数据维护的样本信息。
 * 
 * @details 此信息会在使用 DataReader::read/take 获取数据时与取出的样本样本一同提供给用户。
 */

typedef struct DDS_SampleInfo
{
    /** @brief  数据关联的样本状态。*/
    DDS_SampleStateKind sample_state;
    /** @brief  数据关联的视图状态。 */
    DDS_ViewStateKind view_state;
    /** @brief  数据关联的实例状态。 */
    DDS_InstanceStateKind instance_state;
    /** @brief  数据的源时间戳。 */
    DDS_Time_t source_timestamp;
    /** @brief  数据在发布端的序列号。 */
    DDS_SequenceNumber_t write_sequence_number;
    /** @brief  数据所属的数据实例的唯一标识。 */
    DDS_InstanceHandle_t instance_handle;
    /** @brief  发送此数据的数据写者的唯一标识。 */
    DDS_InstanceHandle_t publication_handle;
    /** @brief  数据所属的数据实例状态从 #DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE 变成 #DDS_ALIVE_INSTANCE_STATE 的次数。 */
    DDS_ULong disposed_generation_count;
    /** @brief  数据所属的数据实例状态从 #DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE 变成 #DDS_ALIVE_INSTANCE_STATE 的次数。 */
    DDS_ULong no_writers_generation_count;
    /**
     * @brief   在 DataReader::read/take 系列方法返回的序列中的同一实例的数据中，此数据后面的数据的个数。
     */
    DDS_ULong sample_rank;
    /**
     * @brief   在 DataReader::read/take 系列方法返回的序列中的同一实例的数据中，
     *          最新的数据（MRSIC）与此数据的代数（generation）差。
     */
    DDS_ULong generation_rank;
    /**
     * @brief   在同一实例的数据（不需要属于同一返回序列）中，
     *          最新的数据（MRS）与此数据的代数（generation）差。
     */
    DDS_ULong absolute_generation_rank;
    /**   
     * @brief   此值为true表示为数据样本，即该样本信息对应的数据样本有效。 
     *
     * @warning 用户在遍历数据样本序列时，使用数据样本之前，需要判定 valid_data == true 。
     */
    DDS_Boolean valid_data;
    /** @brief  数据所属Locator。 */
    void *recive_locator;
    /** @brief  接收队列号。 */
    DDS_ULong recive_order;
    DDS_Boolean is_batch_end;
}DDS_SampleInfo;

/**
 * @struct DDS_SampleInfoValidMember
 *
 * @brief   用于表示 DDS_SampleInfo 中的成员是否有效，用于XML接口中。
 */

typedef struct DDS_SampleInfoValidMember
{
    DDS_Boolean source_timestamp;
    DDS_Boolean valid_data;
    DDS_Boolean instance_handle;
    DDS_Boolean instance_state;
    DDS_Boolean sample_state;
    DDS_Boolean view_state;
}DDS_SampleInfoValidMember;

/**
 * @struct DDS_SampleInfoSeq 
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   声明 DDS_SampleInfoSeq 的序列类型，参见 #DDS_USER_SEQUENCE_CPP 。
 */

DDS_SEQUENCE_CPP(DDS_SampleInfoSeq, DDS_SampleInfo);

#ifdef __cplusplus
}
#endif

#endif /* SampleInfo_h__*/
