/**
 * @file:       BuiltinDataDataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef BuiltinDataDataReader_h__
#define BuiltinDataDataReader_h__

#include "ZRDDSDataReader.h"
#include "ZRDDSCppWrapper.h"

namespace DDS {

/**
 * @struct DDS::ParticipantBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   声明内置数据类型 DDS::ParticipantBuiltinTopicData 的序列。
 */
typedef struct DDS_ParticipantBuiltinTopicDataSeq ParticipantBuiltinTopicDataSeq;

/**  
 * @class DDS::ParticipantBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief 声明内置数据类型 DDS::ParticipantBuiltinTopicData 关联的数据读者
 *  
 * @details 用于从ZRDDS中获取内置域参与者主题数据及其状态，该类由 DDS::ZRDDSDataReader 类模板实例化，模板参数为： 
 *          DDS::ParticipantBuiltinTopicData DDS::ParticipantBuiltinTopicDataSeq ，用法参见 
 *          DDS::DomainParticipant::get_builtin_subscriber 。
 */
typedef DCPSDLL ZRDDSDataReader<ParticipantBuiltinTopicData, ParticipantBuiltinTopicDataSeq> ParticipantBuiltinTopicDataDataReader;

/**
 * @struct DDS::PublicationBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   声明内置数据类型 DDS::PublicationBuiltinTopicData 的序列。
 */
typedef struct DDS_PublicationBuiltinTopicDataSeq PublicationBuiltinTopicDataSeq;

/**  
 * @class DDS::PublicationBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief 声明内置数据类型 DDS::PublicationBuiltinTopicData 关联的数据读者
 *  
 * @details 用于从ZRDDS中获取内置发布者主题数据，该类由 DDS::ZRDDSDataReader 类模板实例化，模板参数为：
 *          DDS::PublicationBuiltinTopicData DDS::PublicationBuiltinTopicDataSeq ，用法参见
 *          DDS::DomainParticipant::get_builtin_subscriber 。
 */
typedef DCPSDLL ZRDDSDataReader<PublicationBuiltinTopicData, PublicationBuiltinTopicDataSeq> PublicationBuiltinTopicDataDataReader;

/**
 * @struct DDS::SubscriptionBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   声明内置数据类型 DDS::SubscriptionBuiltinTopicData 的序列。
 */
typedef struct DDS_SubscriptionBuiltinTopicDataSeq SubscriptionBuiltinTopicDataSeq;

/**  
 * @class DDS::SubscriptionBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief 声明内置数据类型 DDS::SubscriptionBuiltinTopicData 关联的数据读者
 *  
 * @details 用于从ZRDDS中获取内置订阅端主题数据，该类由 DDS::ZRDDSDataReader 类模板实例化，模板参数为：
 *          DDS::SubscriptionBuiltinTopicData DDS::SubscriptionBuiltinTopicDataSeq ，用法参见
 *          DDS::DomainParticipant::get_builtin_subscriber 。
 */
typedef DCPSDLL ZRDDSDataReader<SubscriptionBuiltinTopicData, SubscriptionBuiltinTopicDataSeq> SubscriptionBuiltinTopicDataDataReader;

#ifdef _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

/**
 * @struct DDS::TopicBuiltinTopicDataSeq
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief   声明内置数据类型 DDS::TopicBuiltinTopicDataSeq 的序列。
 */
typedef struct DDS_TopicBuiltinTopicDataSeq TopicBuiltinTopicDataSeq;

/**  
 * @class DDS::TopicBuiltinTopicDataDataReader
 *
 * @ingroup CppDiscoveryTypes
 *
 * @brief 声明内置数据类型 DDS::TopicBuiltinTopicData 关联的数据读者
 *  
 * @details 用于从ZRDDS中获取内置订阅端主题数据，该类由 DDS::ZRDDSDataReader 类模板实例化，模板参数为：
 *          DDS::TopicBuiltinTopicData DDS::TopicBuiltinTopicDataSeq ，用法参见
 *          DDS::DomainParticipant::get_builtin_subscriber 。
 */
typedef DCPSDLL ZRDDSDataReader<TopicBuiltinTopicData, TopicBuiltinTopicDataSeq> TopicBuiltinTopicDataDataReader;

#endif // _ZRDDS_INCLUDE_TOPIC_BUILTIN_TOPIC_DATA

#if defined(_ZRDDSSECURITY)
/**
* @struct DDS::PublicationBuiltinTopicDataSecureSeq
*
* @ingroup CppDiscoveryTypes
*
* @brief   声明内置数据类型 DDS::PublicationBuiltinTopicDataSecure 的序列。
*/

/**
* @class DDS::PublicationBuiltinTopicDataSecureDataReader
*
* @ingroup CppDiscoveryTypes
*
* @brief 声明内置数据类型 DDS::PublicationBuiltinTopicDataSecure 关联的数据读者
*
* @details 用于从ZRDDS中获取内置发布者主题数据，该类由 DDS::ZRDDSDataReader 类模板实例化，模板参数为：
*          DDS::PublicationBuiltinTopicDataSecure DDS::PublicationBuiltinTopicDataSecureSeq ，用法参见
*          DDS::DomainParticipant::get_builtin_subscriber 。
*/

typedef struct DDS_PublicationBuiltinTopicDataSeq PublicationBuiltinTopicDataSecureSeq;
typedef DCPSDLL ZRDDSDataReader<PublicationBuiltinTopicDataSecure, PublicationBuiltinTopicDataSecureSeq>
    PublicationBuiltinTopicDataSecureDataReader;

/**
* @struct DDS::SubscriptionBuiltinTopicDataSecureSeq
*
* @ingroup CppDiscoveryTypes
*
* @brief   声明内置数据类型 DDS::SubscriptionBuiltinTopicDataSecure 的序列。
*/

/**
* @class DDS::SubscriptionBuiltinTopicDataSecureDataReader
*
* @ingroup CppDiscoveryTypes
*
* @brief 声明内置数据类型 DDS::SubscriptionBuiltinTopicDataSecure 关联的数据读者
*
* @details 用于从ZRDDS中获取内置订阅端主题数据，该类由 DDS::ZRDDSDataReader 类模板实例化，模板参数为：
*          DDS::SubscriptionBuiltinTopicDataSecure DDS::SubscriptionBuiltinTopicDataSecureSeq ，用法参见
*          DDS::DomainParticipant::get_builtin_subscriber 。
*/

typedef struct DDS_SubscriptionBuiltinTopicDataSeq SubscriptionBuiltinTopicDataSecureSeq;
typedef DCPSDLL ZRDDSDataReader<SubscriptionBuiltinTopicDataSecure, SubscriptionBuiltinTopicDataSecureSeq>
    SubscriptionBuiltinTopicDataSecureDataReader;

#endif // _ZRDDSSECURITY

} // namespace DDS

#endif // BuiltinDataDataReader_h__
