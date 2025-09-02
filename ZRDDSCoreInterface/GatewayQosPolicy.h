/**
* @file:       GatewayQosPolicy.h
*
* copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
*/

#ifndef GatewayQosPolicy_h__
#define GatewayQosPolicy_h__

#include "ZROSDefine.h"
#ifdef _ZRDDS_INCLUDE_GATEWAY
#include "OsResource.h"
#include "TransportConfigQosPolicy.h"

/**
 * @enum DDS_GatewayQosPolicyKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   网关服务类型。
 */

typedef enum DDS_GatewayQosPolicyKind
{
    /**
     * @brief   无需子网网关参与转发。
     *
     * @ingroup CoreQosStruct
     *
     * @details 该类型为默认类型。默认情况下，实体之间通过组播Data(P)来完成互相发现，后续收发动作通过点对点单播。
     *          当不同子网间组播、单播均能够联通时，网关服务类型采用此默认值即可。
     */
    DDS_NO_FORWARD_GATEWAY_QOS,

    /**
     * @brief   仅需要子网网关将Data(p)转发给已知的同一域号下的其它域参与者。
     *
     * @ingroup CoreQosStruct
     *
     * @details 实际情况下，可能存在在不同子网之间无法使用组播、仅能够使用单播互通的网络环境。
     *          此时，可在网络中部署网关服务，并将域参与者的网关服务类型设置为DDS_SPDP_FORWARD_GATEWAY_QOS，由网关来协助实体之间交换Data(P)并完成匹配。
     *          后续的收发动作中仍可采用默认模式，以点对点单播的方式进行。
     */
    DDS_SPDP_FORWARD_GATEWAY_QOS,

    /**
     * @brief   需要子网网关协助打洞通信。
     *
     * @ingroup CoreQosStruct
     *
     * @warning 该类型未实现。
     */
    DDS_SEDP_FORWARD_GATEWAY_QOS,

    /**
     * @brief   需要子网网关转发所有的数据（包括内置数据以及用户数据）。
     *
     * @ingroup CoreQosStruct
     *
     * @details 实际情况下，可能存在在不同子网之间无法使用组播、也无法使用单播互通的网络环境。
     *          此时，可在不同子网中分别部署网关服务，且网关服务之间需要相互连接，
     *          并将域参与者的网关服务类型设置为DDS_USER_FORWARD_GATEWAY_QOS，由网关来协助实体之间的互相发现、匹配及后续的数据收发动作。
     */
    DDS_USER_FORWARD_GATEWAY_QOS,

    /**
     * @brief   需要子网网关转发目的地为其他子网的所有的数据（包括内置数据以及用户数据），不转发目的地为同一个子网下的数据。
     *
     * @ingroup CoreQosStruct
     *
     * @warning 该类型未实现。
     */
    DDS_USER_FORWARD_ONLY_GATEWAY_QOS
}DDS_GatewayQosPolicyKind;

/**
 * @struct DDS_GatewayQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   子网网关配置策略。
 *
 * @details 在默认的DDS通信过程中，节点与节点之间均通过组播互相发现，进而完成后续的数据收发动作。
 *          然而，在网络环境较为复杂的情况下，比如跨广域网、多子网的情况下，
 *          无法保证所有子网都支持组播发现，也无法保证所有节点均能够互相连通。
 *          因此，提供子网网关的功能，引入了子网网关服务以及GatewayQosPolicy，
 *          用于解决由于网络环境情况复杂导致的无法发现、数据收发问题。
 *          使用该网关服务时，除了设置该QoS以外，还需要将网关服务地址填入域参与者QoS的pdp_destination_addresses。
 *          同时，建议清除域参与者QoS的domain_destination_addresses。
 *
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | ::DDS_NO_FORWARD_GATEWAY_QOS | 数据写者.#kind == 数据读者.#kind | 无 | 无 | 不可变
 */
typedef struct DDS_GatewayQosPolicy
{
    /** @brief   指明该域参与者所使用的网关服务类型，参见@ref DDS_GatewayQosPolicyKind 。 */
    DDS_GatewayQosPolicyKind kind;

    /**
     * @brief   指明中继服务器地址。 
     *
     * @warning 相关功能未实现。
     */
    DDS_TransportConfigQosPolicy relay_addresses;
}DDS_GatewayQosPolicy;

#endif // _ZRDDS_INCLUDE_GATEWAY

#endif /* GatewayQosPolicy_h__*/