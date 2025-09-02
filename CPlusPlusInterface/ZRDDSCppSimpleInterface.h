#ifndef ZRDDSCppSimpleInterface_h__
#define ZRDDSCppSimpleInterface_h__

#include "ZROSDefine.h"

#ifdef _ZRDDS_INCLUDE_SIMPLE_INTERFACE

#include "DomainParticipantFactory.h"
#include "DomainParticipant.h"
#include "ZRDDSTypeSupport.h"
#include "DataReader.h"
#include "DataWriter.h"
#include "ZRBuiltinTypesTypeSupport.h"
#include "ZRBuiltinTypesDataReader.h"
#include "ZRBuiltinTypesDataWriter.h"
#include "DataReaderListener.h"
#include "ZRSleep.h"

namespace DDS {

/**
 * @class   DDSIF DDSIF_SUSTAIN
 *
 * @brief   DDS的CPP简易接口，所有的方法均为静态方法。
 */

class DCPSDLL DDSIF_SUSTAIN
{
public:

    /**
     * @fn  static DomainParticipantFactory* DDSIF_SUSTAIN::Init( const Char* qosFilePath, const Char* qosName);
     *
     * @brief   以指定配置初始化DDS中间件，只在整个程序初始化时调用一次即可。
     *
     * @param   qosFilePath QoS配置文件的路径，可以是绝对路径，也可以是程序运行目录的相对路径，
     *                      为NULL时，默认使用运行目录的 ZRDDS_QOS_PROFILES.xml 配置文件。
     * @param   qosName     QoS配置文件中工厂QoS配置名称，DDS将以 default_lib::default_profile::qosName 代表的QoS初始化DDS域厂，
     *                      允许为NULL，表明使用配置文件中名称为default的配置。
     *
     * @return  NULL表示失败，否则返回DDS域工厂单例。
     */

    static DomainParticipantFactory* Init(
        const Char* qosFilePath,
        const Char* qosName);

    /**
     * @fn  static DomainParticipant* DDSIF_SUSTAIN::CreateDP( const DomainId_t domainId, const Char* qos_name);
     *
     * @brief   DDS创建域参与者，并指明域号与QoS配置名称，同一个域号可能有多个域参与者，
     *          需要为使用不同底层传输协议的主题创建不同的域参与者，即通常SRIO、UDP、TCP的域参与者各一个。
     *
     * @param   domainId    指明域号，域号范围0-232.
     * @param   qos_name    指明QoS配置文件中域参与者QoS配置名称，允许为NULL，表明使用配置文件中名称为default的配置。
     *
     * @return  NULL表示失败，否则返回域参与者的指针，该指针用于后续创建发布者以及订阅者。
     */

    static DomainParticipant* CreateDP(
        const DomainId_t domainId,
        const Char* qos_name);

    /**
     * @fn  static DataWriter* DDSIF_SUSTAIN::PubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataWriterListener* dwListener);
     *
     * @brief   发布主题，指定域参与者、主题名、类型名、QoS配置名称以及监听器。
     *
     * @param [in,out]  self        指明域参与者。
     * @param   topicName           主题名称。
     * @param [in,out]  typeSupport 类型支持对象指明关联的数据类型，规则为： &amp;类型名称+TypeSupport::get_instance,
     *                              如果为零拷贝数据类型则传输 &amp;ZeroCopyBytesTypeSupport::get_instance， 内置非零拷贝传入
     *                              &amp;BytesTypeSupport::get_instance，IDL文件自动生成的传入 &amp;
     *                              类型名称TypeSupport::get_instance对象。
     * @param   qos_name            指明QoS配置文件中数据写者QoS配置名称，允许为NULL，表明使用配置文件中名称为default的配置。
     * @param [in,out]  dwListener  发布者的监听器，用于扩展，填NULL即可。
     *
     * @return  NULL表示失败，否则返回数据写者指针（用于唯一标识创建好的发布者）。
     */

    static DataWriter* PubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataWriterListener* dwListener);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnPubTopic(DataWriter* writer);
     *
     * @brief   指明数据写者指针取消发布。
     *
     * @param [in,out]  writer  指明数据写者指针。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnPubTopic(DataWriter* writer);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   通过域以及主题名称取消发布，如果域内存在多个主题名相同的发布者将删除所有同名主题发布。 
     *          该接口仅在指定域内有且仅有一个域参与者条件下使用；
     *
     * @param   domainId    指明域号。
     * @param   topicName   指明主题名称。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static DataReader* DDSIF_SUSTAIN::SubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataReaderListener* drListener);
     *
     * @brief   订阅主题，指定域参与者、主题名、类型名以及QoS配置名称。
     *
     * @param [in,out]  self        指明域参与者。
     * @param   topicName           主题名称。
     * @param [in,out]  typeSupport 类型支持对象指明关联的数据类型，规则为： &amp;类型名称+TypeSupport::get_instance,
     *                              如果为零拷贝数据类型则传输 &amp;ZeroCopyBytesTypeSupport::get_instance， 内置非零拷贝传入
     *                              &amp;BytesTypeSupport::get_instance，IDL文件自动生成的传入 &amp;
     *                              类型名称TypeSupport::get_instance对象。
     * @param   qos_name            指明QoS配置文件中数据写者QoS配置名称，允许为NULL，表明使用配置文件中名称为default的配置。
     * @param [in,out]  drListener  订阅者的监听器，用于扩展，填NULL即可。
     *
     * @return  NULL表示失败，否则返回数据读者指针（用于唯一标识创建好的订阅者）。
     */

    static DataReader* SubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataReaderListener* drListener);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnSubTopic(DataReader* reader);
     *
     * @brief   指明数据读者指针取消订阅。
     *
     * @param [in,out]  reader  指明数据读者指针。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnSubTopic(DataReader* reader);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   通过域以及主题名称取消订阅，如果域内存在多个主题名相同的订阅者将删除所有同名主题订阅。 
     *          该接口仅在指定域内有且仅有一个域参与者条件下使用；
     *
     * @param   domainId    指明域号。
     * @param   topicName   指明主题名称。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::Finalize();
     *
     * @brief   清理资源。
     *
     * @return  RETCODE_OK表示成功，否则表示部分资源清理失败。
     */

    static ReturnCode_t Finalize();

    /**
     * @fn  static ZeroCopyBytes* DDSIF_SUSTAIN::ZeroCopyBytesCreate(ULong maximum);
     *
     * @brief   创建零拷贝对象，并按最大长度分配空间。
     *
     * @param   maximum 零拷贝最大可能发送的长度。
     *
     * @return  NULL表示失败，可能的原因为分配内存失败，否则返回零拷贝对象。
     */

    static ZeroCopyBytes* ZeroCopyBytesCreate(ULong maximum);

    /**
     * @fn  static void DDSIF_SUSTAIN::ZeroCopyBytesDestroy(ZeroCopyBytes* sample);
     *
     * @brief   与 ZeroCopyBytesCreate 函数对应的回收零拷贝对象空间。
     *
     * @param [in,out]  sample  指明零拷贝对象。
     */

    static void ZeroCopyBytesDestroy(ZeroCopyBytes* sample);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::ZeroCopyBytesWrite( DomainId_t domainId, Char* topicName, ZeroCopyBytes* sample);
     *
     * @brief   向指定的域发送指定主题的零拷贝数据。使用该接口的前提：
     *          - 指定的域内有且仅有一个域参与者；
     *          - 指定的域内有且仅有一个与指定主题关联的发布者；
     *          - 指定的主题关联的数据类型为零拷贝数据类型；
     *          如果不满足以上条件，请使用 ZeroCopyBytesDataWriter::write 接口指定发布者发送数据。.
     *
     * @param   domainId            指明域号。
     * @param [in,out]  topicName   指明主题名称。
     * @param [in,out]  sample      指明发送的数据。
     *
     * @return  #RETCODE_OK 表示发送成功， 其他表示失败。
     */

    static ReturnCode_t ZeroCopyBytesWrite(
        DomainId_t domainId,
        Char* topicName,
        ZeroCopyBytes* sample);

    /**
     * @fn  static Long DDSIF_SUSTAIN::BytesWrapper(Bytes& self, const Char* buffer, const Long length);
     *
     * @brief   用户缓冲区包装成DDS_Bytes类型（非零拷贝缓冲区数据类型），该接口不分配空间，无需对应的回收函数。.
     *
     * @param [in,out]  self    指明包装的目标。
     * @param   buffer          用户提供空间。
     * @param   length          空间长度。
     *
     * @return  0表示成功，否则表示失败。
     */

    static Long BytesWrapper(Bytes& self, const Char* buffer, const Long length);

    /**
     * @fn  static ReturnCode_t DDSIF_SUSTAIN::BytesWrite( DomainId_t domainId, Char* topicName, const Char* content, const Long length);
     *
     * @brief   向指定的域发送指定主题的非零拷贝Bytes数据。使用该接口的前提：
     *          - 指定的域内有且仅有一个域参与者；
     *          - 指定的域内有且仅有一个与指定主题关联的发布者；
     *          - 指定的主题关联的数据类型为Bytes数据类型；
     *          如果不满足以上条件，请使用 BytesDataWriter::write 接口指定发布者发送数据。
     *
     * @param   domainId            指明域号。
     * @param [in,out]  topicName   指明主题名称。
     * @param   content             发送内容缓冲区。
     * @param   length              缓冲区长度。
     *
     * @return  #RETCODE_OK 表示发送成功， 其他表示失败。
     */

    static ReturnCode_t BytesWrite(
        DomainId_t domainId,
        Char* topicName,
        const Char* content,
        const Long length);
};
class DCPSDLL DDSIF
{
public:

    /**
     * @fn  static DomainParticipantFactory* DDSIF::Init( const Char* qosFilePath, const Char* qosName);
     *
     * @brief   以指定配置初始化DDS中间件，只在整个程序初始化时调用一次即可。
     *
     * @param   qosFilePath QoS配置文件的路径，可以是绝对路径，也可以是程序运行目录的相对路径，
     *                      为NULL时，默认使用运行目录的 ZRDDS_QOS_PROFILES.xml 配置文件。
     * @param   qosName     QoS配置文件中工厂QoS配置名称，DDS将以 default_lib::default_profile::qosName 代表的QoS初始化DDS域厂，
     *                      允许为NULL，表明使用配置文件中名称为default的配置。
     *
     * @return  NULL表示失败，否则返回DDS域工厂单例。
     */

    static DomainParticipantFactory* Init(
        const Char* qosFilePath,
        const Char* qosName);

    /**
     * @fn  static DomainParticipant* DDSIF::CreateDP( const DomainId_t domainId, const Char* qos_name);
     *
     * @brief   DDS创建域参与者，并指明域号与QoS配置名称，同一个域号可能有多个域参与者，
     *          需要为使用不同底层传输协议的主题创建不同的域参与者，即通常SRIO、UDP、TCP的域参与者各一个。
     *
     * @param   domainId    指明域号，域号范围0-232.
     * @param   qos_name    指明QoS配置文件中域参与者QoS配置名称，允许为NULL，表明使用配置文件中名称为default的配置。
     *
     * @return  NULL表示失败，否则返回域参与者的指针，该指针用于后续创建发布者以及订阅者。
     */

    static DomainParticipant* CreateDP(
        const DomainId_t domainId,
        const Char* qos_name);

    /**
     * @fn  static DataWriter* DDSIF::PubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataWriterListener* dwListener);
     *
     * @brief   发布主题，指定域参与者、主题名、类型名、QoS配置名称以及监听器。
     *
     * @param [in,out]  self        指明域参与者。
     * @param   topicName           主题名称。
     * @param [in,out]  typeSupport 类型支持对象指明关联的数据类型，规则为： &amp;类型名称+TypeSupport::get_instance,
     *                              如果为零拷贝数据类型则传输 &amp;ZeroCopyBytesTypeSupport::get_instance， 内置非零拷贝传入
     *                              &amp;BytesTypeSupport::get_instance，IDL文件自动生成的传入 &amp;
     *                              类型名称TypeSupport::get_instance对象。
     * @param   qos_name            指明QoS配置文件中数据写者QoS配置名称，允许为NULL，表明使用配置文件中名称为default的配置。
     * @param [in,out]  dwListener  发布者的监听器，用于扩展，填NULL即可。
     *
     * @return  NULL表示失败，否则返回数据写者指针（用于唯一标识创建好的发布者）。
     */

    static DataWriter* PubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataWriterListener* dwListener);

    /**
     * @fn  static ReturnCode_t DDSIF::UnPubTopic(DataWriter* writer);
     *
     * @brief   指明数据写者指针取消发布。
     *
     * @param [in,out]  writer  指明数据写者指针。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnPubTopic(DataWriter* writer);

    /**
     * @fn  static ReturnCode_t DDSIF::UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   通过域以及主题名称取消发布，如果域内存在多个主题名相同的发布者将删除所有同名主题发布。 
     *          该接口仅在指定域内有且仅有一个域参与者条件下使用；
     *
     * @param   domainId    指明域号。
     * @param   topicName   指明主题名称。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnPubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static DataReader* DDSIF::SubTopic( DomainParticipant* self, const Char* topicName, TypeSupport* typeSupport, const Char* qos_name, DataReaderListener* drListener);
     *
     * @brief   订阅主题，指定域参与者、主题名、类型名以及QoS配置名称。
     *
     * @param [in,out]  self        指明域参与者。
     * @param   topicName           主题名称。
     * @param [in,out]  typeSupport 类型支持对象指明关联的数据类型，规则为： &amp;类型名称+TypeSupport::get_instance,
     *                              如果为零拷贝数据类型则传输 &amp;ZeroCopyBytesTypeSupport::get_instance， 内置非零拷贝传入
     *                              &amp;BytesTypeSupport::get_instance，IDL文件自动生成的传入 &amp;
     *                              类型名称TypeSupport::get_instance对象。
     * @param   qos_name            指明QoS配置文件中数据写者QoS配置名称，允许为NULL，表明使用配置文件中名称为default的配置。
     * @param [in,out]  drListener  订阅者的监听器，用于扩展，填NULL即可。
     *
     * @return  NULL表示失败，否则返回数据读者指针（用于唯一标识创建好的订阅者）。
     */

    static DataReader* SubTopic(
        DomainParticipant* self,
        const Char* topicName,
        TypeSupport* typeSupport,
        const Char* qos_name,
        DataReaderListener* drListener);

    /**
     * @fn  static ReturnCode_t DDSIF::UnSubTopic(DataReader* reader);
     *
     * @brief   指明数据读者指针取消订阅。
     *
     * @param [in,out]  reader  指明数据读者指针。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnSubTopic(DataReader* reader);

    /**
     * @fn  static ReturnCode_t DDSIF::UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);
     *
     * @brief   通过域以及主题名称取消订阅，如果域内存在多个主题名相同的订阅者将删除所有同名主题订阅。 
     *          该接口仅在指定域内有且仅有一个域参与者条件下使用；
     *
     * @param   domainId    指明域号。
     * @param   topicName   指明主题名称。
     *
     * @return  #RETCODE_OK 表示取消成功，其他表示失败；
     */

    static ReturnCode_t UnSubTopicWTopicName(DomainId_t domainId, const Char* topicName);

    /**
     * @fn  static ReturnCode_t DDSIF::Finalize();
     *
     * @brief   清理资源。
     *
     * @return  RETCODE_OK表示成功，否则表示部分资源清理失败。
     */

    static ReturnCode_t Finalize();

    /**
     * @fn  static ZeroCopyBytes* DDSIF::ZeroCopyBytesCreate(ULong maximum);
     *
     * @brief   创建零拷贝对象，并按最大长度分配空间。
     *
     * @param   maximum 零拷贝最大可能发送的长度。
     *
     * @return  NULL表示失败，可能的原因为分配内存失败，否则返回零拷贝对象。
     */

    static ZeroCopyBytes* ZeroCopyBytesCreate(ULong maximum);

    /**
     * @fn  static void DDSIF::ZeroCopyBytesDestroy(ZeroCopyBytes* sample);
     *
     * @brief   与 ZeroCopyBytesCreate 函数对应的回收零拷贝对象空间。
     *
     * @param [in,out]  sample  指明零拷贝对象。
     */

    static void ZeroCopyBytesDestroy(ZeroCopyBytes* sample);

    /**
     * @fn  static ReturnCode_t DDSIF::ZeroCopyBytesWrite( DomainId_t domainId, Char* topicName, ZeroCopyBytes* sample);
     *
     * @brief   向指定的域发送指定主题的零拷贝数据。使用该接口的前提：
     *          - 指定的域内有且仅有一个域参与者；
     *          - 指定的域内有且仅有一个与指定主题关联的发布者；
     *          - 指定的主题关联的数据类型为零拷贝数据类型；
     *          如果不满足以上条件，请使用 ZeroCopyBytesDataWriter::write 接口指定发布者发送数据。.
     *
     * @param   domainId            指明域号。
     * @param [in,out]  topicName   指明主题名称。
     * @param [in,out]  sample      指明发送的数据。
     *
     * @return  #RETCODE_OK 表示发送成功， 其他表示失败。
     */

    static ReturnCode_t ZeroCopyBytesWrite(
        DomainId_t domainId,
        Char* topicName,
        ZeroCopyBytes* sample);

    /**
     * @fn  static Long DDSIF::BytesWrapper(Bytes& self, const Char* buffer, const Long length);
     *
     * @brief   用户缓冲区包装成DDS_Bytes类型（非零拷贝缓冲区数据类型），该接口不分配空间，无需对应的回收函数。.
     *
     * @param [in,out]  self    指明包装的目标。
     * @param   buffer          用户提供空间。
     * @param   length          空间长度。
     *
     * @return  0表示成功，否则表示失败。
     */

    static Long BytesWrapper(Bytes& self, const Char* buffer, const Long length);

    /**
     * @fn  static ReturnCode_t DDSIF::BytesWrite( DomainId_t domainId, Char* topicName, const Char* content, const Long length);
     *
     * @brief   向指定的域发送指定主题的非零拷贝Bytes数据。使用该接口的前提：
     *          - 指定的域内有且仅有一个域参与者；
     *          - 指定的域内有且仅有一个与指定主题关联的发布者；
     *          - 指定的主题关联的数据类型为Bytes数据类型；
     *          如果不满足以上条件，请使用 BytesDataWriter::write 接口指定发布者发送数据。
     *
     * @param   domainId            指明域号。
     * @param [in,out]  topicName   指明主题名称。
     * @param   content             发送内容缓冲区。
     * @param   length              缓冲区长度。
     *
     * @return  #RETCODE_OK 表示发送成功， 其他表示失败。
     */

    static ReturnCode_t BytesWrite(
        DomainId_t domainId,
        Char* topicName,
        const Char* content,
        const Long length);
};
} // namespace DDS

#endif //_ZRDDS_INCLUDE_SIMPLE_INTERFACE

#endif // ZRDDSCppSimpleInterface_h__
