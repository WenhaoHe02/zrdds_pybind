/**
 * @file:       ParticipantBuiltinTopicData.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ParticipantBuiltinTopicData_h__
#define ParticipantBuiltinTopicData_h__

#include "OsResource.h"
#include "BuiltinTopicKey_t.h"
#include "UserDataQosPolicy.h"
#include "PropertyList.h"
#include "SRIOPass_t.h"
#include "ZRSequence.h"
#include "Duration_t.h"

#ifdef _ZRDDSSECURITY
#include "DDSBuiltinSecurityCommon.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @struct DDS_ParticipantBuiltinTopicData
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   用于抽象给用户呈现的远端域参与者信息。
 */

typedef struct DDS_ParticipantBuiltinTopicData
{
    /** @brief   用于唯一标识该域参与者。 */
    DDS_BuiltinTopicKey_t key;
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   该域参与者设置的 DDS_UserDataQosPolicy 。 */
    DDS_UserDataQosPolicy user_data;
#endif /* _ZRDDS_INCLUDE_USER_DATA_QOS */
    /** @brief   该域参与者所属节点的属性列表。 */
    DDS_PropertyList property_list;
#ifdef _ZRDDS_MPORT_SRIO
    /** @brief   该域参与者下rio通信所需接受窗大小。 */
    DDS_ULong recv_sub_wnd_size;
#ifdef _ZRDDS_MPORT_FPGA_SRIO
    /** @brief   该域参与者所属节点的srio的id。 */
    DDS_ULong srio_id;
    /** @brief   该域参与者所属节点的桥接表。 */
    SRIOConfigList_t configList;
#endif // _ZRDDS_MPORT_FPGA_SRIO
#endif // _ZRDDS_MPORT_SRIO
    /** @brief   该域参与者所属的域，用于RTPX协议，参见 DDS_DomainParticipantQos::domain_destination_addresses 。 */
    DDS_ULong domain_id;
#ifdef _ZRDDSSECURITY
    /** @brief 指明该Participant内置主题数据中是否包含安全相关数据。 */
    DDS_Boolean contains_security_data;
    /** @brief The identity token */
    IdentityToken identity_token;
    /** @brief The permissions token */
    PermissionsToken permissions_token;
    /** @brief Information describing the participant security */
    ParticipantSecurityInfo security_info;
#endif
    /** @brief   该域参与者创建时间。 */
    DDS_Duration_t create_time;
}DDS_ParticipantBuiltinTopicData;

/**
 * @fn  DCPSDLL void DDS_ParticipantBuiltinTopicDataInitial( DDS_ParticipantBuiltinTopicData* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   初始化 DDS_ParticipantBuiltinTopicData 对象。
 *
 * @param [in,out]  self    指名目标。
 *
 * @pre self为有效的 DDS_ParticipantBuiltinTopicData 对象。
 */

DCPSDLL void DDS_ParticipantBuiltinTopicDataInitial(
    DDS_ParticipantBuiltinTopicData* self);

/**
 * @fn  DCPSDLL void DDS_ParticipantBuiltinTopicDataDestroy( DDS_ParticipantBuiltinTopicData* self);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   清理 DDS_ParticipantBuiltinTopicData 对象空间，但不释放 DDS_ParticipantBuiltinTopicData 自身空间。
 *
 * @param [in,out]  self    指明目标。
 *
 * @pre self为有效的 DDS_ParticipantBuiltinTopicData 对象。
 */

DCPSDLL void DDS_ParticipantBuiltinTopicDataDestroy(
    DDS_ParticipantBuiltinTopicData* self);

/**
 * @fn  DCPSDLL DDS_Boolean DDS_ParticipantBuiltinTopicDataCopy( DDS_ParticipantBuiltinTopicData* dst, const DDS_ParticipantBuiltinTopicData* src);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   拷贝 DDS_ParticipantBuiltinTopicData 对象。
 *
 * @param [in,out]  dst 指明拷贝的目的对象。
 * @param   src         指明拷贝源对象。
 *
 * @return  true表示拷贝成功，false表示拷贝失败，原因可能为空间不足。
 *
 * @pre dst以及src为有效的 DDS_ParticipantBuiltinTopicData 对象。
 */

DCPSDLL DDS_Boolean DDS_ParticipantBuiltinTopicDataCopy(
    DDS_ParticipantBuiltinTopicData* dst,
    const DDS_ParticipantBuiltinTopicData* src);

/* 定义sequence结构*/
DDS_SEQUENCE_CPP(DDS_ParticipantBuiltinTopicDataSeq, DDS_ParticipantBuiltinTopicData);

#ifdef _ZRDDSSECURITY
typedef DDS_ParticipantBuiltinTopicData DDS_ParticipantBuiltinTopicDataSecure;
#endif /* _ZRDDSSECURITY */

#ifdef __cplusplus
}
#endif

#endif /* ParticipantBuiltinTopicData_h__*/
