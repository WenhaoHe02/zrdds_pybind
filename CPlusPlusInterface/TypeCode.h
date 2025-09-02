/**
 * @file:       TypeCode.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef TypeCode_h__
#define TypeCode_h__

#include "ZRDDSCommon.h"
#include "TypeCodeKind.h"

typedef struct TypeCodeHeader TypeCodeHeader;


typedef struct TypeObject TypeObject;

namespace DDS {

class TypeCode;

#ifdef _ZRDDS_INCLUDE_TYPECODE
class DCPSDLL TypeCode
{
public:
	virtual ~TypeCode() {}

    /**
     * @fn  virtual TCTypeKind getKind() const = 0;
     *
     * @brief   获取TypeCode表示的类型.
     *
     * @author  Hzy
     * @date    2016/7/5
     *
     * @return  TC的类型。
     */

    virtual TCTypeKind getKind() const = 0;

    /**
     * @fn  virtual ZR_BOOLEAN compare(const TypeCode* typeCode2) const = 0;
     *
     * @brief   比较两个TypeCode是否指向表示同一个结构.
     *
     * @author  Hzy
     * @date    2016/7/5
     *
     * @param   typeCode2   第二个TypeCode。
     *
     * @return  true表示相等，false表示不相等。
     */

    virtual ZR_BOOLEAN compare(const TypeCode* typeCode2) const = 0;

    /**
     * @fn  virtual const ZR_INT8* getName() const = 0;
     *
     * @brief   获取TypeCode的名称，只支持union/struct/enum类型。
     *
     * @author  Hzy
     * @date    2016/7/5
     *
     * @return  NULL表示失败，否则表示名称。
     */

    virtual const ZR_INT8* getName() const = 0;

    /**
     * @fn  virtual ZR_INT32 getMemberCount() const = 0;
     *
     * @brief   获取TypeCode表示的类型成员个数，只支持union/struct/enum类型。
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  小于0表示失败，否则为有效值.
     */

    virtual ZR_INT32 getMemberCount() const = 0;

    /**
     * @fn  virtual const ZR_INT8* getMemberName(ZR_UINT32 index) const = 0;
     *
     * @brief   获取指定下标成员的名称.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   目标成员下标。
     *
     * @return  NULL表示失败，否则为有效的成员名称指针。
     */

    virtual const ZR_INT8* getMemberName(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getIndexByName(const ZR_INT8* name) const = 0;
     *
     * @brief   通过成员名称获取下标从0开始.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name    成员名称。
     *
     * @return  小于零表示失败，否则为有效的下标。
     */

    virtual ZR_INT32 getIndexByName(const ZR_INT8* name) const = 0;

    /**
     * @fn  virtual TypeCode* getMemberType(ZR_UINT32 index) const = 0;
     *
     * @brief   获取指定下标成员的TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   表示下标。
     *
     * @return  NULL表示失败，否则表示成功。
     */

    virtual TypeCode* getMemberType(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getLabelCount(ZR_UINT32 index) const = 0;
     *
     * @brief   获取Union类型指定的成员的label数量，无效返回 - 1.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   指明下标。
     *
     * @return  A ZR_INT32.
     */

    virtual ZR_INT32 getLabelCount(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getLabel( ZR_UINT32 memberIdx, ZR_UINT32 labelIdx, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   获取Union成员的label.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   memberIdx       成员下标。
     * @param   labelIdx        标签下标。
     * @param [in,out]  expCode 返回是否有效，可能因为参数无效需要返回无效值。
     *
     * @return  如果expCode有效，则返回值为label，否则该返回值无效。
     */

    virtual ZR_INT32 getLabel(
        ZR_UINT32 memberIdx,
        ZR_UINT32 labelIdx,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual ZR_INT32 getDefaultIndex() const = 0;
     *
     * @brief   获取Union类型的默认下标.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  -1表示失败，否则为有效的下标。
     */

    virtual ZR_INT32 getDefaultIndex() const = 0;

    /**
     * @fn  virtual ZR_INT32 getEnumVal( ZR_UINT32 memberIdx, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   获取枚举值的值。
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   memberIdx       成员下标。
     * @param [in,out]  expCode 返回是否有效，可能因为参数无效需要返回无效值。
     *
     * @return  如果expCode有效，则返回值为枚举的值，否则该返回值无效。
     */

    virtual ZR_INT32 getEnumVal(
        ZR_UINT32 memberIdx,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual const ZR_INT8* TypeCode::getEnumString(const TypeCode* self, ZR_UINT32 memberIdx, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   获取枚举成员对应的字符串。
     *
     * @author  Hzy
     * @date    2018/3/16
     *
     * @param   enumVal       枚举值。
     * @param [in,out]  expCode 如果expCode有效，则返回值为枚举的值，否则该返回值无效。
     *
     * @return  NULL表示失败，否则表示枚举字符串值。
     */

    virtual const ZR_INT8* getEnumString(
        ZR_UINT32 enumVal,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual ZR_BOOLEAN isMemberKey( ZR_UINT32 index, TypeCodeExceptionCode* expCode) const = 0;
     *
     * @brief   获取指定结构体成员是否是key域.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index           指向成员下标。
     * @param [in,out]  expCode 返回是否有效，可能因为参数无效需要返回无效值。
     *
     * @return  如果expCode有效，则返回值为时候是key域，否则该返回值无效。
     */

    virtual ZR_BOOLEAN isMemberKey(
        ZR_UINT32 index,
        TypeCodeExceptionCode* expCode) const = 0;

    /**
     * @fn  virtual ZR_INT32 getArrayDimensionCount() const = 0;
     *
     * @brief   获取数组类型的维度。
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  小于0表示无效,否则表示维度。
     */

    virtual ZR_INT32 getArrayDimensionCount() const = 0;

    /**
     * @fn  virtual ZR_INT32 getArrayDimension(ZR_UINT32 index) const = 0;
     *
     * @brief   获取指定下标维度的维数.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   指向维度。
     *
     * @return  小于零表示失败，否则为有效的维数。
     */

    virtual ZR_INT32 getArrayDimension(ZR_UINT32 index) const = 0;

    /**
     * @fn  virtual ZR_INT32 getMaxLength() const = 0;
     *
     * @brief   获取类型最大长度，支持string以及sequence。
     *
     * @author  Hzy
     * @date    2018/2/6
     *
     * @return  -1表示失败，大于0表示最大长度。
     */

    virtual ZR_INT32 getMaxLength() const = 0;

    /**
     * @fn  virtual const TypeCode* getBaseType() const = 0;
     *
     * @brief   获取TypeCode父结构，仅适用于VALUE_TYPE.
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @return  NULL表示获取失败，否则执行父结构的类。
     */

    virtual const TypeCode* getBaseType() const = 0;

    /**
     * @fn  virtual const TypeCode* getElementType() const = 0;
     *
     * @brief   获取元素类型，适用于sequence以及array类型。
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @return  NULL表示失败，否则指向元素.
     */

    virtual const TypeCode* getElementType() const = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::addMemberToEnum( ZR_UINT32 index, const ZR_INT8* name, ZR_UINT32 value) = 0;
     *
     * @brief   向枚举类型添加成员.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index   指明添加的位置，大于当前成员个数则添加在尾部。
     * @param   name    成员名称。
     * @param   value   添加的成员值。
     *
     * @return  大于0表示添加后枚举成员个数，小于0表示失败.
     */

    virtual ZR_INT32 addMemberToEnum(
        ZR_UINT32 index,
        const ZR_INT8* name,
        ZR_UINT32 value) = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::addMemberToUnion( ZR_UINT32 index, const ZR_INT8* name, ZR_UINT32 labelCount, ZR_UINT32* labels, const TypeCode* tc) = 0;
     *
     * @brief   向联合类型添加成员.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index           指明添加的位置，大于当前成员个数则添加在尾部。
     * @param   name            成员的名称。
     * @param   labelCount      该成员标签数量。
     * @param [in,out]  labels  该成员的标签数组。
     * @param   tc              该成员的类型。
     *
     * @return  返回添加后联合成员个数，小于0表示失败。
     */

    virtual ZR_INT32 addMemberToUnion(ZR_UINT32 index, const ZR_INT8* name, ZR_UINT32 labelCount, ZR_UINT32* labels, const TypeCode* tc) = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::addMemberToStruct( ZR_UINT32 index, const ZR_INT8* name, const TypeCode* tc, ZR_BOOLEAN isKey) = 0;
     *
     * @brief   向结构体类型添加成员.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   index           指明添加的位置，大于当前成员个数则添加在尾部。
     * @param   memberId        指定该成员的Id, -1表示与下标一致。
     * @param   name            成员的名称。
     * @param   tc              成员类型。
     * @param   isKey           该成员是否是key。
     * @param   isOption        该成员是否是可选的。
     *
     * @return  返回添加后结构体成员个数，小于0表示失败。
     */

    virtual ZR_INT32 addMemberToStruct(ZR_UINT32 index,
        ZR_UINT32 memberId,
        const ZR_INT8* name,
        const TypeCode* tc,
        ZR_BOOLEAN isKey,
        ZR_BOOLEAN isOption) = 0;

    /**
     * @fn  virtual ZR_INT32 TypeCode::addMemberToValueType(ZR_UINT32 index, ZR_UINT32 memberId, const ZR_INT8* name, const TypeCodeHeader* tc, ZR_BOOLEAN isKey, ZR_BOOLEAN isOption);
     *
     * @brief   向ValueType类型添加成员.
     *
     * @author  Rainnus
     * @date    2016/10/21
     *
     * @param   index           指明添加的位置，大于当前成员个数则添加在尾部。
     * @param   memberId        指定该成员的Id, -1表示与下标一致。
     * @param   name            成员的名称。
     * @param   tc              成员类型。
     * @param   isKey           该成员是否是key。
     * @param   isOption        该成员是否是可选的。
     *
     * @return  返回添加后ValueType成员个数，小于0表示失败。
     */

    virtual ZR_INT32 addMemberToValueType(ZR_UINT32 index, ZR_UINT32 memberId,
        const ZR_INT8* name,
        const TypeCode* tc,
        ZR_BOOLEAN isKey,
        ZR_BOOLEAN isOption) = 0;

    /**
     * @fn virtual ZR_INT32 TypeCode::printIDL() = 0;
     *
     * @brief   打印指定的TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  小于零表示打印出错，0表示打印成功。
     */

    virtual ZR_INT32 printIDL() const = 0;

    /**
     * @fn  virtual ZR_INT8* TypeCode::getPrintableString() = 0;
     *
     * @brief   获取等价的IDL文件内容的缓冲区，此方法若返回成功，则必须调用releasePrintableString方法释放空间。
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @return  NULL获取失败，否则指向内容。
     */

    virtual ZR_INT8* getPrintableString() const = 0;

    /**
     * @fn  virtual void TypeCode::releasePrintableString(ZR_INT8* buffer) = 0;
     *
     * @brief   释放由TypeCodeGetTypePrintableString底层创建的空间。
     *
     * @author  Hzy
     * @date    2016/12/13
     *
     * @param [in,out]  buffer  指向由TypeCodeGetTypePrintableString返回的空间。
     */

    virtual void releasePrintableString(ZR_INT8* buffer) const = 0;

    /**
     * @fn  virtual TypeCodeHeader* TypeCode::getImpl() = 0;
     *
     * @brief   获取底层实例。
     *
     * @author  Hzy
     * @date    2016/10/18
     *
     * @return  关联的底层实现。
     */

    virtual TypeCodeHeader* getImpl() = 0;

    /**
     * @fn virtual ZR_BOOLEAN TypeCodeFactory::hasKey() = 0;
     *
     * @brief 判断类型是否包含key域，仅对struct type和value type有效，其余类型均返回false
     *
     * @author Tim
     * @date 17/11/16
     *
     * @return A ZR_BOOLEAN
     */
    virtual ZR_BOOLEAN hasKey() const = 0;
};

class DCPSDLL TypeCodeFactory
{
public:
    virtual ~TypeCodeFactory(){}
    /**
     * @fn  static TypeCodeFactory& TypeCodeFactory::getInstance();
     *
     * @brief   获取TypeCodeFactory的单例.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @return  NULL表示失败，否则成功。
     */

    static TypeCodeFactory& getInstance();

    /**
     * @fn  static void TypeCodeFactory::finalize();
     *
     * @brief   析构全局TypeCode单例。
     *
     * @author  Hzy
     * @date    2016/7/6
     */

    static void finalize();

    /**
     * @fn virtual TypeCode* TypeCodeFactory::getPrimitiveTC(TCTypeKind kind) = 0;
     *
     * @brief   获取基本数据类型的TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   kind    指明基本数据类型。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* getPrimitiveTC(TCTypeKind kind) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createStructTC(const ZR_INT8* name) = 0;
     *
     * @brief   创建结构体TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name    结构体的名称。
     * @param   kind    该结构体的extensibility属性。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createStructTC(const ZR_INT8* name,
        ExtensibilityKind kind) = 0;

    /**
     * @fn  TypeCode* TypeCodeFactory::createValueTypeTC( TypeCodeFactory* self, const ZR_INT8* name, TypeCodeModifierKind modifierKind, ExtensibilityKind kind, const TypeCode*baseTC);
     *
     * @brief   Type code factory create value type tc.
     *
     * @author  Rainnus
     * @date    2016/10/21
     *
     * @param   name            valueType名称。
     * @param   modifierKind    modifier的类型。
     * @param   kind            extensibility类型。
     * @param   baseTC          继承的类型。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createValueTypeTC(
        const ZR_INT8* name, 
        TypeCodeModifierKind modifierKind, 
        ExtensibilityKind kind, 
        const TypeCode* baseTC) = 0;
    /**
     * @fn  virtual TypeCode* TypeCodeFactory::wrapperTypeCode(TypeCodeHeader* cTypeCode);
     *
     * @brief   从C版本的TypCodeheader包装成C++对象。
     *
     * @author  Hzy
     * @date    2016/10/18
     *
     * @param [in,out]  cTypeCode   底层结构。
     *
     * @return  包装的结构。
     */

    virtual TypeCode* wrapperTypeCode(TypeCodeHeader* cTypeCode) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createEnumTC(const ZR_INT8* name) = 0;
     *
     * @brief   创建枚举类型TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name    枚举类型的名称。
     * @param   bitBound        位宽大小。
     * @param   kind            Extenbility属性值。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createEnumTC(const ZR_INT8* name,
        ZR_UINT32 bitBound,
        ExtensibilityKind kind) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createUnionTC(const ZR_INT8* name, const TypeCode* switchTC, ZR_UINT32 defaultIdx) = 0;
     *
     * @brief   创建联合类型TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   name        联合类型的名称。
     * @param   switchTC    辨别符的TC。
     * @param   defaultIdx  默认的成员下标。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createUnionTC(const ZR_INT8* name, const TypeCode* switchTC, ZR_UINT32 defaultIdx) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createStringTC(const ZR_UINT32 length) = 0;
     *
     * @brief   创建String类型TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   length  string的长度。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createStringTC(const ZR_UINT32 length) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createSequenceTC(const ZR_UINT32 length, const TypeCode* tc) = 0;
     *
     * @brief   创建Sequence类型TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   length  Sequence的长度。
     * @param   tc      元素的TypeCode。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createSequenceTC(const ZR_UINT32 length, const TypeCode* tc) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::createArrayTC(const ZR_UINT32 dimensionCount, const ZR_UINT32* dimensions, const TypeCode* tc) = 0;
     *
     * @brief   创建数组类型TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   dimensionCount  数组维度。
     * @param   dimensions      各个维度的维数。
     * @param   tc              元素的TypeCode。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* createArrayTC(const ZR_UINT32 dimensionCount, const ZR_UINT32* dimensions, const TypeCode* tc) = 0;

    /**
     * @fn virtual TypeCode* TypeCodeFactory::cloneTC(const TypeCode* tc) = 0;
     *
     * @brief   拷贝一个TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param   tc  源TypeCode。
     *
     * @return  NULL表示失败，否则为有效的TypeCode。
     */

    virtual TypeCode* cloneTC(const TypeCode* tc) = 0;

    /**
     * @fn virtual ZR_BOOLEAN TypeCodeFactory::deleteTC(TypeCode* tc) = 0;
     *
     * @brief   删除一个TypeCode.
     *
     * @author  Hzy
     * @date    2016/7/6
     *
     * @param [in,out]  tc  删除的目标。
     *
     * @return  true表示删除成功，false表示删除失败。
     */

    virtual ZR_BOOLEAN deleteTC(TypeCode* tc) = 0;

#ifdef _ZRDDS_INCLUDE_TYPE_OBJECT
    /**
     * @fn  virtual TypeCode TypeCodeFactory::createFromTypeObject(const TypeObject* typeObject);
     *
     * @brief   从TypeObject构造等价的TypeCode.
     *
     * @author  Hzy
     * @date    2017/2/24
     *
     * @param   typeObject  源TypeObject。
     *
     * @return  NULL表示失败，否则返回转化的结果。
     */

    virtual TypeCode* createFromTypeObject(const TypeObject* typeObject) = 0;
#endif
};

#endif // _ZRDDS_INCLUDE_TYPECODE
} // namespace DDS

#endif // TypeCode_h__
