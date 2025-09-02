/**
 * @file:       DomainParticipantQos.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DomainParticipantQos_h__
#define DomainParticipantQos_h__

#include "UserDataQosPolicy.h"
#include "EntityFactoryQosPolicy.h"
#include "ReceiverThreadConfigQosPolicy.h"
#include "TransportConfigQosPolicy.h"
#include "ThreadCoreAffinityQosPolicy.h"
#include "DiscoveryConfigQosPolicy.h"
#include "DDSMsgStatisticsInfoQosPolicy.h"
#include "RapidIOControllerQosPolicy.h"
#include "PropertyQosPolicy.h"
#ifdef _ZRDDS_INCLUDE_GATEWAY
#include "GatewayQosPolicy.h"
#endif // _ZRDDS_INCLUDE_GATEWAY

/**
 * @struct DDS_DomainParticipantQos
 *
 * @ingroup CoreQosStruct
 *
 * @brief   定义域参与者的QoS配置。
 */

typedef struct DDS_DomainParticipantQos
{
#ifdef _ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   域参与者携带信息配置。 */
    DDS_UserDataQosPolicy user_data;
#endif //_ZRDDS_INCLUDE_USER_DATA_QOS
    /** @brief   实体工厂配置。 */
    DDS_EntityFactoryQosPolicy entity_factory;
    /** @brief   接收线程数量配置。  */
    DDS_ReceiverThreadConfigQosPolicy receiver_thread_config;
    /**   
     * @brief   RTPX报文的目的地址配置。 
     *
     * @details 由于ZRDDS在不同域进行端口隔离，对于想要在运行时获取DDS系统中的所有可能的域的信息的应用程序（例如：监控类应用）
     *          需要打破这种隔离，ZRDDS使用RTPX报文完成该功能，ZRDDS在外发布自身域参与者信息时，同时向 #domain_destination_addresses
     *          地址列表中发布RTPX报文，接收端收到RTPX报文时，会调用 DDS::DomainParticipantListener::on_domain_received 
     *          方法通知用户有某个域下的数据到达，默认为udpv4://239.255.0.1//7400，
     *          即组播地址为239.255.0.1，端口通过RTPS协议计算。 
     */
    DDS_TransportConfigQosPolicy domain_destination_addresses;
    /**   
     * @brief   RTPX报文的监听地址。 
     *          
     * @details 一般监控类应用设置该地址来动态发现DDS系统中的不同域，默认为udpv4://239.255.0.1//7400，
     *          即组播地址为239.255.0.1，端口通过RTPS协议计算。 
     */
    DDS_TransportConfigQosPolicy domain_receive_addresses;
    /** @brief  SPDP协议的源地址列表。
    *
    * @details 默认为udpv4://default//0，即所有地址都发组播，端口由系统自动分配。
    */
    DDS_TransportConfigQosPolicy pdp_send_addresses;
    /** @brief  SPDP协议的目的地址列表。  
     * 
     * @details 默认为udpv4://239.255.0.1//0，即组播地址为239.255.0.1，端口通过RTPS协议计算。 
     */
    DDS_TransportConfigQosPolicy pdp_destination_addresses;
    /**   
     * @brief   SPDP协议的监听地址列表。
     *  
     * @details 默认为udpv4://239.255.0.1//0，即组播地址为239.255.0.1，端口通过RTPS协议计算。 
     */
    DDS_TransportConfigQosPolicy pdp_receive_addresses;
    /**   
     * @brief   内置发现协议SEDP使用的地址监听列表。
     *          
     * @details 默认为udpv4://default//0，即本机地址，端口通过RTPS协议计算。 
     */
    DDS_TransportConfigQosPolicy metatraffic_receive_addresses;
    /**   
     * @brief   用户数据使用的地址监听列表。
     *           
     * @details 默认为udpv4://default//0，即本机地址，端口通过RTPS协议计算。 
     */
    DDS_TransportConfigQosPolicy usertraffic_receive_addresses;
    /** @brief   DDS线程/任务依附性设置。 */
    DDS_ThreadCoreAffinityQosPolicy thread_core_affinity;
    /** @brief   SPDP发现配置。 */
    DDS_DiscoveryConfigQosPolicy discovery_config;
#ifdef _ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
    /** @brief   配置报文统计信息。 */
    DDS_MsgStatisticsInfoQosPolicy message_staticstics_info_config;
#endif //_ZRDDS_INCLUDE_MSGSTATISTICSINFO_QOS
    /**   
     * @brief   配置RTPS报文的端序，true表示小端（默认），false表示大端。 
     * 
     * @note    建议在大端环境中设置成false，以提供序列化以及反序列化的性能，不可变。 
     */
    DDS_Boolean rtps_message_little_endian;
#ifdef _ZRDDS_RIO
    /** @brief The rapidio controller */
    DDS_RapidIOControllerQosPolicy rapidio_controller;
#endif /* _ZRDDS_RIO */
    /** @brief   该实体的属性列表。 */
    DDS_PropertyQosPolicy property;
#ifdef _ZRDDS_INCLUDE_GATEWAY
    /** @brief   对路由服务的配置。 */
    DDS_GatewayQosPolicy gateway;
#endif // _ZRDDS_INCLUDE_GATEWAY
}DDS_DomainParticipantQos;

#endif /* DomainParticipantQos_h__*/
