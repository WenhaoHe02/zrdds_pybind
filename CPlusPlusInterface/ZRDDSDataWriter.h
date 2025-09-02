/**
 * @file:       ZRDDSDataWriter.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSDataWriter_h__
#define ZRDDSDataWriter_h__

#include "DataWriter.h"
#include <stdlib.h>

struct DataWriterImpl;

namespace DDS {

/**
 * @class   ZRDDSDataWriter
 *
 * @ingroup CppPublication
 *
 * @tparam  T       用户定义数据类型，例如： Foo
 *
 * @brief   ZRDDS提供的数据写者模板类，用于提供强类型安全接口的数据写者接口。
 *          
 * @details 模板参数T为用户定义数据类型，本模板仅定义数据写者中与主题关联的数据类型相关的接口，
 *          其余与类型无关的接口直接使用父类 DDS::DataWriter 的即可。
 *
 */
template<typename T>
class ZRDDSDataWriter : public DataWriter
{
public:

    /**
     * @fn InstanceHandle_t ZRDDSDataWriter::register_instance(const T& data);
     *
     * @brief 向数据写者注册一个实例
     *
     * @details 当数据类型T中带有键域声明的成员时，成员的取值不同会形成不同的实例，
     *          该接口向数据写者注册一个实例，数据写者会读取传入的 @e data 中声明为键域的数据域，
     *          根据其值生成一个实例句柄并返回给用户。实例句柄用于索引实例，如 #write 操作中的 @e handle 参数。
     *          当 DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == true 时，
     *          且调用 #write 接口时 @e handle 参数传入 #DDS_HANDLE_NIL_NATIVE 时，会自动注册未注册的实例，
     *          但是发送速度会减慢，因此可使用先注册的实例句柄提升发送的速度。
     *
     * @param data 样本内容，只有被声明为键域的成员会被读取。
     *
     * @return 如果注册成功，返回样本对应的实例句柄，否则返回 #DDS_HANDLE_NIL_NATIVE
     */
    InstanceHandle_t register_instance(const T& data);

    /**
     * @fn InstanceHandle_t ZRDDSDataWriter::register_instance_w_timestamp( const T& data, const Time_t& timestamp);
     *
     * @brief 向数据写者注册一个实例（见 #register_instance ），并使用提供的时间戳覆盖默认的时间戳
     *
     * @param data      样本内容，只有被声明为键域的成员会被读取。
     * @param timestamp 用户提供的时间戳
     *
     * @return 如果注册成功，返回样本对应的实例句柄，否则返回 #DDS_HANDLE_NIL_NATIVE
     */
    InstanceHandle_t register_instance_w_timestamp(
        const T& data,
        const Time_t& timestamp);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::unregister_instance( const T& data, const InstanceHandle_t& handle);
     *
     * @brief 将已经注册的实例从数据写者中注销
     *
     * @details 可以使用数据样本或实例句柄进行注销，两者同时提供且有冲突或都缺失时，返回错误
     *
     * @param data   样本内容，只有被声明为键域的成员会被读取
     * @param handle 注册实例时得到的实例句柄或 #DDS_HANDLE_NIL_NATIVE
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示注销实例成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET  :参数中提供的样本与实例句柄不匹配；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t unregister_instance(
        const T& data,
        const InstanceHandle_t& handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::unregister_instance_w_timestamp( const T& data, const InstanceHandle_t& handle, const Time_t& timestamp);
     *
     * @brief 将已经注册的实例从数据写者中注销（见 #unregister_instance ），并使用提供的时间戳覆盖默认的时间戳
     *
     * @details 可以使用数据样本或实例句柄进行注销，两者同时提供且有冲突或都缺失时，返回错误。
     *
     * @param data      样本内容，只有被声明为键域的成员会被读取
     * @param handle    注册实例时得到的实例句柄或 #DDS_HANDLE_NIL_NATIVE
     * @param timestamp 用户提供的时间戳
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示注销实例成功；
     *         - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *         - #DDS_RETCODE_PRECONDITION_NOT_MET  :参数中提供的样本与实例句柄不匹配；
     *         - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t unregister_instance_w_timestamp(
        const T& data,
        const InstanceHandle_t& handle,
        const Time_t& timestamp);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::get_key_value( T& key_holder, const InstanceHandle_t& handle);
     *
     * @brief 从实例句柄获取对应的样本值，只有声明为键域的数据域的值有效。
     *
     * @param [in,out] key_holder 保存获取到的样本值内容的样本
     * @param handle              需要获取的实例对应的实例句柄
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t get_key_value(
        T& key_holder,
        const InstanceHandle_t& handle);

    /**
     * @fn InstanceHandle_t ZRDDSDataWriter::lookup_instance(const T& key_holder);
     *
     * @brief 通过样本值查询实例句柄。
     *
     * @param key_holder 保存样本值内容的样本
     *
     * @return 如果查询成功，返回样本对应的实例句柄，否则返回 #DDS_HANDLE_NIL_NATIVE
     */
    InstanceHandle_t lookup_instance(const T& key_holder);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write(const T& data, const InstanceHandle_t& handle);
     *
     * @brief 发布一个数据样本。
     *
     * @details 该接口可能发生阻塞：当设置为可靠传输，且该数据写者历史数据配置 DDS_HistoryQosPolicy::kind == 
     *          #DDS_KEEP_ALL_HISTORY_QOS 时，若样本超出限制时会发生阻塞，
     *          当使用同步发送且调用协议栈接口出现阻塞时会发生阻塞，
     *          若因样本超出限制导致阻塞，最长阻塞时间通过 DDS_ReliabilityQosPolicy::max_blocking_time 配置，
     *          因协议栈导致的阻塞最长阻塞时间不可预知
     *
     * @param data   需要发布的数据样本。
     * @param handle 数据样本对应的实例句柄，当该数据写者资源限制配置 
     *               DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == true时，
     *               可以传入 #DDS_HANDLE_NIL_NATIVE ，此时底层将自动注册 @e data 所属数据实例。
     *
     * @return 当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :当前资源不足；
     *          - #DDS_RETCODE_TIMEOUT :当前操作超时；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t write(const T& data, const InstanceHandle_t& handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write_w_timestamp( const T& instance, const InstanceHandle_t& handle, const Time_t& timestamp);
     *
     * @brief 发布一个数据样本（见 #write ），并使用提供的时间戳覆盖默认的时间戳。
     *
     * @param instance  需要发布的数据样本。
     * @param handle    数据样本对应的实例句柄，当该数据写者资源限制配置
     *               DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == true时，
     *               可以传入 #DDS_HANDLE_NIL_NATIVE ，此时底层将自动注册 @e instance 所属数据实例。
     * @param timestamp 用户提供的时间戳
     *
     * @return 当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :当前资源不足；
     *          - #DDS_RETCODE_TIMEOUT :当前操作超时；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t write_w_timestamp(
        const T& instance, 
        const InstanceHandle_t& handle, 
        const Time_t& timestamp);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write_w_dst(const T& instance, const InstanceHandle_t& handle, const Time_t& timestamp, const InstanceHandle_t& dst_handle);
     *
     * @brief 向指定对端发布一个数据样本。
     *
     * @param instance      需要发布的数据样本。
     * @param handle        数据样本对应的实例句柄，当该数据写者资源限制配置
     *                      DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == true时，
     *                      可以传入 #DDS_HANDLE_NIL_NATIVE ，此时底层将自动注册 @e instance 所属数据实例。
     * @param timestamp     用户提供的时间戳
     * @param dst_handle    对端的唯一标识，若为数据读者的唯一标识，则向该数据读者发布；若为域参与者的唯一标识，则向该域参与者创建的所有数据读者发布。
     *
     * @return 当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :当前资源不足；
     *          - #DDS_RETCODE_TIMEOUT :当前操作超时；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t write_w_dst(
        const T& instance,
        const InstanceHandle_t& handle,
        const Time_t& timestamp,
        const InstanceHandle_t& dst_handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::write_w_dst(const T& instance, const InstanceHandle_t& handle, const InstanceHandle_t& dst_handle);
     *
     * @brief 向指定对端发布一个数据样本。
     *
     * @param instance      需要发布的数据样本。
     * @param handle        数据样本对应的实例句柄，当该数据写者资源限制配置
     *                      DDS_DataWriterResourceLimitsQosPolicy::autoregister_instances == true时，
     *                      可以传入 #DDS_HANDLE_NIL_NATIVE ，此时底层将自动注册 @e instance 所属数据实例。
     * @param dst_handle    对端的唯一标识，若为数据读者的唯一标识，则向该数据读者发布；若为域参与者的唯一标识，则向该域参与者创建的所有数据读者发布。
     *
     * @return 当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示获取成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_OUT_OF_RESOURCES :当前资源不足；
     *          - #DDS_RETCODE_TIMEOUT :当前操作超时；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t write_w_dst(
        const T& instance,
        const InstanceHandle_t& handle,
        const InstanceHandle_t& dst_handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::dispose( const T& instance, const InstanceHandle_t& handle);
     *
     * @brief 销毁一个已经注册的实例。
     *
     * @details 可以使用数据样本或实例句柄进行销毁，两者同时提供且有冲突或都缺失时，返回错误。
     *
     * @param instance  样本内容，只有被声明为键域的成员会被读取
     * @param handle    注册实例时得到的实例句柄或 #DDS_HANDLE_NIL_NATIVE
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示注销实例成功；
     *          - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET  :参数中提供的样本与实例句柄不匹配；
     *          - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t dispose(
        const T& instance, 
        const InstanceHandle_t& handle);

    /**
     * @fn ReturnCode_t ZRDDSDataWriter::dispose_w_timestamp( const T& instance, const InstanceHandle_t& handle, const Time_t& timestamp);
     *
     * @brief 销毁一个已经注册的实例（见 #unregister_instance ），并使用提供的时间戳覆盖默认的时间戳。
     *
     * @param instance  样本内容，只有被声明为键域的成员会被读取
     * @param handle    注册实例时得到的实例句柄或 #DDS_HANDLE_NIL_NATIVE
     * @param timestamp 用户提供的时间戳
     *
     * @return 当前可能的返回值如下：
     *         - #DDS_RETCODE_OK :表示注销实例成功；
     *         - #DDS_RETCODE_NOT_ENABLED :表示实体未使能；
     *         - #DDS_RETCODE_PRECONDITION_NOT_MET  :参数中提供的样本与实例句柄不匹配；
     *         - #DDS_RETCODE_BAD_PARAMETER :参数中存在错误；
     *         - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     *
     * @details 可以使用数据样本或实例句柄进行销毁，两者同时提供且有冲突或都缺失时，返回错误。
     */
    ReturnCode_t dispose_w_timestamp(
        const T& instance, 
        const InstanceHandle_t& handle, 
        const Time_t& timestamp);
    static ZRDDSDataWriter* createI(DataWriter *impl, void *typesupport);
    static ReturnCode_t destroyI(ZRDDSDataWriter *dw, void* typesupport);
protected:
    ZRDDSDataWriter(DataWriter *impl);
};

template<typename T>
ZRDDSDataWriter<T>::ZRDDSDataWriter(DataWriter *impl)
    :DataWriter(impl)
{

}

template<typename T>
ZRDDSDataWriter<T>* ZRDDSDataWriter<T>::createI(DataWriter *impl, void *typesupport)
{
    return new ZRDDSDataWriter<T>(impl);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::destroyI(ZRDDSDataWriter *dw, void* typesupport)
{
    if (NULL != dw) delete dw;
    return DDS_RETCODE_OK;
}

template<typename T>
InstanceHandle_t ZRDDSDataWriter<T>::register_instance(const T& data)
{
    return m_impl->register_instance_untype(&data, NULL);
}

template<typename T>
InstanceHandle_t ZRDDSDataWriter<T>::register_instance_w_timestamp(
    const T& data,
    const Time_t& timestamp)
{
    return m_impl->register_instance_untype(&data, &timestamp);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::unregister_instance(
    const T& data,
    const InstanceHandle_t& handle)
{
    return m_impl->unregister_instance_untype(&data, handle, NULL);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::unregister_instance_w_timestamp(
    const T& data,
    const InstanceHandle_t& handle,
    const Time_t& timestamp)
{
    return m_impl->unregister_instance_untype(&data, handle, &timestamp);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::get_key_value(
    T& key_holder,
    const InstanceHandle_t& handle)
{
    return m_impl->get_key_value_untype(&key_holder, handle);
}

template<typename T>
InstanceHandle_t ZRDDSDataWriter<T>::lookup_instance(const T& key_holder)
{
    return m_impl->lookup_instance_untype(&key_holder);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::write(const T& data, const InstanceHandle_t& handle)
{
    return m_impl->write_untype_w_dst(&data, handle, NULL, NULL);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::write_w_timestamp(
    const T& data,
    const InstanceHandle_t& handle,
    const Time_t& timestamp)
{
    return m_impl->write_untype_w_dst(&data, handle, &timestamp, NULL);
}

template<typename T>
ReturnCode_t DDS::ZRDDSDataWriter<T>::write_w_dst(
    const T& instance,
    const InstanceHandle_t& handle,
    const Time_t& timestamp,
    const InstanceHandle_t& dst_handle)
{
    return m_impl->write_untype_w_dst(&instance, handle, &timestamp, &dst_handle);
}

template<typename T>
ReturnCode_t DDS::ZRDDSDataWriter<T>::write_w_dst(
    const T& instance,
    const InstanceHandle_t& handle,
    const InstanceHandle_t& dst_handle)
{
    return m_impl->write_untype_w_dst(&instance, handle, NULL, &dst_handle);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::dispose(
    const T& instance,
    const InstanceHandle_t& handle)
{
    return m_impl->dispose_untype(&instance, handle, NULL);
}

template<typename T>
ReturnCode_t ZRDDSDataWriter<T>::dispose_w_timestamp(
    const T& instance,
    const InstanceHandle_t& handle,
    const Time_t& timestamp)
{
    return m_impl->dispose_untype(&instance, handle, &timestamp);
}

} // namespace DDS

#endif // ZRDDSDataWriter_h__
