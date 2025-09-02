/**
 * @file:       DomainId_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DOMAINID_T_H)
#define _DOMAINID_T_H

#include "OsResource.h"

/**
 * @typedef DDS_ULong DDS_DomainId_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   用来表示域参与者所属域的值。
 *
 * @details  使用无符号整型来表示域参与者所属域的值，在RTPS协议下，由于端口计算方式:不能超过65536，一个域中端口不会 userPort =
 *              (7400+250*domainId+2*partId + 11)， builtinPort = (7400+250*domainId+2*partId + 10)
 *              在单独一个节点上，域的取值范围是[0, 232],其中[0, 231]域中有125个Participant，232域中有64个Participant。
 */

typedef DDS_ULong DDS_DomainId_t;

#endif  /* _DOMAINID_T_H */
