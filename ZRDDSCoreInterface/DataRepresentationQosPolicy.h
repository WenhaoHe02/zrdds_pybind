/**
 * @file:       DataRepresentationQosPolicy.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DataRepresentationQosPolicy_h__
#define DataRepresentationQosPolicy_h__

#include "OsResource.h"
#include "ZRBuiltinTypes.h"

/**
 * @def DDS_XCDR_DATA_REPRESENTATION();
 *
 * @ingroup CoreMacro
 *
 * @brief   网络传输的数据为使用CDR方式序列化后的样本。
 */

#define DDS_XCDR_DATA_REPRESENTATION 0x0000

/**
 * @def DDS_XML_DATA_REPRESENTATION();
 *
 * @ingroup CoreMacro
 *
 * @brief   网络传输的数据为使用XML方式方式序列化的样本。
 */

#define DDS_XML_DATA_REPRESENTATION 0x0001

/**
 * @struct DDS_DataRepresentationQosPolicy
 *
 * @ingroup CoreQosStruct
 *
 * @brief   数据封装格式配置QoS。
 * @details 
 *          - 包括三个内容：
 *              - 数据封装的标识；
 *              - 数据写者、数据读者所支持的封装类型以及所偏好的封装类型；  
 *              - 基于给定的封装种类，在数据写者/数据读者之间选取合适的封装种类的选择方法。  
 *          - 每个主题、数据写者、数据读者都应该含有这个Qos；  
 *          - 具有提供方和请求方的语义；  
 *          - 在使能之后不能使能；  
 *          - 数据写者端仅仅提供一种数据封装标识（虽然结构为一个列表，厂商自定义第一个元素之后的意义）  
 *          - 数据读者端请求一种或者多种封装格式；  
 *          - 兼容性：数据读者端包含数据写者端的封装格式;  
 *          - 默认为空的列表，等价于只有一个XCDR元素;  
 *              
 * @warning 该QoS暂未实现。
 */

typedef struct DDS_DataRepresentationQosPolicy 
{
    /** @brief   数据封装标识列表。 */
    DDS_ShortSeq value;
}DDS_DataRepresentationQosPolicy ;

#endif /* DataRepresentationQosPolicy_h__*/
