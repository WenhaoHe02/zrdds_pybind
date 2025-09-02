/**
 * @file:       DynamicDataTypeSupport.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef DynamicDataTypeSupport_h__
#define DynamicDataTypeSupport_h__

#include "OsResource.h"
#include "ZRDDSCommon.h"
#include "ZRDDSCppWrapper.h"

#ifdef _ZRDDS_INCLUDE_DYNAMIC_DATA
typedef struct ZRDynamicData ZRDynamicData;
typedef struct ZRDynamicDataProperty_t ZRDynamicDataProperty_t;

namespace DDS {

class TypeCode;
class DomainParticipant;

class DCPSDLL ZRDynamicDataTypeSupport
{
public:
    static ZRDynamicDataTypeSupport* create(TypeCode *type, const ZRDynamicDataProperty_t *props);

    static void destroy(ZRDynamicDataTypeSupport* typesupport);

    virtual ~ZRDynamicDataTypeSupport(){}

    virtual const Char* get_type_name() = 0;

    virtual ReturnCode_t register_type(
        DomainParticipant *participant,
        const Char* type_name) = 0;

    virtual ReturnCode_t unregister_type(
        DomainParticipant *participant,
        const Char* type_name) = 0;

    virtual const TypeCode* get_data_type() = 0;

    virtual ZRDynamicData* create_data() = 0;

    virtual ReturnCode_t delete_data(ZRDynamicData *data) = 0;

    virtual void print_data(const ZRDynamicData *data) = 0;

    virtual ReturnCode_t initialize_data(ZRDynamicData *data) = 0;

    virtual ReturnCode_t finalize_data(ZRDynamicData *data) = 0;

    virtual ReturnCode_t copy_data(ZRDynamicData *dst, const ZRDynamicData *source) = 0;

    virtual TypeCode* get_typecode() = 0;

protected:
    ZRDynamicDataTypeSupport(){}
};

} // namespace DDS

#endif // _ZRDDS_INCLUDE_DYNAMIC_DATA

#endif // DynamicData_h__
