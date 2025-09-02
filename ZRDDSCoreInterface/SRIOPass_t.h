/**
 * @file:       SRIOPass_t.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef SRIOPass_H
#define SRIOPass_H

#include "OsResource.h"
#ifdef _ZRDDS_MPORT_FPGA_SRIO
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _LINUX
#include <sys/file.h>
#include <unistd.h>
#include <dirent.h>
#endif

typedef struct MessageBlock MessageBlock;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @ingroup	BaseType模块
 * @struct  SRIOPass_t
 *
 * @brief	当使用SRIO方式进行跨机箱传输时，SRIOPass_t表示一条数据通道（发或收），是当前节点和所在机箱的FPGA节点之间的数据通道
 *
 * @author	Wby
 * @date	2021/6/21
 */

typedef struct SRIOPass_t
{
    /** @brief   FC通道的唯一标识，key. */
    ZR_UINT32 num;
    /** @brief   FC通道的标识. */
    ZR_UINT32 fc_msg_id;
    /** @brief	   远端FC的id. */
    ZR_UINT32 fc_remote_id;
    /** @brief	   SRIO的发送节点id. */
    ZR_UINT32 srio_src_id;
    /** @brief   SRIO的接收节点id. */
    ZR_UINT32 srio_dst_id;
    /** @brief   门铃信息. */
    ZR_UINT32 db;
    /** @brief	   SRIO接收地址. */
    ZR_UINT64 srio_addr;
    /** @brief   通道使能状态. */
    ZR_BOOLEAN enable;
    /** @brief	   通道使用状态，未使用为0，已使用为进程id. */
    ZR_UINT32 used;
}SRIOPass_t;

/**
* @fn  ZR_BOOLEAN SRIOPassIsEqual(SRIOPass_t* left, SRIOPass_t* right);
*
* @brief   比较SRIOPass。
*
* @author  Wby
* @date    2022/8/11
*
* @param   left    作为比较的前一个SRIOPass。
* @param   right    作为比较的后一个SRIOPass。
*
* @return  true表示相同，false表示不相同。
*/

ZR_BOOLEAN SRIOPassIsEqual(SRIOPass_t* left, SRIOPass_t* right);

/**
* @fn  ZR_INT32 SRIOPassCopy(SRIOPass_t* src, SRIOPass_t* dst);
*
* @brief   拷贝SRIOPass。
*
* @author  Wby
* @date    2022/8/11
*
* @param   src    拷贝来源SRIOPass。
* @param   [in,out]   dst    拷贝目的SRIOPass。
*
* @return  0表示成功，小于0表示失败。
*/

ZR_INT32 SRIOPassCopy(SRIOPass_t* src, SRIOPass_t* dst);

/**
 * @fn  ZR_INT32 SRIOPassFromString(SRIOPass_t* self, const ZR_INT8* strformat);
 *
 * @brief   从字符串型构造SRIOPass。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    转换结果。
 * @param   strformat       输入的字符串。
 *
 * @return  0表示成功，小于0表示失败。
 */

ZR_INT32 SRIOPassFromString(SRIOPass_t* self, const ZR_INT8* strformat);

/**
 * @fn  ZR_BOOLEAN SRIOPassSerialize(const SRIOPass_t* pass, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   序列化SRIOPass。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   pass            需要序列化的SRIOPass。
 * @param [in,out]  dst     目标缓冲区。
 * @param   littleEndian    要求端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOPassSerialize(const SRIOPass_t* pass, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOPassDeserialize(SRIOPass_t* addr, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   反序列化SRIOPass。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   pass            反序列化的结果。
 * @param [in,out]  dst     源缓冲区。
 * @param   littleEndian    要求端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOPassDeserialize(SRIOPass_t* addr, MessageBlock* src, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_INT8* SRIOPassListToString(const SRIOPass_t* SRIOPass);
 *
 * @brief   转化成可打印的字符串，用于调试。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   SRIOPass 指明目标。
 *
 * @return  返回字符串。
 */

ZR_INT8* SRIOPassToString(const SRIOPass_t* SRIOPass);
ZR_INT8* SRIOPassToString2(const SRIOPass_t* SRIOPass);

/**
 * @def BUFFERED_SRIOPASS_NUM
 *
 * @brief   SRIOPassList中最大缓存的SRIOPass个数。
 *
 * @author  Wby
 * @date    2021/6/21
 */

#define BUFFERED_SRIOPASS_NUM 32

/**
 * @typedef struct SRIOPassList_t
 *
 * @brief   该SRIOPassList_t用于保存一个机箱内若干收/发通道对应的SRIOPass。
 */

typedef struct SRIOPassList_t
{
    /** @brief   列表中SRIOPass个数。*/
    ZR_UINT32 m_size;
    /** @brief   列表内容数组。*/
    SRIOPass_t m_buffer[BUFFERED_SRIOPASS_NUM];
    /** @brief   当缓冲区用满时，申请额外的空间。*/
    SRIOPass_t* m_values;
}SRIOPassList_t;

/**
 * @fn  SRIOPass_t* SRIOPassListFind(SRIOPassList_t* self, ZR_UINT32 msg_id);
 *
 * @brief   获取指定对端fc端口和通道号的SRIOPass。
 *
 * @author  Wby
 * @date    2021/6/25
 *
 * @param [in,out]  self    指明目标。
 * @param   remote_fc_id           指定对端fc端口。
 * @param   msg_id           指定通道号。
 *
 * @return  NULL表示获取失败，否则返回元素。
 */

SRIOPass_t* SRIOPassListFind(SRIOPassList_t* self, ZR_UINT32 remote_fc_id, ZR_UINT32 msg_id);

/**
 * @fn  const ZR_INT8* SRIOPassListToString(const SRIOPassList_t* SRIOPassList);
 *
 * @brief   转换为一个可打印的字符串，用于调试输出。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   SRIOPassList 指明目标。
 *
 * @return  "Empty"为空，否则为n行，每一行代表一个SRIOPass。
 */

ZR_INT8* SRIOPassListToString(const SRIOPassList_t* SRIOPassList);

/**
 * @fn  void SRIOPassListInitial(SRIOPassList_t* self);
 *
 * @brief   初始化空的列表。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    If non-null, the self.
 */

void SRIOPassListInitial(SRIOPassList_t* self);

/**
 * @fn  ZR_UINT32 SRIOPassListInsertSRIOPass(SRIOPassList_t* self, const SRIOPass_t* pass);
 *
 * @brief   插入一个SRIOPass进入列表。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    通道列表。
 * @param   addr            需要插入的通道。
 *
 * @return  成功返回0，小于零表示失败。
 */

ZR_INT32 SRIOPassListInsertSRIOPass(SRIOPassList_t* self, const SRIOPass_t* pass);

/**
 * @fn  ZR_INT32 SRIOPassListCopy(SRIOPassList_t* self, const SRIOPassList_t* right);
 *
 * @brief   拷贝SRIOPassList。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    指明目标。
 * @param   right           表明拷贝来源。
 *
 * @return  0表示成功，小于0表示失败。
 */

ZR_INT32 SRIOPassListCopy(SRIOPassList_t* self, const SRIOPassList_t* right);

/**
 * @fn  ZR_UINT32 SRIOPassListClear(SRIOPassList_t* self);
 *
 * @brief   清空列表，并释放空间，在析构SRIOPassList时使用，否则会造成内存泄漏。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    需要清空的列表。
 *
 * @return  成功返回0，否则返回小于0.
 */

ZR_UINT32 SRIOPassListClear(SRIOPassList_t* self);

/**
 * @fn  ZR_UINT32 SRIOPassListGetSize(const SRIOPassList_t* self);
 *
 * @brief   获取通道列表序列化大小。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   self    通道列表。
 *
 * @return  0表示失败，其他表示序列化所需大小。
 */

ZR_UINT32 SRIOPassListGetSize(const SRIOPassList_t* self);

/**
 * @fn  SRIOPass_t* SRIOPassListAt(SRIOPassList_t* self, ZR_UINT32 index);
 *
 * @brief   获取指定下标的SRIOPass。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   self    指定通道列表。
 * @param   index   指定下标。
 *
 * @return  NULL表示获取失败，否则返回元素。
 */

SRIOPass_t* SRIOPassListAt(SRIOPassList_t* self, ZR_UINT32 index);

/**
 * @fn  const SRIOPass_t* SRIOPassListConstAt(SRIOPassList_t* self, ZR_UINT32 index);
 *
 * @brief   const版本的下标操作。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    指明目标。
 * @param   index   指定下标。
 *
 * @return  NULL表示获取失败，否则返回元素。
 */

const SRIOPass_t* SRIOPassListConstAt(const SRIOPassList_t* self, ZR_UINT32 index);

/**
 * @fn  ZR_BOOLEAN SRIOPassListSerialize(const SRIOPassList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   序列化SRIOPassList。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param   self            需要序列化的SRIOPassList。
 * @param [in,out]  dst     目标缓冲区。
 * @param   littleEndian    是否使用端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOPassListSerialize(const SRIOPassList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOPassListDeserialize(SRIOPassList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   反序列化SRIOPassList。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    反序列化结果。
 * @param [in,out]  src     源缓冲区。
 * @param   littleEndian    是否使用端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOPassListDeserialize(SRIOPassList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);

/**
 * @typedef struct SRIOConfig_t
 *
 * @brief   该SRIOConfig_t用于保存一个机箱内若干收/发通道对应的SRIOPass。
 */

typedef struct SRIOConfig_t
{
    /** @brief   该域参与者所属节点所在机箱的跨机箱FC的id的唯一标识。 */
    DDS_ULong fc_no;
    // TODO
    DDS_ULong temp;
    /** @brief   该域参与者所属节点所在机箱的跨机箱FC的id。 */
    DDS_ULong fc_id;
    /** @brief   该域参与者所属节点所在机箱的所有跨机箱发送通道列表。 */
    SRIOPassList_t srio_send_list;
    /** @brief   该域参与者所属节点所在机箱的所有跨机箱接收通道列表。 */
    SRIOPassList_t srio_recv_list;
}SRIOConfig_t;

/**
 * @fn  ZR_BOOLEAN SRIOConfigSerialize(const SRIOConfig_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   序列化SRIOConfig_t。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self            需要序列化的SRIOConfig_t。
 * @param [in,out]  dst     目标缓冲区。
 * @param   littleEndian    是否使用端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOConfigSerialize(const SRIOConfig_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOConfigDeserialize(SRIOConfig_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   反序列化SRIOConfig_t。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    反序列化结果。
 * @param [in,out]  src     源缓冲区。
 * @param   littleEndian    是否使用端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOConfigDeserialize(SRIOConfig_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
   
/**
 * @fn  void SRIOConfigInitial(SRIOConfig_t* self);
 *
 * @brief   初始化空的桥接路由。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    If non-null, the self.
 */

void SRIOConfigInitial(SRIOConfig_t* self);

/**
 * @fn  ZR_UINT32 SRIOConfigClear(SRIOConfig_t* self);
 *
 * @brief   清空桥接，并释放空间，在析构SRIOConfig时使用，否则会造成内存泄漏。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    需要清空的桥接。
 *
 * @return  成功返回0，否则返回小于0.
 */

ZR_UINT32 SRIOConfigClear(SRIOConfig_t* self);

/**
 * @fn  ZR_INT32 SRIOConfigCopy(SRIOConfig_t* self, const SRIOConfig_t* right);
 *
 * @brief   拷贝SRIOConfig_t。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    指明目标。
 * @param   right           表明拷贝来源。
 *
 * @return  0表示成功，小于0表示失败。
 */

ZR_INT32 SRIOConfigCopy(SRIOConfig_t* self, const SRIOConfig_t* right);

/**
 * @fn  ZR_UINT32 SRIOConfigGetSize(const SRIOConfig_t* self);
 *
 * @brief   获取桥接序列化大小。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self    桥接。
 *
 * @return  0表示失败，其他表示序列化所需大小。
 */

ZR_UINT32 SRIOConfigGetSize(const SRIOConfig_t* self);

/**
 * @fn  const ZR_INT8* SRIOConfigToString(const SRIOConfig_t* SRIOConfig);
 *
 * @brief   转换为一个可打印的字符串，用于调试输出。
 *
 * @author  Wby
 * @date    2021/10/9
 *
 * @param   SRIOConfig 指明目标。
 *
 * @return  "Empty"为空，否则为n块，每块分成三段代表一个SRIOConfig。
 */

ZR_INT8* SRIOConfigToString(const SRIOConfig_t* SRIOConfig);

#define BUFFERED_SRIOCONFIG_NUM 2

/**
 * @typedef struct SRIOPassList_t
 *
 * @brief   该SRIOPassList_t用于保存一个机箱内若干收/发通道对应的SRIOPass。
 */

typedef struct SRIOConfigList_t
{
    /** @brief   列表中SRIOConfig个数。*/
    ZR_UINT32 m_size;
    /** @brief   列表内容数组。*/
    SRIOConfig_t m_buffer[BUFFERED_SRIOCONFIG_NUM];
    /** @brief   当缓冲区用满时，申请额外的空间。*/
    SRIOConfig_t* m_values;
}SRIOConfigList_t;

/**
* @fn  ZR_BOOLEAN SRIOConfigListFromXML(SRIOConfigList_t* self, const ZR_INT8* xmlPath, FILE* passFile, const ZR_UINT32 cabNo, const ZR_UINT32 chassisNo);
*
* @brief   解析XML形式的配置表内容并保存在SRIOConfigList_t。
*
* @author  Wby
* @date    2021/12/1
*
* @param  [in,out] self            需要保存的SRIOConfigList_t。
* @param   xmlPath         配置表的路径。
* @param   passFile         通道使能状态文件。
* @param   cabNo         机柜号。
* @param   chassisNo         机箱号。
*
* @return  true表示成功，false表示失败。
*/

ZR_BOOLEAN SRIOConfigListFromXML(SRIOConfigList_t* self, const ZR_INT8* xmlPath, FILE* passFile, const ZR_UINT32 cabNo, const ZR_UINT32 chassisNo);

/**
 * @fn  ZR_BOOLEAN SRIOConfigListSerialize(const SRIOConfigList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);
 *
 * @brief   序列化SRIOConfigList_t。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self            需要序列化的SRIOConfigList_t。
 * @param [in,out]  dst     目标缓冲区。
 * @param   littleEndian    是否使用端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOConfigListSerialize(const SRIOConfigList_t* self, MessageBlock* dst, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_BOOLEAN SRIOConfigListDeserialize(SRIOConfigList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);
 *
 * @brief   反序列化SRIOConfigList。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    反序列化结果。
 * @param [in,out]  src     源缓冲区。
 * @param   littleEndian    是否使用端序。
 *
 * @return  true表示成功，false表示失败。
 */

ZR_BOOLEAN SRIOConfigListDeserialize(SRIOConfigList_t* self, MessageBlock* src, ZR_BOOLEAN littleEndian);

/**
 * @fn  ZR_UINT32 SRIOConfigListInsertSRIOConfig(SRIOConfigList_t* self, const SRIOConfig_t* pass);
 *
 * @brief   插入一个SRIOPass进入列表。
 *
 * @author  Wby
 * @date    2021/6/21
 *
 * @param [in,out]  self    通道列表。
 * @param   addr            需要插入的通道。
 *
 * @return  成功返回0，小于零表示失败。
 */

ZR_INT32 SRIOConfigListInsertSRIOConfig(SRIOConfigList_t* self, const SRIOConfig_t* config);

/**
 * @fn  void SRIOConfigListInitial(SRIOConfigList_t* self);
 *
 * @brief   初始化空的桥接路由表。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    If non-null, the self.
 */

void SRIOConfigListInitial(SRIOConfigList_t* self);

/**
 * @fn  ZR_UINT32 SRIOConfigListClear(SRIOConfigList_t* self);
 *
 * @brief   清空桥接表，并释放空间，在析构SRIOConfigList时使用，否则会造成内存泄漏。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    需要清空的桥接表。
 *
 * @return  成功返回0，否则返回小于0.
 */

ZR_UINT32 SRIOConfigListClear(SRIOConfigList_t* self);

/**
 * @fn  ZR_INT32 SRIOConfigListCopy(SRIOConfigList_t* self, const SRIOConfigList_t* right);
 *
 * @brief   拷贝SRIOConfigList_t。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    指明目标。
 * @param   right           表明拷贝来源。
 *
 * @return  0表示成功，小于0表示失败。
 */

ZR_INT32 SRIOConfigListCopy(SRIOConfigList_t* self, const SRIOConfigList_t* right);

/**
 * @fn  ZR_UINT32 SRIOConfigListGetSize(const SRIOConfigList_t* self);
 *
 * @brief   获取桥接表序列化大小。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self    桥接表。
 *
 * @return  0表示失败，其他表示序列化所需大小。
 */

ZR_UINT32 SRIOConfigListGetSize(const SRIOConfigList_t* self);

/**
 * @fn  SRIOConfig_t* SRIOConfigListAt(SRIOConfigList_t* self, ZR_UINT32 index);
 *
 * @brief   获取指定下标的SRIOConfig。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param   self    指定桥接表。
 * @param   index   指定下标。
 *
 * @return  NULL表示获取失败，否则返回元素。
 */

SRIOConfig_t* SRIOConfigListAt(SRIOConfigList_t* self, ZR_UINT32 index);

/**
 * @fn  const SRIOConfig_t* SRIOConfigListConstAt(SRIOConfigList_t* self, ZR_UINT32 index);
 *
 * @brief   const版本的下标操作。
 *
 * @author  Wby
 * @date    2021/9/30
 *
 * @param [in,out]  self    指明目标。
 * @param   index   指定下标。
 *
 * @return  NULL表示获取失败，否则返回元素。
 */

const SRIOConfig_t* SRIOConfigListConstAt(const SRIOConfigList_t* self, ZR_UINT32 index);

/**
 * @fn  SRIOPass_t* SRIOConfigListFindPass(SRIOConfigList_t* self, ZR_UINT32 fc_NO, ZR_UINT32 msg_id);
 *
 * @brief   获取指定本地fc端口、对端fc端口和通道号的SRIOPass。
 *
 * @author  Wby
 * @date    2021/10/8
 *
 * @param [in,out]  self    指明目标。
 * @param   local_fc_id           指定本地fc端口。
 * @param   remote_fc_id           指定对端fc端口。
 * @param   msg_id           指定通道号。
 *
 * @return  NULL表示获取失败，否则返回元素。
 */

SRIOPass_t* SRIOConfigListFindPass(SRIOConfigList_t* self, ZR_UINT32 local_fc_id, ZR_UINT32 remote_fc_id, ZR_UINT32 msg_id, ZR_BOOLEAN isSend);

/**
 * @fn  const ZR_INT8* SRIOConfigListToString(const SRIOConfigList_t* SRIOConfigList);
 *
 * @brief   转换为一个可打印的字符串，用于调试输出。
 *
 * @author  Wby
 * @date    2021/10/9
 *
 * @param   SRIOConfigList 指明目标。
 *
 * @return  "Empty"为空，否则为n块，每块分成三段代表一个SRIOConfig。
 */

ZR_INT8* SRIOConfigListToString(const SRIOConfigList_t* SRIOConfigList);

#ifdef __cplusplus
}
#endif
#endif // _ZRDDS_MPORT_FPGA_SRIO
#endif