/**
* @file:       PublicationSendStatus.h
*
* copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
*/

#ifndef PublicationSendStatus_h__
#define PublicationSendStatus_h__

#include "InstanceHandle_t.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @enum DDS_TransportKind
 *
 * @ingroup CoreBaseStructTransportKind
 *
 * @brief   用于标识通信使用的传输方式。
 */

typedef enum DDS_TransportKind
{
    /** @brief  保留的Locator_t类型。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_RESERVED = 0,
    /** @brief  使用IPv4的UDP传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_UDPv4 = 1,
    /** @brief  使用IPv6的UDP传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_UDPv6 = 2,
    /** @brief   使用IPv4的TCP传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4 = 8,
    /** @brief   使用IPv6的TCP传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv6 = 16,
    /** @brief  使用无RTPS协议的UDP传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_UDPv4_RAW = 32,
    /** @brief  使用无RTPS协议的TCP传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4_RAW = 64,
    /** @brief   使用IPv4的TCP多核传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4_CC = 128,
    /** @brief   使用IPv4的TCP多网卡传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_TCPv4_MC = 256,
    /** @brief   使用共享内存的传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_SHMEM = 16777216,
    /** @brief   使用RapidIO的传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_RAPIDIO = 100,
    /** @brief   使用PCI-E的传输方式。 @ingroup CoreBaseStructTransportKind */
    DDS_TRANSPORT_KIND_PCIE,
#ifdef _ZRDDS_INCLUDE_DPDK_ANS
    DDS_TRANSPORT_KIND_DPDK_ANS_UDPv4,
#endif //_ZRDDS_INCLUDE_DPDK_ANS
}DDS_TransportKind;

/**
 * @enum DDS_LocatorStatusKind
 *
 * @ingroup CoreBaseStructLocatorStatusKind
 *
 * @brief   用于标识当前连接的通信状态。
 */

typedef enum DDS_LocatorStatusKind
{
    /** @brief   当前连接未使用。 @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_NOT_VALID,
    /** @brief   当前连接未发过数据。 @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_WATING_SEND,
    /** @brief   当前连接正常通信，发过数据。 @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_SENDED,
    /** @brief   当前连接通信异常。 @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_ERROR,
    /** @brief   当前连接正在重连。 @ingroup CoreBaseStructLocatorStatusKind */
    DDS_LOCATOR_STATUS_RECONNECTING,
}DDS_LocatorStatusKind;

/**
 * @struct DDS_PublicationSendLocator
 *
 * @ingroup CoreBaseStruct
 *
 * @brief    数据写者与数据读者通信使用的连接信息。
 */

typedef struct DDS_PublicationSendLocator
{
    /** @brief   当前连接使用的传输方式。 */
    DDS_TransportKind locator_type;
    /** @brief   当前连接传输数据的目的地址。 */
    DDS_Octet locator_addr[4];
    /** @brief   当前连接传输数据的目的端口。 */
    DDS_ULong locator_port;
    /** @brief   当前连接的通信状态。 */
    DDS_LocatorStatusKind locator_status;
    /** @brief   当前连接最新的传输返回值。 */
    DDS_Long locator_return_code;
}DDS_PublicationSendLocator;

/**
 * @struct DDS_PublicationSendLocatorSeq
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   声明 DDS_PublicationSendLocator 的序列类型，参见 #DDS_USER_SEQUENCE_CPP 。
 */
DDS_SEQUENCE_CPP(DDS_PublicationSendLocatorSeq, DDS_PublicationSendLocator);

/**
 * @struct DDS_PublicationSendStatus
 *
 * @ingroup CoreBaseStruct
 *
 * @brief    数据写者的发送状态。
 */

typedef struct DDS_PublicationSendStatus
{
    /** @brief   与当前数据写者通信的数据读者的唯一标识。 */
    DDS_InstanceHandle_t subscription_handle;
    /** @brief   与该数据读者的所有通信连接信息。 */
    DDS_PublicationSendLocatorSeq send_locators;
}DDS_PublicationSendStatus;

/**
 * @struct DDS_PublicationSendStatusSeq
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   声明 DDS_PublicationSendStatus 的序列类型，参见 #DDS_USER_SEQUENCE_CPP 。
 */
DDS_SEQUENCE_CPP(DDS_PublicationSendStatusSeq, DDS_PublicationSendStatus);

#ifdef __cplusplus
}
#endif

#endif /* PublicationSendStatus_h__*/
