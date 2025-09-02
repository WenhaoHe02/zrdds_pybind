#ifndef ZRUserLog_h__
#define ZRUserLog_h__

#include "InstanceHandle_t.h"

#if defined(_WIN32) && defined(_ZRDDS_GENERATOR_DEBUG_INFO)
#define ZRLOG_DO_STRINGIZE(x) #x
#define ZRLOG_STRINGIZE(x) ZRLOG_DO_STRINGIZE(x)
template<const int line, const int number> 
void ZRLogWarningPrint() 
{ 
#pragma message(__FUNCSIG__) 
}
#define ZRLOG_MESSAGE_STRING(msg) "ZRLOG_INFO: " __FILE__ ": " __FUNCTION__ ": " ZRLOG_STRINGIZE(__LINE__) ": " msg
#define ZRLOG_PRINT_MESSAGE(msg, debugNo) __pragma(message(ZRLOG_MESSAGE_STRING(msg))); ZRLogWarningPrint<__LINE__, debugNo>();
#else
#define ZRLOG_PRINT_MESSAGE(msg, debugNo) 
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define ZRDDS_NETWORK_TOPIC "ZRDDS_NETWORK_TOPIC"

#define ZRDDS_DOMAINPARTICIPANT_TOPIC "ZRDDS_DOMAINPARTICIPANT_TOPIC"

#define ZRDDS_PUBLISHER_TOPIC "ZRDDS_PUBLISHER_TOPIC"

#define ZRDDS_DOMAINPARTICIPANTFACTORY_TOPIC "ZRDDS_DOMAINPARTICIPANTFACTORY_TOPIC"

#define ZRDDS_MPORT_TOPIC "ZRDDS_MPORT_TOPIC"

#define ZRDDS_SHMEM_TOPIC "ZRDDS_SHMEM_TOPIC"

#define ZRDDS_VALIDATOR_TOPIC "ZRDDS_VALIDATOR_TOPIC"

#define ZRDDS_INTERACTIVECMD_TOPIC "ZRDDS_INTERACTIVECMD_TOPIC"

#define ZRDDS_ANY_TOPICNAME "ZRDDS_ANY_LOG_TOPIC_NAME___"

#define ZRDDS_LOG_ENABLE_BEGIN_NUM 7000

#define ZRDDS_LOG_ENABLE_END_NUM 7000

/**
 * @enum    ZRLogDisplayStyle
 *
 * @brief    日志输出样式风格。
 */

typedef enum ZRLogDisplayStyle
{
    /** @brief 默认模式. */
    GRACEFUL_STYLE = 0,
    /** @brief 极简模式. */
    PRACTICAL_STYLE = 2,
    /** @brief 元信息模式. */
    META_STYLE = 4,
    /** @brief 调试模式，如果是调试日志，则只显示日志号；其它日志正常显示. */
    DEBUG_STYLE = 6,
    /** @brief 未知，将采用默认模式. */
    UNKNOWN_STYLE
}ZRLogDisplayStyle;

/**
 * @typedef enum ZRLogBackupMode
 *
 * @brief   日志备份模式.
 */
typedef enum ZRLogBackupMode
{
    /** @brief  默认模式。不使用日志备份功能。每次重启应用，都将覆盖原有日志。 */
    ZRLOG_BACKUP_NOTUSED,
    /** @brief  同名备份模式。当有同名日志时，将原有的日志备份到日志输出目录/日志文件名-时间戳。 */
    ZRLOG_BACKUP_EXIST_FILE,
    /**   
     * @brief   当前日志文件达到一定大小后将进行备份，并重新创建日志文件。  
     *          选用该模式后，日志文件的名称将为“日志文件名称_创建时间.ddslog” 
     */
    ZRLOG_BACKUP_FILE_SIZE,
    /**
     * @brief   每隔一段时间后将进行备份，并重新创建日志文件。
     *          选用该模式后，日志文件的名称将为“日志文件名称_创建时间.ddslog”
     */
    ZRLOG_BACKUP_TIME_INTERVAL,
} ZRLogBackupMode;

/**
 * @typedef struct ZRLogBackupParam
 *
 * @brief   Defines an alias representing the zr log parameter.
 */

typedef struct ZRLogBackupParam
{
    /** @brief   日志备份模式. */
    ZRLogBackupMode mode;
    /**   
     * @brief   当mode被设置为ZRLOG_BACKUP_NOTUSED时，该参数无效。 
     *          当mode被设置为ZRLOG_BACKUP_FILE_SIZE时，该参数为日志文件大小上限（KB）。
     *          当mode被设置为ZRLOG_BACKUP_TIME_INTERVAL时，该参数为时间间隔（s）。
     */
    ZR_INT32 param;
}ZRLogBackupParam;

/**
 * @typedef struct ZRLogParam
 *
 * @brief   Defines an alias representing the zr log parameter.
 */

typedef struct ZRLogParam
{
    /** @brief   输出到控制台的日志等级。 */
    ZR_UINT32 consoleMask;
    /** @brief   输出到文件中的日志等级。 */
    ZR_UINT32 fileMask;
    /** @brief   输出到分布式日志的日志等级。 */
    ZR_UINT32 distMask;
    /** @brief   日志展示风格。 */
    ZRLogDisplayStyle style;
    /** @brief   指定日志的输出文件路径。如果设置为NULL，则将使用默认路径（当前运行目录）。初始化后该参数不可变。 */
    ZR_INT8* logFileDir;
    /** @brief   指定日志的输出文件名。如果设置为NULL，则将使用默认名称（应用名.ddslog）。初始化后该参数不可变。 */
    ZR_INT8* logFileName;
    /** @brief   应用备份策略。初始化后该策略不可变。 */
    ZRLogBackupParam backupParam;
} ZRLogParam;

DCPSDLL extern void ZRLogParamInitial(ZRLogParam* param);

/**
 * @enum DDS_LogType
 *
 * @ingroup CoreQosStruct
 *
 * @brief   用于表示某一条日志的输出等级，对于不同的等级的用户可以看到不同的日志文件。
 *
 */

typedef enum DDS_LogType
{
    /** @brief  程序出现不可忽略的错误。 @ingroup CoreQosStruct */
    ZRLOG_ERROR = 0x0001 << 1,
    /** @brief  系统管理员视角的信息,比如一些调试信息。 @ingroup CoreQosStruct */
    ZRLOG_ADMIN_INFO = 0x0001 << 2,
    /** @brief  通知用户视角信息，即只能看到自定义Endpoint之间的数据交互。 @ingroup CoreQosStruct */
    ZRLOG_USER_INFO = 0x0001 << 3,
    /** @brief  警告信息但是能够正常运行。 @ingroup CoreQosStruct */
    ZRLOG_WARNING = 0x0001 << 4,
    /** @brief  无效的选项。  @ingroup CoreQosStruct */
    LOGTYPE_UNKNOWN = 0x0001 << 9
} DDS_LogType;

/**
 * @typedef ZR_INT32(*ZRLogCallbackInitialize)(void* logCallbackParam)
 *
 * @brief   第三方日志接口中用于初始化的回调函数。
 *          如果需要设置第三方日志接口，且需要预先进行初始化的操作（如分配空间等），则用户需要实现该类型的函数，
 *          并在函数实现中编写初始化操作的逻辑。
 *          将对应将函数指针填入ZRLogCallbackParam中，并调用ZRLogSetListener。
 *          如果返回非0值，则表示初始化操作失败，该第三方日志接口将不会启用。
 */
typedef ZR_INT32(*ZRLogCallbackInitialize)(void* logCallbackParam);

/**
 * @typedef ZR_INT32(*ZRLogCallback)(DDS_LogType type, const ZR_INT8* topicName, 
 *          unsigned int debugNo, const ZR_INT8* time, const ZR_INT8* file, 
 *          const ZR_INT8* func, ZR_UINT32 line, const ZR_INT8* content, void* logCallbackParam)
 *
 * @brief   第三方日志接口中用于日志输出的回调函数。
 *          如果需要设置第三方日志接口，则用户需要实现该类型的函数，并在函数实现中编写自定义的日志处理的逻辑。
 *          将对应将函数指针填入ZRLogCallbackParam中，并调用ZRLogSetListener。
 *          回调接口将会优先调用。
 *          如果返回0，则表示需要继续调用ZRDDS原始的日志输出动作；如果返回-1，则表示跳过ZRDDS原始的日志输出动作。
 */

typedef ZR_INT32(*ZRLogCallbackOutput)(DDS_LogType type, const ZR_INT8* topicName, 
    unsigned int debugNo, const ZR_INT8* time, const ZR_INT8* file, 
    const ZR_INT8* func, ZR_UINT32 line, const ZR_INT8* content, void* logCallbackParam);

/**
 * @typedef ZR_INT32(*ZRLogCallbackFinalize)(void* logCallbackParam)
 *
 * @brief   第三方日志接口中用于结束处理的回调函数。
 *          如果用户在设置第三方日志接口时，传入初始化回调并进行了初始化的操作（如分配空间等），则建议实现该类型的函数，
 *          并在函数实现中编写对应的析构、结束处理逻辑。
 *          将对应将函数指针填入ZRLogCallbackParam中，并调用ZRLogSetListener。
 *          如果返回非0值，则表示结束处理存在错误。（尽管错误，该第三方日志接口也会被移除，不会再启用）
 */

typedef ZR_INT32(*ZRLogCallbackFinalize)(void* logCallbackParam);

/**
 * @struct  ZRLogCallbackParam
 *
 * @brief   用于存放用户回调函数指针、传参的结构体.
 */

typedef struct ZRLogCallback
{
    /** @brief   第三方日志接口中用于初始化的回调函数，可以为NULL. */
    ZRLogCallbackInitialize initialize_callback;
    /** @brief   第三方日志接口中用于日志输出的回调函数，不可以为NULL，否则ZRLogSetListener会失败*/
    ZRLogCallbackOutput log_output_callback;
    /** @brief   第三方日志接口中用于结束处理的回调函数，可以为NULL. */
    ZRLogCallbackFinalize finalize_callback;
    /** @brief   第三方日志接口中的用户传参. */
    void* log_callback_param;
}ZRLogCallback;

/**
 * @fn    extern ZR_INT32 ZRLogInitial(ZR_UINT32 consoleMask, ZR_UINT32 fileMask, ZRLogDisplayStyle style);
 *
 * @brief    初始化用户日志接口.
 *
 * @param    consoleMask    输出到控制台的日志等级掩码.
 * @param    fileMask       输出到日志文件的日志等级掩码.
 * @param    style           日志风格，默认为GRACEFUL_STYLE.
 *
 * @return    A ZR_INT32.
 */

DCPSDLL extern ZR_INT32 ZRLogInitial(const ZRLogParam* param);

/**
 * @fn  ZR_INT32 ZRLogInitial();
 *
 * @brief   回收为日志系统提供资源等。
 *
 * @author  Hzy
 * @date    2015/9/24
 */

DCPSDLL extern ZR_INT32 ZRLogDestroy();

/**
 * @fn    void ZRLogSetDisplayStyle(ZRLogDisplayStyle style);
 *
 * @brief    设置风格样式.
 *
 * @param    style    The style.
 */

DCPSDLL extern void ZRLogSetDisplayStyle(ZRLogDisplayStyle style);

/**
 * @fn  ZR_INT32 ZRLogSetListener(ZRLogCallback listener);
 *
 * @brief   设置第三方日志回调接口。
 *          需要由用户自行管理ZRLogCallback指针。
 *          如果在未调用ZRLogRemoveListener的情况下，释放了该指针的空间，可能会导致程序崩溃。
 *          在输出日志时，将会优先调用第三方接口。
 *
 * @param   listener    回调接口的指针.
 *
 * @return  若设置成功，则返回0，否则返回非0值.
 */

DCPSDLL extern ZR_INT32 ZRLogSetListener(ZRLogCallback* listener);

/**
 * @fn  ZR_INT32 ZRLogRemoveListener(ZRLogCallback listener);
 *
 * @brief   移除第三方日志回调接口。
 *          移除后，ZRLogCallback指针并未被释放，需要由用户手动释放。
 *
 * @param   listener    回调接口的函数指针.
 *
 * @return  若移除成功，则返回0，否则返回非0值.
 */

DCPSDLL extern ZR_INT32 ZRLogRemoveListener(ZRLogCallback* listener);

/**
 * @fn  ZR_BOOLEAN ZRLogDebugMask(ZR_UINT32 debugNum);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   指定的调试信息编号是否启用。
 *
 * @param   debugNum    指明调试信息编号。
 *
 * @return  true表示已启用，false表示未启用。
 */

DCPSDLL ZR_BOOLEAN ZRLogDebugMask(ZR_UINT32 debugNum);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskEnableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   使能调试信息范围。
 *
 * @param   beginNum    开始编号(包含)。
 * @param   endNum      结束编号(包含)。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskEnableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);

/**
 * @fn  void ZRLogDebugMaskDisableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   取消调试信息范围。
 *
 * @param   beginNum    开始编号(包含)。
 * @param   endNum      结束编号(包含)。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskDisableRange(ZR_UINT32 beginNum, ZR_UINT32 endNum);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskEnableTopicName(const ZR_INT8* topicName);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   使能指定主题数据的日志。
 *
 * @param   topicName   指明主题名称，由用户保证主题名称的有效性。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskEnableTopicName(const ZR_INT8* topicName);

/**
 * @fn  ZR_INT8 ZRLogDebugMaskDisableTopicName(const ZR_INT8* topicName);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   取消使能指定主题数据的日志。
 *
 * @param   topicName   指明主题名称，由用户保证主题名称的有效性。
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT8 ZRLogDebugMaskDisableTopicName(const ZR_INT8* topicName);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskEnableEntityId(const DDS_InstanceHandle_t* handle);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   使能指定实体的日志。
 *
 * @param   handle  实体唯一标识，( Entity::get_instance_handle ), 由用户保证InstanceHandle的有效性。.
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskEnableEntityId(const DDS_InstanceHandle_t* handle);

/**
 * @fn  ZR_INT32 ZRLogDebugMaskDisableEntityId(const DDS_InstanceHandle_t* handle);
 *
 * @ingroup ZRDDSLog
 *
 * @brief   使能指定实体的日志。
 *
 * @param   handle  实体唯一标识，( Entity::get_instance_handle ), 由用户保证InstanceHandle的有效性。.
 *
 * @return  0表示成功，小于0表示失败。
 */

DCPSDLL ZR_INT32 ZRLogDebugMaskDisableEntityId(const DDS_InstanceHandle_t* handle);

/**
 * @fn  void ZRLogBeginLog(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie);
 *
 * @brief   当需要连续写入日志信息时调用， 必须与ZRLogEndLog配合使用。
 *
 * @param   type    以下调试信息所属的类型。
 * @param   file    所属文件名。
 * @param   func    所属函数名。
 * @param   line    行数。
 * @param   combie  是否将连续日志合并成一个，在分布式日志时有区别，合并后发送一条日志，不合并则发送多条日志，合并对于连续输出的长度有限制。
 */

DCPSDLL extern void ZRLogBeginLog(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie);

/**
 * @fn  DCPSDLL extern void ZRLogBeginLogWNo(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie, const ZR_INT8* topicName, ZR_UINT32 debugNo);
 *
 * @brief   当需要连续写入日志信息时调用， 必须与ZRLogEndLog配合使用。.
 *
 * @param   type        以下调试信息所属的类型。
 * @param   file        所属文件名。
 * @param   func        所属函数名。
 * @param   line        行数。
 * @param   combie      是否将连续日志合并成一个，在分布式日志时有区别，合并后发送一条日志，不合并则发送多条日志，合并对于连续输出的长度有限制。
 * @param   topicName   主题名。
 * @param   debugNo     编号。
 */

DCPSDLL extern void ZRLogBeginLogWNo(DDS_LogType type, const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, ZR_BOOLEAN combie, const ZR_INT8* topicName, ZR_UINT32 debugNo);

/**
 * @fn  void ZRLogEndLog();
 *
 * @brief   当连续写入日志信息结束时调用， 与ZRLogBeginLog配合使用。
 *
 */
DCPSDLL extern void ZRLogEndLog();

DCPSDLL extern void ZRLogToConsole(DDS_LogType type, const struct GUID_t* guid, const ZR_INT8* topicName, ZR_UINT32 debugNo,
    const ZR_INT8* file, const ZR_INT8* func, ZR_UINT32 line, const ZR_INT8* content, ...);

DCPSDLL extern ZR_BOOLEAN ZRLogVerifyDebugCondition(ZR_UINT32 debugNo, const ZR_INT8* topicName, const struct GUID_t* guid);

DCPSDLL extern void ZRLogAquireLock();

DCPSDLL extern void ZRLogReleaseLock();

DCPSDLL extern const ZR_INT8* InstanceHandleToString(const DDS_InstanceHandle_t* self);

DCPSDLL extern const ZR_INT8* InstanceHandleToString2(const DDS_InstanceHandle_t* self);

/**
 * @def ZRLOG(type, format, ...) ZRLogToConsole(type, __FILE__, __FUNCTION__, __LINE__, format,
 *      ##__VA_ARGS__)
 *
 * @ingroup ZRDDSLog
 *
 * @brief   输出日志的宏。
 *
 * @param   type    该日志所属的级别。
 * @param   format  字符串格式(类printf).
 * @param   ...     变参。
 */

#define ZRLOG(type, format, ...)                                                                \
        ZRLogAquireLock();                                                                      \
        ZRLogToConsole(type, NULL, NULL, 0, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__); \
        ZRLogReleaseLock();

/**
 * @def ZRLOG_W_NO(type, guid, topic, debugNo, format, ...) ZRLOG_PRINT_MESSAGE(format, debugNo);
 *
 * @brief   输出带编号日志的宏。.
 *
 * @param   type    该日志所属的级别。.
 * @param   guid    该日志所属实体.
 * @param   topic   该日志所属主题.
 * @param   debugNo 该日志的编号.
 * @param   format  字符串格式(类printf).
 * @param   ...     变参。.
 */
#define ZRLOG_W_NO(type, guid, topic, debugNo, format, ...)                                                                \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(type, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
    }

/**
 * @def ZRLOG_DEBUG(guid, topic, debugNo, format, ...) if (ZRLogVerifyDebugCondition(debugNo,
 *      topic, guid))
 *
 * @ingroup ZRDDSLog
 *
 * @brief   输出调试信息宏。
 *
 * @param   guid    该调试信息所属实体。
 * @param   topic   该调试信息所属主题。
 * @param   debugNo 该调试信息的编号。
 * @param   format  字符串格式(类printf).
 * @param   ...     变参。
 */

#ifndef _ZRDDS_FT_6678_MPORT_SRIO
#define ZRLOG_DEBUG(guid, topic, debugNo, format, ...)                                                              \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
    }

#else
#define ZRLOG_DEBUG(guid, topic, debugNo, format, ...)
#endif

/**
 * @def ZRLOG_DEBUG_W_POS(guid, topic, debugNo, file, func, line, format, ...)
 *
 * @ingroup ZRDDSLog
 *
 * @brief   输出调试信息宏，并携带位置信息。
 *
 * @param   guid    该调试信息所属实体。
 * @param   topic   该调试信息所属主题。
 * @param   debugNo 该调试信息的编号。
 * @param   file    所属文件，字符串型。
 * @param   func    所属函数，字符串型。
 * @param   line    行号，整型。
 * @param   format  字符串格式(类printf).
 * @param   ...     变参。
 */

#define ZRLOG_DEBUG_W_POS(guid, topic, debugNo, file, func, line, format, ...)                          \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                               \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                \
    {                                                                                               \
        ZRLogAquireLock();                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, file, func, line, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                         \
    }

/**
 * @def ZRLOG_USER(guid, topic, debugNo, format, ...) ZRLOG_PRINT_MESSAGE(format, debugNo);
 *
 * @ingroup  ZRDDSLog
 *
 * @brief   输出用户信息宏。
 *
 * @param   guid    该信息所属实体。
 * @param   topic   该信息所属主题。
 * @param   debugNo 该信息的编号。
 * @param   format  字符串格式(类printf).
 * @param   ...     变参。
 */

#define ZRLOG_USER(guid, topic, debugNo, format, ...)                                               \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                            \
    {                                                                                               \
        ZRLogAquireLock();                                                                          \
        ZRLogToConsole(ZRLOG_USER_INFO, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);   \
        ZRLogReleaseLock();                                                                         \
    }

/**
 * @def ZRLOG_USER_W_POS(guid, topic, debugNo, file, func, line, format, ...)
 *
 * @ingroup ZRDDSLog
 *
 * @brief   输出用户信息宏。
 *
 * @param   guid    该用户信息所属实体。
 * @param   topic   该用户信息所属主题。
 * @param   debugNo 该用户信息的编号。
 * @param   file    所属文件，字符串型。
 * @param   func    所属函数，字符串型。
 * @param   line    行号，整型。
 * @param   format  字符串格式(类printf).
 * @param   ...     变参。
 */

#define ZRLOG_USER_W_POS(guid, topic, debugNo, file, func, line, format, ...)                       \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                            \
    {                                                                                               \
        ZRLogAquireLock();                                                                          \
        ZRLogToConsole(ZRLOG_USER_INFO, guid, topic, debugNo, file, func, line, format, ##__VA_ARGS__);   \
        ZRLogReleaseLock();                                                                         \
    }

/**
 * @def ZRLOG_DEBUG_W_EXP(guid, topic, debugNo, preState1, preState2, postState1, postState2,
 *      format, ...) ZRLOG_PRINT_MESSAGE(format, debugNo);
 *
 * @ingroup  ZRDDSLog
 *
 * @brief   输出调试信息宏，在输出前后分别执行指定表达式。
 *
 * @param   guid        该调试信息所属实体。
 * @param   topic       该调试信息所属主题。
 * @param   debugNo     该调试信息的编号。
 * @param   preState1   第一条前置语句。
 * @param   preState2   第二条前置语句。
 * @param   postState1  第一条后置语句。
 * @param   postState2  第二条后置语句。
 * @param   format      字符串格式(类printf).
 * @param   ...         变参。
 */

#define ZRLOG_DEBUG_W_EXP(guid, topic, debugNo, preState1, preState2, postState1, postState2, format, ...)          \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        preState1;                                                                                                  \
        preState2;                                                                                                  \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
        postState1;                                                                                                 \
        postState2;                                                                                                 \
    }

/**
 * @def ZRLOG_DEBUG_W_EXP2(guid, topic, debugNo, preState1, preState2, postState1, postState2,
 *      format, ...) if (ZRLogVerifyDebugCondition(debugNo, topic, guid))
 *
 * @ingroup  ZRDDSLog
 *
 * @brief   输出调试信息宏，连续输出日志，在输出字符串后调用输出函数输出剩余内容。
 *
 * @param   guid        该调试信息所属实体。
 * @param   topic       该调试信息所属主题。
 * @param   debugNo     该调试信息的编号。
 * @param   preState1   第一条前置语句。
 * @param   preState2   第二条前置语句。
 * @param   postState1  第一条后置语句。
 * @param   postState2  第二条后置语句。
 * @param   format      字符串格式(类printf).
 * @param   ...         变参。
 */

#define ZRLOG_DEBUG_W_EXP2(guid, topic, debugNo, preState1, preState2, postState1, postState2, format, ...)         \
    ZRLOG_PRINT_MESSAGE(format, debugNo);                                                                           \
    if (ZRLogVerifyDebugCondition(debugNo, topic, guid))                                                            \
    {                                                                                                               \
        ZRLogBeginLogWNo(ZRLOG_ADMIN_INFO, __FILE__, __FUNCTION__, __LINE__, true, topic, debugNo);                 \
        preState1;                                                                                                  \
        preState2;                                                                                                  \
        ZRLogAquireLock();                                                                                          \
        ZRLogToConsole(ZRLOG_ADMIN_INFO, guid, topic, debugNo, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);  \
        ZRLogReleaseLock();                                                                                         \
        postState1;                                                                                                 \
        postState2;                                                                                                 \
        ZRLogEndLog();                                                                                              \
    }

#ifdef __cplusplus
}
#endif

#endif // ZRUserLog_h__
