/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/
#include "ZRMemPool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai_infer.h"

namespace data_structure {

#define T Bytes
#define TSeq BytesSeq
#define TINITIALIZE BytesInitializeEx
#define TFINALIZE BytesFinalizeEx
#define TCOPY BytesCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean BytesInitialize(Bytes* self)
    {
        return BytesInitializeEx(self, NULL, true);
    }

    void BytesFinalize(Bytes* self)
    {
        BytesFinalizeEx(self, NULL, true);
    }

    DDS_Boolean BytesCopy(
        Bytes* dst,
        const Bytes* src)
    {
        return BytesCopyEx(dst, src, NULL);
    }

    Bytes* BytesCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        Bytes* newSample = (Bytes*)ZRMalloc(pool, sizeof(Bytes));
        if (newSample == NULL) {
            printf("malloc for Bytes failed.");
            return NULL;
        }
        if (!BytesInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            BytesDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void BytesDestroySample(ZRMemPool* pool, Bytes* sample)
    {
        if (sample == NULL) return;
        BytesFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong BytesGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong BytesGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long BytesGetKeyHash(
        const Bytes* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = BytesSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean BytesHasKey()
    {
        return false;
    }

    TypeCodeHeader* BytesGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = BytesGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean BytesInitializeEx(
        Bytes* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        DDS_OctetSeq_initialize_ex(&self->value, pool, allocateMemory);

        if (allocateMemory) {
        } else {
        }
        return true;
    }

    void BytesFinalizeEx(
        Bytes* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        DDS_OctetSeq_finalize(&self->value);
        if (deletePointers) {
        }
    }

    DDS_Boolean BytesCopyEx(
        Bytes* dst,
        const Bytes* src,
        ZRMemPool* pool)
    {
        if (!DDS_OctetSeq_copy(&dst->value, &src->value)) {
            printf("copy member value failed.");
            return false;
        }
        return true;
    }

    void BytesPrintData(const Bytes* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        DDS_ULong valueTmpLen = DDS_OctetSeq_get_length(&sample->value);
        printf("sample->value: %d\n", valueTmpLen);
        for (DDS_ULong i = 0; i < valueTmpLen; ++i) {
            printf("sample->value[%u]: 0x%02x\n", i, *DDS_OctetSeq_get_reference(&sample->value, i));
        }
        printf("\n");

    }

    DDS::TypeCode* BytesGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::Bytes",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct Bytes typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.getPrimitiveTC(DDS_TK_UCHAR);
        if (memberTc != NULL) {
            memberTc = factory.createSequenceTC(MAX_UINT32_VALUE, memberTc);
        }
        if (memberTc == NULL) {
            printf("Get Member value TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "value",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long BytesSerialize(const Bytes* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&(sample->value)._length, 4)) {
            printf("serialize length of sample->value failed.");
            return -2;
        }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        if (!CDRSerializerNoSerializingMode(cdr)) {
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
            if ((sample->value)._contiguousBuffer) {
                if (!CDRSerializerPutUntypeArray(cdr, (DDS_Octet*)(sample->value)._contiguousBuffer, (sample->value)._length, 1)) {
                    printf("serialize sample->value failed.");
                    return -2;
                }
            } else {
                for (DDS_ULong i = 0; i < (sample->value)._length; ++i) {
                    if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&*DDS_OctetSeq_get_reference(&sample->value, i), 1)) {
                        printf("serialize sample->value failed.");
                        return -2;
                    }
                }
            }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        }
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

        return 0;
    }

    DDS_Long BytesDeserialize(
        Bytes* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong valueTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&valueTmpLen, 4)) {
            DDS_OctetSeq_initialize_ex(&sample->value, pool, true);
            return 0;
        }
        if (!DDS_OctetSeq_ensure_length(&sample->value, valueTmpLen, valueTmpLen)) {
            printf("Set maxiumum member sample->value failed.");
            return -3;
        }
        if (sample->value._contiguousBuffer) {
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->value._contiguousBuffer, valueTmpLen, 1)) {
                printf("deserialize sample->value failed.");
                return -2;
            }
        } else {
            for (DDS_ULong i = 0; i < valueTmpLen; ++i) {
                if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&*DDS_OctetSeq_get_reference(&sample->value, i), 1)) {
                    printf("deserialize sample->value failed.");
                    return -2;
                }
            }
        }
        return 0;
    }

    DDS_ULong BytesGetSerializedSampleSize(const Bytes* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);
        DDS_ULong valueLen = DDS_OctetSeq_get_length(&sample->value);
        if (valueLen != 0) {
            currentAlignment += 1 * valueLen;
        }

        return currentAlignment - initialAlignment;
    }

    DDS_Long BytesSerializeKey(const Bytes* sample, CDRSerializer* cdr)
    {
        if (BytesSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long BytesDeserializeKey(
        Bytes* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (BytesDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong BytesGetSerializedKeySize(const Bytes* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += BytesGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* BytesLoanSampleBuf(Bytes* sample, DDS_Boolean takeBuffer)
    {
        DDS_Char* rst = (DDS_Char*)(sample->value._contiguousBuffer);
        if (takeBuffer) {
            sample->value._length = 0;
            sample->value._maximum = 0;
            sample->value._contiguousBuffer = NULL;
        }
        return rst;
    }

    void BytesReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ZRDealloc(NULL, sampleBuf);
    }

    DDS_Long BytesLoanDeserialize(Bytes* sampleBuf,
                                  CDRDeserializer* cdr,
                                  DDS_ULong curIndex,
                                  DDS_ULong totalNum,
                                  DDS_Char* base,
                                  DDS_ULong offset,
                                  DDS_ULong space,
                                  DDS_ULong fixedHeaderLen)
    {
#ifdef _ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE
        DDS_OctetSeq* sampleSeq = &(sampleBuf->value);
        DDS_Char** fragments = sampleSeq->_fixedFragments;
        DDS_Char** headers = sampleSeq->_fixedHeader;
        if (totalNum > 64) {
            if (sampleSeq->_variousFragments == NULL || sampleSeq->_fragmentNum < totalNum) {
                ZRDealloc(NULL, sampleSeq->_variousFragments);
                ZRDealloc(NULL, sampleSeq->_variousHeader);
                // ��Ƭ��������64����Ҫ��̬����
                sampleSeq->_variousFragments = (DDS_Char**)ZRMalloc(NULL, totalNum * sizeof(DDS_Char*));
                sampleSeq->_variousHeader = (DDS_Char**)ZRMalloc(NULL, totalNum * sizeof(DDS_Char*));
                if (NULL == sampleSeq->_variousFragments || NULL == sampleSeq->_variousHeader) {
                    printf("malloc for _variousFragments failed.\n");
                    return -1;
                }
                memset(sampleSeq->_variousFragments, 0, sizeof(totalNum * sizeof(DDS_Char*)));
                memset(sampleSeq->_variousHeader, 0, sizeof(totalNum * sizeof(DDS_Char*)));
            }
            fragments = sampleSeq->_variousFragments;
            headers = sampleSeq->_variousHeader;
        }
        sampleSeq->_fragmentNum = totalNum;
        if (totalNum == 1) {
            sampleSeq->_length = *(DDS_ULong*)(base + offset + fixedHeaderLen - 4);
            sampleSeq->_maximum = sampleSeq->_length;
            sampleSeq->_firstFragSize = space - fixedHeaderLen;
            fragments[curIndex] = base + offset + fixedHeaderLen;
            headers[curIndex] = base;
        } else if (curIndex == 0) {
            sampleSeq->_length = *(DDS_ULong*)(base + offset + fixedHeaderLen - 4);
            sampleSeq->_maximum = sampleSeq->_length;
            sampleSeq->_firstFragSize = space - fixedHeaderLen;
            fragments[curIndex] = base + offset + fixedHeaderLen;
            headers[curIndex] = base;
        } else if (curIndex == totalNum - 1) {
            sampleSeq->_lastFragSize = space;
            fragments[curIndex] = base + offset;
            headers[curIndex] = base;
        } else {
            sampleSeq->_fragmentSize = space;
            fragments[curIndex] = base + offset;
            headers[curIndex] = base;
        }
#endif /* _ZRDDS_INCLUDE_DR_NO_SERIALIZE_MODE */
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long BytesOnSiteDeserialize(CDRDeserializer* cdr,
                                    Bytes* sample,
                                    DDS_ULong offset,
                                    DDS_ULong totalSize,
                                    DDS_Char* payload,
                                    DDS_ULong payloadLen,
                                    DDS_ULong fixedHeaderLen)
    {
        DDS_OctetSeq* seqMember = &(sample->value);
        if (!DDS_OctetSeq_set_maximum(seqMember, totalSize - fixedHeaderLen)) {
            printf("Set maxiumum member value failed.");
            return -3;
        }
        if (offset == 0) {
            if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&seqMember->_length, 4)) {
                printf("get value length failed.");
                return -1;
            }
            memcpy(seqMember->_contiguousBuffer,
                   (DDS_Char*)payload + fixedHeaderLen,
                   payloadLen - fixedHeaderLen);
            return 0;
        }
        memcpy(seqMember->_contiguousBuffer + offset - fixedHeaderLen,
               payload, payloadLen);
        return 0;
    }

    DDS_Boolean BytesNoSerializingSupported()
    {
        return true;
    }

    DDS_ULong BytesFixedHeaderLength()
    {
        DDS_ULong curLen = 0;
        curLen += CDRSerializerGetUntypeSize(4, curLen);
        return curLen;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T SingleTask
#define TSeq SingleTaskSeq
#define TINITIALIZE SingleTaskInitializeEx
#define TFINALIZE SingleTaskFinalizeEx
#define TCOPY SingleTaskCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean SingleTaskInitialize(SingleTask* self)
    {
        return SingleTaskInitializeEx(self, NULL, true);
    }

    void SingleTaskFinalize(SingleTask* self)
    {
        SingleTaskFinalizeEx(self, NULL, true);
    }

    DDS_Boolean SingleTaskCopy(
        SingleTask* dst,
        const SingleTask* src)
    {
        return SingleTaskCopyEx(dst, src, NULL);
    }

    SingleTask* SingleTaskCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        SingleTask* newSample = (SingleTask*)ZRMalloc(pool, sizeof(SingleTask));
        if (newSample == NULL) {
            printf("malloc for SingleTask failed.");
            return NULL;
        }
        if (!SingleTaskInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            SingleTaskDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void SingleTaskDestroySample(ZRMemPool* pool, SingleTask* sample)
    {
        if (sample == NULL) return;
        SingleTaskFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong SingleTaskGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong SingleTaskGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long SingleTaskGetKeyHash(
        const SingleTask* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = SingleTaskSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean SingleTaskHasKey()
    {
        return false;
    }

    TypeCodeHeader* SingleTaskGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = SingleTaskGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean SingleTaskInitializeEx(
        SingleTask* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->request_id = NULL;

        self->task_id = NULL;

        self->model_id = NULL;

        self->client_id = NULL;

        if (!data_structure::BytesInitializeEx(&self->payload, pool, allocateMemory)) {
            printf("Initialize member self->payload failed.");
            return false;
        }

        if (allocateMemory) {
        } else {
            if (self->request_id != NULL) {
                self->request_id[0] = '\0';
            }
            if (self->task_id != NULL) {
                self->task_id[0] = '\0';
            }
            if (self->model_id != NULL) {
                self->model_id[0] = '\0';
            }
            if (self->client_id != NULL) {
                self->client_id[0] = '\0';
            }
        }
        return true;
    }

    void SingleTaskFinalizeEx(
        SingleTask* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::BytesFinalizeEx(&self->payload, pool, deletePointers);
        if (deletePointers) {
        }
    }

    DDS_Boolean SingleTaskCopyEx(
        SingleTask* dst,
        const SingleTask* src,
        ZRMemPool* pool)
    {
        if (src->request_id == NULL) {
            ZRDealloc(pool, dst->request_id);
            dst->request_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->request_id);
            DDS_Long dstLen = -1;
            if (dst->request_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->request_id) < srcLen) {
                ZRDealloc(pool, dst->request_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->request_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->request_id == NULL) {
                    printf("malloc for request_id failed.");
                    return false;
                }
            }
            strcpy(dst->request_id, src->request_id);
        }
        if (src->task_id == NULL) {
            ZRDealloc(pool, dst->task_id);
            dst->task_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->task_id);
            DDS_Long dstLen = -1;
            if (dst->task_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->task_id) < srcLen) {
                ZRDealloc(pool, dst->task_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->task_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->task_id == NULL) {
                    printf("malloc for task_id failed.");
                    return false;
                }
            }
            strcpy(dst->task_id, src->task_id);
        }
        if (src->model_id == NULL) {
            ZRDealloc(pool, dst->model_id);
            dst->model_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->model_id);
            DDS_Long dstLen = -1;
            if (dst->model_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->model_id) < srcLen) {
                ZRDealloc(pool, dst->model_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->model_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->model_id == NULL) {
                    printf("malloc for model_id failed.");
                    return false;
                }
            }
            strcpy(dst->model_id, src->model_id);
        }
        if (src->client_id == NULL) {
            ZRDealloc(pool, dst->client_id);
            dst->client_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->client_id);
            DDS_Long dstLen = -1;
            if (dst->client_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->client_id) < srcLen) {
                ZRDealloc(pool, dst->client_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->client_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->client_id == NULL) {
                    printf("malloc for client_id failed.");
                    return false;
                }
            }
            strcpy(dst->client_id, src->client_id);
        }
        if (!data_structure::BytesCopyEx(&dst->payload, &src->payload, pool)) {
            printf("copy member payload failed.");
            return false;
        }
        return true;
    }

    void SingleTaskPrintData(const SingleTask* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->request_id != NULL) {
            printf("sample->request_id(%d): %s\n", strlen(sample->request_id), sample->request_id);
        } else {
            printf("sample->request_id(0): NULL\n");
        }
        printf("\n");

        if (sample->task_id != NULL) {
            printf("sample->task_id(%d): %s\n", strlen(sample->task_id), sample->task_id);
        } else {
            printf("sample->task_id(0): NULL\n");
        }
        printf("\n");

        if (sample->model_id != NULL) {
            printf("sample->model_id(%d): %s\n", strlen(sample->model_id), sample->model_id);
        } else {
            printf("sample->model_id(0): NULL\n");
        }
        printf("\n");

        if (sample->client_id != NULL) {
            printf("sample->client_id(%d): %s\n", strlen(sample->client_id), sample->client_id);
        } else {
            printf("sample->client_id(0): NULL\n");
        }
        printf("\n");

        data_structure::BytesPrintData(&sample->payload);
        printf("\n");

    }

    DDS::TypeCode* SingleTaskGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::SingleTask",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct SingleTask typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member request_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "request_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member task_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "task_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member model_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "model_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member client_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            3,
            3,
            "client_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::BytesGetTypeCode();
        if (memberTc == NULL) {
            printf("Get Member payload TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            4,
            4,
            "payload",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long SingleTaskSerialize(const SingleTask* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->request_id, sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1)) {
            printf("serialize sample->request_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->task_id, sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1)) {
            printf("serialize sample->task_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->model_id, sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1)) {
            printf("serialize sample->model_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->client_id, sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1)) {
            printf("serialize sample->client_id failed.");
            return -2;
        }

        if (data_structure::BytesSerialize(&sample->payload, cdr) < 0) {
            printf("serialize sample->payload failed.");
            return -2;
        }

        return 0;
    }

    DDS_Long SingleTaskDeserialize(
        SingleTask* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong request_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&request_idTmpLen, 4)) {
            sample->request_id = NULL;
            sample->task_id = NULL;
            sample->model_id = NULL;
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == request_idTmpLen) {
            ZRDealloc(pool, sample->request_id);
            sample->request_id = NULL;
        } else {
            if (sample->request_id == NULL) {
                sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                if (sample->request_id == NULL) {
                    printf("malloc for sample->request_id failed(%d).", request_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->request_id) + 1 < request_idTmpLen) {
                    ZRDealloc(pool, sample->request_id);
                    sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                    if (sample->request_id == NULL) {
                        printf("realloc for sample->request_id failed(%d).", request_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->request_id, request_idTmpLen, 1)) {
                printf("deserialize member sample->request_id failed.");
                return -4;
            }
        }
        DDS_ULong task_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&task_idTmpLen, 4)) {
            sample->task_id = NULL;
            sample->model_id = NULL;
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == task_idTmpLen) {
            ZRDealloc(pool, sample->task_id);
            sample->task_id = NULL;
        } else {
            if (sample->task_id == NULL) {
                sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                if (sample->task_id == NULL) {
                    printf("malloc for sample->task_id failed(%d).", task_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->task_id) + 1 < task_idTmpLen) {
                    ZRDealloc(pool, sample->task_id);
                    sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                    if (sample->task_id == NULL) {
                        printf("realloc for sample->task_id failed(%d).", task_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->task_id, task_idTmpLen, 1)) {
                printf("deserialize member sample->task_id failed.");
                return -4;
            }
        }
        DDS_ULong model_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&model_idTmpLen, 4)) {
            sample->model_id = NULL;
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == model_idTmpLen) {
            ZRDealloc(pool, sample->model_id);
            sample->model_id = NULL;
        } else {
            if (sample->model_id == NULL) {
                sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                if (sample->model_id == NULL) {
                    printf("malloc for sample->model_id failed(%d).", model_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->model_id) + 1 < model_idTmpLen) {
                    ZRDealloc(pool, sample->model_id);
                    sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                    if (sample->model_id == NULL) {
                        printf("realloc for sample->model_id failed(%d).", model_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->model_id, model_idTmpLen, 1)) {
                printf("deserialize member sample->model_id failed.");
                return -4;
            }
        }
        DDS_ULong client_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&client_idTmpLen, 4)) {
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == client_idTmpLen) {
            ZRDealloc(pool, sample->client_id);
            sample->client_id = NULL;
        } else {
            if (sample->client_id == NULL) {
                sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                if (sample->client_id == NULL) {
                    printf("malloc for sample->client_id failed(%d).", client_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->client_id) + 1 < client_idTmpLen) {
                    ZRDealloc(pool, sample->client_id);
                    sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                    if (sample->client_id == NULL) {
                        printf("realloc for sample->client_id failed(%d).", client_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->client_id, client_idTmpLen, 1)) {
                printf("deserialize member sample->client_id failed.");
                return -4;
            }
        }
        if (data_structure::BytesDeserialize(&sample->payload, cdr, pool) < 0) {
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        return 0;
    }

    DDS_ULong SingleTaskGetSerializedSampleSize(const SingleTask* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1, currentAlignment);

        currentAlignment += data_structure::BytesGetSerializedSampleSize(&sample->payload, currentAlignment);

        return currentAlignment - initialAlignment;
    }

    DDS_Long SingleTaskSerializeKey(const SingleTask* sample, CDRSerializer* cdr)
    {
        if (SingleTaskSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long SingleTaskDeserializeKey(
        SingleTask* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (SingleTaskDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong SingleTaskGetSerializedKeySize(const SingleTask* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += SingleTaskGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* SingleTaskLoanSampleBuf(SingleTask* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void SingleTaskReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long SingleTaskLoanDeserialize(SingleTask* sampleBuf,
                                       CDRDeserializer* cdr,
                                       DDS_ULong curIndex,
                                       DDS_ULong totalNum,
                                       DDS_Char* base,
                                       DDS_ULong offset,
                                       DDS_ULong space,
                                       DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long SingleTaskOnSiteDeserialize(CDRDeserializer* cdr,
                                         SingleTask* sample,
                                         DDS_ULong offset,
                                         DDS_ULong totalSize,
                                         DDS_Char* payload,
                                         DDS_ULong payloadLen,
                                         DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean SingleTaskNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong SingleTaskFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T InferenceRequest
#define TSeq InferenceRequestSeq
#define TINITIALIZE InferenceRequestInitializeEx
#define TFINALIZE InferenceRequestFinalizeEx
#define TCOPY InferenceRequestCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean InferenceRequestInitialize(InferenceRequest* self)
    {
        return InferenceRequestInitializeEx(self, NULL, true);
    }

    void InferenceRequestFinalize(InferenceRequest* self)
    {
        InferenceRequestFinalizeEx(self, NULL, true);
    }

    DDS_Boolean InferenceRequestCopy(
        InferenceRequest* dst,
        const InferenceRequest* src)
    {
        return InferenceRequestCopyEx(dst, src, NULL);
    }

    InferenceRequest* InferenceRequestCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        InferenceRequest* newSample = (InferenceRequest*)ZRMalloc(pool, sizeof(InferenceRequest));
        if (newSample == NULL) {
            printf("malloc for InferenceRequest failed.");
            return NULL;
        }
        if (!InferenceRequestInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            InferenceRequestDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void InferenceRequestDestroySample(ZRMemPool* pool, InferenceRequest* sample)
    {
        if (sample == NULL) return;
        InferenceRequestFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong InferenceRequestGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong InferenceRequestGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long InferenceRequestGetKeyHash(
        const InferenceRequest* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = InferenceRequestSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean InferenceRequestHasKey()
    {
        return false;
    }

    TypeCodeHeader* InferenceRequestGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = InferenceRequestGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean InferenceRequestInitializeEx(
        InferenceRequest* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->request_id = NULL;

        data_structure::SingleTaskSeq_initialize_ex(&self->tasks, pool, allocateMemory);

        if (allocateMemory) {
        } else {
            if (self->request_id != NULL) {
                self->request_id[0] = '\0';
            }
        }
        return true;
    }

    void InferenceRequestFinalizeEx(
        InferenceRequest* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::SingleTaskSeq_finalize(&self->tasks);
        if (deletePointers) {
        }
    }

    DDS_Boolean InferenceRequestCopyEx(
        InferenceRequest* dst,
        const InferenceRequest* src,
        ZRMemPool* pool)
    {
        if (src->request_id == NULL) {
            ZRDealloc(pool, dst->request_id);
            dst->request_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->request_id);
            DDS_Long dstLen = -1;
            if (dst->request_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->request_id) < srcLen) {
                ZRDealloc(pool, dst->request_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->request_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->request_id == NULL) {
                    printf("malloc for request_id failed.");
                    return false;
                }
            }
            strcpy(dst->request_id, src->request_id);
        }
        if (!data_structure::SingleTaskSeq_copy(&dst->tasks, &src->tasks)) {
            printf("copy member tasks failed.");
            return false;
        }
        return true;
    }

    void InferenceRequestPrintData(const InferenceRequest* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->request_id != NULL) {
            printf("sample->request_id(%d): %s\n", strlen(sample->request_id), sample->request_id);
        } else {
            printf("sample->request_id(0): NULL\n");
        }
        printf("\n");

        DDS_ULong tasksTmpLen = data_structure::SingleTaskSeq_get_length(&sample->tasks);
        printf("sample->tasks: %d\n", tasksTmpLen);
        for (DDS_ULong i = 0; i < tasksTmpLen; ++i) {
            data_structure::SingleTaskPrintData(&*data_structure::SingleTaskSeq_get_reference(&sample->tasks, i));
        }
        printf("\n");

    }

    DDS::TypeCode* InferenceRequestGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::InferenceRequest",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct InferenceRequest typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member request_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "request_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::SingleTaskGetTypeCode();
        if (memberTc != NULL) {
            memberTc = factory.createSequenceTC(MAX_UINT32_VALUE, memberTc);
        }
        if (memberTc == NULL) {
            printf("Get Member tasks TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "tasks",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long InferenceRequestSerialize(const InferenceRequest* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->request_id, sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1)) {
            printf("serialize sample->request_id failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&(sample->tasks)._length, 4)) {
            printf("serialize length of sample->tasks failed.");
            return -2;
        }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        if (!CDRSerializerNoSerializingMode(cdr)) {
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
            for (DDS_ULong i = 0; i < (sample->tasks)._length; ++i) {
                if (data_structure::SingleTaskSerialize(&*data_structure::SingleTaskSeq_get_reference(&sample->tasks, i), cdr) < 0) {
                    printf("serialize sample->tasks failed.");
                    return -2;
                }
            }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        }
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

        return 0;
    }

    DDS_Long InferenceRequestDeserialize(
        InferenceRequest* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong request_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&request_idTmpLen, 4)) {
            sample->request_id = NULL;
            data_structure::SingleTaskSeq_initialize_ex(&sample->tasks, pool, true);
            return 0;
        }
        if (0 == request_idTmpLen) {
            ZRDealloc(pool, sample->request_id);
            sample->request_id = NULL;
        } else {
            if (sample->request_id == NULL) {
                sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                if (sample->request_id == NULL) {
                    printf("malloc for sample->request_id failed(%d).", request_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->request_id) + 1 < request_idTmpLen) {
                    ZRDealloc(pool, sample->request_id);
                    sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                    if (sample->request_id == NULL) {
                        printf("realloc for sample->request_id failed(%d).", request_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->request_id, request_idTmpLen, 1)) {
                printf("deserialize member sample->request_id failed.");
                return -4;
            }
        }
        DDS_ULong tasksTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&tasksTmpLen, 4)) {
            data_structure::SingleTaskSeq_initialize_ex(&sample->tasks, pool, true);
            return 0;
        }
        if (!data_structure::SingleTaskSeq_ensure_length(&sample->tasks, tasksTmpLen, tasksTmpLen)) {
            printf("Set maxiumum member sample->tasks failed.");
            return -3;
        }
        for (DDS_ULong i = 0; i < tasksTmpLen; ++i) {
            if (data_structure::SingleTaskDeserialize(&*data_structure::SingleTaskSeq_get_reference(&sample->tasks, i), cdr, pool) < 0) {
                printf("deserialize sample->tasks failed.");
                return -2;
            }
        }
        return 0;
    }

    DDS_ULong InferenceRequestGetSerializedSampleSize(const InferenceRequest* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);
        DDS_ULong tasksLen = data_structure::SingleTaskSeq_get_length(&sample->tasks);
        if (tasksLen != 0) {
            for (DDS_ULong i = 0; i < tasksLen; ++i) {
                data_structure::SingleTask* curEle = data_structure::SingleTaskSeq_get_reference(&sample->tasks, i);
                currentAlignment += data_structure::SingleTaskGetSerializedSampleSize(curEle, currentAlignment);
            }
        }

        return currentAlignment - initialAlignment;
    }

    DDS_Long InferenceRequestSerializeKey(const InferenceRequest* sample, CDRSerializer* cdr)
    {
        if (InferenceRequestSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long InferenceRequestDeserializeKey(
        InferenceRequest* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (InferenceRequestDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong InferenceRequestGetSerializedKeySize(const InferenceRequest* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += InferenceRequestGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* InferenceRequestLoanSampleBuf(InferenceRequest* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void InferenceRequestReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long InferenceRequestLoanDeserialize(InferenceRequest* sampleBuf,
                                             CDRDeserializer* cdr,
                                             DDS_ULong curIndex,
                                             DDS_ULong totalNum,
                                             DDS_Char* base,
                                             DDS_ULong offset,
                                             DDS_ULong space,
                                             DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long InferenceRequestOnSiteDeserialize(CDRDeserializer* cdr,
                                               InferenceRequest* sample,
                                               DDS_ULong offset,
                                               DDS_ULong totalSize,
                                               DDS_Char* payload,
                                               DDS_ULong payloadLen,
                                               DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean InferenceRequestNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong InferenceRequestFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T Task
#define TSeq TaskSeq
#define TINITIALIZE TaskInitializeEx
#define TFINALIZE TaskFinalizeEx
#define TCOPY TaskCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean TaskInitialize(Task* self)
    {
        return TaskInitializeEx(self, NULL, true);
    }

    void TaskFinalize(Task* self)
    {
        TaskFinalizeEx(self, NULL, true);
    }

    DDS_Boolean TaskCopy(
        Task* dst,
        const Task* src)
    {
        return TaskCopyEx(dst, src, NULL);
    }

    Task* TaskCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        Task* newSample = (Task*)ZRMalloc(pool, sizeof(Task));
        if (newSample == NULL) {
            printf("malloc for Task failed.");
            return NULL;
        }
        if (!TaskInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            TaskDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void TaskDestroySample(ZRMemPool* pool, Task* sample)
    {
        if (sample == NULL) return;
        TaskFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong TaskGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong TaskGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long TaskGetKeyHash(
        const Task* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = TaskSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean TaskHasKey()
    {
        return false;
    }

    TypeCodeHeader* TaskGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = TaskGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean TaskInitializeEx(
        Task* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->request_id = NULL;

        self->task_id = NULL;

        self->client_id = NULL;

        if (!data_structure::BytesInitializeEx(&self->payload, pool, allocateMemory)) {
            printf("Initialize member self->payload failed.");
            return false;
        }

        if (allocateMemory) {
        } else {
            if (self->request_id != NULL) {
                self->request_id[0] = '\0';
            }
            if (self->task_id != NULL) {
                self->task_id[0] = '\0';
            }
            if (self->client_id != NULL) {
                self->client_id[0] = '\0';
            }
        }
        return true;
    }

    void TaskFinalizeEx(
        Task* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::BytesFinalizeEx(&self->payload, pool, deletePointers);
        if (deletePointers) {
        }
    }

    DDS_Boolean TaskCopyEx(
        Task* dst,
        const Task* src,
        ZRMemPool* pool)
    {
        if (src->request_id == NULL) {
            ZRDealloc(pool, dst->request_id);
            dst->request_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->request_id);
            DDS_Long dstLen = -1;
            if (dst->request_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->request_id) < srcLen) {
                ZRDealloc(pool, dst->request_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->request_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->request_id == NULL) {
                    printf("malloc for request_id failed.");
                    return false;
                }
            }
            strcpy(dst->request_id, src->request_id);
        }
        if (src->task_id == NULL) {
            ZRDealloc(pool, dst->task_id);
            dst->task_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->task_id);
            DDS_Long dstLen = -1;
            if (dst->task_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->task_id) < srcLen) {
                ZRDealloc(pool, dst->task_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->task_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->task_id == NULL) {
                    printf("malloc for task_id failed.");
                    return false;
                }
            }
            strcpy(dst->task_id, src->task_id);
        }
        if (src->client_id == NULL) {
            ZRDealloc(pool, dst->client_id);
            dst->client_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->client_id);
            DDS_Long dstLen = -1;
            if (dst->client_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->client_id) < srcLen) {
                ZRDealloc(pool, dst->client_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->client_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->client_id == NULL) {
                    printf("malloc for client_id failed.");
                    return false;
                }
            }
            strcpy(dst->client_id, src->client_id);
        }
        if (!data_structure::BytesCopyEx(&dst->payload, &src->payload, pool)) {
            printf("copy member payload failed.");
            return false;
        }
        return true;
    }

    void TaskPrintData(const Task* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->request_id != NULL) {
            printf("sample->request_id(%d): %s\n", strlen(sample->request_id), sample->request_id);
        } else {
            printf("sample->request_id(0): NULL\n");
        }
        printf("\n");

        if (sample->task_id != NULL) {
            printf("sample->task_id(%d): %s\n", strlen(sample->task_id), sample->task_id);
        } else {
            printf("sample->task_id(0): NULL\n");
        }
        printf("\n");

        if (sample->client_id != NULL) {
            printf("sample->client_id(%d): %s\n", strlen(sample->client_id), sample->client_id);
        } else {
            printf("sample->client_id(0): NULL\n");
        }
        printf("\n");

        data_structure::BytesPrintData(&sample->payload);
        printf("\n");

    }

    DDS::TypeCode* TaskGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::Task",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct Task typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member request_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "request_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member task_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "task_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member client_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "client_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::BytesGetTypeCode();
        if (memberTc == NULL) {
            printf("Get Member payload TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            3,
            3,
            "payload",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long TaskSerialize(const Task* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->request_id, sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1)) {
            printf("serialize sample->request_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->task_id, sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1)) {
            printf("serialize sample->task_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->client_id, sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1)) {
            printf("serialize sample->client_id failed.");
            return -2;
        }

        if (data_structure::BytesSerialize(&sample->payload, cdr) < 0) {
            printf("serialize sample->payload failed.");
            return -2;
        }

        return 0;
    }

    DDS_Long TaskDeserialize(
        Task* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong request_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&request_idTmpLen, 4)) {
            sample->request_id = NULL;
            sample->task_id = NULL;
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == request_idTmpLen) {
            ZRDealloc(pool, sample->request_id);
            sample->request_id = NULL;
        } else {
            if (sample->request_id == NULL) {
                sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                if (sample->request_id == NULL) {
                    printf("malloc for sample->request_id failed(%d).", request_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->request_id) + 1 < request_idTmpLen) {
                    ZRDealloc(pool, sample->request_id);
                    sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                    if (sample->request_id == NULL) {
                        printf("realloc for sample->request_id failed(%d).", request_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->request_id, request_idTmpLen, 1)) {
                printf("deserialize member sample->request_id failed.");
                return -4;
            }
        }
        DDS_ULong task_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&task_idTmpLen, 4)) {
            sample->task_id = NULL;
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == task_idTmpLen) {
            ZRDealloc(pool, sample->task_id);
            sample->task_id = NULL;
        } else {
            if (sample->task_id == NULL) {
                sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                if (sample->task_id == NULL) {
                    printf("malloc for sample->task_id failed(%d).", task_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->task_id) + 1 < task_idTmpLen) {
                    ZRDealloc(pool, sample->task_id);
                    sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                    if (sample->task_id == NULL) {
                        printf("realloc for sample->task_id failed(%d).", task_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->task_id, task_idTmpLen, 1)) {
                printf("deserialize member sample->task_id failed.");
                return -4;
            }
        }
        DDS_ULong client_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&client_idTmpLen, 4)) {
            sample->client_id = NULL;
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        if (0 == client_idTmpLen) {
            ZRDealloc(pool, sample->client_id);
            sample->client_id = NULL;
        } else {
            if (sample->client_id == NULL) {
                sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                if (sample->client_id == NULL) {
                    printf("malloc for sample->client_id failed(%d).", client_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->client_id) + 1 < client_idTmpLen) {
                    ZRDealloc(pool, sample->client_id);
                    sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                    if (sample->client_id == NULL) {
                        printf("realloc for sample->client_id failed(%d).", client_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->client_id, client_idTmpLen, 1)) {
                printf("deserialize member sample->client_id failed.");
                return -4;
            }
        }
        if (data_structure::BytesDeserialize(&sample->payload, cdr, pool) < 0) {
            if (!data_structure::BytesInitializeEx(&sample->payload, pool, true)) {
                printf("Initialize member sample->payload failed.");
                return -2;
            }
            return 0;
        }
        return 0;
    }

    DDS_ULong TaskGetSerializedSampleSize(const Task* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1, currentAlignment);

        currentAlignment += data_structure::BytesGetSerializedSampleSize(&sample->payload, currentAlignment);

        return currentAlignment - initialAlignment;
    }

    DDS_Long TaskSerializeKey(const Task* sample, CDRSerializer* cdr)
    {
        if (TaskSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long TaskDeserializeKey(
        Task* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (TaskDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong TaskGetSerializedKeySize(const Task* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += TaskGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* TaskLoanSampleBuf(Task* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void TaskReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long TaskLoanDeserialize(Task* sampleBuf,
                                 CDRDeserializer* cdr,
                                 DDS_ULong curIndex,
                                 DDS_ULong totalNum,
                                 DDS_Char* base,
                                 DDS_ULong offset,
                                 DDS_ULong space,
                                 DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long TaskOnSiteDeserialize(CDRDeserializer* cdr,
                                   Task* sample,
                                   DDS_ULong offset,
                                   DDS_ULong totalSize,
                                   DDS_Char* payload,
                                   DDS_ULong payloadLen,
                                   DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean TaskNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong TaskFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T OpenBatch
#define TSeq OpenBatchSeq
#define TINITIALIZE OpenBatchInitializeEx
#define TFINALIZE OpenBatchFinalizeEx
#define TCOPY OpenBatchCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean OpenBatchInitialize(OpenBatch* self)
    {
        return OpenBatchInitializeEx(self, NULL, true);
    }

    void OpenBatchFinalize(OpenBatch* self)
    {
        OpenBatchFinalizeEx(self, NULL, true);
    }

    DDS_Boolean OpenBatchCopy(
        OpenBatch* dst,
        const OpenBatch* src)
    {
        return OpenBatchCopyEx(dst, src, NULL);
    }

    OpenBatch* OpenBatchCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        OpenBatch* newSample = (OpenBatch*)ZRMalloc(pool, sizeof(OpenBatch));
        if (newSample == NULL) {
            printf("malloc for OpenBatch failed.");
            return NULL;
        }
        if (!OpenBatchInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            OpenBatchDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void OpenBatchDestroySample(ZRMemPool* pool, OpenBatch* sample)
    {
        if (sample == NULL) return;
        OpenBatchFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong OpenBatchGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong OpenBatchGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long OpenBatchGetKeyHash(
        const OpenBatch* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = OpenBatchSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean OpenBatchHasKey()
    {
        return false;
    }

    TypeCodeHeader* OpenBatchGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = OpenBatchGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean OpenBatchInitializeEx(
        OpenBatch* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->batch_id = NULL;

        self->model_id = NULL;

        self->size = 0;

        self->create_ts_ms = 0;

        if (allocateMemory) {
        } else {
            if (self->batch_id != NULL) {
                self->batch_id[0] = '\0';
            }
            if (self->model_id != NULL) {
                self->model_id[0] = '\0';
            }
        }
        return true;
    }

    void OpenBatchFinalizeEx(
        OpenBatch* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        if (deletePointers) {
        }
    }

    DDS_Boolean OpenBatchCopyEx(
        OpenBatch* dst,
        const OpenBatch* src,
        ZRMemPool* pool)
    {
        if (src->batch_id == NULL) {
            ZRDealloc(pool, dst->batch_id);
            dst->batch_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->batch_id);
            DDS_Long dstLen = -1;
            if (dst->batch_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->batch_id) < srcLen) {
                ZRDealloc(pool, dst->batch_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->batch_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->batch_id == NULL) {
                    printf("malloc for batch_id failed.");
                    return false;
                }
            }
            strcpy(dst->batch_id, src->batch_id);
        }
        if (src->model_id == NULL) {
            ZRDealloc(pool, dst->model_id);
            dst->model_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->model_id);
            DDS_Long dstLen = -1;
            if (dst->model_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->model_id) < srcLen) {
                ZRDealloc(pool, dst->model_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->model_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->model_id == NULL) {
                    printf("malloc for model_id failed.");
                    return false;
                }
            }
            strcpy(dst->model_id, src->model_id);
        }
        dst->size = src->size;
        dst->create_ts_ms = src->create_ts_ms;
        return true;
    }

    void OpenBatchPrintData(const OpenBatch* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->batch_id != NULL) {
            printf("sample->batch_id(%d): %s\n", strlen(sample->batch_id), sample->batch_id);
        } else {
            printf("sample->batch_id(0): NULL\n");
        }
        printf("\n");

        if (sample->model_id != NULL) {
            printf("sample->model_id(%d): %s\n", strlen(sample->model_id), sample->model_id);
        } else {
            printf("sample->model_id(0): NULL\n");
        }
        printf("\n");

        printf("sample->size: %d\n", sample->size);
        printf("\n");

        printf("sample->create_ts_ms: %d\n", sample->create_ts_ms);
        printf("\n");

    }

    DDS::TypeCode* OpenBatchGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::OpenBatch",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct OpenBatch typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member batch_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "batch_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member model_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "model_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.getPrimitiveTC(DDS_TK_INT);
        if (memberTc == NULL) {
            printf("Get Member size TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "size",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.getPrimitiveTC(DDS_TK_INT);
        if (memberTc == NULL) {
            printf("Get Member create_ts_ms TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            3,
            3,
            "create_ts_ms",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long OpenBatchSerialize(const OpenBatch* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->batch_id, sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1)) {
            printf("serialize sample->batch_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->model_id, sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1)) {
            printf("serialize sample->model_id failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&sample->size, 4)) {
            printf("serialize sample->size failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&sample->create_ts_ms, 4)) {
            printf("serialize sample->create_ts_ms failed.");
            return -2;
        }

        return 0;
    }

    DDS_Long OpenBatchDeserialize(
        OpenBatch* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong batch_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&batch_idTmpLen, 4)) {
            sample->batch_id = NULL;
            sample->model_id = NULL;
            sample->size = 0;
            sample->create_ts_ms = 0;
            return 0;
        }
        if (0 == batch_idTmpLen) {
            ZRDealloc(pool, sample->batch_id);
            sample->batch_id = NULL;
        } else {
            if (sample->batch_id == NULL) {
                sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                if (sample->batch_id == NULL) {
                    printf("malloc for sample->batch_id failed(%d).", batch_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->batch_id) + 1 < batch_idTmpLen) {
                    ZRDealloc(pool, sample->batch_id);
                    sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                    if (sample->batch_id == NULL) {
                        printf("realloc for sample->batch_id failed(%d).", batch_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->batch_id, batch_idTmpLen, 1)) {
                printf("deserialize member sample->batch_id failed.");
                return -4;
            }
        }
        DDS_ULong model_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&model_idTmpLen, 4)) {
            sample->model_id = NULL;
            sample->size = 0;
            sample->create_ts_ms = 0;
            return 0;
        }
        if (0 == model_idTmpLen) {
            ZRDealloc(pool, sample->model_id);
            sample->model_id = NULL;
        } else {
            if (sample->model_id == NULL) {
                sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                if (sample->model_id == NULL) {
                    printf("malloc for sample->model_id failed(%d).", model_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->model_id) + 1 < model_idTmpLen) {
                    ZRDealloc(pool, sample->model_id);
                    sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                    if (sample->model_id == NULL) {
                        printf("realloc for sample->model_id failed(%d).", model_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->model_id, model_idTmpLen, 1)) {
                printf("deserialize member sample->model_id failed.");
                return -4;
            }
        }
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&sample->size, 4)) {
            sample->size = 0;
            sample->create_ts_ms = 0;
            return 0;
        }
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&sample->create_ts_ms, 4)) {
            sample->create_ts_ms = 0;
            return 0;
        }
        return 0;
    }

    DDS_ULong OpenBatchGetSerializedSampleSize(const OpenBatch* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);

        return currentAlignment - initialAlignment;
    }

    DDS_Long OpenBatchSerializeKey(const OpenBatch* sample, CDRSerializer* cdr)
    {
        if (OpenBatchSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long OpenBatchDeserializeKey(
        OpenBatch* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (OpenBatchDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong OpenBatchGetSerializedKeySize(const OpenBatch* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += OpenBatchGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* OpenBatchLoanSampleBuf(OpenBatch* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void OpenBatchReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long OpenBatchLoanDeserialize(OpenBatch* sampleBuf,
                                      CDRDeserializer* cdr,
                                      DDS_ULong curIndex,
                                      DDS_ULong totalNum,
                                      DDS_Char* base,
                                      DDS_ULong offset,
                                      DDS_ULong space,
                                      DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long OpenBatchOnSiteDeserialize(CDRDeserializer* cdr,
                                        OpenBatch* sample,
                                        DDS_ULong offset,
                                        DDS_ULong totalSize,
                                        DDS_Char* payload,
                                        DDS_ULong payloadLen,
                                        DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean OpenBatchNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong OpenBatchFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T Claim
#define TSeq ClaimSeq
#define TINITIALIZE ClaimInitializeEx
#define TFINALIZE ClaimFinalizeEx
#define TCOPY ClaimCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean ClaimInitialize(Claim* self)
    {
        return ClaimInitializeEx(self, NULL, true);
    }

    void ClaimFinalize(Claim* self)
    {
        ClaimFinalizeEx(self, NULL, true);
    }

    DDS_Boolean ClaimCopy(
        Claim* dst,
        const Claim* src)
    {
        return ClaimCopyEx(dst, src, NULL);
    }

    Claim* ClaimCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        Claim* newSample = (Claim*)ZRMalloc(pool, sizeof(Claim));
        if (newSample == NULL) {
            printf("malloc for Claim failed.");
            return NULL;
        }
        if (!ClaimInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            ClaimDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void ClaimDestroySample(ZRMemPool* pool, Claim* sample)
    {
        if (sample == NULL) return;
        ClaimFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong ClaimGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong ClaimGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long ClaimGetKeyHash(
        const Claim* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = ClaimSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean ClaimHasKey()
    {
        return false;
    }

    TypeCodeHeader* ClaimGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = ClaimGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean ClaimInitializeEx(
        Claim* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->batch_id = NULL;

        self->worker_id = NULL;

        self->queue_length = 0;

        if (allocateMemory) {
        } else {
            if (self->batch_id != NULL) {
                self->batch_id[0] = '\0';
            }
            if (self->worker_id != NULL) {
                self->worker_id[0] = '\0';
            }
        }
        return true;
    }

    void ClaimFinalizeEx(
        Claim* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        if (deletePointers) {
        }
    }

    DDS_Boolean ClaimCopyEx(
        Claim* dst,
        const Claim* src,
        ZRMemPool* pool)
    {
        if (src->batch_id == NULL) {
            ZRDealloc(pool, dst->batch_id);
            dst->batch_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->batch_id);
            DDS_Long dstLen = -1;
            if (dst->batch_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->batch_id) < srcLen) {
                ZRDealloc(pool, dst->batch_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->batch_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->batch_id == NULL) {
                    printf("malloc for batch_id failed.");
                    return false;
                }
            }
            strcpy(dst->batch_id, src->batch_id);
        }
        if (src->worker_id == NULL) {
            ZRDealloc(pool, dst->worker_id);
            dst->worker_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->worker_id);
            DDS_Long dstLen = -1;
            if (dst->worker_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->worker_id) < srcLen) {
                ZRDealloc(pool, dst->worker_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->worker_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->worker_id == NULL) {
                    printf("malloc for worker_id failed.");
                    return false;
                }
            }
            strcpy(dst->worker_id, src->worker_id);
        }
        dst->queue_length = src->queue_length;
        return true;
    }

    void ClaimPrintData(const Claim* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->batch_id != NULL) {
            printf("sample->batch_id(%d): %s\n", strlen(sample->batch_id), sample->batch_id);
        } else {
            printf("sample->batch_id(0): NULL\n");
        }
        printf("\n");

        if (sample->worker_id != NULL) {
            printf("sample->worker_id(%d): %s\n", strlen(sample->worker_id), sample->worker_id);
        } else {
            printf("sample->worker_id(0): NULL\n");
        }
        printf("\n");

        printf("sample->queue_length: %d\n", sample->queue_length);
        printf("\n");

    }

    DDS::TypeCode* ClaimGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::Claim",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct Claim typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member batch_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "batch_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member worker_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "worker_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.getPrimitiveTC(DDS_TK_INT);
        if (memberTc == NULL) {
            printf("Get Member queue_length TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "queue_length",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long ClaimSerialize(const Claim* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->batch_id, sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1)) {
            printf("serialize sample->batch_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->worker_id, sample->worker_id == NULL ? 0 : strlen(sample->worker_id) + 1)) {
            printf("serialize sample->worker_id failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&sample->queue_length, 4)) {
            printf("serialize sample->queue_length failed.");
            return -2;
        }

        return 0;
    }

    DDS_Long ClaimDeserialize(
        Claim* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong batch_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&batch_idTmpLen, 4)) {
            sample->batch_id = NULL;
            sample->worker_id = NULL;
            sample->queue_length = 0;
            return 0;
        }
        if (0 == batch_idTmpLen) {
            ZRDealloc(pool, sample->batch_id);
            sample->batch_id = NULL;
        } else {
            if (sample->batch_id == NULL) {
                sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                if (sample->batch_id == NULL) {
                    printf("malloc for sample->batch_id failed(%d).", batch_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->batch_id) + 1 < batch_idTmpLen) {
                    ZRDealloc(pool, sample->batch_id);
                    sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                    if (sample->batch_id == NULL) {
                        printf("realloc for sample->batch_id failed(%d).", batch_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->batch_id, batch_idTmpLen, 1)) {
                printf("deserialize member sample->batch_id failed.");
                return -4;
            }
        }
        DDS_ULong worker_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&worker_idTmpLen, 4)) {
            sample->worker_id = NULL;
            sample->queue_length = 0;
            return 0;
        }
        if (0 == worker_idTmpLen) {
            ZRDealloc(pool, sample->worker_id);
            sample->worker_id = NULL;
        } else {
            if (sample->worker_id == NULL) {
                sample->worker_id = (DDS_Char*)ZRMalloc(pool, worker_idTmpLen);
                if (sample->worker_id == NULL) {
                    printf("malloc for sample->worker_id failed(%d).", worker_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->worker_id) + 1 < worker_idTmpLen) {
                    ZRDealloc(pool, sample->worker_id);
                    sample->worker_id = (DDS_Char*)ZRMalloc(pool, worker_idTmpLen);
                    if (sample->worker_id == NULL) {
                        printf("realloc for sample->worker_id failed(%d).", worker_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->worker_id, worker_idTmpLen, 1)) {
                printf("deserialize member sample->worker_id failed.");
                return -4;
            }
        }
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&sample->queue_length, 4)) {
            sample->queue_length = 0;
            return 0;
        }
        return 0;
    }

    DDS_ULong ClaimGetSerializedSampleSize(const Claim* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->worker_id == NULL ? 0 : strlen(sample->worker_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);

        return currentAlignment - initialAlignment;
    }

    DDS_Long ClaimSerializeKey(const Claim* sample, CDRSerializer* cdr)
    {
        if (ClaimSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long ClaimDeserializeKey(
        Claim* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (ClaimDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong ClaimGetSerializedKeySize(const Claim* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += ClaimGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* ClaimLoanSampleBuf(Claim* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void ClaimReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long ClaimLoanDeserialize(Claim* sampleBuf,
                                  CDRDeserializer* cdr,
                                  DDS_ULong curIndex,
                                  DDS_ULong totalNum,
                                  DDS_Char* base,
                                  DDS_ULong offset,
                                  DDS_ULong space,
                                  DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long ClaimOnSiteDeserialize(CDRDeserializer* cdr,
                                    Claim* sample,
                                    DDS_ULong offset,
                                    DDS_ULong totalSize,
                                    DDS_Char* payload,
                                    DDS_ULong payloadLen,
                                    DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean ClaimNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong ClaimFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T Grant
#define TSeq GrantSeq
#define TINITIALIZE GrantInitializeEx
#define TFINALIZE GrantFinalizeEx
#define TCOPY GrantCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean GrantInitialize(Grant* self)
    {
        return GrantInitializeEx(self, NULL, true);
    }

    void GrantFinalize(Grant* self)
    {
        GrantFinalizeEx(self, NULL, true);
    }

    DDS_Boolean GrantCopy(
        Grant* dst,
        const Grant* src)
    {
        return GrantCopyEx(dst, src, NULL);
    }

    Grant* GrantCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        Grant* newSample = (Grant*)ZRMalloc(pool, sizeof(Grant));
        if (newSample == NULL) {
            printf("malloc for Grant failed.");
            return NULL;
        }
        if (!GrantInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            GrantDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void GrantDestroySample(ZRMemPool* pool, Grant* sample)
    {
        if (sample == NULL) return;
        GrantFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong GrantGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong GrantGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long GrantGetKeyHash(
        const Grant* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = GrantSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean GrantHasKey()
    {
        return false;
    }

    TypeCodeHeader* GrantGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = GrantGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean GrantInitializeEx(
        Grant* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->batch_id = NULL;

        self->winner_worker_id = NULL;

        if (allocateMemory) {
        } else {
            if (self->batch_id != NULL) {
                self->batch_id[0] = '\0';
            }
            if (self->winner_worker_id != NULL) {
                self->winner_worker_id[0] = '\0';
            }
        }
        return true;
    }

    void GrantFinalizeEx(
        Grant* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        if (deletePointers) {
        }
    }

    DDS_Boolean GrantCopyEx(
        Grant* dst,
        const Grant* src,
        ZRMemPool* pool)
    {
        if (src->batch_id == NULL) {
            ZRDealloc(pool, dst->batch_id);
            dst->batch_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->batch_id);
            DDS_Long dstLen = -1;
            if (dst->batch_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->batch_id) < srcLen) {
                ZRDealloc(pool, dst->batch_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->batch_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->batch_id == NULL) {
                    printf("malloc for batch_id failed.");
                    return false;
                }
            }
            strcpy(dst->batch_id, src->batch_id);
        }
        if (src->winner_worker_id == NULL) {
            ZRDealloc(pool, dst->winner_worker_id);
            dst->winner_worker_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->winner_worker_id);
            DDS_Long dstLen = -1;
            if (dst->winner_worker_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->winner_worker_id) < srcLen) {
                ZRDealloc(pool, dst->winner_worker_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->winner_worker_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->winner_worker_id == NULL) {
                    printf("malloc for winner_worker_id failed.");
                    return false;
                }
            }
            strcpy(dst->winner_worker_id, src->winner_worker_id);
        }
        return true;
    }

    void GrantPrintData(const Grant* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->batch_id != NULL) {
            printf("sample->batch_id(%d): %s\n", strlen(sample->batch_id), sample->batch_id);
        } else {
            printf("sample->batch_id(0): NULL\n");
        }
        printf("\n");

        if (sample->winner_worker_id != NULL) {
            printf("sample->winner_worker_id(%d): %s\n", strlen(sample->winner_worker_id), sample->winner_worker_id);
        } else {
            printf("sample->winner_worker_id(0): NULL\n");
        }
        printf("\n");

    }

    DDS::TypeCode* GrantGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::Grant",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct Grant typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member batch_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "batch_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member winner_worker_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "winner_worker_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long GrantSerialize(const Grant* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->batch_id, sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1)) {
            printf("serialize sample->batch_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->winner_worker_id, sample->winner_worker_id == NULL ? 0 : strlen(sample->winner_worker_id) + 1)) {
            printf("serialize sample->winner_worker_id failed.");
            return -2;
        }

        return 0;
    }

    DDS_Long GrantDeserialize(
        Grant* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong batch_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&batch_idTmpLen, 4)) {
            sample->batch_id = NULL;
            sample->winner_worker_id = NULL;
            return 0;
        }
        if (0 == batch_idTmpLen) {
            ZRDealloc(pool, sample->batch_id);
            sample->batch_id = NULL;
        } else {
            if (sample->batch_id == NULL) {
                sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                if (sample->batch_id == NULL) {
                    printf("malloc for sample->batch_id failed(%d).", batch_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->batch_id) + 1 < batch_idTmpLen) {
                    ZRDealloc(pool, sample->batch_id);
                    sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                    if (sample->batch_id == NULL) {
                        printf("realloc for sample->batch_id failed(%d).", batch_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->batch_id, batch_idTmpLen, 1)) {
                printf("deserialize member sample->batch_id failed.");
                return -4;
            }
        }
        DDS_ULong winner_worker_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&winner_worker_idTmpLen, 4)) {
            sample->winner_worker_id = NULL;
            return 0;
        }
        if (0 == winner_worker_idTmpLen) {
            ZRDealloc(pool, sample->winner_worker_id);
            sample->winner_worker_id = NULL;
        } else {
            if (sample->winner_worker_id == NULL) {
                sample->winner_worker_id = (DDS_Char*)ZRMalloc(pool, winner_worker_idTmpLen);
                if (sample->winner_worker_id == NULL) {
                    printf("malloc for sample->winner_worker_id failed(%d).", winner_worker_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->winner_worker_id) + 1 < winner_worker_idTmpLen) {
                    ZRDealloc(pool, sample->winner_worker_id);
                    sample->winner_worker_id = (DDS_Char*)ZRMalloc(pool, winner_worker_idTmpLen);
                    if (sample->winner_worker_id == NULL) {
                        printf("realloc for sample->winner_worker_id failed(%d).", winner_worker_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->winner_worker_id, winner_worker_idTmpLen, 1)) {
                printf("deserialize member sample->winner_worker_id failed.");
                return -4;
            }
        }
        return 0;
    }

    DDS_ULong GrantGetSerializedSampleSize(const Grant* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->winner_worker_id == NULL ? 0 : strlen(sample->winner_worker_id) + 1, currentAlignment);

        return currentAlignment - initialAlignment;
    }

    DDS_Long GrantSerializeKey(const Grant* sample, CDRSerializer* cdr)
    {
        if (GrantSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long GrantDeserializeKey(
        Grant* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (GrantDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong GrantGetSerializedKeySize(const Grant* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += GrantGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* GrantLoanSampleBuf(Grant* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void GrantReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long GrantLoanDeserialize(Grant* sampleBuf,
                                  CDRDeserializer* cdr,
                                  DDS_ULong curIndex,
                                  DDS_ULong totalNum,
                                  DDS_Char* base,
                                  DDS_ULong offset,
                                  DDS_ULong space,
                                  DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long GrantOnSiteDeserialize(CDRDeserializer* cdr,
                                    Grant* sample,
                                    DDS_ULong offset,
                                    DDS_ULong totalSize,
                                    DDS_Char* payload,
                                    DDS_ULong payloadLen,
                                    DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean GrantNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong GrantFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T TaskList
#define TSeq TaskListSeq
#define TINITIALIZE TaskListInitializeEx
#define TFINALIZE TaskListFinalizeEx
#define TCOPY TaskListCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean TaskListInitialize(TaskList* self)
    {
        return TaskListInitializeEx(self, NULL, true);
    }

    void TaskListFinalize(TaskList* self)
    {
        TaskListFinalizeEx(self, NULL, true);
    }

    DDS_Boolean TaskListCopy(
        TaskList* dst,
        const TaskList* src)
    {
        return TaskListCopyEx(dst, src, NULL);
    }

    TaskList* TaskListCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        TaskList* newSample = (TaskList*)ZRMalloc(pool, sizeof(TaskList));
        if (newSample == NULL) {
            printf("malloc for TaskList failed.");
            return NULL;
        }
        if (!TaskListInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            TaskListDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void TaskListDestroySample(ZRMemPool* pool, TaskList* sample)
    {
        if (sample == NULL) return;
        TaskListFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong TaskListGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong TaskListGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long TaskListGetKeyHash(
        const TaskList* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = TaskListSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean TaskListHasKey()
    {
        return false;
    }

    TypeCodeHeader* TaskListGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = TaskListGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean TaskListInitializeEx(
        TaskList* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->batch_id = NULL;

        self->model_id = NULL;

        self->assigned_worker_id = NULL;

        data_structure::TaskSeq_initialize_ex(&self->tasks, pool, allocateMemory);

        if (allocateMemory) {
        } else {
            if (self->batch_id != NULL) {
                self->batch_id[0] = '\0';
            }
            if (self->model_id != NULL) {
                self->model_id[0] = '\0';
            }
            if (self->assigned_worker_id != NULL) {
                self->assigned_worker_id[0] = '\0';
            }
        }
        return true;
    }

    void TaskListFinalizeEx(
        TaskList* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::TaskSeq_finalize(&self->tasks);
        if (deletePointers) {
        }
    }

    DDS_Boolean TaskListCopyEx(
        TaskList* dst,
        const TaskList* src,
        ZRMemPool* pool)
    {
        if (src->batch_id == NULL) {
            ZRDealloc(pool, dst->batch_id);
            dst->batch_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->batch_id);
            DDS_Long dstLen = -1;
            if (dst->batch_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->batch_id) < srcLen) {
                ZRDealloc(pool, dst->batch_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->batch_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->batch_id == NULL) {
                    printf("malloc for batch_id failed.");
                    return false;
                }
            }
            strcpy(dst->batch_id, src->batch_id);
        }
        if (src->model_id == NULL) {
            ZRDealloc(pool, dst->model_id);
            dst->model_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->model_id);
            DDS_Long dstLen = -1;
            if (dst->model_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->model_id) < srcLen) {
                ZRDealloc(pool, dst->model_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->model_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->model_id == NULL) {
                    printf("malloc for model_id failed.");
                    return false;
                }
            }
            strcpy(dst->model_id, src->model_id);
        }
        if (src->assigned_worker_id == NULL) {
            ZRDealloc(pool, dst->assigned_worker_id);
            dst->assigned_worker_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->assigned_worker_id);
            DDS_Long dstLen = -1;
            if (dst->assigned_worker_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->assigned_worker_id) < srcLen) {
                ZRDealloc(pool, dst->assigned_worker_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->assigned_worker_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->assigned_worker_id == NULL) {
                    printf("malloc for assigned_worker_id failed.");
                    return false;
                }
            }
            strcpy(dst->assigned_worker_id, src->assigned_worker_id);
        }
        if (!data_structure::TaskSeq_copy(&dst->tasks, &src->tasks)) {
            printf("copy member tasks failed.");
            return false;
        }
        return true;
    }

    void TaskListPrintData(const TaskList* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->batch_id != NULL) {
            printf("sample->batch_id(%d): %s\n", strlen(sample->batch_id), sample->batch_id);
        } else {
            printf("sample->batch_id(0): NULL\n");
        }
        printf("\n");

        if (sample->model_id != NULL) {
            printf("sample->model_id(%d): %s\n", strlen(sample->model_id), sample->model_id);
        } else {
            printf("sample->model_id(0): NULL\n");
        }
        printf("\n");

        if (sample->assigned_worker_id != NULL) {
            printf("sample->assigned_worker_id(%d): %s\n", strlen(sample->assigned_worker_id), sample->assigned_worker_id);
        } else {
            printf("sample->assigned_worker_id(0): NULL\n");
        }
        printf("\n");

        DDS_ULong tasksTmpLen = data_structure::TaskSeq_get_length(&sample->tasks);
        printf("sample->tasks: %d\n", tasksTmpLen);
        for (DDS_ULong i = 0; i < tasksTmpLen; ++i) {
            data_structure::TaskPrintData(&*data_structure::TaskSeq_get_reference(&sample->tasks, i));
        }
        printf("\n");

    }

    DDS::TypeCode* TaskListGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::TaskList",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct TaskList typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member batch_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "batch_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member model_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "model_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member assigned_worker_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "assigned_worker_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::TaskGetTypeCode();
        if (memberTc != NULL) {
            memberTc = factory.createSequenceTC(MAX_UINT32_VALUE, memberTc);
        }
        if (memberTc == NULL) {
            printf("Get Member tasks TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            3,
            3,
            "tasks",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long TaskListSerialize(const TaskList* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->batch_id, sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1)) {
            printf("serialize sample->batch_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->model_id, sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1)) {
            printf("serialize sample->model_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->assigned_worker_id, sample->assigned_worker_id == NULL ? 0 : strlen(sample->assigned_worker_id) + 1)) {
            printf("serialize sample->assigned_worker_id failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&(sample->tasks)._length, 4)) {
            printf("serialize length of sample->tasks failed.");
            return -2;
        }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        if (!CDRSerializerNoSerializingMode(cdr)) {
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
            for (DDS_ULong i = 0; i < (sample->tasks)._length; ++i) {
                if (data_structure::TaskSerialize(&*data_structure::TaskSeq_get_reference(&sample->tasks, i), cdr) < 0) {
                    printf("serialize sample->tasks failed.");
                    return -2;
                }
            }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        }
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

        return 0;
    }

    DDS_Long TaskListDeserialize(
        TaskList* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong batch_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&batch_idTmpLen, 4)) {
            sample->batch_id = NULL;
            sample->model_id = NULL;
            sample->assigned_worker_id = NULL;
            data_structure::TaskSeq_initialize_ex(&sample->tasks, pool, true);
            return 0;
        }
        if (0 == batch_idTmpLen) {
            ZRDealloc(pool, sample->batch_id);
            sample->batch_id = NULL;
        } else {
            if (sample->batch_id == NULL) {
                sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                if (sample->batch_id == NULL) {
                    printf("malloc for sample->batch_id failed(%d).", batch_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->batch_id) + 1 < batch_idTmpLen) {
                    ZRDealloc(pool, sample->batch_id);
                    sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                    if (sample->batch_id == NULL) {
                        printf("realloc for sample->batch_id failed(%d).", batch_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->batch_id, batch_idTmpLen, 1)) {
                printf("deserialize member sample->batch_id failed.");
                return -4;
            }
        }
        DDS_ULong model_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&model_idTmpLen, 4)) {
            sample->model_id = NULL;
            sample->assigned_worker_id = NULL;
            data_structure::TaskSeq_initialize_ex(&sample->tasks, pool, true);
            return 0;
        }
        if (0 == model_idTmpLen) {
            ZRDealloc(pool, sample->model_id);
            sample->model_id = NULL;
        } else {
            if (sample->model_id == NULL) {
                sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                if (sample->model_id == NULL) {
                    printf("malloc for sample->model_id failed(%d).", model_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->model_id) + 1 < model_idTmpLen) {
                    ZRDealloc(pool, sample->model_id);
                    sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                    if (sample->model_id == NULL) {
                        printf("realloc for sample->model_id failed(%d).", model_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->model_id, model_idTmpLen, 1)) {
                printf("deserialize member sample->model_id failed.");
                return -4;
            }
        }
        DDS_ULong assigned_worker_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&assigned_worker_idTmpLen, 4)) {
            sample->assigned_worker_id = NULL;
            data_structure::TaskSeq_initialize_ex(&sample->tasks, pool, true);
            return 0;
        }
        if (0 == assigned_worker_idTmpLen) {
            ZRDealloc(pool, sample->assigned_worker_id);
            sample->assigned_worker_id = NULL;
        } else {
            if (sample->assigned_worker_id == NULL) {
                sample->assigned_worker_id = (DDS_Char*)ZRMalloc(pool, assigned_worker_idTmpLen);
                if (sample->assigned_worker_id == NULL) {
                    printf("malloc for sample->assigned_worker_id failed(%d).", assigned_worker_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->assigned_worker_id) + 1 < assigned_worker_idTmpLen) {
                    ZRDealloc(pool, sample->assigned_worker_id);
                    sample->assigned_worker_id = (DDS_Char*)ZRMalloc(pool, assigned_worker_idTmpLen);
                    if (sample->assigned_worker_id == NULL) {
                        printf("realloc for sample->assigned_worker_id failed(%d).", assigned_worker_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->assigned_worker_id, assigned_worker_idTmpLen, 1)) {
                printf("deserialize member sample->assigned_worker_id failed.");
                return -4;
            }
        }
        DDS_ULong tasksTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&tasksTmpLen, 4)) {
            data_structure::TaskSeq_initialize_ex(&sample->tasks, pool, true);
            return 0;
        }
        if (!data_structure::TaskSeq_ensure_length(&sample->tasks, tasksTmpLen, tasksTmpLen)) {
            printf("Set maxiumum member sample->tasks failed.");
            return -3;
        }
        for (DDS_ULong i = 0; i < tasksTmpLen; ++i) {
            if (data_structure::TaskDeserialize(&*data_structure::TaskSeq_get_reference(&sample->tasks, i), cdr, pool) < 0) {
                printf("deserialize sample->tasks failed.");
                return -2;
            }
        }
        return 0;
    }

    DDS_ULong TaskListGetSerializedSampleSize(const TaskList* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->assigned_worker_id == NULL ? 0 : strlen(sample->assigned_worker_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);
        DDS_ULong tasksLen = data_structure::TaskSeq_get_length(&sample->tasks);
        if (tasksLen != 0) {
            for (DDS_ULong i = 0; i < tasksLen; ++i) {
                data_structure::Task* curEle = data_structure::TaskSeq_get_reference(&sample->tasks, i);
                currentAlignment += data_structure::TaskGetSerializedSampleSize(curEle, currentAlignment);
            }
        }

        return currentAlignment - initialAlignment;
    }

    DDS_Long TaskListSerializeKey(const TaskList* sample, CDRSerializer* cdr)
    {
        if (TaskListSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long TaskListDeserializeKey(
        TaskList* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (TaskListDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong TaskListGetSerializedKeySize(const TaskList* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += TaskListGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* TaskListLoanSampleBuf(TaskList* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void TaskListReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long TaskListLoanDeserialize(TaskList* sampleBuf,
                                     CDRDeserializer* cdr,
                                     DDS_ULong curIndex,
                                     DDS_ULong totalNum,
                                     DDS_Char* base,
                                     DDS_ULong offset,
                                     DDS_ULong space,
                                     DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long TaskListOnSiteDeserialize(CDRDeserializer* cdr,
                                       TaskList* sample,
                                       DDS_ULong offset,
                                       DDS_ULong totalSize,
                                       DDS_Char* payload,
                                       DDS_ULong payloadLen,
                                       DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean TaskListNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong TaskListFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T WorkerTaskResult
#define TSeq WorkerTaskResultSeq
#define TINITIALIZE WorkerTaskResultInitializeEx
#define TFINALIZE WorkerTaskResultFinalizeEx
#define TCOPY WorkerTaskResultCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean WorkerTaskResultInitialize(WorkerTaskResult* self)
    {
        return WorkerTaskResultInitializeEx(self, NULL, true);
    }

    void WorkerTaskResultFinalize(WorkerTaskResult* self)
    {
        WorkerTaskResultFinalizeEx(self, NULL, true);
    }

    DDS_Boolean WorkerTaskResultCopy(
        WorkerTaskResult* dst,
        const WorkerTaskResult* src)
    {
        return WorkerTaskResultCopyEx(dst, src, NULL);
    }

    WorkerTaskResult* WorkerTaskResultCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        WorkerTaskResult* newSample = (WorkerTaskResult*)ZRMalloc(pool, sizeof(WorkerTaskResult));
        if (newSample == NULL) {
            printf("malloc for WorkerTaskResult failed.");
            return NULL;
        }
        if (!WorkerTaskResultInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            WorkerTaskResultDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void WorkerTaskResultDestroySample(ZRMemPool* pool, WorkerTaskResult* sample)
    {
        if (sample == NULL) return;
        WorkerTaskResultFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong WorkerTaskResultGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong WorkerTaskResultGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long WorkerTaskResultGetKeyHash(
        const WorkerTaskResult* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = WorkerTaskResultSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean WorkerTaskResultHasKey()
    {
        return false;
    }

    TypeCodeHeader* WorkerTaskResultGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = WorkerTaskResultGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean WorkerTaskResultInitializeEx(
        WorkerTaskResult* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->request_id = NULL;

        self->task_id = NULL;

        self->client_id = NULL;

        self->status = NULL;

        if (!data_structure::BytesInitializeEx(&self->output_blob, pool, allocateMemory)) {
            printf("Initialize member self->output_blob failed.");
            return false;
        }

        DDS_StringSeq_initialize_ex(&self->texts, pool, allocateMemory);

        if (allocateMemory) {
        } else {
            if (self->request_id != NULL) {
                self->request_id[0] = '\0';
            }
            if (self->task_id != NULL) {
                self->task_id[0] = '\0';
            }
            if (self->client_id != NULL) {
                self->client_id[0] = '\0';
            }
            if (self->status != NULL) {
                self->status[0] = '\0';
            }
        }
        return true;
    }

    void WorkerTaskResultFinalizeEx(
        WorkerTaskResult* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::BytesFinalizeEx(&self->output_blob, pool, deletePointers);
        DDS_StringSeq_finalize(&self->texts);
        if (deletePointers) {
        }
    }

    DDS_Boolean WorkerTaskResultCopyEx(
        WorkerTaskResult* dst,
        const WorkerTaskResult* src,
        ZRMemPool* pool)
    {
        if (src->request_id == NULL) {
            ZRDealloc(pool, dst->request_id);
            dst->request_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->request_id);
            DDS_Long dstLen = -1;
            if (dst->request_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->request_id) < srcLen) {
                ZRDealloc(pool, dst->request_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->request_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->request_id == NULL) {
                    printf("malloc for request_id failed.");
                    return false;
                }
            }
            strcpy(dst->request_id, src->request_id);
        }
        if (src->task_id == NULL) {
            ZRDealloc(pool, dst->task_id);
            dst->task_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->task_id);
            DDS_Long dstLen = -1;
            if (dst->task_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->task_id) < srcLen) {
                ZRDealloc(pool, dst->task_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->task_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->task_id == NULL) {
                    printf("malloc for task_id failed.");
                    return false;
                }
            }
            strcpy(dst->task_id, src->task_id);
        }
        if (src->client_id == NULL) {
            ZRDealloc(pool, dst->client_id);
            dst->client_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->client_id);
            DDS_Long dstLen = -1;
            if (dst->client_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->client_id) < srcLen) {
                ZRDealloc(pool, dst->client_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->client_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->client_id == NULL) {
                    printf("malloc for client_id failed.");
                    return false;
                }
            }
            strcpy(dst->client_id, src->client_id);
        }
        if (src->status == NULL) {
            ZRDealloc(pool, dst->status);
            dst->status = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->status);
            DDS_Long dstLen = -1;
            if (dst->status == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->status) < srcLen) {
                ZRDealloc(pool, dst->status);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->status = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->status == NULL) {
                    printf("malloc for status failed.");
                    return false;
                }
            }
            strcpy(dst->status, src->status);
        }
        if (!data_structure::BytesCopyEx(&dst->output_blob, &src->output_blob, pool)) {
            printf("copy member output_blob failed.");
            return false;
        }
        if (!DDS_StringSeq_copy(&dst->texts, &src->texts)) {
            printf("copy member texts failed.");
            return false;
        }
        return true;
    }

    void WorkerTaskResultPrintData(const WorkerTaskResult* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->request_id != NULL) {
            printf("sample->request_id(%d): %s\n", strlen(sample->request_id), sample->request_id);
        } else {
            printf("sample->request_id(0): NULL\n");
        }
        printf("\n");

        if (sample->task_id != NULL) {
            printf("sample->task_id(%d): %s\n", strlen(sample->task_id), sample->task_id);
        } else {
            printf("sample->task_id(0): NULL\n");
        }
        printf("\n");

        if (sample->client_id != NULL) {
            printf("sample->client_id(%d): %s\n", strlen(sample->client_id), sample->client_id);
        } else {
            printf("sample->client_id(0): NULL\n");
        }
        printf("\n");

        if (sample->status != NULL) {
            printf("sample->status(%d): %s\n", strlen(sample->status), sample->status);
        } else {
            printf("sample->status(0): NULL\n");
        }
        printf("\n");

        data_structure::BytesPrintData(&sample->output_blob);
        printf("\n");

        DDS_ULong textsTmpLen = DDS_StringSeq_get_length(&sample->texts);
        printf("sample->texts: %d\n", textsTmpLen);
        for (DDS_ULong i = 0; i < textsTmpLen; ++i) {
            if (*DDS_StringSeq_get_reference(&sample->texts, i) != NULL) {
                printf("sample->texts[%u](%d): %s\n", i, strlen(*DDS_StringSeq_get_reference(&sample->texts, i)), *DDS_StringSeq_get_reference(&sample->texts, i));
            } else {
                printf("sample->texts[%u](0): NULL\n", i);
            }
        }
        printf("\n");

    }

    DDS::TypeCode* WorkerTaskResultGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::WorkerTaskResult",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct WorkerTaskResult typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member request_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "request_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member task_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "task_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member client_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "client_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member status TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            3,
            3,
            "status",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::BytesGetTypeCode();
        if (memberTc == NULL) {
            printf("Get Member output_blob TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            4,
            4,
            "output_blob",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc != NULL) {
            memberTc = factory.createSequenceTC(MAX_UINT32_VALUE, memberTc);
        }
        if (memberTc == NULL) {
            printf("Get Member texts TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            5,
            5,
            "texts",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long WorkerTaskResultSerialize(const WorkerTaskResult* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->request_id, sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1)) {
            printf("serialize sample->request_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->task_id, sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1)) {
            printf("serialize sample->task_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->client_id, sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1)) {
            printf("serialize sample->client_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->status, sample->status == NULL ? 0 : strlen(sample->status) + 1)) {
            printf("serialize sample->status failed.");
            return -2;
        }

        if (data_structure::BytesSerialize(&sample->output_blob, cdr) < 0) {
            printf("serialize sample->output_blob failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&(sample->texts)._length, 4)) {
            printf("serialize length of sample->texts failed.");
            return -2;
        }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        if (!CDRSerializerNoSerializingMode(cdr)) {
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
            for (DDS_ULong i = 0; i < (sample->texts)._length; ++i) {
                if (!CDRSerializerPutString(cdr, (DDS_Char*)*DDS_StringSeq_get_reference(&sample->texts, i), *DDS_StringSeq_get_reference(&sample->texts, i) == NULL ? 0 : strlen(*DDS_StringSeq_get_reference(&sample->texts, i)) + 1)) {
                    printf("serialize sample->texts failed.");
                    return -2;
                }
            }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        }
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

        return 0;
    }

    DDS_Long WorkerTaskResultDeserialize(
        WorkerTaskResult* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong request_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&request_idTmpLen, 4)) {
            sample->request_id = NULL;
            sample->task_id = NULL;
            sample->client_id = NULL;
            sample->status = NULL;
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            DDS_StringSeq_initialize_ex(&sample->texts, pool, true);
            return 0;
        }
        if (0 == request_idTmpLen) {
            ZRDealloc(pool, sample->request_id);
            sample->request_id = NULL;
        } else {
            if (sample->request_id == NULL) {
                sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                if (sample->request_id == NULL) {
                    printf("malloc for sample->request_id failed(%d).", request_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->request_id) + 1 < request_idTmpLen) {
                    ZRDealloc(pool, sample->request_id);
                    sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                    if (sample->request_id == NULL) {
                        printf("realloc for sample->request_id failed(%d).", request_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->request_id, request_idTmpLen, 1)) {
                printf("deserialize member sample->request_id failed.");
                return -4;
            }
        }
        DDS_ULong task_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&task_idTmpLen, 4)) {
            sample->task_id = NULL;
            sample->client_id = NULL;
            sample->status = NULL;
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            DDS_StringSeq_initialize_ex(&sample->texts, pool, true);
            return 0;
        }
        if (0 == task_idTmpLen) {
            ZRDealloc(pool, sample->task_id);
            sample->task_id = NULL;
        } else {
            if (sample->task_id == NULL) {
                sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                if (sample->task_id == NULL) {
                    printf("malloc for sample->task_id failed(%d).", task_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->task_id) + 1 < task_idTmpLen) {
                    ZRDealloc(pool, sample->task_id);
                    sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                    if (sample->task_id == NULL) {
                        printf("realloc for sample->task_id failed(%d).", task_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->task_id, task_idTmpLen, 1)) {
                printf("deserialize member sample->task_id failed.");
                return -4;
            }
        }
        DDS_ULong client_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&client_idTmpLen, 4)) {
            sample->client_id = NULL;
            sample->status = NULL;
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            DDS_StringSeq_initialize_ex(&sample->texts, pool, true);
            return 0;
        }
        if (0 == client_idTmpLen) {
            ZRDealloc(pool, sample->client_id);
            sample->client_id = NULL;
        } else {
            if (sample->client_id == NULL) {
                sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                if (sample->client_id == NULL) {
                    printf("malloc for sample->client_id failed(%d).", client_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->client_id) + 1 < client_idTmpLen) {
                    ZRDealloc(pool, sample->client_id);
                    sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                    if (sample->client_id == NULL) {
                        printf("realloc for sample->client_id failed(%d).", client_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->client_id, client_idTmpLen, 1)) {
                printf("deserialize member sample->client_id failed.");
                return -4;
            }
        }
        DDS_ULong statusTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&statusTmpLen, 4)) {
            sample->status = NULL;
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            DDS_StringSeq_initialize_ex(&sample->texts, pool, true);
            return 0;
        }
        if (0 == statusTmpLen) {
            ZRDealloc(pool, sample->status);
            sample->status = NULL;
        } else {
            if (sample->status == NULL) {
                sample->status = (DDS_Char*)ZRMalloc(pool, statusTmpLen);
                if (sample->status == NULL) {
                    printf("malloc for sample->status failed(%d).", statusTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->status) + 1 < statusTmpLen) {
                    ZRDealloc(pool, sample->status);
                    sample->status = (DDS_Char*)ZRMalloc(pool, statusTmpLen);
                    if (sample->status == NULL) {
                        printf("realloc for sample->status failed(%d).", statusTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->status, statusTmpLen, 1)) {
                printf("deserialize member sample->status failed.");
                return -4;
            }
        }
        if (data_structure::BytesDeserialize(&sample->output_blob, cdr, pool) < 0) {
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            DDS_StringSeq_initialize_ex(&sample->texts, pool, true);
            return 0;
        }
        DDS_ULong textsTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&textsTmpLen, 4)) {
            DDS_StringSeq_initialize_ex(&sample->texts, pool, true);
            return 0;
        }
        if (!DDS_StringSeq_ensure_length(&sample->texts, textsTmpLen, textsTmpLen)) {
            printf("Set maxiumum member sample->texts failed.");
            return -3;
        }
        for (DDS_ULong i = 0; i < (sample->texts).length(); ++i) {
            DDS_ULong tmpLength = 0;
            if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&tmpLength, 4)) {
                printf("deserializer string length failed.");
                return -3;
            }
            DDS_Octet* tmpValue = (DDS_Octet*)ZRMalloc(pool, tmpLength);
            if (!CDRDeserializerGetUntypeArray(cdr, tmpValue, tmpLength, 1)) {
                printf("deserializer string failed.");
                return -3;
            }
            if (!DDS_StringSeq_set(&sample->texts, i, (const DDS_Char**)&tmpValue)) {
                printf("deserializer string failed.");
                return -3;
            }
            ZRDealloc(pool, tmpValue);
        }

        return 0;
    }

    DDS_ULong WorkerTaskResultGetSerializedSampleSize(const WorkerTaskResult* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->status == NULL ? 0 : strlen(sample->status) + 1, currentAlignment);

        currentAlignment += data_structure::BytesGetSerializedSampleSize(&sample->output_blob, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);
        DDS_ULong textsLen = DDS_StringSeq_get_length(&sample->texts);
        if (textsLen != 0) {
            for (DDS_ULong i = 0; i < textsLen; ++i) {
                currentAlignment += CDRSerializerGetStringSize(strlen(sample->texts[i]) + 1, currentAlignment);
            }
        }

        return currentAlignment - initialAlignment;
    }

    DDS_Long WorkerTaskResultSerializeKey(const WorkerTaskResult* sample, CDRSerializer* cdr)
    {
        if (WorkerTaskResultSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long WorkerTaskResultDeserializeKey(
        WorkerTaskResult* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (WorkerTaskResultDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong WorkerTaskResultGetSerializedKeySize(const WorkerTaskResult* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += WorkerTaskResultGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* WorkerTaskResultLoanSampleBuf(WorkerTaskResult* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void WorkerTaskResultReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long WorkerTaskResultLoanDeserialize(WorkerTaskResult* sampleBuf,
                                             CDRDeserializer* cdr,
                                             DDS_ULong curIndex,
                                             DDS_ULong totalNum,
                                             DDS_Char* base,
                                             DDS_ULong offset,
                                             DDS_ULong space,
                                             DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long WorkerTaskResultOnSiteDeserialize(CDRDeserializer* cdr,
                                               WorkerTaskResult* sample,
                                               DDS_ULong offset,
                                               DDS_ULong totalSize,
                                               DDS_Char* payload,
                                               DDS_ULong payloadLen,
                                               DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean WorkerTaskResultNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong WorkerTaskResultFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T WorkerResult
#define TSeq WorkerResultSeq
#define TINITIALIZE WorkerResultInitializeEx
#define TFINALIZE WorkerResultFinalizeEx
#define TCOPY WorkerResultCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean WorkerResultInitialize(WorkerResult* self)
    {
        return WorkerResultInitializeEx(self, NULL, true);
    }

    void WorkerResultFinalize(WorkerResult* self)
    {
        WorkerResultFinalizeEx(self, NULL, true);
    }

    DDS_Boolean WorkerResultCopy(
        WorkerResult* dst,
        const WorkerResult* src)
    {
        return WorkerResultCopyEx(dst, src, NULL);
    }

    WorkerResult* WorkerResultCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        WorkerResult* newSample = (WorkerResult*)ZRMalloc(pool, sizeof(WorkerResult));
        if (newSample == NULL) {
            printf("malloc for WorkerResult failed.");
            return NULL;
        }
        if (!WorkerResultInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            WorkerResultDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void WorkerResultDestroySample(ZRMemPool* pool, WorkerResult* sample)
    {
        if (sample == NULL) return;
        WorkerResultFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong WorkerResultGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong WorkerResultGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long WorkerResultGetKeyHash(
        const WorkerResult* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = WorkerResultSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean WorkerResultHasKey()
    {
        return false;
    }

    TypeCodeHeader* WorkerResultGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = WorkerResultGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean WorkerResultInitializeEx(
        WorkerResult* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->batch_id = NULL;

        self->model_id = NULL;

        self->worker_id = NULL;

        data_structure::WorkerTaskResultSeq_initialize_ex(&self->results, pool, allocateMemory);

        if (allocateMemory) {
        } else {
            if (self->batch_id != NULL) {
                self->batch_id[0] = '\0';
            }
            if (self->model_id != NULL) {
                self->model_id[0] = '\0';
            }
            if (self->worker_id != NULL) {
                self->worker_id[0] = '\0';
            }
        }
        return true;
    }

    void WorkerResultFinalizeEx(
        WorkerResult* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::WorkerTaskResultSeq_finalize(&self->results);
        if (deletePointers) {
        }
    }

    DDS_Boolean WorkerResultCopyEx(
        WorkerResult* dst,
        const WorkerResult* src,
        ZRMemPool* pool)
    {
        if (src->batch_id == NULL) {
            ZRDealloc(pool, dst->batch_id);
            dst->batch_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->batch_id);
            DDS_Long dstLen = -1;
            if (dst->batch_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->batch_id) < srcLen) {
                ZRDealloc(pool, dst->batch_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->batch_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->batch_id == NULL) {
                    printf("malloc for batch_id failed.");
                    return false;
                }
            }
            strcpy(dst->batch_id, src->batch_id);
        }
        if (src->model_id == NULL) {
            ZRDealloc(pool, dst->model_id);
            dst->model_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->model_id);
            DDS_Long dstLen = -1;
            if (dst->model_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->model_id) < srcLen) {
                ZRDealloc(pool, dst->model_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->model_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->model_id == NULL) {
                    printf("malloc for model_id failed.");
                    return false;
                }
            }
            strcpy(dst->model_id, src->model_id);
        }
        if (src->worker_id == NULL) {
            ZRDealloc(pool, dst->worker_id);
            dst->worker_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->worker_id);
            DDS_Long dstLen = -1;
            if (dst->worker_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->worker_id) < srcLen) {
                ZRDealloc(pool, dst->worker_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->worker_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->worker_id == NULL) {
                    printf("malloc for worker_id failed.");
                    return false;
                }
            }
            strcpy(dst->worker_id, src->worker_id);
        }
        if (!data_structure::WorkerTaskResultSeq_copy(&dst->results, &src->results)) {
            printf("copy member results failed.");
            return false;
        }
        return true;
    }

    void WorkerResultPrintData(const WorkerResult* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->batch_id != NULL) {
            printf("sample->batch_id(%d): %s\n", strlen(sample->batch_id), sample->batch_id);
        } else {
            printf("sample->batch_id(0): NULL\n");
        }
        printf("\n");

        if (sample->model_id != NULL) {
            printf("sample->model_id(%d): %s\n", strlen(sample->model_id), sample->model_id);
        } else {
            printf("sample->model_id(0): NULL\n");
        }
        printf("\n");

        if (sample->worker_id != NULL) {
            printf("sample->worker_id(%d): %s\n", strlen(sample->worker_id), sample->worker_id);
        } else {
            printf("sample->worker_id(0): NULL\n");
        }
        printf("\n");

        DDS_ULong resultsTmpLen = data_structure::WorkerTaskResultSeq_get_length(&sample->results);
        printf("sample->results: %d\n", resultsTmpLen);
        for (DDS_ULong i = 0; i < resultsTmpLen; ++i) {
            data_structure::WorkerTaskResultPrintData(&*data_structure::WorkerTaskResultSeq_get_reference(&sample->results, i));
        }
        printf("\n");

    }

    DDS::TypeCode* WorkerResultGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::WorkerResult",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct WorkerResult typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member batch_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "batch_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member model_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "model_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member worker_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "worker_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::WorkerTaskResultGetTypeCode();
        if (memberTc != NULL) {
            memberTc = factory.createSequenceTC(MAX_UINT32_VALUE, memberTc);
        }
        if (memberTc == NULL) {
            printf("Get Member results TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            3,
            3,
            "results",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long WorkerResultSerialize(const WorkerResult* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->batch_id, sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1)) {
            printf("serialize sample->batch_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->model_id, sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1)) {
            printf("serialize sample->model_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->worker_id, sample->worker_id == NULL ? 0 : strlen(sample->worker_id) + 1)) {
            printf("serialize sample->worker_id failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&(sample->results)._length, 4)) {
            printf("serialize length of sample->results failed.");
            return -2;
        }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        if (!CDRSerializerNoSerializingMode(cdr)) {
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
            for (DDS_ULong i = 0; i < (sample->results)._length; ++i) {
                if (data_structure::WorkerTaskResultSerialize(&*data_structure::WorkerTaskResultSeq_get_reference(&sample->results, i), cdr) < 0) {
                    printf("serialize sample->results failed.");
                    return -2;
                }
            }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        }
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

        return 0;
    }

    DDS_Long WorkerResultDeserialize(
        WorkerResult* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong batch_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&batch_idTmpLen, 4)) {
            sample->batch_id = NULL;
            sample->model_id = NULL;
            sample->worker_id = NULL;
            data_structure::WorkerTaskResultSeq_initialize_ex(&sample->results, pool, true);
            return 0;
        }
        if (0 == batch_idTmpLen) {
            ZRDealloc(pool, sample->batch_id);
            sample->batch_id = NULL;
        } else {
            if (sample->batch_id == NULL) {
                sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                if (sample->batch_id == NULL) {
                    printf("malloc for sample->batch_id failed(%d).", batch_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->batch_id) + 1 < batch_idTmpLen) {
                    ZRDealloc(pool, sample->batch_id);
                    sample->batch_id = (DDS_Char*)ZRMalloc(pool, batch_idTmpLen);
                    if (sample->batch_id == NULL) {
                        printf("realloc for sample->batch_id failed(%d).", batch_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->batch_id, batch_idTmpLen, 1)) {
                printf("deserialize member sample->batch_id failed.");
                return -4;
            }
        }
        DDS_ULong model_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&model_idTmpLen, 4)) {
            sample->model_id = NULL;
            sample->worker_id = NULL;
            data_structure::WorkerTaskResultSeq_initialize_ex(&sample->results, pool, true);
            return 0;
        }
        if (0 == model_idTmpLen) {
            ZRDealloc(pool, sample->model_id);
            sample->model_id = NULL;
        } else {
            if (sample->model_id == NULL) {
                sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                if (sample->model_id == NULL) {
                    printf("malloc for sample->model_id failed(%d).", model_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->model_id) + 1 < model_idTmpLen) {
                    ZRDealloc(pool, sample->model_id);
                    sample->model_id = (DDS_Char*)ZRMalloc(pool, model_idTmpLen);
                    if (sample->model_id == NULL) {
                        printf("realloc for sample->model_id failed(%d).", model_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->model_id, model_idTmpLen, 1)) {
                printf("deserialize member sample->model_id failed.");
                return -4;
            }
        }
        DDS_ULong worker_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&worker_idTmpLen, 4)) {
            sample->worker_id = NULL;
            data_structure::WorkerTaskResultSeq_initialize_ex(&sample->results, pool, true);
            return 0;
        }
        if (0 == worker_idTmpLen) {
            ZRDealloc(pool, sample->worker_id);
            sample->worker_id = NULL;
        } else {
            if (sample->worker_id == NULL) {
                sample->worker_id = (DDS_Char*)ZRMalloc(pool, worker_idTmpLen);
                if (sample->worker_id == NULL) {
                    printf("malloc for sample->worker_id failed(%d).", worker_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->worker_id) + 1 < worker_idTmpLen) {
                    ZRDealloc(pool, sample->worker_id);
                    sample->worker_id = (DDS_Char*)ZRMalloc(pool, worker_idTmpLen);
                    if (sample->worker_id == NULL) {
                        printf("realloc for sample->worker_id failed(%d).", worker_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->worker_id, worker_idTmpLen, 1)) {
                printf("deserialize member sample->worker_id failed.");
                return -4;
            }
        }
        DDS_ULong resultsTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&resultsTmpLen, 4)) {
            data_structure::WorkerTaskResultSeq_initialize_ex(&sample->results, pool, true);
            return 0;
        }
        if (!data_structure::WorkerTaskResultSeq_ensure_length(&sample->results, resultsTmpLen, resultsTmpLen)) {
            printf("Set maxiumum member sample->results failed.");
            return -3;
        }
        for (DDS_ULong i = 0; i < resultsTmpLen; ++i) {
            if (data_structure::WorkerTaskResultDeserialize(&*data_structure::WorkerTaskResultSeq_get_reference(&sample->results, i), cdr, pool) < 0) {
                printf("deserialize sample->results failed.");
                return -2;
            }
        }
        return 0;
    }

    DDS_ULong WorkerResultGetSerializedSampleSize(const WorkerResult* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->batch_id == NULL ? 0 : strlen(sample->batch_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->model_id == NULL ? 0 : strlen(sample->model_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->worker_id == NULL ? 0 : strlen(sample->worker_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);
        DDS_ULong resultsLen = data_structure::WorkerTaskResultSeq_get_length(&sample->results);
        if (resultsLen != 0) {
            for (DDS_ULong i = 0; i < resultsLen; ++i) {
                data_structure::WorkerTaskResult* curEle = data_structure::WorkerTaskResultSeq_get_reference(&sample->results, i);
                currentAlignment += data_structure::WorkerTaskResultGetSerializedSampleSize(curEle, currentAlignment);
            }
        }

        return currentAlignment - initialAlignment;
    }

    DDS_Long WorkerResultSerializeKey(const WorkerResult* sample, CDRSerializer* cdr)
    {
        if (WorkerResultSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long WorkerResultDeserializeKey(
        WorkerResult* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (WorkerResultDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong WorkerResultGetSerializedKeySize(const WorkerResult* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += WorkerResultGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* WorkerResultLoanSampleBuf(WorkerResult* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void WorkerResultReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long WorkerResultLoanDeserialize(WorkerResult* sampleBuf,
                                         CDRDeserializer* cdr,
                                         DDS_ULong curIndex,
                                         DDS_ULong totalNum,
                                         DDS_Char* base,
                                         DDS_ULong offset,
                                         DDS_ULong space,
                                         DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long WorkerResultOnSiteDeserialize(CDRDeserializer* cdr,
                                           WorkerResult* sample,
                                           DDS_ULong offset,
                                           DDS_ULong totalSize,
                                           DDS_Char* payload,
                                           DDS_ULong payloadLen,
                                           DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean WorkerResultNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong WorkerResultFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T ResultItem
#define TSeq ResultItemSeq
#define TINITIALIZE ResultItemInitializeEx
#define TFINALIZE ResultItemFinalizeEx
#define TCOPY ResultItemCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean ResultItemInitialize(ResultItem* self)
    {
        return ResultItemInitializeEx(self, NULL, true);
    }

    void ResultItemFinalize(ResultItem* self)
    {
        ResultItemFinalizeEx(self, NULL, true);
    }

    DDS_Boolean ResultItemCopy(
        ResultItem* dst,
        const ResultItem* src)
    {
        return ResultItemCopyEx(dst, src, NULL);
    }

    ResultItem* ResultItemCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        ResultItem* newSample = (ResultItem*)ZRMalloc(pool, sizeof(ResultItem));
        if (newSample == NULL) {
            printf("malloc for ResultItem failed.");
            return NULL;
        }
        if (!ResultItemInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            ResultItemDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void ResultItemDestroySample(ZRMemPool* pool, ResultItem* sample)
    {
        if (sample == NULL) return;
        ResultItemFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong ResultItemGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong ResultItemGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long ResultItemGetKeyHash(
        const ResultItem* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = ResultItemSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean ResultItemHasKey()
    {
        return false;
    }

    TypeCodeHeader* ResultItemGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = ResultItemGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean ResultItemInitializeEx(
        ResultItem* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->task_id = NULL;

        self->status = NULL;

        if (!data_structure::BytesInitializeEx(&self->output_blob, pool, allocateMemory)) {
            printf("Initialize member self->output_blob failed.");
            return false;
        }

        if (allocateMemory) {
        } else {
            if (self->task_id != NULL) {
                self->task_id[0] = '\0';
            }
            if (self->status != NULL) {
                self->status[0] = '\0';
            }
        }
        return true;
    }

    void ResultItemFinalizeEx(
        ResultItem* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::BytesFinalizeEx(&self->output_blob, pool, deletePointers);
        if (deletePointers) {
        }
    }

    DDS_Boolean ResultItemCopyEx(
        ResultItem* dst,
        const ResultItem* src,
        ZRMemPool* pool)
    {
        if (src->task_id == NULL) {
            ZRDealloc(pool, dst->task_id);
            dst->task_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->task_id);
            DDS_Long dstLen = -1;
            if (dst->task_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->task_id) < srcLen) {
                ZRDealloc(pool, dst->task_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->task_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->task_id == NULL) {
                    printf("malloc for task_id failed.");
                    return false;
                }
            }
            strcpy(dst->task_id, src->task_id);
        }
        if (src->status == NULL) {
            ZRDealloc(pool, dst->status);
            dst->status = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->status);
            DDS_Long dstLen = -1;
            if (dst->status == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->status) < srcLen) {
                ZRDealloc(pool, dst->status);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->status = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->status == NULL) {
                    printf("malloc for status failed.");
                    return false;
                }
            }
            strcpy(dst->status, src->status);
        }
        if (!data_structure::BytesCopyEx(&dst->output_blob, &src->output_blob, pool)) {
            printf("copy member output_blob failed.");
            return false;
        }
        return true;
    }

    void ResultItemPrintData(const ResultItem* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->task_id != NULL) {
            printf("sample->task_id(%d): %s\n", strlen(sample->task_id), sample->task_id);
        } else {
            printf("sample->task_id(0): NULL\n");
        }
        printf("\n");

        if (sample->status != NULL) {
            printf("sample->status(%d): %s\n", strlen(sample->status), sample->status);
        } else {
            printf("sample->status(0): NULL\n");
        }
        printf("\n");

        data_structure::BytesPrintData(&sample->output_blob);
        printf("\n");

    }

    DDS::TypeCode* ResultItemGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::ResultItem",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct ResultItem typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member task_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "task_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member status TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "status",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::BytesGetTypeCode();
        if (memberTc == NULL) {
            printf("Get Member output_blob TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "output_blob",
            memberTc,
            false,
            false);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long ResultItemSerialize(const ResultItem* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->task_id, sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1)) {
            printf("serialize sample->task_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->status, sample->status == NULL ? 0 : strlen(sample->status) + 1)) {
            printf("serialize sample->status failed.");
            return -2;
        }

        if (data_structure::BytesSerialize(&sample->output_blob, cdr) < 0) {
            printf("serialize sample->output_blob failed.");
            return -2;
        }

        return 0;
    }

    DDS_Long ResultItemDeserialize(
        ResultItem* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong task_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&task_idTmpLen, 4)) {
            sample->task_id = NULL;
            sample->status = NULL;
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            return 0;
        }
        if (0 == task_idTmpLen) {
            ZRDealloc(pool, sample->task_id);
            sample->task_id = NULL;
        } else {
            if (sample->task_id == NULL) {
                sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                if (sample->task_id == NULL) {
                    printf("malloc for sample->task_id failed(%d).", task_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->task_id) + 1 < task_idTmpLen) {
                    ZRDealloc(pool, sample->task_id);
                    sample->task_id = (DDS_Char*)ZRMalloc(pool, task_idTmpLen);
                    if (sample->task_id == NULL) {
                        printf("realloc for sample->task_id failed(%d).", task_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->task_id, task_idTmpLen, 1)) {
                printf("deserialize member sample->task_id failed.");
                return -4;
            }
        }
        DDS_ULong statusTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&statusTmpLen, 4)) {
            sample->status = NULL;
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            return 0;
        }
        if (0 == statusTmpLen) {
            ZRDealloc(pool, sample->status);
            sample->status = NULL;
        } else {
            if (sample->status == NULL) {
                sample->status = (DDS_Char*)ZRMalloc(pool, statusTmpLen);
                if (sample->status == NULL) {
                    printf("malloc for sample->status failed(%d).", statusTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->status) + 1 < statusTmpLen) {
                    ZRDealloc(pool, sample->status);
                    sample->status = (DDS_Char*)ZRMalloc(pool, statusTmpLen);
                    if (sample->status == NULL) {
                        printf("realloc for sample->status failed(%d).", statusTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->status, statusTmpLen, 1)) {
                printf("deserialize member sample->status failed.");
                return -4;
            }
        }
        if (data_structure::BytesDeserialize(&sample->output_blob, cdr, pool) < 0) {
            if (!data_structure::BytesInitializeEx(&sample->output_blob, pool, true)) {
                printf("Initialize member sample->output_blob failed.");
                return -2;
            }
            return 0;
        }
        return 0;
    }

    DDS_ULong ResultItemGetSerializedSampleSize(const ResultItem* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->task_id == NULL ? 0 : strlen(sample->task_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->status == NULL ? 0 : strlen(sample->status) + 1, currentAlignment);

        currentAlignment += data_structure::BytesGetSerializedSampleSize(&sample->output_blob, currentAlignment);

        return currentAlignment - initialAlignment;
    }

    DDS_Long ResultItemSerializeKey(const ResultItem* sample, CDRSerializer* cdr)
    {
        if (ResultItemSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long ResultItemDeserializeKey(
        ResultItem* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (ResultItemDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong ResultItemGetSerializedKeySize(const ResultItem* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += ResultItemGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* ResultItemLoanSampleBuf(ResultItem* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void ResultItemReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long ResultItemLoanDeserialize(ResultItem* sampleBuf,
                                       CDRDeserializer* cdr,
                                       DDS_ULong curIndex,
                                       DDS_ULong totalNum,
                                       DDS_Char* base,
                                       DDS_ULong offset,
                                       DDS_ULong space,
                                       DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long ResultItemOnSiteDeserialize(CDRDeserializer* cdr,
                                         ResultItem* sample,
                                         DDS_ULong offset,
                                         DDS_ULong totalSize,
                                         DDS_Char* payload,
                                         DDS_ULong payloadLen,
                                         DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean ResultItemNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong ResultItemFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
#define T ResultUpdate
#define TSeq ResultUpdateSeq
#define TINITIALIZE ResultUpdateInitializeEx
#define TFINALIZE ResultUpdateFinalizeEx
#define TCOPY ResultUpdateCopyEx

#include "ZRSequence.cpp"
#include "ZRCPlusPlusSequence.cpp"

#undef TCOPY
#undef TFINALIZE
#undef TINITIALIZE
#undef TSeq
#undef T

    DDS_Boolean ResultUpdateInitialize(ResultUpdate* self)
    {
        return ResultUpdateInitializeEx(self, NULL, true);
    }

    void ResultUpdateFinalize(ResultUpdate* self)
    {
        ResultUpdateFinalizeEx(self, NULL, true);
    }

    DDS_Boolean ResultUpdateCopy(
        ResultUpdate* dst,
        const ResultUpdate* src)
    {
        return ResultUpdateCopyEx(dst, src, NULL);
    }

    ResultUpdate* ResultUpdateCreateSample(
        ZRMemPool* pool,
        DDS_Boolean allocMutable)
    {
        ResultUpdate* newSample = (ResultUpdate*)ZRMalloc(pool, sizeof(ResultUpdate));
        if (newSample == NULL) {
            printf("malloc for ResultUpdate failed.");
            return NULL;
        }
        if (!ResultUpdateInitializeEx(newSample, pool, allocMutable)) {
            printf("initial Sample failed.");
            ResultUpdateDestroySample(pool, newSample);
            return NULL;
        }
        return newSample;
    }

    void ResultUpdateDestroySample(ZRMemPool* pool, ResultUpdate* sample)
    {
        if (sample == NULL) return;
        ResultUpdateFinalizeEx(sample, pool, true);
        ZRDealloc(pool, sample);
    }

    DDS_ULong ResultUpdateGetSerializedSampleMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_ULong ResultUpdateGetSerializedKeyMaxSize()
    {
        return MAX_UINT32_VALUE;
    }

    DDS_Long ResultUpdateGetKeyHash(
        const ResultUpdate* sample,
        CDRSerializer* cdr,
        DDS::KeyHash_t* result)
    {
        DDS_Long ret = ResultUpdateSerializeKey(sample, cdr);
        if (ret < 0) {
            printf("serialize key failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        ret = CDRSerializeGetKeyHash(cdr, result->value, true);
        if (ret < 0) {
            printf("get keyhash failed.");
            *result = DDS_HANDLE_NIL_NATIVE;
            return -1;
        }
        result->valid = true;
        return 0;
    }

    DDS_Boolean ResultUpdateHasKey()
    {
        return false;
    }

    TypeCodeHeader* ResultUpdateGetInnerTypeCode()
    {
#ifdef _ZRDDS_INCLUDE_TYPECODE
        DDS::TypeCode* userTypeCode = ResultUpdateGetTypeCode();
        if (userTypeCode == NULL) return NULL;
        return userTypeCode->getImpl();
#else
        return NULL;
#endif
    }

    DDS_Boolean ResultUpdateInitializeEx(
        ResultUpdate* self,
        ZRMemPool* pool,
        DDS_Boolean allocateMemory)
    {
        self->request_id = NULL;

        self->client_id = NULL;

        data_structure::ResultItemSeq_initialize_ex(&self->items, pool, allocateMemory);

        if (allocateMemory) {
        } else {
            if (self->request_id != NULL) {
                self->request_id[0] = '\0';
            }
            if (self->client_id != NULL) {
                self->client_id[0] = '\0';
            }
        }
        return true;
    }

    void ResultUpdateFinalizeEx(
        ResultUpdate* self,
        ZRMemPool* pool,
        DDS_Boolean deletePointers)
    {
        data_structure::ResultItemSeq_finalize(&self->items);
        if (deletePointers) {
        }
    }

    DDS_Boolean ResultUpdateCopyEx(
        ResultUpdate* dst,
        const ResultUpdate* src,
        ZRMemPool* pool)
    {
        if (src->request_id == NULL) {
            ZRDealloc(pool, dst->request_id);
            dst->request_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->request_id);
            DDS_Long dstLen = -1;
            if (dst->request_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->request_id) < srcLen) {
                ZRDealloc(pool, dst->request_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->request_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->request_id == NULL) {
                    printf("malloc for request_id failed.");
                    return false;
                }
            }
            strcpy(dst->request_id, src->request_id);
        }
        if (src->client_id == NULL) {
            ZRDealloc(pool, dst->client_id);
            dst->client_id = NULL;
        } else {
            DDS_ULong srcLen = strlen(src->client_id);
            DDS_Long dstLen = -1;
            if (dst->client_id == NULL) {
                dstLen = srcLen + 1;
            } else if (strlen(dst->client_id) < srcLen) {
                ZRDealloc(pool, dst->client_id);
                dstLen = srcLen + 1;
            }
            if (dstLen >= 0) {
                dst->client_id = (DDS_Char*)ZRMalloc(pool, dstLen);
                if (dst->client_id == NULL) {
                    printf("malloc for client_id failed.");
                    return false;
                }
            }
            strcpy(dst->client_id, src->client_id);
        }
        if (!data_structure::ResultItemSeq_copy(&dst->items, &src->items)) {
            printf("copy member items failed.");
            return false;
        }
        return true;
    }

    void ResultUpdatePrintData(const ResultUpdate* sample)
    {
        if (sample == NULL) {
            printf("NULL\n");
            return;
        }
        if (sample->request_id != NULL) {
            printf("sample->request_id(%d): %s\n", strlen(sample->request_id), sample->request_id);
        } else {
            printf("sample->request_id(0): NULL\n");
        }
        printf("\n");

        if (sample->client_id != NULL) {
            printf("sample->client_id(%d): %s\n", strlen(sample->client_id), sample->client_id);
        } else {
            printf("sample->client_id(0): NULL\n");
        }
        printf("\n");

        DDS_ULong itemsTmpLen = data_structure::ResultItemSeq_get_length(&sample->items);
        printf("sample->items: %d\n", itemsTmpLen);
        for (DDS_ULong i = 0; i < itemsTmpLen; ++i) {
            data_structure::ResultItemPrintData(&*data_structure::ResultItemSeq_get_reference(&sample->items, i));
        }
        printf("\n");

    }

    DDS::TypeCode* ResultUpdateGetTypeCode()
    {
        static DDS::TypeCode* s_typeCode = NULL;
        if (s_typeCode != NULL) return s_typeCode;
        DDS::TypeCodeFactory& factory = DDS::TypeCodeFactory::getInstance();

        s_typeCode = factory.createStructTC(
            "data_structure::ResultUpdate",
            DDS_EXTENSIBLE_EXTENSIBILITY);
        if (s_typeCode == NULL) {
            printf("create struct ResultUpdate typecode failed.");
            return s_typeCode;
        }
        DDS_Long ret = 0;
        DDS::TypeCode* memberTc = NULL;
        DDS::TypeCode* eleTc = NULL;

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member request_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            0,
            0,
            "request_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = factory.createStringTC(MAX_UINT32_VALUE);
        if (memberTc == NULL) {
            printf("Get Member client_id TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            1,
            1,
            "client_id",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        memberTc = data_structure::ResultItemGetTypeCode();
        if (memberTc != NULL) {
            memberTc = factory.createSequenceTC(MAX_UINT32_VALUE, memberTc);
        }
        if (memberTc == NULL) {
            printf("Get Member items TypeCode failed.");
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }
        ret = s_typeCode->addMemberToStruct(
            2,
            2,
            "items",
            memberTc,
            false,
            false);
        factory.deleteTC(memberTc);
        if (ret < 0) {
            factory.deleteTC(s_typeCode);
            s_typeCode = NULL;
            return NULL;
        }

        return s_typeCode;
    }

    DDS_Long ResultUpdateSerialize(const ResultUpdate* sample, CDRSerializer* cdr)
    {
        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->request_id, sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1)) {
            printf("serialize sample->request_id failed.");
            return -2;
        }

        if (!CDRSerializerPutString(cdr, (DDS_Char*)sample->client_id, sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1)) {
            printf("serialize sample->client_id failed.");
            return -2;
        }

        if (!CDRSerializerPutUntype(cdr, (DDS_Octet*)&(sample->items)._length, 4)) {
            printf("serialize length of sample->items failed.");
            return -2;
        }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        if (!CDRSerializerNoSerializingMode(cdr)) {
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
            for (DDS_ULong i = 0; i < (sample->items)._length; ++i) {
                if (data_structure::ResultItemSerialize(&*data_structure::ResultItemSeq_get_reference(&sample->items, i), cdr) < 0) {
                    printf("serialize sample->items failed.");
                    return -2;
                }
            }
#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
        }
#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

        return 0;
    }

    DDS_Long ResultUpdateDeserialize(
        ResultUpdate* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        // no key
        DDS_ULong request_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&request_idTmpLen, 4)) {
            sample->request_id = NULL;
            sample->client_id = NULL;
            data_structure::ResultItemSeq_initialize_ex(&sample->items, pool, true);
            return 0;
        }
        if (0 == request_idTmpLen) {
            ZRDealloc(pool, sample->request_id);
            sample->request_id = NULL;
        } else {
            if (sample->request_id == NULL) {
                sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                if (sample->request_id == NULL) {
                    printf("malloc for sample->request_id failed(%d).", request_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->request_id) + 1 < request_idTmpLen) {
                    ZRDealloc(pool, sample->request_id);
                    sample->request_id = (DDS_Char*)ZRMalloc(pool, request_idTmpLen);
                    if (sample->request_id == NULL) {
                        printf("realloc for sample->request_id failed(%d).", request_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->request_id, request_idTmpLen, 1)) {
                printf("deserialize member sample->request_id failed.");
                return -4;
            }
        }
        DDS_ULong client_idTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&client_idTmpLen, 4)) {
            sample->client_id = NULL;
            data_structure::ResultItemSeq_initialize_ex(&sample->items, pool, true);
            return 0;
        }
        if (0 == client_idTmpLen) {
            ZRDealloc(pool, sample->client_id);
            sample->client_id = NULL;
        } else {
            if (sample->client_id == NULL) {
                sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                if (sample->client_id == NULL) {
                    printf("malloc for sample->client_id failed(%d).", client_idTmpLen);
                    return -3;
                }
            } else {
                if (strlen(sample->client_id) + 1 < client_idTmpLen) {
                    ZRDealloc(pool, sample->client_id);
                    sample->client_id = (DDS_Char*)ZRMalloc(pool, client_idTmpLen);
                    if (sample->client_id == NULL) {
                        printf("realloc for sample->client_id failed(%d).", client_idTmpLen);
                        return -3;
                    }
                }
            }
            if (!CDRDeserializerGetUntypeArray(cdr, (DDS_Octet*)sample->client_id, client_idTmpLen, 1)) {
                printf("deserialize member sample->client_id failed.");
                return -4;
            }
        }
        DDS_ULong itemsTmpLen = 0;
        if (!CDRDeserializerGetUntype(cdr, (DDS_Octet*)&itemsTmpLen, 4)) {
            data_structure::ResultItemSeq_initialize_ex(&sample->items, pool, true);
            return 0;
        }
        if (!data_structure::ResultItemSeq_ensure_length(&sample->items, itemsTmpLen, itemsTmpLen)) {
            printf("Set maxiumum member sample->items failed.");
            return -3;
        }
        for (DDS_ULong i = 0; i < itemsTmpLen; ++i) {
            if (data_structure::ResultItemDeserialize(&*data_structure::ResultItemSeq_get_reference(&sample->items, i), cdr, pool) < 0) {
                printf("deserialize sample->items failed.");
                return -2;
            }
        }
        return 0;
    }

    DDS_ULong ResultUpdateGetSerializedSampleSize(const ResultUpdate* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += CDRSerializerGetStringSize(sample->request_id == NULL ? 0 : strlen(sample->request_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetStringSize(sample->client_id == NULL ? 0 : strlen(sample->client_id) + 1, currentAlignment);

        currentAlignment += CDRSerializerGetUntypeSize(4, currentAlignment);
        DDS_ULong itemsLen = data_structure::ResultItemSeq_get_length(&sample->items);
        if (itemsLen != 0) {
            for (DDS_ULong i = 0; i < itemsLen; ++i) {
                data_structure::ResultItem* curEle = data_structure::ResultItemSeq_get_reference(&sample->items, i);
                currentAlignment += data_structure::ResultItemGetSerializedSampleSize(curEle, currentAlignment);
            }
        }

        return currentAlignment - initialAlignment;
    }

    DDS_Long ResultUpdateSerializeKey(const ResultUpdate* sample, CDRSerializer* cdr)
    {
        if (ResultUpdateSerialize(sample, cdr) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_Long ResultUpdateDeserializeKey(
        ResultUpdate* sample,
        CDRDeserializer* cdr,
        ZRMemPool* pool)
    {
        if (ResultUpdateDeserialize(sample, cdr, pool) < 0) {
            return -1;
        }
        return 0;
    }

    DDS_ULong ResultUpdateGetSerializedKeySize(const ResultUpdate* sample, DDS_ULong currentAlignment)
    {
        DDS_ULong initialAlignment = currentAlignment;

        currentAlignment += ResultUpdateGetSerializedSampleSize(sample, currentAlignment);
        return currentAlignment - initialAlignment;
    }

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
    DDS_Char* ResultUpdateLoanSampleBuf(ResultUpdate* sample, DDS_Boolean takeBuffer)
    {
        return NULL;
    }

    void ResultUpdateReturnSampleBuf(DDS_Char* sampleBuf)
    {
        ;
    }

    DDS_Long ResultUpdateLoanDeserialize(ResultUpdate* sampleBuf,
                                         CDRDeserializer* cdr,
                                         DDS_ULong curIndex,
                                         DDS_ULong totalNum,
                                         DDS_Char* base,
                                         DDS_ULong offset,
                                         DDS_ULong space,
                                         DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

#endif /*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
    DDS_Long ResultUpdateOnSiteDeserialize(CDRDeserializer* cdr,
                                           ResultUpdate* sample,
                                           DDS_ULong offset,
                                           DDS_ULong totalSize,
                                           DDS_Char* payload,
                                           DDS_ULong payloadLen,
                                           DDS_ULong fixedHeaderLen)
    {
        return 0;
    }

    DDS_Boolean ResultUpdateNoSerializingSupported()
    {
        return false;
    }

    DDS_ULong ResultUpdateFixedHeaderLength()
    {
        return 0;
    }

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/
}
