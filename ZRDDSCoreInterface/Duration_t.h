/**
 * @file:       Duration_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#if !defined(_DURATION_T_H)
#define _DURATION_T_H

#include "ZRDDSCommon.h"
#include "OsResource.h"

#define DDS_MILLISEC_PER_SEC    1000
#define DDS_MICROSEC_PER_SEC    1000000
#define DDS_NANOSEC_PER_SEC     1000000000

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * 保留的Duration_t值
 */
DCPSDLL extern const DDS_Long DDS_DURATION_INFINITE_SEC;	/* 无穷秒 */
DCPSDLL extern const DDS_Long DDS_DURATION_ZERO_SEC;	/* 0秒 */
DCPSDLL extern const DDS_ULong DDS_DURATION_INFINITE_NSEC;/* 无穷纳秒 */
DCPSDLL extern const DDS_ULong DDS_DURATION_ZERO_NSEC;	/* 0纳秒 */

/**
 * @struct  DDS_Duration_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   用来表明一段时间段，协议规定至少有毫微秒的分辨率。
 *
 * @details  ZRDDS的的实现只精确到了毫秒，Windows/linux时间由clock获取，vxworks时间由time获取，精确到秒。
 */

typedef struct DCPSDLL DDS_Duration_t
{
    /** @brief	秒的值. */
    DDS_Long sec;
    /** @brief	毫微秒的值. */
    DDS_ULong nanosec;
#ifdef _ZRDDSCPPINTERFACE
    DDS_Boolean operator==(const DDS_Duration_t& duration) const;
    DDS_Boolean operator<(const DDS_Duration_t& duration) const;
    DDS_Boolean operator<=(const DDS_Duration_t& duration) const;
    DDS_Boolean operator>(const DDS_Duration_t& duration) const;
    DDS_Boolean operator>=(const DDS_Duration_t& duration) const;
    DDS_Duration_t operator+(const DDS_Duration_t& duration) const;
    DDS_Duration_t operator-(const DDS_Duration_t& duration) const;
#endif
}DDS_Duration_t;

/**
 * @fn  DCPSDLL DDS_Duration_t DurationAdd(const DDS_Duration_t* self, const DDS_Duration_t* right);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   两个 DDS_Duration_t 相加返回一个新的结果。
 *
 * @param   self    左加数。
 * @param   right   右加数。
 *
 * @return  返回的结果。
 */

DCPSDLL DDS_Duration_t DurationAdd(const DDS_Duration_t* self, const DDS_Duration_t* right);

/**
 * @fn  void DurationAddAssign(Duration_t* self, const Duration_t* right);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   DDS_Duration_t 加等于操作。
 *
 * @param [in,out]  self    加数。
 * @param   right           被加数。
 */


DCPSDLL DDS_Duration_t DurationSub(const DDS_Duration_t* self, const DDS_Duration_t* subtractor);

/**
 * @fn  DCPSDLL DDS_Long DurationCompare(const DDS_Duration_t* const self, const DDS_Duration_t* const right);
 *
 * @ingroup  CoreFunction
 *
 * @brief   DDS_Duration_t 的小于函数。
 *
 * @param   self    指向左边的参数对象。
 * @param   right   指向右边的参数对象。
 *
 * @return  - 0表示两个对象值相等
 *          - 大于0表示左边对象大于右边对象大小  
 *          - 小于0表示左边对象小于右边对象大小
 */

DCPSDLL DDS_Long DurationCompare(const DDS_Duration_t* const self,
    const DDS_Duration_t* const right);

/**
 * @fn  DCPSDLL DDS_ULongLong DurationGetMicrosec(const DDS_Duration_t* const self);
 *
 * @ingroup  CoreFunction
 *
 * @brief   获取等价的微秒数。
 *
 * @param   self    转化目标。
 *
 * @return  计算的结果。
 */

DCPSDLL DDS_ULongLong DurationGetMicrosec(const DDS_Duration_t* const self);

/**
 * @fn  DCPSDLL DDS_ULongLong DurationGetMillisec(const DDS_Duration_t* const self);
 *
 * @ingroup  CoreFunction
 *
 * @brief   获取等价的毫秒数。
 *
 * @param   self    转化目标。
 *
 * @return  计算的结果。
 */

DCPSDLL DDS_ULongLong DurationGetMillisec(const DDS_Duration_t* const self);

/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromSec(DDS_ULong seconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从秒数转换为等价的 DDS_Duration_t 。
 *
 * @param   seconds 秒数。
 *
 * @return  与seconds相等的 DDS_Duration_t 时间段。
 */

DCPSDLL DDS_Duration_t DurationFromSec(DDS_ULong seconds);

/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromMillis(DDS_ULong milliseconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从毫秒数转换为等价的 DDS_Duration_t 。
 *
 * @param   milliseconds 毫秒数。
 *
 * @return  与milliseconds相等的 DDS_Duration_t 时间段。
 */

DCPSDLL DDS_Duration_t DurationFromMillis(DDS_ULong milliseconds);

/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromMicros(DDS_ULong microseconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从微秒数转换为等价的 DDS_Duration_t 。
 *
 * @param   microseconds 毫秒数。
 *
 * @return  与microseconds相等的 DDS_Duration_t 时间段。
 */

DCPSDLL DDS_Duration_t DurationFromMicros(DDS_ULong microseconds);


/**
 * @fn  DCPSDLL DDS_Duration_t DurationFromNanos(DDS_ULong nanoseconds);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   从纳秒数转换为等价的 DDS_Duration_t 。
 *
 * @param   nanoseconds 纳秒数。
 *
 * @return  与nanoseconds相等的 DDS_Duration_t 时间段。
 */
DCPSDLL DDS_Duration_t DurationFromNanos(DDS_ULong nanoseconds);

/* 协议用到的一些Duration_t的默认值 */
/** @brief	无效的值。@ingroup   CoreVar */
DCPSDLL extern const DDS_Duration_t INVALID_DURATION;
/** @brief   无限长。 @ingroup  CoreVar */
DCPSDLL extern const DDS_Duration_t INFINITE_DURATION;
/** @brief   时间为0。@ingroup  CoreVar */
DCPSDLL extern const DDS_Duration_t ZERO_DURATION;

/** @brief	HB延迟响应（发送ACKNACK）时间，100ms.*/
extern const DDS_Duration_t DEFALUT_HB_RESP_DELAY;
/** @brief	HB抑制，防止过快地收到HB, 0s. */
extern const DDS_Duration_t DEFALUT_HB_SUPPRESSION;
/** @brief	写入HistoryCache的最大延迟时间,100ms. */
extern DDS_Duration_t DEFALUT_MAX_BLOCKING_TIME;
/** @brief	发送HB的周期. */
extern const DDS_Duration_t DEFALUT_HB_PERIOD;
/** @brief	ACKNACK的响应延迟时间,200ms. */
extern const DDS_Duration_t DEFALUT_NACK_RESP_DELAY;
/** @brief	NACK抑制，SENT变成Unacknowledged状态(协议有问题)，10ms. */
extern const DDS_Duration_t DEFALUT_NACK_SUPPRESSION;
/** @brief	发送Participant心跳时间. */
extern const DDS_Duration_t DEFALUT_UPDATE_PARTICIPANT;
/** @brief	Participant过期时间,15s. */
extern const DDS_Duration_t DEFALUT_PARTICIPANT_LEASE;
/** @brief	ParticipantReader检查更新Participant存活信息的间隔. */
extern const DDS_Duration_t DEFALUT_CHECK_PARTICIPANT_STALE;
/** @brief	Writer刷新响应超时周期. */
extern const DDS_Duration_t DEFALUT_REFRESH_UNACK;
/** @brief  默认的Data(p)发送抑制时间。 */
extern DDS_Duration_t DEFAULT_DATAP_SUPPRESSION;

/**
 * @typedef struct DDS_Duration_t DDS_Time_t
 *
 * @ingroup CoreBaseStruct
 *
 * @brief   时间点，参考IETF NTP定义，time = seconds+[fraction/(2^32)].
 *
 * @sa  DDS_Duration_t
 */

typedef struct DDS_Duration_t DDS_Time_t;
/** @brief	时间点为0。 @ingroup   CoreVar */
DCPSDLL extern const DDS_Time_t DDS_TIME_ZERO;
/** @brief	无效的时间点。 @ingroup   CoreVar */
DCPSDLL extern const DDS_Time_t DDS_TIME_INVALID;
/** @brief	无限长的时间点。 @ingroup   CoreVar */
DCPSDLL extern const DDS_Time_t DDS_TIME_INFINITE;

/**
 * @fn  DCPSDLL void ZRGetNowTime(DDS_Time_t* nowTime);
 *
 * @ingroup CoreBaseFunction
 *
 * @brief   返回调用该函数时的UTC标准时间。
 *
 * @param [in,out]  nowTime 出口参数，当前时间戳。
 */

DCPSDLL void ZRGetNowTime(DDS_Time_t* nowTime);

/**
 * @fn  DDS_Long ZRGetNowTimeString(DDS_Char* strformat);
 *
 * @ingroup  CoreFunction
 *
 * @brief   获取日历时间的字符串形式. 格式"1970-01-01 00:00:00:000"。
 *
 * @param [in,out]  strformat   字符串缓冲区用来存储结果，需要保证有足够的空间。
 *
 * @pre     strformat为64字节以上的空间。
 *
 * @return  返回距离1970/1/1 00:00:00的毫秒数.
 */

DDS_LongLong ZRGetNowTimeString(DDS_Char* strformat);

/**
* @fn  DDS_Long ZRGetNowTimeString2(DDS_Char* strformat);
*
* @ingroup  CoreFunction
*
* @brief   获取日历时间的字符串形式. 格式"1970-01-01-00-00-00-000"。
*
* @param [in,out]  strformat   字符串缓冲区用来存储结果，需要保证有足够的空间。
*
* @pre     strformat为64字节以上的空间。
*
* @return  返回距离1970/1/1 00:00:00的毫秒数.
*/

DDS_LongLong ZRGetNowTimeString2(DDS_Char* strformat);

#ifdef __cplusplus
}
#endif

#endif  /*_DURATION_T_H*/
