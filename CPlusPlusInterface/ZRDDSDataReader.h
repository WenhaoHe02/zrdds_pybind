/**
 * @file:       ZRDDSDataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSDataReader_h__
#define ZRDDSDataReader_h__

#include "DataReader.h"

namespace DDS {

/**
 * @class   ZRDDSDataReader
 *
 * @ingroup CppSubscription
 *
 * @tparam  T       用户定义数据类型，例如： Foo 
 * @tparam  TSeq    用户定义数据类型序列，例如： FooSeq
 *
 * @brief   ZRDDS提供的订阅者模板类，用于提供强类型安全接口的数据读者接口。
 *          
 * @details 模板参数T为用户定义数据类型，TSeq用户定义数据类型序列，本模板仅定义数据读者中与主题关联的数据类型相关的接口，
 *          其余与类型无关的接口直接使用父类 DDS::DataReader 的即可。
 *
 */
template<typename T, typename TSeq>
class ZRDDSDataReader : public DataReader
{
public:

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   该接口从数据读者底层获取用户样本数据。
     *
     * @details 该方法返回的样本顺序参见 DDS_PresentationQosPolicy 。 @e data_values 以及 @e sample_infos 两个
     *          序列必须具有相同的 长度（ FooSeq::length 下简称len）、最大长度（ FooSeq::maximum 下简称max_len）、
     *          是否拥有空间（ FooSeq::has_ownership 下简称own） 三个属性，否则将返回 #DDS_RETCODE_PRECONDITION_NOT_MET 错误。
     *          当该函数返回成功时，@e data_values 以及 @e sample_infos 的这三个属性也相同，且下标相同的样本以及样本
     *          信息相对应。
     *          
     *          当 max_len == 0，则表明用户没有提供样本空间，该方法将以“租借”（零拷贝，返回数据的指针）的方式填充 
     *          @e data_values 以及 @e sample_infos ，即own属性设置成false，len设置为获取到的样本数量，
     *          当用户使用完返回的数据样本时应该调用 #return_loan 方法归还这些空间；
     *          
     *          当 max_len > 0 && own == true 时，则表明用户提供了样本空间，该方法将底层存储的数据样本以及
     *          对应的样本信息拷贝到提供的空间中，len表示拷贝的样本个数，max_len保持不变，这些数据样本序列无需归还，
     *          但为了统一用户的使用习惯，调用 #return_loan 亦可，底层会忽略本次调用。
     *          当 @e max_samples <= max_len 时，该方法至多获取 @e max_samples 个样本，
     *          当 @e max_samples > max_len 时，该方法将返回 #DDS_RETCODE_PRECONDITION_NOT_MET  错误。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   sample_mask             指定目标数据样本的访问状态集合的掩码；
     * @param   view_mask               指定目标数据样本的视图状态集合的掩码；
     * @param   instance_mask           指定目标数据样本的所属实例的实例状态集合的掩码；
     *                                  
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示取出数据成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET  :参数中存在错误；
     *          - #DDS_RETCODE_NO_DATA :表示当前没有满足条件的数据；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     *
     * @note    - 使用@ref read-take 系列函数时，应判断返回值是否成功，否则容易造成程序异常；
     *          - 在使用参数返回的数据时，应检查相应的 DDS_SampleInfo::valid_data 是否有效；  
     */

    ReturnCode_t read(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   该接口从数据读者底层取出用户样本数据。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   sample_mask             指定目标数据样本的访问状态集合的掩码；
     * @param   view_mask               指定目标数据样本的视图状态集合的掩码；
     * @param   instance_mask           指定目标数据样本的所属实例的实例状态集合的掩码；
     *
     * @details 该方法与 #read 方式类似，区别在于本方法会将获取到的数据样本从底层队列中移除，移除的时机如下：
     *          - 当采用零拷贝的方式获取时，在调用 #return_loan 后移除；  
     *          - 如果用户提供存储空间即采用拷贝的方式获取时，在本方法已经移除；
     *
     * @return  参见 #read 方法。
     */

    ReturnCode_t take(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_next_sample( T &data_value, SampleInfo &sample_info);
     *
     * @brief   该方法用于从通信中间件依次读取未读取过的样本。
     *          
     * @details 该方法由用户提供样本空间，将从底层的数据样本拷贝到参数提供的空间中，无需调用 #return_loan 方法。
     *          样本的顺序由 DDS_PresentationQosPolicy 确定。
     *
     * @param [in,out]  data_value  输入输出参数，保存从数据读者中读取的样本结果；
     * @param [in,out]  sample_info 输入输出参数，保存从数据读者中读取的样本信息结果；
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示取出数据成功；
     *          - #DDS_RETCODE_NO_DATA :表示当前没有满足条件的数据；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t read_next_sample(
        T &data_value,
        SampleInfo &sample_info);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_next_sample( T &data_value, SampleInfo &sample_info);
     *
     * @brief   该方法用于从通信中间件依次取出未读取过的样本。
     *
     * @param [in,out]  data_value  输入输出参数，保存从数据读者中读取的样本结果；
     * @param [in,out]  sample_info 输入输出参数，保存从数据读者中读取的样本信息结果；
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示取出数据成功；
     *          - #DDS_RETCODE_NO_DATA :表示当前没有满足条件的数据；
     *          - #DDS_RETCODE_ERROR :表示未知错误导致的读取错误。
     */
    ReturnCode_t take_next_sample(
        T &data_value,
        SampleInfo &sample_info);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   读取指定数据实例中满足条件的数据样本集合。
     *
     * @details 该方法在 #read 接口基础上再加上指定数据实例的要求。
     *          
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   handle                  指明目标数据实例的标识。
     * @param   sample_mask             指定目标数据样本的访问状态集合的掩码；
     * @param   view_mask               指定目标数据样本的视图状态集合的掩码；
     * @param   instance_mask           指定目标数据样本的所属实例的实例状态集合的掩码；
     *
     * @return  参见 #read 方法，此外当底层没有 @e handle 标识的数据实例信息时将返回 #DDS_RETCODE_BAD_PARAMETER 。
     */

    ReturnCode_t read_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   取出指定数据实例中满足条件的数据样本集合。
     *
     * @details 该方法在 #take 接口基础上再加上指定数据实例的要求。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   handle                  指明目标数据实例的标识。
     * @param   sample_mask             指定目标数据样本的访问状态集合的掩码；
     * @param   view_mask               指定目标数据样本的视图状态集合的掩码；
     * @param   instance_mask           指定目标数据样本的所属实例的实例状态集合的掩码；
     *
     * @return  参见 #read 方法，此外当底层没有 @e handle 标识的数据实例信息时将返回 #DDS_RETCODE_BAD_PARAMETER 。
     */

    ReturnCode_t take_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_next_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   读取指定数据实例后面（不一定为紧邻的数据实例）数据实例中满足条件的数据样本集合。
     *
     * @details 数据实例的顺序定义如下：
     *          - 传入 #DDS_HANDLE_NIL_NATIVE 特殊值，则从最小的数据实例开始查找。
     *          - 按照数据样本创建的时间顺序，即数据样本收到第一个数据样本的顺序。
     *          
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   previous_handle         指明当前的数据实例标识。
     * @param   sample_mask             指定目标数据样本的访问状态集合的掩码；
     * @param   view_mask               指定目标数据样本的视图状态集合的掩码；
     * @param   instance_mask           指定目标数据样本的所属实例的实例状态集合的掩码；
     *
     * @return  参见 #read 方法。
     */

    ReturnCode_t read_next_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_next_instance( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, SampleStateMask sample_mask, ViewStateMask view_mask, InstanceStateMask instance_mask);
     *
     * @brief   取出指定数据实例后面（不一定为紧邻的数据实例）数据实例中满足条件的数据样本集合。
     *
     * @details 数据实例的顺序定义如下：
     *          - 传入 #DDS_HANDLE_NIL_NATIVE 特殊值，则从最小的数据实例开始查找。
     *          - 按照数据样本创建的时间顺序，即数据样本收到第一个数据样本的顺序。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   previous_handle         指明当前的数据实例标识。
     * @param   sample_mask             指定目标数据样本的访问状态集合的掩码；
     * @param   view_mask               指定目标数据样本的视图状态集合的掩码；
     * @param   instance_mask           指定目标数据样本的所属实例的实例状态集合的掩码；
     *
     * @return  参见 #read 方法。
     */

    ReturnCode_t take_next_instance(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        SampleStateMask sample_mask,
        ViewStateMask view_mask,
        InstanceStateMask instance_mask);

#ifdef _ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_next_instance_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, ReadCondition *condition);
     *
     * @brief   读取指定数据实例后面（不一定为紧邻的数据实例）数据实例中满足条件的数据样本集合。
     *
     * @details 该方法与 #read_next_instance 功能完全相同，该方法使用 #DDS::ReadCondition 代替分开写的三个状态。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   previous_handle         指明当前的数据实例标识。
     * @param [in,out]  condition       指明目标状态。
     *
     * @return  参见 #read 方法，当传入的 @e condition 无效是，返回 #DDS_RETCODE_PRECONDITION_NOT_MET 。
     */

    ReturnCode_t read_next_instance_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        ReadCondition *condition);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_next_instance_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, const InstanceHandle_t &previous_handle, ReadCondition *condition);
     *
     * @brief   取出指定数据实例后面（不一定为紧邻的数据实例）数据实例中满足条件的数据样本集合。
     *
     * @details 该方法与 #take_next_instance 功能完全相同，该方法使用 #DDS::ReadCondition 代替分开写的三个状态。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param   previous_handle         指明当前的数据实例标识。
     * @param [in,out]  condition       指明目标状态。
     *
     * @return  参见 #read 方法，当传入的 @e condition 无效是，返回 #DDS_RETCODE_PRECONDITION_NOT_MET 。
     */

    ReturnCode_t take_next_instance_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        const InstanceHandle_t &previous_handle,
        ReadCondition *condition);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::read_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, ReadCondition *condition);
     *
     * @brief   该接口从数据读者底层获取用户样本数据。
     *
     * @details 该方法与 #read 功能完全相同，该方法使用 #DDS::ReadCondition 代替分开写的三个状态。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param [in,out]  condition       指明目标状态。
     *
     * @return  参见 #read 方法，当传入的 @e condition 无效是，返回 #DDS_RETCODE_PRECONDITION_NOT_MET 。
     */

    ReturnCode_t read_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        ReadCondition *condition);

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::take_w_condition( TSeq &data_values, SampleInfoSeq &sample_infos, Long max_samples, ReadCondition *condition);
     *
     * @brief   该接口从数据读者底层取出用户样本数据。
     *
     * @details 该方法与 #take 功能完全相同，该方法使用 #DDS::ReadCondition 代替分开写的三个状态。
     *
     * @param [in,out]  data_values     输入输出参数，保存从数据读者中读取的样本序列结果；
     * @param [in,out]  sample_infos    输入输出参数，保存从数据读者中读取的样本信息序列结果；
     * @param   max_samples             指明本次操作最多从底层读取的样本个数；
     * @param [in,out]  condition       指明目标状态。
     *
     * @return  参见 #read 方法，当传入的 @e condition 无效是，返回 #DDS_RETCODE_PRECONDITION_NOT_MET 。
     */

    ReturnCode_t take_w_condition(
        TSeq &data_values,
        SampleInfoSeq &sample_infos,
        Long max_samples,
        ReadCondition *condition);
#endif //_ZRDDS_INCLUDE_READ_CONDITION

    /**
     * @fn  ReturnCode_t ZRDDSDataReader::return_loan( TSeq &data_values, SampleInfoSeq &sample_infos);
     *
     * @brief   该方法用于应用归还从数据读者租借的空间。
     *          
     * @details 为了简化应用的使用，数据读者提供参数有效性检查，参数无效返回 #DDS_RETCODE_PRECONDITION_NOT_MET  
     *          当归还成功后，序列的最大长度以及长度属性设置为0，拥有空间设置为true。检查的有效性包括：
     *          - 传入的样本序列是否为通信中间件租借出去的，如果是，则进行归还操作，否则直接忽略；
     *          - 传入的样本序列是否完整以及样本信息以及样本是否一一对应；
     *          - 传入的样本序列是否属于该数据读者，如果是，则继续归还；
     *
     * @param [in,out]  data_values     从 #read #take 系列方法中返回的参数。
     * @param [in,out]  sample_infos    从 #read #take 系统方法中返回的参数。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示成功；
     *          - #DDS_RETCODE_PRECONDITION_NOT_MET :表示传入的参数不满足条件。
     */

    ReturnCode_t return_loan(
        TSeq &data_values,
        SampleInfoSeq &sample_infos);

    ReturnCode_t return_recv_buffer(
        SampleInfo &sample_info);

    ReturnCode_t loan_recv_buffer(
        SampleInfo &sample_info);
    /**
     * @fn  ReturnCode_t ZRDDSDataReader::get_key_value( T &key_holder, const InstanceHandle_t &handle);
     *
     * @brief   通过数据实例的唯一标识获取数据实例的键值。
     *
     * @param [in,out]  key_holder  出口参数，用于保存数据实例的键值，注意本函数仅仅填充键成员。。
     * @param   handle              传入的唯一标识。
     *
     * @return  当前可能的返回值如下：
     *          - #DDS_RETCODE_OK :表示成功；
     *          - #DDS_RETCODE_BAD_PARAMETER :表示底层没有指定的数据实例信息。
     */

    ReturnCode_t get_key_value(
        T &key_holder,
        const InstanceHandle_t &handle);

    /**
     * @fn  InstanceHandle_t ZRDDSDataReader::lookup_instance(T& instance);
     *
     * @brief   通过数据实例键值查找相应的标识。
     *
     * @param [in,out]  instance    代表数据实例的数据样本；
     *
     * @return  当前可能的返回值如下：
     *          - 有效的标识 （ DDS_InstanceHandle_t::valid ） 表示获取成功；
     *          - #DDS_HANDLE_NIL_NATIVE :表示底层没有指定数据实例的信息，或者关联的数据类型未定义键值；
     */

    InstanceHandle_t lookup_instance(T& instance);

    static ZRDDSDataReader* createI(DataReader* impl, void* typesupport);

    static ReturnCode_t destroyI(ZRDDSDataReader *dr, void* typesupport);

protected:
    ZRDDSDataReader(DataReader* impl);

    ~ZRDDSDataReader();
private:
    ReturnCode_t readOrTake(TSeq &data_values, DataReaderReadOrTakeParams& params);
};

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::readOrTake(
    TSeq &dataValues,
    DataReaderReadOrTakeParams& params)
{
    ReturnCode_t result = DDS_RETCODE_OK;
    params.isLoan = false;
    params.dataPtrArray = NULL;
    params.dataCount = 0;
    params.dataSeqLen = dataValues.length();
    params.dataSeqMaxLen = dataValues.maximum();
    params.dataSeq_has_ownership = dataValues.has_ownership();
    params.dataSeqBuffer= (ZR_INT8*)dataValues.get_contiguous_buffer();
    params.dataSize = sizeof(T);
    params.dataSeqBufferType = 0;

    result = this->m_cppImpl->read_or_take_untype(params);
    if (result == DDS_RETCODE_NO_DATA)
    {
        dataValues.length(0);
        params.sampleInfos->length(0);
        return result;
    }

    if (result != DDS_RETCODE_OK)
    {
        return result;
    }

    if (params.isLoan)
    {
        if (!dataValues.loan_discontiguous((T**)params.dataPtrArray, params.dataCount, params.dataCount))
        {
            result = DDS_RETCODE_ERROR;
            this->m_cppImpl->return_loan_untype(params.dataPtrArray, params.dataCount, params.sampleInfos);
        }
    }
    else
    {
        if (!dataValues.length(params.dataCount))
        {
            result = DDS_RETCODE_ERROR;
        }
        if (!params.sampleInfos->length(params.dataCount))
        {
            result = DDS_RETCODE_ERROR;
        }
    }
    return result;
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = false;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = true;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_next_sample(
    T &data_value,
    SampleInfo &sample_info)
{
    return this->m_cppImpl->read_or_take_next_sample_untype(
        (ZR_INT8*)&data_value,
        &sample_info,
        false);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_next_sample(
    T &data_value,
    SampleInfo &sample_info)
{
    return this->m_cppImpl->read_or_take_next_sample_untype(
        (ZR_INT8*)&data_value,
        &sample_info,
        true);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = false;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = true;
    params.isNext = false;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_next_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = false;
    params.isNext = true;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_next_instance(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    SampleStateMask sample_mask,
    ViewStateMask view_mask,
    InstanceStateMask instance_mask)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.sampleMask = sample_mask;
    params.viewMask = view_mask;
    params.instanceMask = instance_mask;
    params.isTake = true;
    params.isNext = true;
    params.userCondition = NULL;
    return this->readOrTake(data_values, params);
}

#ifdef _ZRDDS_INCLUDE_READ_CONDITION
template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_next_instance_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.isTake = false;
    params.isNext = true;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_next_instance_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    const InstanceHandle_t &previous_handle,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = &previous_handle;
    params.isTake = true;
    params.isNext = true;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::read_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.isTake = false;
    params.isNext = false;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::take_w_condition(
    TSeq &data_values,
    SampleInfoSeq &sample_infos,
    Long max_samples,
    ReadCondition *condition)
{
    DataReaderReadOrTakeParams params;
    params.sampleInfos = &sample_infos;
    params.maxSamples = max_samples;
    params.handle = NULL;
    params.isTake = true;
    params.isNext = false;
    params.userCondition = condition;
    return this->readOrTake(data_values, params);
}
#endif //_ZRDDS_INCLUDE_READ_CONDITION

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::return_loan(
    TSeq &data_values,
    SampleInfoSeq &sample_infos)
{
    ReturnCode_t result = DDS_RETCODE_OK;
    if (data_values.has_ownership() &&
        sample_infos.has_ownership())
    {
        return result;
    }

    Long dataSeqMaxLen = data_values.maximum();
    T **dataSeqDiscontiguousBuffer = data_values.get_discontiguous_buffer();
    result = this->m_cppImpl->return_loan_untype(
        (void**)dataSeqDiscontiguousBuffer, dataSeqMaxLen, &sample_infos);
    if (result != DDS_RETCODE_OK)
    {
        return result;
    }
    if (!data_values.unloan())
    {
        result = DDS_RETCODE_ERROR;
        return result;
    }
    if (!sample_infos.unloan())
    {
        return DDS_RETCODE_ERROR;
    }
    return result;
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::return_recv_buffer(
    SampleInfo &sample_info)
{
    return this->m_cppImpl->return_recv_buffer_untype(
        &sample_info);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::loan_recv_buffer(
    SampleInfo &sample_info)
{
    return this->m_cppImpl->loan_recv_buffer_untype(
        &sample_info);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::get_key_value(
    T &key_holder,
    const InstanceHandle_t &handle)
{
    return this->m_cppImpl->get_key_value_untype(
        (void*)&key_holder,
        &handle);
}

template<typename T, typename TSeq>
InstanceHandle_t ZRDDSDataReader<T, TSeq>::lookup_instance(T& instance)
{
    return this->m_cppImpl->lookup_instance_untype((void*)&instance);
}

template<typename T, typename TSeq>
ZRDDSDataReader<T, TSeq>* ZRDDSDataReader<T, TSeq>::createI(DataReader* impl, void* typesupport)
{
    return new ZRDDSDataReader<T, TSeq>(impl);
}

template<typename T, typename TSeq>
ReturnCode_t ZRDDSDataReader<T, TSeq>::destroyI(ZRDDSDataReader<T, TSeq> *dr, void* typesupport)
{
    if (NULL != dr) delete dr;
    return DDS_RETCODE_OK;
}

template<typename T, typename TSeq>
ZRDDSDataReader<T, TSeq>::ZRDDSDataReader(DataReader* impl)
    :DataReader(impl)
{
}

template<typename T, typename TSeq>
ZRDDSDataReader<T, TSeq>::~ZRDDSDataReader() {}

} // namespace DDS

#endif // ZRDDSDataReader_h__
