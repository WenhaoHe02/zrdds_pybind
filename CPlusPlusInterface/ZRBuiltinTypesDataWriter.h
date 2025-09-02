/**
 * @file:       ZRBuiltinTypesDataWriter.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DDSBuiltinUserTypesDataWriter_h__
#define DDSBuiltinUserTypesDataWriter_h__

#include <stdlib.h>
#include "ZRBuiltinTypes.h"
#include "ZRDDSDataWriter.h"

#ifdef _ZRDDS_INCLUDE_BUILTIN_TYPES

namespace DDS {

typedef ZRDDSDataWriter<Boolean> BooleanDataWriter;

typedef ZRDDSDataWriter<Octet> OctetDataWriter;

typedef ZRDDSDataWriter<Char> CharDataWriter;

typedef ZRDDSDataWriter<Short> ShortDataWriter;

typedef ZRDDSDataWriter<UShort> UShortDataWriter;

typedef ZRDDSDataWriter<Long> LongDataWriter;

typedef ZRDDSDataWriter<ULong> ULongDataWriter;

typedef ZRDDSDataWriter<LongLong> LongLongDataWriter;

typedef ZRDDSDataWriter<ULongLong> ULongLongDataWriter;

typedef ZRDDSDataWriter<Float> FloatDataWriter;

typedef ZRDDSDataWriter<Double> DoubleDataWriter;

typedef ZRDDSDataWriter<String> StringDataWriter;

typedef ZRDDSDataWriter<KeyedString> KeyedStringDataWriter;

typedef ZRDDSDataWriter<Bytes> BytesDataWriter;

typedef ZRDDSDataWriter<KeyedBytes> KeyedBytesDataWriter;

typedef ZRDDSDataWriter<ZeroCopyBytes> ZeroCopyBytesDataWriter;

} // namespace DDS

#endif //_ZRDDS_INCLUDE_BUILTIN_TYPES

#endif

