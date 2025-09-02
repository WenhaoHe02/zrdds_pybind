/**
 * @file:       ReceiverThreadConfigQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ReceiverThreadConfig_h__
#define ReceiverThreadConfig_h__

/**
 * @enum DDS_ReceiverThreadKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   配置域参与者下接收线程策略。
 *
 * @details 接收线程用于ZRDDS从协议栈接收数据并处理。接收线程从协议栈获取到原始数据后，需要对原始数据进行反序列化和分发。
 *          从协议栈中获取到的数据包括内置发现报文和用户的数据报文，两者使用不同的端口，为避免DDS内置数据影响用户数据报文的处理，
 *          ZRDDS利用该QoS向用户提供配置接收线程模型的能力。在典型情况下，ZRDDS需监听如下几类端口：
 *          1. 接收内置组播数据包；  
 *          2. 接收内部单播数据包；  
 *          3. 接收用户单播数据包；
 */

typedef enum DDS_ReceiverThreadKind
{
    /**   
     * @brief  每个端口一个接收线程。 
     *
     * @ingroup CoreQosStruct
     *          
     * @details 默认类型，域参与者中配置的每个端口均使用单独的线程监听并处理，默认情况下为 总接收线程数 = 用户有效IP数量 * 3。
     */
    DDS_THREAD_PER_PORT,

    /**   
     * @brief  每个类型一个接收线程，内置的一个线程，用户的一个线程。
     *
     * @ingroup CoreQosStruct
     *          
     * @details 域参与者中配置的每类端口使用单独的线程监听并处理，默认情况下 总接收线程数 = 2。
     */
    DDS_THREAD_PER_KIND,

    /**   
     * @brief  所有的端口都使用一个线程。 
     *
     * @ingroup CoreQosStruct
     *          
     * @details 域参与者中配置的所有端口使用单独的线程监听并处理，默认情况下 总接收线程数 = 1。
     */
    DDS_THREAD_ALL_PORTS 
}DDS_ReceiverThreadKind;

/**
 * @struct DDS_ReceiverThreadConfigQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   域参与者的接收线程配置。
 *
 * @details 该QoS用于配置域参与者的接收线程，receive_buffer_length默认为0，表示接收缓存区大小由使用协议的最大分片大小确定，大于0时则由该成员控制所有协议下的接收缓冲区大小。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #kind | DDS_THREAD_ALL_PORTS | 无 | 无 | 无 | 不可变
 *          #receive_buffer_length | 0 | 无 | 无 | 无 | 不可变
 */

typedef struct DDS_ReceiverThreadConfigQosPolicy
{
    /** @brief   接收线程的类型。 */
    DDS_ReceiverThreadKind kind;
    /** @brief   配置接收缓冲区。 */
    DDS_Long receive_buffer_length;
#ifdef _LINUX
    /** @brief   是否选用select多路复用模式，设置为false代表使用epoll模式。 */
    DDS_Boolean use_select;
#endif // _LINUX
}DDS_ReceiverThreadConfigQosPolicy;

#endif /* ReceiverThreadConfig_h__ */
