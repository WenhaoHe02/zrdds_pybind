/**
 * @file:       ZRCPlusPlusSequence.cpp
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>
#include "OsResource.h"
#include "ZRDDSCommon.h"

#if defined(_ZRDDSCPPINTERFACE) && defined(T) && defined(TSeq)
#define CONCATENATE(A, B)  A ## B

#if defined(TGetTypeCodeFunc)
#define TINITIALIZE_c(T)                    CONCATENATE(T, _initialize)
#define TINITIALIZE                         TINITIALIZE_c(T)
#endif

#define TSeq_is_initialized_c(TSeq)           CONCATENATE(TSeq, _is_initialized)
#define TSeq_is_initialized                   TSeq_is_initialized_c(TSeq)

#define TSeq_get_c(TSeq)                     CONCATENATE(TSeq, _get)
#define TSeq_get                             TSeq_get_c(TSeq)

#define TSeq_set_c(TSeq)                     CONCATENATE(TSeq, _set)
#define TSeq_set                             TSeq_set_c(TSeq)

#define TSeq_initialize_c(TSeq)              CONCATENATE(TSeq, _initialize)
#define TSeq_initialize                      TSeq_initialize_c(TSeq)

#define TSeq_new_c(TSeq)                     CONCATENATE(TSeq, _new)
#define TSeq_new                             TSeq_new_c(TSeq)

#define TSeq_get_maximum_c(TSeq)              CONCATENATE(TSeq, _get_maximum)
#define TSeq_get_maximum                      TSeq_get_maximum_c(TSeq)

#define TSeq_set_maximum_c(TSeq)              CONCATENATE(TSeq, _set_maximum)
#define TSeq_set_maximum                      TSeq_set_maximum_c(TSeq)

#define TSeq_get_length_c(TSeq)               CONCATENATE(TSeq, _get_length)
#define TSeq_get_length                       TSeq_get_length_c(TSeq)

#define TSeq_set_length_c(TSeq)               CONCATENATE(TSeq, _set_length)
#define TSeq_set_length                       TSeq_set_length_c(TSeq)

#define TSeq_ensure_length_c(TSeq)            CONCATENATE(TSeq, _ensure_length)
#define TSeq_ensure_length                    TSeq_ensure_length_c(TSeq)

#define TSeq_get_reference_c(TSeq)            CONCATENATE(TSeq, _get_reference)
#define TSeq_get_reference                    TSeq_get_reference_c(TSeq)

#define TSeq_append_c(TSeq)                  CONCATENATE(TSeq, _append)
#define TSeq_append                          TSeq_append_c(TSeq)

#define TSeq_append_autosize_c(TSeq)        CONCATENATE(TSeq, _append_autosize)
#define TSeq_append_autosize                TSeq_append_autosize_c(TSeq)

#define TSeq_copy_no_alloc_c(TSeq)           CONCATENATE(TSeq, _copy_no_alloc)
#define TSeq_copy_no_alloc                   TSeq_copy_no_alloc_c(TSeq)

#define TSeq_copy_c(TSeq)                    CONCATENATE(TSeq, _copy)
#define TSeq_copy                            TSeq_copy_c(TSeq)

#define TSeq_compare_c(TSeq)                 CONCATENATE(TSeq, _compare)
#define TSeq_compare                         TSeq_compare_c(TSeq)

#define TSeq_from_array_c(TSeq)               CONCATENATE(TSeq, _from_array)
#define TSeq_from_array                       TSeq_from_array_c(TSeq)

#define TSeq_to_array_c(TSeq)                 CONCATENATE(TSeq, _to_array)
#define TSeq_to_array                         TSeq_to_array_c(TSeq)

#define TSeq_loan_contiguous_c(TSeq)          CONCATENATE(TSeq, _loan_contiguous)
#define TSeq_loan_contiguous                  TSeq_loan_contiguous_c(TSeq)

#define TSeq_loan_discontiguous_c(TSeq)       CONCATENATE(TSeq, _loan_discontiguous)
#define TSeq_loan_discontiguous               TSeq_loan_discontiguous_c(TSeq)

#define TSeq_unloan_c(TSeq)                  CONCATENATE(TSeq, _unloan)
#define TSeq_unloan                          TSeq_unloan_c(TSeq)

#define TSeq_get_contiguous_buffer_c(TSeq)     CONCATENATE(TSeq, _get_contiguous_buffer)
#define TSeq_get_contiguous_buffer             TSeq_get_contiguous_buffer_c(TSeq)

#define TSeq_get_discontiguous_buffer_c(TSeq)  CONCATENATE(TSeq, _get_discontiguous_buffer)
#define TSeq_get_discontiguous_buffer          TSeq_get_discontiguous_buffer_c(TSeq)

#define TSeq_get_reader_and_data_ptr_c(TSeq)     CONCATENATE(TSeq, _get_reader_and_data_ptr)
#define TSeq_get_reader_and_data_ptr             TSeq_get_reader_and_data_ptr_c(TSeq)

#define TSeq_set_reader_and_data_ptr_c(TSeq)     CONCATENATE(TSeq, _set_reader_and_data_ptr)
#define TSeq_set_reader_and_data_ptr             TSeq_set_reader_and_data_ptr_c(TSeq)

#define TSeq_has_ownership_c(TSeq)            CONCATENATE(TSeq, _has_ownership)
#define TSeq_has_ownership                    TSeq_has_ownership_c(TSeq)

#define TSeq_clear_c(TSeq)                   CONCATENATE(TSeq, _clear)
#define TSeq_clear                           TSeq_clear_c(TSeq)

#define TSeq_finalize_c(TSeq)                CONCATENATE(TSeq, _finalize)
#define TSeq_finalize                        TSeq_finalize_c(TSeq)

TSeq::TSeq(DDS_ULong max/* = 0*/)
{
    TSeq_initialize(this);
    if (max > 0)
    {
        TSeq_set_maximum(this, max);
    }
}

TSeq::~TSeq()
{
    TSeq_finalize(this);
}

TSeq::TSeq(const struct TSeq& seq)
{
    TSeq_initialize(this);
    TSeq_copy(this, &seq);
}
//
//TSeq& TSeq::operator=(const struct TSeq& src_seq, DDS_Boolean cpp)
//{
//    if (cpp)
//    {
//        TSeq_copy(this, &src_seq);
//    }
//    return *this;
//}

const T& TSeq::operator[](DDS_ULong i) const
{
    return (const T&)*TSeq_get_reference(this, i);
}

T& TSeq::operator[](DDS_ULong i)
{
    return *TSeq_get_reference(this, i);
}

DDS_Boolean TSeq::append(const T& val)
{
    return TSeq_append(this, &val);
}

DDS_Boolean TSeq::append_autosize(const T& val)
{
    return TSeq_append_autosize(this, &val);
}

DDS_ULong TSeq::maximum() const
{
    return TSeq_get_maximum(this);
}

DDS_Boolean TSeq::maximum(DDS_ULong new_max)
{
    return TSeq_set_maximum(this, new_max);
}

DDS_ULong TSeq::length() const
{
    return TSeq_get_length(this);
}

DDS_Boolean TSeq::length(DDS_ULong new_length)
{
    return TSeq_set_length(this, new_length);
}

DDS_Boolean TSeq::clear()
{
    return TSeq_clear(this);
}

DDS_Boolean TSeq::unloan()
{
    return TSeq_unloan(this);
}

T* TSeq::get_contiguous_buffer() const
{
    return TSeq_get_contiguous_buffer(this);
}

T** TSeq::get_discontiguous_buffer() const
{
    return TSeq_get_discontiguous_buffer(this);
}

DDS_Boolean TSeq::set_at(DDS_ULong i, const T& val)
{
    return TSeq_set(this, i, &val);
}

const T& TSeq::get_at(DDS_ULong i) const
{
    return (const T&)*TSeq_get_reference(this, i);
}

DDS_Boolean TSeq::ensure_length(DDS_ULong length, DDS_ULong max)
{
    return TSeq_ensure_length(this, length, max);
}

DDS_Boolean TSeq::has_ownership() const
{
    return TSeq_has_ownership(this);
}

DDS_Boolean TSeq::copy_no_alloc(const struct TSeq& src_seq)
{
    return TSeq_copy_no_alloc(this, &src_seq);
}

DDS_Long TSeq::compare(const struct TSeq& compared_seq) const
{
    return TSeq_compare(this, &compared_seq);
}

DDS_Boolean TSeq::from_array(const T array[], DDS_ULong length)
{
    return TSeq_from_array(this, array, length);
}

DDS_Boolean TSeq::to_array(T array[], DDS_ULong length) const
{
    return TSeq_to_array(this, array, length);
}

DDS_Boolean TSeq::loan_contiguous(T* buffer, DDS_ULong new_length, DDS_ULong new_max)
{
    return TSeq_loan_contiguous(this, buffer, new_length, new_max);
}

DDS_Boolean TSeq::loan_discontiguous(T** buffer, DDS_ULong new_length, DDS_ULong new_max)
{
    return TSeq_loan_discontiguous(this, buffer, new_length, new_max);
}

#undef TSeq_is_initialized_c       
#undef TSeq_is_initialized       

#undef TSeq_get_c                   
#undef TSeq_get    

#undef TSeq_set_c                   
#undef TSeq_set  

#undef TSeq_initialize_c            
#undef TSeq_initialize

#undef TSeq_new_c
#undef TSeq_new

#undef TSeq_get_maximum_c           
#undef TSeq_get_maximum

#undef TSeq_set_maximum_c            
#undef TSeq_set_maximum

#undef TSeq_get_length_c             
#undef TSeq_get_length

#undef TSeq_set_length_c             
#undef TSeq_set_length

#undef TSeq_ensure_length_c          
#undef TSeq_ensure_length

#undef TSeq_get_reference_c          
#undef TSeq_get_reference

#undef TSeq_append_c                
#undef TSeq_append

#undef TSeq_append_autosize_c                
#undef TSeq_append_autosize

#undef TSeq_copy_no_alloc_c           
#undef TSeq_copy_no_alloc

#undef TSeq_copy_c                  
#undef TSeq_copy

#undef TSeq_compare_c                  
#undef TSeq_compare

#undef TSeq_from_array_c             
#undef TSeq_from_array

#undef TSeq_to_array_c             
#undef TSeq_to_array

#undef TSeq_loan_contiguous_c      
#undef TSeq_loan_contiguous  

#undef TSeq_loan_discontiguous_c   
#undef TSeq_loan_discontiguous

#undef TSeq_unloan_c              
#undef TSeq_unloan

#undef TSeq_get_contiguous_buffer_c 
#undef TSeq_get_contiguous_buffer

#undef TSeq_get_discontiguous_buffer_c
#undef TSeq_get_discontiguous_buffer

#undef TSeq_get_reader_and_data_ptr_c 
#undef TSeq_get_reader_and_data_ptr 

#undef TSeq_set_reader_and_data_ptr_c 
#undef TSeq_set_reader_and_data_ptr

#undef TSeq_has_ownership_c
#undef TSeq_has_ownership

#undef TSeq_clear_c
#undef TSeq_clear

#undef TSeq_finalize_c 
#undef TSeq_finalize

#undef CONCATENATE
#endif
