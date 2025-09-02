/**
 * @file:       ReturnCode_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_RETURNCODE_T_H)
#define _RETURNCODE_T_H

/**
 * @enum    DDS_ReturnCode_t
 *
 * @ingroup CoreBaseStruct
 * 
 * @brief   ZRDDS接口的返回值类型。
 */

typedef enum DDS_ReturnCode_t
{
    /** @brief 执行成功。 @ingroup CoreBaseStruct */
    DDS_RETCODE_OK = 0,
    /** @brief 执行出错。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_ERROR = 1,
    /** @brief 不支持操作。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_UNSUPPORTED = 2,
    /** @brief 不正确的参数。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_BAD_PARAMETER = 3,
    /** @brief 调用操作的前置条件未满足。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_PRECONDITION_NOT_MET = 4,
    /** @brief 资源不够。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_OUT_OF_RESOURCES = 5,
    /** @brief 实体未使能，不能进行该操作。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_NOT_ENABLED = 6,
    /** @brief 试图修改使能后不能修改的Qos。 @ingroup CoreBaseStruct */
    DDS_RETCODE_IMMUTABLE_POLICY = 7,
    /** @brief 不一致的Qos。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_INCONSISTENT = 8,
    /** @brief 试图删除已经被删除的实体。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_ALREADY_DELETED = 9,
    /** @brief 操作超时。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_TIMEOUT = 10,
    /** @brief 在读数据的时候，没有有效的数据。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_NO_DATA = 11,
    /** @brief 非法的操作。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_ILLEGAL_OPERATION = 12,
    /** @brief 操作因安全原因被拒绝。 @ingroup CoreBaseStruct  */
    DDS_RETCODE_NOT_ALLOWED_BY_SEC = 13
}DDS_ReturnCode_t;

#endif  /*_RETURNCODE_T_H*/
