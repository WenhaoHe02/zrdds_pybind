#ifndef ZRDDSInteractiveCMD_h__
#define ZRDDSInteractiveCMD_h__

/**
 * @typedef struct ZRDDSInteractiveCmdReqID
 *
 * @brief   用于标识命令的目的端。
 */

typedef struct ZRDDSInteractiveCmdReqID
{
    /** @brief   标识节点。 */
    DDS_Long hostId;
    /** @brief   标识应用。 */
    DDS_Long appId;
    /** @brief   标识序列号。 */
    DDS_Long seq;
} ZRDDSInteractiveCmdReqID; // @Extensibility(EXTENSIBLE)

/**
 * @typedef enum ZRDDSInteractiveCmdKind
 *
 * @brief   区分不同命令的类型。
 */

typedef enum ZRDDSInteractiveCmdKind
{
    ZRDDS_SET_LOG_ENABLE_RANGE = 0,
    ZRDDS_SET_LOG_DISABLE_RANGE = 1,
    ZRDDS_SET_LOG_ENABLE_TOPIC = 2,
    ZRDDS_SET_LOG_DISABLE_TOPIC = 3,
    ZRDDS_SET_LOG_ENABLE_ENTITYID = 4,
    ZRDDS_SET_LOG_DISABLE_ENTITYID = 5,
    ZRDDS_SET_LOG_MASK = 6,
    ZRDDS_GET_VARIABLE_VALUE = 7,
    ZRDDS_SET_LOG_STYLE = 8
} ZRDDSInteractiveCmdKind;// @BitBound(32)
/**
 * @typedef struct ZRDDSInteractiveCMD
 *
 * @brief   定义外部请求DDS执行的命令。
 *
 * @details 当前支持的命令名称以及参数参数下表。
 *          
 *          类型 | 名称 | 参数
 *          --- | --- | ---
 *          0 | zrdds.set.log.enable.range | 0,2
 *          1 | zrdds.set.log.disable.range | 0,2
 *          2 | zrdds.set.log.enable.topic | topic_name
 *          3 | zrdds.set.log.disable.topic | topic_name
 *          4 | zrdds.set.log.enable.entity_id | c0a80000 00000000 00000000 00000000
 *          5 | zrdds.set.log.disable.entity_id | c0a80000 00000000 00000000 00000000
 *          6 | zrdds.set.log.mask | 0xffff(console) 0xfffff(file) 0xfffff(dist) 
 *          7 | zrdds.get.variable.value | %s(全局变量名称):(offset(相对于当前地址的偏移量)*size(读取内存的大小，小于0有特殊含义。-1 为上一步读取结果的解引用，-2 为上一步地址加上offset（不再读取内存）))+  
 *          8 | zrdds.set.log.style  |  与ZRLogDisplayStyle中的值相对应
 */

typedef struct ZRDDSInteractiveCMD
{
    /** @brief   命令ID。 */
    ZRDDSInteractiveCmdReqID cmdId;
    /** @brief   命令类型。*/
    ZRDDSInteractiveCmdKind cmdKind;
    /** @brief   命令参数。 */
    char cmdParameter[1024];
}ZRDDSInteractiveCMD;

/**
 * @typedef struct ZRDDSInteractiveResponse
 *
 * @brief   命令执行结果。
 */

typedef struct ZRDDSInteractiveResponse
{
    /** @brief   该响应关联的请求标识。 */
    ZRDDSInteractiveCmdReqID cmdId;
    /** @brief   命令执行结果。 */
    ZR_UINT32 ret;
    /** @brief   详细信息。 */
    DDS_Char response[1074];
} ZRDDSInteractiveResponse;

#endif // ZRDDSInteractiveCMD_h__
