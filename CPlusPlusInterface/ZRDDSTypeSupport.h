/**
 * @file:       ZRDDSTypeSupport.h
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#ifndef ZRDDSTypeSupport_h__
#define ZRDDSTypeSupport_h__

#include "TypeSupport.h"

#define DDSTypeSupport(TTypeSupport, TType)         \
    class TTypeSupport : public DDS::TypeSupport    \
    {                                               \
    public:                                         \
        static TTypeSupport* get_instance();        \
                                                    \
        static void finalize_instance();            \
                                                    \
        virtual const DDS::Char* get_type_name();   \
                                                    \
        virtual DDS::ReturnCode_t register_type(    \
            DDS::DomainParticipant *participant,    \
            const DDS::Char* type_name);            \
                                                    \
        virtual DDS::ReturnCode_t unregister_type(  \
            DDS::DomainParticipant *participant,    \
            const DDS::Char* type_name);            \
                                                    \
        virtual DDS::Boolean has_key();             \
                                                    \
    protected:                                      \
        TTypeSupport();                             \
        ~TTypeSupport();                            \
    private:                                        \
        static TTypeSupport* m_instance;            \
    };

#define DDSInnerTypeSupport(TTypeSupport, TType)        \
    class DCPSDLL TTypeSupport : public DDS::TypeSupport\
    {                                                   \
    public:                                             \
        static TTypeSupport* get_instance();            \
                                                        \
        static void finalize_instance();                \
                                                        \
        virtual const DDS::Char* get_type_name();       \
                                                        \
        virtual DDS::ReturnCode_t register_type(        \
            DDS::DomainParticipant *participant,        \
            const DDS::Char* type_name);                \
                                                        \
        virtual DDS::ReturnCode_t unregister_type(      \
            DDS::DomainParticipant *participant,        \
            const DDS::Char* type_name);                \
                                                        \
        virtual DDS::Boolean has_key();                 \
                                                        \
    protected:                                          \
        TTypeSupport();                                 \
        ~TTypeSupport();                                \
    private:                                            \
        static TTypeSupport* m_instance;                \
    };

#endif // ZRDDSTypeSupport_h__
