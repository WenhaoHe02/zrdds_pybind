/**
 * @file:       DDSLogQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSLogQosPolicy_h__
#define DDSLogQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @typedef enum DDS_LogBackupKind
 *
 * @ingroup CoreQosStruct
 *
 * @brief   本地日志文件的备份策略。
 */

typedef enum DDS_LogBackupKind
{
    /** @brief  默认模式。不使用日志备份功能。每次重启应用，都将覆盖原有日志。 @ingroup CoreQosStruct */
    DDS_LOG_BACKUP_NOTUSED_QOS,
    /** @brief  同名备份模式。当有同名日志时，将原有的日志备份到日志输出目录/日志文件名-时间戳。 */
    DDS_LOG_BACKUP_EXIST_FILE,
    /**
    * @brief   当前日志文件达到一定大小后将进行备份，并重新创建日志文件。
    *          选用该模式后，日志文件的名称将为“日志文件名称_创建时间.ddslog”。
    *          @ingroup CoreQosStruct
    */
    DDS_LOG_BACKUP_FILE_SIZE_QOS,
    /**
    * @brief   每隔一段时间后将进行备份，并重新创建日志文件。
    *          选用该模式后，日志文件的名称将为“日志文件名称_创建时间.ddslog”。
    *          @ingroup CoreQosStruct
    */
    DDS_LOG_BACKUP_TIME_INTERVAL_QOS,
}DDS_LogBackupKind;

/**
 * @struct DDS_LogQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   DDS的日志系统配置QoS。
 *
 * @details DDS日志系统包括本地日志以及用于DDS管理监视器的分布式日志两个子系统。
 *          - 通过配置本地日志子系统，DDS将日志输出到控制台或者与DDS程序同一目录下的日志文件（名称为:进程(任务)名称.ddslog）。 
 *          - 通过配置分布式日子系统，DDS通过内置主题的数据写者将日志发布出去，  
 *              DDS管理监控器将会收到该日志信息，并向用户展示。
 *          成员 | 默认值 | 匹配规则检查 | 有效性检查 | 兼容性检查 | 可变性检查
 *          --- | --- | --- | --- | --- | ---
 *          #console_mask | 0xffff | 无 | 无 | 无 | 不可变
 *          #file_mask | 0xffff | 无 | 无 | 无 | 不可变
 *          #local_level_mask | 0xffff | 无 | 无 | 无 | 不可变
 *          #enable_distributed_log | false | 无 | 无 | 无 | 不可变
 *          #distributed_log_writer_domain_id | 0 | 无 | 无 | 无 | 不可变
 *          #distributed_log_level_mask | 0xffff | 无 | 无 | 无 | 不可变
 *          #file_dir | NULL | 无 | 无 | 无 | 不可变
 *          #file_name | NULL | 无 | 无 | 无 | 不可变
 *          #file_backup_kind | #DDS_LOG_BACKUP_NOTUSED_QOS | 无 | 无 | 无 | 不可变
 *          #file_backup_param | 0 | 无 | 无 | 无 | 不可变
 */

typedef struct DDS_LogQosPolicy
{
    /** @brief   本地日志控制台输出级别类型掩码，为 ::DDS_LogType 枚举值按位或的结果。 */
    DDS_ULong console_mask;
    /** @brief   本地日志日志文件输出级别类型掩码，为 ::DDS_LogType 枚举值按位或的结果。 */
    DDS_ULong file_mask;
    /**
     * @brief   本地日志级别掩码。 
     * 
     * @note    该成员已被废弃，由 #console_mask 以及 #file_mask 代替。
     */
    DDS_ULong local_level_mask;
    /** @brief   控制是否使能分布式日志。 */
    DDS_Boolean enable_distributed_log;
	/** @brief   分布式日志使能结束标志。 */
    DDS_Boolean enable_distributed_log_finished;
    /** @brief   控制分布式日志主题所属域。 */
    DDS_Long distributed_log_writer_domain_id;
    /** @brief   控制分布式日志级别，为 ::DDS_LogType 枚举值按位或的结果。 */
    DDS_Long distributed_log_level_mask;
    /** @brief   指定本地日志文件的输出文件路径。如果设置为NULL，则将使用默认路径（当前运行目录）。 */
    DDS_CharSeq file_dir;
    /** @brief   指定本地日志文件的输出文件名。如果设置为NULL，则将使用默认名称（进程名称.ddslog）。 */
    DDS_CharSeq file_name;
    /** @brief   指定本地日志文件的备份模式。 */
    DDS_LogBackupKind file_backup_kind;
    /**
     * @brief   本地日志文件备份相关参数。
     *          当file_backup_kind被设置为DDS_LOG_BACKUP_NOTUSED_QOS时，该参数无效。
     *          当file_backup_kind被设置为DDS_LOG_BACKUP_FILE_SIZE_QOS时，该参数为日志文件大小上限（KB）。
     *          当file_backup_kind被设置为DDS_LOG_BACKUP_TIME_INTERVAL_QOS时，该参数为时间间隔（s）。
     */
    DDS_Long file_backup_param;

}DDS_LogQosPolicy;

#endif /* DDSLogQosPolicy_h__*/
