/**
 * @file:       ZRPSSystemInterface.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(ZRPSSYSTEMZR_INT32ERFACE_H)
#define ZRPSSYSTEMZR_INT32ERFACE_H

#include "OsResource.h"
#include "ZRDDSCommon.h"

#ifdef _ZRDDS_INCLUDE_PSINTERFACE

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @typedef void(*ZRPSCALLBACKFUN)( const DDS_Char* topicName, const DDS_Long topicNo, void* buffer, DDS_Long len)
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   订阅端回调函数，参数如下： 
 *          - topicName: 数据所属主题名称   
 *          - topicNo: 数据所属主题号   
 *          - buffer: 接收到的数据内容   
 *          - len: 接收到的数据长度。
 */

typedef void(*ZRPSCALLBACKFUN)(
    const DDS_Char* topicName,
    const DDS_Long topicNo,
    void* buffer,
    DDS_Long len);

/**
 * @typedef void(*ZRPSBUILTINCALLBACKFUN)( const DDS_Char* topicName, DDS_Long entityState, DDS_Long entityKind, const DDS_Char* entityId)
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   发现回调函数，参数如下：
 *          - topicName: 数据所属主题名称，当表示为NULL时表示发现的为域参与者；
 *          - entityState: 该实体的状态，1表示上线，0表示下线；
 *          - entityKind: 实体的类型a:  
 *              - 0表示域参与者；  
 *              - 1表示数据写者；  
 *              - 2表示订阅者；  
 *          - entityId: 该实体的唯一标识的字符串。
 */

typedef void(*ZRPSBUILTINCALLBACKFUN)(
    const DDS_Char* topicName,
    DDS_Long entityState,
    DDS_Long entityKind,
    const DDS_Char* entityId);

/**
 * @fn  DCPSDLL const DDS_Char* ZRPSInterface_GetEntityId( const DDS_Char* topicName, DDS_Long entityKind);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   获取指定主题名关联的数据写者或者数据读者的接口。
 *
 * @param   topicName   主题名称.
 * @param   entityKind  1表示数据写者，2表示数据读者。
 *
 * @return  NULL表示查找失败，否则返回对应的唯一标识的字符串。
 */

DCPSDLL const DDS_Char* ZRPSInterface_GetEntityId(
    const DDS_Char* topicName,
    DDS_Long entityKind);

/**
 * @fn  DCPSDLL void ZRPSInterface_Init(DDS_ULong domain_id);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   初始化接口，在使用该接口之前调用。
 *
 * @param   domain_id   所属域。
 */

DCPSDLL void ZRPSInterface_Init(DDS_ULong domain_id);

/**
 * @fn  DCPSDLL void ZRPSInterface_SetBuiltinCallBack( ZRPSBUILTINCALLBACKFUN callback);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   注册发现接口.
 *
 * @param   callback    发现接口函数.
 */

DCPSDLL void ZRPSInterface_SetBuiltinCallBack(
    ZRPSBUILTINCALLBACKFUN callback);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_Publish( const DDS_Char* topicName);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   向中间件注册与某个主题相关的发布者。
 *
 * @param   topicName   该发布者关联的主题名。
 *
 * @return  中间件返回的主题号。
 */

DCPSDLL DDS_Long ZRPSInterface_Publish(
    const DDS_Char* topicName);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_Publish_WConfig( const DDS_Char* topicName, DDS_Boolean strongReliable);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   向中间件注册与某个主题相关的发布者，并携带可靠性配置。
 *
 * @param   topicName   该发布者关联的主题名。
 * @param   strongReliable  是否具备强可靠配置。
 *
 * @return  中间件返回的主题号。
 */

DCPSDLL DDS_Long ZRPSInterface_Publish_WConfig(
    const DDS_Char* topicName,
    DDS_Boolean strongReliable);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_UnPublish( const DDS_Long topicNo);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   向中间件注销某个主题的发布者。
 *
 * @param   topicNo 与该发布者关联的主题号。
 *
 * @return  成功返回0，否则返回-1。
 */

DCPSDLL DDS_Long ZRPSInterface_UnPublish(
    const DDS_Long topicNo);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_SendData( void* buffer, DDS_Long len, const DDS_Long topicNo);
 *
 * @ingroup  CoreBaseFunction
 *
 * @brief   发布者发布消息。
 *
 * @param [in,out]  buffer  数据内容。
 * @param   len             数据长度。
 * @param   topicNo         发布数据关联的主题号。
 *
 * @return  成功返回0，否则返回-1。
 */

DCPSDLL DDS_Long ZRPSInterface_SendData(
    void* buffer, 
    DDS_Long len,
    const DDS_Long topicNo);

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_Subscribe( const DDS_Char* topicName, ZRPSCALLBACKFUN callBackFun, DDS_Boolean reliable = true);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   向中间件注册与某个主题相关的订阅者。
 *
 * @param   topicName   该订阅者关联的主题名。
 * @param   callBackFun 订阅者接收回调函数。
 * @param   reliable    该主题是否需要可靠（可能导致发布端阻塞），默认为可靠。
 *
 * @return  中间件返回的主题号。
 */

DCPSDLL DDS_Long ZRPSInterface_Subscribe(
    const DDS_Char* topicName,
    ZRPSCALLBACKFUN callBackFun, 
    DDS_Boolean reliable
#ifdef __cplusplus
    = true
#endif
    );

/**
 * @fn  DCPSDLL DDS_Long ZRPSInterface_UnSubscribe( DDS_Long topicNo);
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   向中间件注销某个主题的订阅者。
 *
 * @param   topicNo 与该订阅者关联的主题号。
 *
 * @return  成功返回0，否则返回-1。
 */

DCPSDLL DDS_Long ZRPSInterface_UnSubscribe(
    DDS_Long topicNo);

/**
 * @fn  DCPSDLL void ZRPSInterface_Destory();
 *
 * @ingroup CoreBaseFunction   
 *
 * @brief   注销接口，不再使用ZRPSSystemInterface接口时，调用释放资源。
 */

DCPSDLL void ZRPSInterface_Destory();

#ifdef __cplusplus
}
#endif

#endif /*_ZRDDS_INCLUDE_PSINTERFACE*/

#endif
