/**
 * @file:       ZRSequence.cpp
 *
 * copyright:   Copyright (c) 2018 ZhenRong Technology, Inc. All rights reserved.
 */

#undef TCOPY_NO_DEFINED
#undef TCOMPARE_NO_DEFINED
#undef TINITIALIZE_NO_DEFINED
#undef TFINALIZE_NO_DEFINED

#define QUOTE(name) #name

#ifndef TCOPY
#define TCOPY(self, src, mempool)    \
    do                      \
    {                       \
    } while (0)

#define TCOPY_NO_DEFINED
#endif

#ifndef TCOMPARE
#define TCOMPARE(self, src) \
    do                      \
    {                       \
    } while (0)
#define TCOMPARE_NO_DEFINED
#endif /*!TCOMPARE*/

#ifndef TGetTypeCodeFunc
#ifndef TINITIALIZE
#define TINITIALIZE(self)   \
    do                      \
    {                       \
    } while (0)

#define TINITIALIZE_NO_DEFINED
#endif
#endif

#ifndef TFINALIZE
#define TFINALIZE(self)     \
    do                      \
    {                       \
    } while (0)

#define TFINALIZE_NO_DEFINED
#endif

#ifndef DDS_SEQUENCE_LENGTH_UNLIMITED
#define DDS_SEQUENCE_LENGTH_UNLIMITED (-1)
#endif
#ifndef DDS_SEQUENCE_LENGTH_LIMITATION
#define DDS_SEQUENCE_LENGTH_LIMITATION DDS_SEQUENCE_LENGTH_UNLIMITED
#define UNDEF_DDS_SEQUENCE_LENGTH_LIMITATION
#endif

#if defined(T) && defined(TSeq)
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

#define TSeq_initialize_ex_c(TSeq)            CONCATENATE(TSeq, _initialize_ex)
#define TSeq_initialize_ex                    TSeq_initialize_ex_c(TSeq)

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

#define TSeq_copy_no_alloc_c(TSeq)             CONCATENATE(TSeq, _copy_no_alloc)
#define TSeq_copy_no_alloc                     TSeq_copy_no_alloc_c(TSeq)

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

#define TSeq_shallow_copy_c(TSeq)             CONCATENATE(TSeq, _shallow_copy)
#define TSeq_shallow_copy                     TSeq_shallow_copy_c(TSeq)

#if defined(TGetTypeCodeFunc)
DDS_Boolean TINITIALIZE(struct T *self)
{
    ZRDynamicDataProperty_t tmpProp;
    ZRDynamicDataProperty_initialize(&tmpProp);
    return ZRDynamicData_initialize(self, TGetTypeCodeFunc(), &tmpProp);
}
#endif

DDS_Boolean TSeq_is_initialized(const struct TSeq *self)
{
    return self->_sequenceInit == DDS_INITIALIZE_NUMBER;
}

DDS_Boolean TSeq_set(struct TSeq *self, DDS_ULong index, const T *newValue)
{
    if (!TSeq_is_initialized(self) || !self->_owned || index >= self->_length)
    {
        return false;
    }
#if defined(TCOPY_NO_DEFINED)
    self->_contiguousBuffer[index] = *(T*)newValue;
#else
    TCOPY(&(self->_contiguousBuffer[index]), newValue, self->_mempool);
    self->_allocMemory = true;
#endif
    return true;
}

void TSeq_initialize(struct TSeq *self)
{
    TSeq_initialize_ex(self, NULL, false);
}

void TSeq_initialize_ex(struct TSeq *self, ZRMemPool* mempool, DDS_Boolean allocateMemory)
{
    memset(self, 0, sizeof(TSeq));
    self->_owned = true;
    self->_sequenceInit = DDS_INITIALIZE_NUMBER;
    self->_mempool = mempool;
    self->_allocMemory = allocateMemory;
}

struct TSeq *TSeq_new(DDS_ULong newMax)
{
    struct TSeq *newSeq = (struct TSeq *)malloc(sizeof(struct TSeq));
    if (NULL == newSeq)
    {
        return NULL;
    }
    TSeq_initialize(newSeq);
    if (!TSeq_set_maximum(newSeq, newMax))
    {
        return NULL;
    }
    return newSeq;
}

DDS_ULong TSeq_get_maximum(const struct TSeq *self)
{
    return self->_maximum;
}

DDS_Boolean TSeq_set_maximum(struct TSeq *self, DDS_ULong newMax)
{
    ZR_UINT32 index = 0;
    if (!TSeq_is_initialized(self) || !self->_owned)
    {
        return false;
    }
    if (DDS_SEQUENCE_LENGTH_LIMITATION != DDS_SEQUENCE_LENGTH_UNLIMITED
        && newMax > DDS_SEQUENCE_LENGTH_LIMITATION)
    {
        return false;
    }

    if (self->_maximum != newMax)
    {
        ZR_UINT32 newLen = (self->_length > newMax ? newMax : self->_length);
        T *oldBuffer = self->_contiguousBuffer;
        T *newBuffer = (T *)ZRMalloc(NULL, sizeof(T)* newMax);
        if (newBuffer == NULL)
        {
            return false;
        }

#if defined(TINITIALIZE_NO_DEFINED)
        /*memset(newBuffer, 0, sizeof(T) * newMax);*/
#else
        for (index = 0; index < newMax; ++index)
        {
            TINITIALIZE(&(newBuffer[index]), self->_mempool, self->_allocMemory);
        }
#endif

        if (oldBuffer != NULL)
        {
#if defined(TCOPY_NO_DEFINED)
            memcpy(newBuffer, oldBuffer, sizeof(T) * newLen);
#else
            for (index = 0; index < newLen; ++index)
            {
                TCOPY(&(newBuffer[index]), (const T *)&(oldBuffer[index]), self->_mempool);
            }
#endif
#ifndef TFINALIZE_NO_DEFINED
            for (index = 0; index < self->_maximum; ++index)
            {
                TFINALIZE(&(oldBuffer[index]), self->_mempool, self->_allocMemory);
            }
#endif
            ZRDealloc(NULL, oldBuffer);
        }
        self->_length = newLen;
        self->_maximum = newMax;
        self->_contiguousBuffer = newBuffer;
    }
    return true;
}

DDS_ULong TSeq_get_length(const struct TSeq *self)
{
    return self->_length;
}

DDS_Boolean TSeq_set_length(struct TSeq *self, DDS_ULong newLength)
{
    if (newLength > self->_maximum)
    {
        return false;
    }
    self->_length = newLength;
    return true;
}

DDS_Boolean TSeq_ensure_length(struct TSeq *self, DDS_ULong length, DDS_ULong max)
{
    if (!TSeq_is_initialized(self) || length > max || !self->_owned)
    {
        return false;
    }
    if (self->_maximum < max)
    {
        if (!TSeq_set_maximum(self, max))
        {
            return false;
        }
    }
    self->_length = length;
    return true;
}

T* TSeq_get_reference(const struct TSeq *self, DDS_ULong index)
{
    ZR_UINT32 i = 0;
    if (!TSeq_is_initialized(self) || index >= self->_length)
    {
        return NULL;
    }
    if (self->_contiguousBuffer != NULL)
    {
        return &(self->_contiguousBuffer[index]);
    }
    else if (self->_discontiguousBuffer != NULL)
    {
        return self->_discontiguousBuffer[index];
    }
#ifdef _ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
    else if (self->_fragmentNum > 0)
    {
        ZR_UINT32 curOffset = 0;
        T** fragments = (T**)(self->_fixedFragments);
        if (self->_fragmentNum > 64)
        {
            fragments = self->_variousFragments;
        }
        for (i = 0; i < self->_fragmentNum; ++i)
        {
            ZR_UINT32 currentLen = self->_fragmentSize;
            if (i == 0)
            {
                currentLen = self->_firstFragSize;
            }
            else if (i == self->_fragmentNum - 1)
            {
                currentLen = self->_lastFragSize;
            }
            if (curOffset + currentLen <= index)
            {
                curOffset += currentLen;
                continue;
            }
            return &(fragments[i][index - curOffset]);
        }
    }
#endif //_ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
    return NULL;
}

DDS_Boolean TSeq_append(struct TSeq *self, const T *newValue)
{
    if (!TSeq_is_initialized(self) || !self->_owned || self->_length == self->_maximum)
    {
        return false;
    }
#if defined(TCOPY_NO_DEFINED)
    self->_contiguousBuffer[self->_length] = *(T*)newValue;
#else
    TCOPY(&(self->_contiguousBuffer[self->_length]), newValue, self->_mempool);
    self->_allocMemory = true;
#endif
    ++self->_length;
    return true;
}

DDS_Boolean TSeq_append_autosize(struct TSeq *self, const T *newValue)
{
    if (!TSeq_ensure_length(self, self->_length, self->_length + 1))
    {
        return false;
    }
    return TSeq_append(self, newValue);
}

DDS_Boolean TSeq_copy_no_alloc(struct TSeq *self, const struct TSeq *src)
{
    ZR_UINT32 index = 0;
    if (!TSeq_is_initialized(self) || self->_maximum < src->_length || !self->_owned)
    {
        return false;
    }
    self->_length = src->_length;
#if defined(TCOPY_NO_DEFINED)
    if (src->_contiguousBuffer != NULL)
    {
        memcpy(self->_contiguousBuffer, src->_contiguousBuffer, sizeof(T) * self->_length);
    }
#ifdef _ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
    else if (src->_fragmentNum > 0)
    {
        ZR_UINT32 curOffset = 0;
        /* only for CharSeq and OctetSeq */
        T** fragments = (T**)(src->_fixedFragments);
        if (src->_fragmentNum > 64)
        {
            fragments = src->_variousFragments;
        }
        for (index = 0; index < src->_fragmentNum; ++index)
        {
            ZR_UINT32 currentLen = src->_fragmentSize;
            if (index == 0)
            {
                currentLen = src->_firstFragSize;
            }
            else if (index == src->_fragmentNum - 1)
            {
                currentLen = src->_lastFragSize;
            }
            memcpy(self->_contiguousBuffer + curOffset, fragments[index], currentLen);
            curOffset += currentLen;
        }
    }
#endif //_ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
#else
    for (index = 0; index < self->_length; ++index)
    {
        TCOPY(&(self->_contiguousBuffer[index]), (const T *)&(src->_contiguousBuffer[index]), self->_mempool);
    }
    self->_allocMemory = true;
#endif
    return true;
}

struct TSeq* TSeq_copy(struct TSeq *self, const struct TSeq *src)
{
    if (!TSeq_is_initialized(self) || !TSeq_ensure_length(self, src->_length, src->_length))
    {
        return NULL;
    }
    if (!TSeq_copy_no_alloc(self, src))
    {
        return NULL;
    }
    return self;
}

DDS_Long TSeq_compare(const struct TSeq *self, const struct TSeq *src)
{
    ZR_UINT32 index = 0;
    ZR_INT32 res = 0;
    if (self->_length != src->_length)
    {
        return self->_length - src->_length;
    }
#if defined(TCOMPARE_NO_DEFINED)
    res = memcmp(self->_contiguousBuffer, src->_contiguousBuffer, sizeof(T)*self->_length);
    if (res != 0)
    {
        return res;
    }
#else
    for (index = 0; index < self->_length; ++index)
    {
        res = TCOMPARE((const T *)TSeq_get_reference(self, index), (const T *)TSeq_get_reference(src, index));
        if (res != 0)
        {
            return res;
        }
    }
#endif

    return 0;
}

DDS_Boolean TSeq_from_array(struct TSeq *self, const T* array, DDS_ULong length)
{
    ZR_UINT32 index = 0;
    if (!TSeq_is_initialized(self) || !TSeq_ensure_length(self, length, length))
    {
        return false;
    }
#if defined(TCOPY_NO_DEFINED)
    memcpy(self->_contiguousBuffer, array, sizeof(T) * length);
#else
    for (index = 0; index < length; ++index)
    {
        TCOPY(&(self->_contiguousBuffer[index]), &(array[index]), self->_mempool);
        self->_allocMemory = true;
    }
#endif
    return true;
}

DDS_Boolean TSeq_to_array(const struct TSeq *self, T* array, DDS_ULong length)
{
    ZR_UINT32 index = 0;
    if (!TSeq_is_initialized(self) || self->_maximum < length)
    {
        return false;
    }
    if (length == 0)
    {
        return true;
    }
    if (self->_contiguousBuffer != NULL)
    {
#if defined(TCOPY_NO_DEFINED)
        memcpy(array, self->_contiguousBuffer, sizeof(T) * length);
#else
        for (index = 0; index < length; ++index)
        {
            TCOPY(&(array[index]), (const T *)&(self->_contiguousBuffer[index]), self->_mempool);
        }
#endif
        return true;
    }
    else if (self->_discontiguousBuffer != NULL)
    {
        for (index = 0; index < length; ++index)
        {
#if defined(TCOPY_NO_DEFINED)
            memcpy(array + index, (const T *)(self->_discontiguousBuffer[index]), sizeof(T));
#else
            TCOPY(&(array[index]), (const T *)(self->_discontiguousBuffer[index]), self->_mempool);
#endif
        }
        return true;
    }
#ifdef _ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
    else if (self->_fragmentNum > 0)
    {
        ZR_UINT32 curOffset = 0;
        /* only for CharSeq and OctetSeq */
        T** fragments = (T**)(self->_fixedFragments);
        if (self->_fragmentNum > 64)
        {
            fragments = self->_variousFragments;
        }
        for (index = 0; index < self->_fragmentNum; ++index)
        {
            ZR_UINT32 currentLen = self->_fragmentSize;
            if (index == 0)
            {
                currentLen = self->_firstFragSize;
            }
            else if (index == self->_fragmentNum - 1)
            {
                currentLen = self->_lastFragSize;
            }
            memcpy(array + curOffset, fragments[index], currentLen);
            curOffset += currentLen;
        }
        return true;
    }
#endif //_ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
    return false;
}

DDS_Boolean TSeq_loan_contiguous(struct TSeq *self, T *buffer, DDS_ULong newLength, DDS_ULong newMax)
{
    if (!TSeq_is_initialized(self) || self->_maximum != 0 || !self->_owned)
    {
        return false;
    }
    self->_owned = false;
    self->_maximum = newMax;
    self->_length = newLength;
    self->_contiguousBuffer = buffer;
    return true;
}

DDS_Boolean TSeq_loan_discontiguous(struct TSeq *self, T **buffer, DDS_ULong newLength, DDS_ULong newMax)
{
    if (!TSeq_is_initialized(self) || self->_maximum != 0 || !self->_owned)
    {
        return false;
    }
    self->_owned = false;
    self->_maximum = newMax;
    self->_length = newLength;
    self->_discontiguousBuffer = buffer;
    return true;
}

DDS_Boolean TSeq_unloan(struct TSeq *self)
{
    if (!TSeq_is_initialized(self) || self->_owned)
    {
        return false;
    }
    self->_owned = true;
    self->_maximum = 0;
    self->_length = 0;
    self->_contiguousBuffer = NULL;
    self->_discontiguousBuffer = NULL;
    return true;
}

T* TSeq_get_contiguous_buffer(const struct TSeq *self)
{
    if (!TSeq_is_initialized(self))
    {
        return NULL;
    }
    return self->_contiguousBuffer;
}

T** TSeq_get_discontiguous_buffer(const struct TSeq *self)
{
    if (!TSeq_is_initialized(self))
    {
        return NULL;
    }
    return self->_discontiguousBuffer;
}

void TSeq_get_reader_and_data_ptr(const struct TSeq *self, void **readerPtr, void **dataPtr)
{
    *readerPtr = self->_readerPtr;
    *dataPtr = self->_dataPtr;
}

void TSeq_set_reader_and_data_ptr(struct TSeq *self, void *readerPtr, void *dataPtr)
{
    self->_readerPtr = readerPtr;
    self->_dataPtr = dataPtr;
}

DDS_Boolean TSeq_has_ownership(const struct TSeq *self)
{
    return self->_owned;
}

DDS_Boolean TSeq_clear(struct TSeq *self)
{
	ZR_UINT32 index = 0;
    if (!self->_owned)
    {
        return false;
    }
    if (self->_contiguousBuffer != NULL)
    {
#ifndef TFINALIZE_NO_DEFINED
        for (index = 0; index < self->_maximum; index++)
        {
            TFINALIZE(&(self->_contiguousBuffer[index]), self->_mempool, self->_allocMemory);
        }
#endif
        ZRDealloc(NULL, self->_contiguousBuffer);
        self->_contiguousBuffer = NULL;
    }
    self->_discontiguousBuffer = NULL;
    self->_maximum = 0;
    self->_length = 0;
    self->_readerPtr = NULL;
    self->_dataPtr = NULL;
    return true;
}

DDS_Boolean TSeq_finalize(struct TSeq *self)
{
    if (TSeq_is_initialized(self))
    {
        self->_sequenceInit = 0xfeeefeee;
        return TSeq_clear(self);
    }
    return true;
}

void TSeq_shallow_copy(struct TSeq *self, struct TSeq *other)
{
    memcpy(self, other, sizeof(TSeq));
}

#ifdef __cplusplus
TSeq& TSeq::operator=(const struct TSeq& src_seq)
{
    if (this == &src_seq)
    {
        return *this;
    }
    if(NULL == TSeq_copy(this, &src_seq))
    {
        printf("Seq_copy failed.\n");
    }
    return *this;
}
#endif

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


#if defined(TFINALIZE_NO_DEFINED)
#undef TFINALIZE_NO_DEFINED
#undef TFINALIZE
#endif

#ifndef TGetTypeCodeFunc
#if defined(TINITIALIZE_NO_DEFINED)
#undef TINITIALIZE_NO_DEFINED
#undef TINITIALIZE
#endif
#endif

#if defined(TCOMPARE_NO_DEFINED)
#undef TCOMPARE_NO_DEFINED
#undef TCOMPARE
#endif

#if defined(TCOPY_NO_DEFINED)
#undef TCOPY_NO_DEFINED
#undef TCOPY
#endif

#ifdef UNDEF_DDS_SEQUENCE_LENGTH_LIMITATION
#undef DDS_SEQUENCE_LENGTH_LIMITATION
#undef UNDEF_DDS_SEQUENCE_LENGTH_LIMITATION
#endif

#undef QUOTE
