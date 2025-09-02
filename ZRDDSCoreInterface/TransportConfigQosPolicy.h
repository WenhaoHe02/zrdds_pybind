/**
 * @file:       TransportConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TransportConfigQosPolicy_h__
#define TransportConfigQosPolicy_h__

#include "ZRBuiltinTypes.h"

/**
 * @struct DDS_TransportConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   传输方式配置。
 *
 * @details 配置底层的传输方式，不同类型地址具有不同的默认值，配置的地址字符串格式：type://address//port，当前
 *          允许在域参与者级别或者直接在数据写者以及数据读者上配置地址，均表示监听数据的地址，该配置的默认值由其含义决定，可变性为不可变。
 *          ZRDDS当前可配置的地址方式参见下表，通常使用该QoS来配置用户数据传输的地址，内置数据则不提供配置：
 *          类型 | type | address | port | 举例
 *          --- | --- | --- | --- | ---
 *          UDP | udpv4 | default: RTPS中默认的地址，即本机所有有效的IP地址；形如a.b.c.d的点十制IPv4地址 | 0:表示通过域以及域参与者ID计算出来的端口；1 - 65535指定端口 | udpv4://default//0，表示使用默认地址，udpv4://192.168.150.54//7655，指定端口
 *          TCP | tcpv4 | default: RTPS中默认的地址，即本机所有有效的IP地址；形如a.b.c.d的点十制IPv4地址 | 0:表示通过域以及域参与者ID计算出来的端口；1 - 65535指定端口 | tcpv4://default//0，表示使用默认地址，但使用TCP代替默认的UDP，tcpv4://192.168.150.54//7655，指定端口
 *          不运行RTPS的UDP协议 | udpv4_raw | default: RTPS中默认的地址，即本机所有有效的IP地址；形如a.b.c.d的点十制IPv4地址 | 0:表示通过域以及域参与者ID计算出来的端口；1 - 65535指定端口 | udpv4_raw://192.168.150.54//7655，指定端口
 *          不运行RTPS的TCP协议 | tcpv4_raw | default: RTPS中默认的地址，即本机所有有效的IP地址；形如a.b.c.d的点十制IPv4地址 | 0:表示通过域以及域参与者ID计算出来的端口；1 - 65535指定端口 | tcpv4_raw://192.168.150.54//7655，指定端口
 *          共享内存 | shmem | 该字段无效 | 该字段表示共享内存的大小 | shmem://default//16777216：表示16MB大小的共享内存
 *          RapidIO总线 | rapidio | 该字段无效 | 0:使用自动分配的虚拟端口；1 - 65535指定虚拟端口。虚拟端口只用于逻辑上区分数据到达的目的地，建议使用自动分配的方式配置，避免出现冲突 | rapidio://0//0，表示使用RapidIO且自动分配虚拟端口，rapidio://0//64，指定RapidIO虚拟端口为64
 *          PCIE总线 | pcie | 该字段无效 | 0:使用自动分配的虚拟端口；1 - 65535指定虚拟端口。虚拟端口只用于逻辑上区分数据到达的目的地，建议使用自动分配的方式配置，避免出现冲突 | pcie://0//0，表示使用PCIE且自动分配虚拟端口，pcie://0//64，指定PCIE虚拟端口为64
 *          DPDK | dpdk-ans | default: RTPS中默认的地址，即本机所有有效的IP地址；形如a.b.c.d的点十制IPv4地址 | 0:表示通过域以及域参与者ID计算出来的端口；1 - 65535指定端口 | dpdk-ans://default//0，表示使用默认地址，dpdk-ans://192.168.150.54//7655，指定端口
 *
 *          其中，udpv4类型address字段配置成组播地址时，将监听组播，远程实体向本地发送数据时，也是向配置的组播中发送数据，典型的组播地址配置如：udpv4://239.255.0.2//0
 *          udpv4以及tcpv4的address字段配置为网络地址时（以一个或多个0结尾，例如：192.168.1.0），DDS将自动选取本机属于该子网地址的IP地址进行通信。
 *          由于地址中未配置子网掩码，DDS将逐字节比较非0的地址字节（字节为0的认为相同），如192.168.1.3属于子网192.168.1.0，192.168.5.5不属于子网192.168.1.0.
 *
 *          说明：不运行RTPS的协议，通常用于需要及其高速的数据传输速率的情况下，此时ZRDDS仅运行发现协议，进行主题匹配，
 *          主题的数据传输不在底层做处理（序列化、队列维持、QoS配置等），直接与网络交互，而ZRDDS当前使用RDMA进行传输的
 *          方式依赖于Mellanox公司的VMA技术，在运行ZRDDS程序前，加上```LD_PRELOAD=libvma.so```命令加载VMA库使用正常的以太网配置，即可使用RDMA传输。
 *          40G以太网的配置与千兆的配置相同，底层使用何种速度的网络通信，取决的address段指向的接口速度。
 *          当前的DPDK通信依赖于DPDK-ANS客户端转发，使用DPDK通信的前提为网卡支持DPDK，并且已经正确以KNI模式启动DPDK-ANS客户端。
 *
 * @note    该QoS在作为 DomainParticipantQoS 成员时，使用 0 表示自动计算端口，在作为 DataWriterQoS 以及DataReaderQoS 成员时 0 为非法端口，使用65536表示不关心端口，由系统自动分配。
 */

typedef struct DDS_TransportConfigQosPolicy
{
    /** @brief   配置的地址字符串格式： */
    DDS_StringSeq addresses;
}DDS_TransportConfigQosPolicy;

#endif /* TransportConfigQosPolicy_h__ */
