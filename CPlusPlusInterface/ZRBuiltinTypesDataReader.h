/**
 * @file:       ZRBuiltinTypesDataReader.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSBuiltinUserTypesDataReader_h__
#define DDSBuiltinUserTypesDataReader_h__

#include "ZRBuiltinTypes.h"
#include "ZRDDSDataReader.h"

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

namespace DDS {

typedef ZRDDSDataReader<Boolean, BooleanSeq> BooleanDataReader;

typedef ZRDDSDataReader<Octet, OctetSeq> OctetDataReader;

typedef ZRDDSDataReader<Char, CharSeq> CharDataReader;

typedef ZRDDSDataReader<Short, ShortSeq> ShortDataReader;

typedef ZRDDSDataReader<UShort, UShortSeq> UShortDataReader;

typedef ZRDDSDataReader<Long, LongSeq> LongDataReader;

typedef ZRDDSDataReader<ULong, ULongSeq> ULongDataReader;

typedef ZRDDSDataReader<LongLong, LongLongSeq> LongLongDataReader;

typedef ZRDDSDataReader<ULongLong, ULongLongSeq> ULongLongDataReader;

typedef ZRDDSDataReader<Float, FloatSeq> FloatDataReader;

typedef ZRDDSDataReader<Double, DoubleSeq> DoubleDataReader;

typedef ZRDDSDataReader<String, StringSeq> StringDataReader;

typedef ZRDDSDataReader<KeyedString, KeyedStringSeq> KeyedStringDataReader;

typedef ZRDDSDataReader<Bytes, BytesSeq> BytesDataReader;

typedef ZRDDSDataReader<KeyedBytes, KeyedBytesSeq> KeyedBytesDataReader;

typedef ZRDDSDataReader<ZeroCopyBytes, ZeroCopyBytesSeq> ZeroCopyBytesDataReader;

} // namespace DDS

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

#endif

