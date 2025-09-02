/**
 * @file:       SampleStateKind.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SampleStateKind_h__
#define SampleStateKind_h__

/**
 * @enum DDS_SampleStateKind
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   该类型表示数据样本的被读取状态。
 *
 * @details  数据样本被读取状态是数据读者为底层保存的数据维护的一个状态信息，表明该样本是否被用户通过 
 *           DataReader::read 系列方法获取访问成功过。当用户 调用 DataReader::return_loan 方法归还数据样本时，
 *           数据变为 #DDS_READ_SAMPLE_STATE 状态。
 */

typedef enum DDS_SampleStateKind
{
    /**
     * @brief  该数据样本已经被用户访问过。
     *
     * @ingroup CoreBaseStruct
     *
     * @details 表示用户曾通过 DataReader::read 系列方法访问过此样本并且已经通过 DataReader::return_loan 方法归还。
     */
     
    DDS_READ_SAMPLE_STATE = 0x0001 << 0,

    /**
     * @brief  该数据样本未被用户访问过。
     *
     * @ingroup CoreBaseStruct
     *
     * @details 表示用户未曾通过 DataReader::read 系列方法访问过此样本或者还未通过 DataReader::return_loan 方法归还空间。
     */
    DDS_NOT_READ_SAMPLE_STATE = 0x0001 << 1
}DDS_SampleStateKind;

#endif /* SampleStateKind_h__*/
