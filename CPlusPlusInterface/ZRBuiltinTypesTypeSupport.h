/**
 * @file:       ZRBuiltinTypesTypeSupport.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRBuiltinTypesTypeSupport_h__
#define ZRBuiltinTypesTypeSupport_h__

#include "ZRDDSTypeSupport.h"

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES
namespace DDS {

DDSInnerTypeSupport(BooleanTypeSupport, Boolean);

DDSInnerTypeSupport(OctetTypeSupport, Octet);

DDSInnerTypeSupport(CharTypeSupport, Char);

DDSInnerTypeSupport(ShortTypeSupport, Short);

DDSInnerTypeSupport(UShortTypeSupport, UShort);

DDSInnerTypeSupport(LongTypeSupport, Long);

DDSInnerTypeSupport(ULongTypeSupport, ULong);

DDSInnerTypeSupport(LongLongTypeSupport, LongLong);

DDSInnerTypeSupport(ULongLongTypeSupport, ULongLong);

DDSInnerTypeSupport(FloatTypeSupport, Float);

DDSInnerTypeSupport(DoubleTypeSupport, Double);

DDSInnerTypeSupport(StringTypeSupport, String);

DDSInnerTypeSupport(KeyedStringTypeSupport, KeyedString);

DDSInnerTypeSupport(BytesTypeSupport, Bytes);

DDSInnerTypeSupport(KeyedBytesTypeSupport, KeyedBytes);

DDSInnerTypeSupport(ZeroCopyBytesTypeSupport, ZeroCopyBytes);

} // namespace DDS

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

#endif

