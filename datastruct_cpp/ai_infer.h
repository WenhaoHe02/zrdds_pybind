#ifndef ai_infer_H_
#define ai_infer_H_

/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/
#include "OsResource.h"
#include "ZRSequence.h"
#include "TypeCode.h"
#include "CDRStream.h"
#include "ZRDDSCppWrapper.h"
#include "ZRBuiltinTypes.h"

typedef struct ZRMemPool ZRMemPool;


namespace data_structure
{
typedef struct Bytes
{
    DDS_OctetSeq value; // @ID(0) /* unbounded sequence */ 
} Bytes; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(BytesSeq, Bytes);

// 用户使用接口
DDS_Boolean BytesInitialize(
    Bytes* self);

DDS_Boolean BytesInitializeEx(
    Bytes* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void BytesFinalize(
    Bytes* self);

void BytesFinalizeEx(
    Bytes* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean BytesCopy(
    Bytes* dst,
    const Bytes* src);

DDS_Boolean BytesCopyEx(
    Bytes* dst,
    const Bytes* src,
    ZRMemPool* pool);

void BytesPrintData(
    const Bytes* sample);

DDS::TypeCode* BytesGetTypeCode();

// 底层使用函数
Bytes* BytesCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void BytesDestroySample(
    ZRMemPool* pool,
    Bytes* sample);

DDS_ULong BytesGetSerializedSampleMaxSize();

DDS_ULong BytesGetSerializedSampleSize(
    const Bytes* sample,
    DDS_ULong currentAlignment);

DDS_Long BytesSerialize(
    const Bytes* sample,
    CDRSerializer* cdr);

DDS_Long BytesDeserialize(
    Bytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong BytesGetSerializedKeyMaxSize();

DDS_ULong BytesGetSerializedKeySize(
    const Bytes* sample,
    DDS_ULong currentAlignment);

DDS_Long BytesSerializeKey(
    const Bytes* sample,
    CDRSerializer* cdr);

DDS_Long BytesDeserializeKey(
    Bytes* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long BytesGetKeyHash(
    const Bytes* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean BytesHasKey();

TypeCodeHeader* BytesGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean BytesNoSerializingSupported();

DDS_ULong BytesFixedHeaderLength();

DDS_Long BytesOnSiteDeserialize(CDRDeserializer* cdr,
    Bytes* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* BytesLoanSampleBuf(Bytes* sample, DDS_Boolean takeBuffer);

void BytesReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long BytesLoanDeserialize(Bytes* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct SingleTask
{
    DDS_Char* request_id; // @ID(0) /* unbounded string */ 
    DDS_Char* task_id; // @ID(1) /* unbounded string */ 
    DDS_Char* model_id; // @ID(2) /* unbounded string */ 
    DDS_Char* client_id; // @ID(3) /* unbounded string */ 
    data_structure::Bytes payload; // @ID(4)
} SingleTask; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(SingleTaskSeq, SingleTask);

// 用户使用接口
DDS_Boolean SingleTaskInitialize(
    SingleTask* self);

DDS_Boolean SingleTaskInitializeEx(
    SingleTask* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void SingleTaskFinalize(
    SingleTask* self);

void SingleTaskFinalizeEx(
    SingleTask* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean SingleTaskCopy(
    SingleTask* dst,
    const SingleTask* src);

DDS_Boolean SingleTaskCopyEx(
    SingleTask* dst,
    const SingleTask* src,
    ZRMemPool* pool);

void SingleTaskPrintData(
    const SingleTask* sample);

DDS::TypeCode* SingleTaskGetTypeCode();

// 底层使用函数
SingleTask* SingleTaskCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void SingleTaskDestroySample(
    ZRMemPool* pool,
    SingleTask* sample);

DDS_ULong SingleTaskGetSerializedSampleMaxSize();

DDS_ULong SingleTaskGetSerializedSampleSize(
    const SingleTask* sample,
    DDS_ULong currentAlignment);

DDS_Long SingleTaskSerialize(
    const SingleTask* sample,
    CDRSerializer* cdr);

DDS_Long SingleTaskDeserialize(
    SingleTask* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong SingleTaskGetSerializedKeyMaxSize();

DDS_ULong SingleTaskGetSerializedKeySize(
    const SingleTask* sample,
    DDS_ULong currentAlignment);

DDS_Long SingleTaskSerializeKey(
    const SingleTask* sample,
    CDRSerializer* cdr);

DDS_Long SingleTaskDeserializeKey(
    SingleTask* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long SingleTaskGetKeyHash(
    const SingleTask* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean SingleTaskHasKey();

TypeCodeHeader* SingleTaskGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean SingleTaskNoSerializingSupported();

DDS_ULong SingleTaskFixedHeaderLength();

DDS_Long SingleTaskOnSiteDeserialize(CDRDeserializer* cdr,
    SingleTask* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* SingleTaskLoanSampleBuf(SingleTask* sample, DDS_Boolean takeBuffer);

void SingleTaskReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long SingleTaskLoanDeserialize(SingleTask* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct InferenceRequest
{
    DDS_Char* request_id; // @ID(0) /* unbounded string */ 
    data_structure::SingleTaskSeq tasks; // @ID(1) /* unbounded sequence */ 
} InferenceRequest; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(InferenceRequestSeq, InferenceRequest);

// 用户使用接口
DDS_Boolean InferenceRequestInitialize(
    InferenceRequest* self);

DDS_Boolean InferenceRequestInitializeEx(
    InferenceRequest* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void InferenceRequestFinalize(
    InferenceRequest* self);

void InferenceRequestFinalizeEx(
    InferenceRequest* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean InferenceRequestCopy(
    InferenceRequest* dst,
    const InferenceRequest* src);

DDS_Boolean InferenceRequestCopyEx(
    InferenceRequest* dst,
    const InferenceRequest* src,
    ZRMemPool* pool);

void InferenceRequestPrintData(
    const InferenceRequest* sample);

DDS::TypeCode* InferenceRequestGetTypeCode();

// 底层使用函数
InferenceRequest* InferenceRequestCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void InferenceRequestDestroySample(
    ZRMemPool* pool,
    InferenceRequest* sample);

DDS_ULong InferenceRequestGetSerializedSampleMaxSize();

DDS_ULong InferenceRequestGetSerializedSampleSize(
    const InferenceRequest* sample,
    DDS_ULong currentAlignment);

DDS_Long InferenceRequestSerialize(
    const InferenceRequest* sample,
    CDRSerializer* cdr);

DDS_Long InferenceRequestDeserialize(
    InferenceRequest* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong InferenceRequestGetSerializedKeyMaxSize();

DDS_ULong InferenceRequestGetSerializedKeySize(
    const InferenceRequest* sample,
    DDS_ULong currentAlignment);

DDS_Long InferenceRequestSerializeKey(
    const InferenceRequest* sample,
    CDRSerializer* cdr);

DDS_Long InferenceRequestDeserializeKey(
    InferenceRequest* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long InferenceRequestGetKeyHash(
    const InferenceRequest* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean InferenceRequestHasKey();

TypeCodeHeader* InferenceRequestGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean InferenceRequestNoSerializingSupported();

DDS_ULong InferenceRequestFixedHeaderLength();

DDS_Long InferenceRequestOnSiteDeserialize(CDRDeserializer* cdr,
    InferenceRequest* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* InferenceRequestLoanSampleBuf(InferenceRequest* sample, DDS_Boolean takeBuffer);

void InferenceRequestReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long InferenceRequestLoanDeserialize(InferenceRequest* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct Task
{
    DDS_Char* request_id; // @ID(0) /* unbounded string */ 
    DDS_Char* task_id; // @ID(1) /* unbounded string */ 
    DDS_Char* client_id; // @ID(2) /* unbounded string */ 
    data_structure::Bytes payload; // @ID(3)
} Task; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(TaskSeq, Task);

// 用户使用接口
DDS_Boolean TaskInitialize(
    Task* self);

DDS_Boolean TaskInitializeEx(
    Task* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void TaskFinalize(
    Task* self);

void TaskFinalizeEx(
    Task* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean TaskCopy(
    Task* dst,
    const Task* src);

DDS_Boolean TaskCopyEx(
    Task* dst,
    const Task* src,
    ZRMemPool* pool);

void TaskPrintData(
    const Task* sample);

DDS::TypeCode* TaskGetTypeCode();

// 底层使用函数
Task* TaskCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void TaskDestroySample(
    ZRMemPool* pool,
    Task* sample);

DDS_ULong TaskGetSerializedSampleMaxSize();

DDS_ULong TaskGetSerializedSampleSize(
    const Task* sample,
    DDS_ULong currentAlignment);

DDS_Long TaskSerialize(
    const Task* sample,
    CDRSerializer* cdr);

DDS_Long TaskDeserialize(
    Task* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong TaskGetSerializedKeyMaxSize();

DDS_ULong TaskGetSerializedKeySize(
    const Task* sample,
    DDS_ULong currentAlignment);

DDS_Long TaskSerializeKey(
    const Task* sample,
    CDRSerializer* cdr);

DDS_Long TaskDeserializeKey(
    Task* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long TaskGetKeyHash(
    const Task* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean TaskHasKey();

TypeCodeHeader* TaskGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean TaskNoSerializingSupported();

DDS_ULong TaskFixedHeaderLength();

DDS_Long TaskOnSiteDeserialize(CDRDeserializer* cdr,
    Task* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* TaskLoanSampleBuf(Task* sample, DDS_Boolean takeBuffer);

void TaskReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long TaskLoanDeserialize(Task* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct OpenBatch
{
    DDS_Char* batch_id; // @ID(0) /* unbounded string */ 
    DDS_Char* model_id; // @ID(1) /* unbounded string */ 
    DDS_Long size; // @ID(2)
    DDS_Long create_ts_ms; // @ID(3)
} OpenBatch; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(OpenBatchSeq, OpenBatch);

// 用户使用接口
DDS_Boolean OpenBatchInitialize(
    OpenBatch* self);

DDS_Boolean OpenBatchInitializeEx(
    OpenBatch* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void OpenBatchFinalize(
    OpenBatch* self);

void OpenBatchFinalizeEx(
    OpenBatch* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean OpenBatchCopy(
    OpenBatch* dst,
    const OpenBatch* src);

DDS_Boolean OpenBatchCopyEx(
    OpenBatch* dst,
    const OpenBatch* src,
    ZRMemPool* pool);

void OpenBatchPrintData(
    const OpenBatch* sample);

DDS::TypeCode* OpenBatchGetTypeCode();

// 底层使用函数
OpenBatch* OpenBatchCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void OpenBatchDestroySample(
    ZRMemPool* pool,
    OpenBatch* sample);

DDS_ULong OpenBatchGetSerializedSampleMaxSize();

DDS_ULong OpenBatchGetSerializedSampleSize(
    const OpenBatch* sample,
    DDS_ULong currentAlignment);

DDS_Long OpenBatchSerialize(
    const OpenBatch* sample,
    CDRSerializer* cdr);

DDS_Long OpenBatchDeserialize(
    OpenBatch* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong OpenBatchGetSerializedKeyMaxSize();

DDS_ULong OpenBatchGetSerializedKeySize(
    const OpenBatch* sample,
    DDS_ULong currentAlignment);

DDS_Long OpenBatchSerializeKey(
    const OpenBatch* sample,
    CDRSerializer* cdr);

DDS_Long OpenBatchDeserializeKey(
    OpenBatch* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long OpenBatchGetKeyHash(
    const OpenBatch* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean OpenBatchHasKey();

TypeCodeHeader* OpenBatchGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean OpenBatchNoSerializingSupported();

DDS_ULong OpenBatchFixedHeaderLength();

DDS_Long OpenBatchOnSiteDeserialize(CDRDeserializer* cdr,
    OpenBatch* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* OpenBatchLoanSampleBuf(OpenBatch* sample, DDS_Boolean takeBuffer);

void OpenBatchReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long OpenBatchLoanDeserialize(OpenBatch* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct Claim
{
    DDS_Char* batch_id; // @ID(0) /* unbounded string */ 
    DDS_Char* worker_id; // @ID(1) /* unbounded string */ 
    DDS_Long queue_length; // @ID(2)
} Claim; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(ClaimSeq, Claim);

// 用户使用接口
DDS_Boolean ClaimInitialize(
    Claim* self);

DDS_Boolean ClaimInitializeEx(
    Claim* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void ClaimFinalize(
    Claim* self);

void ClaimFinalizeEx(
    Claim* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean ClaimCopy(
    Claim* dst,
    const Claim* src);

DDS_Boolean ClaimCopyEx(
    Claim* dst,
    const Claim* src,
    ZRMemPool* pool);

void ClaimPrintData(
    const Claim* sample);

DDS::TypeCode* ClaimGetTypeCode();

// 底层使用函数
Claim* ClaimCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void ClaimDestroySample(
    ZRMemPool* pool,
    Claim* sample);

DDS_ULong ClaimGetSerializedSampleMaxSize();

DDS_ULong ClaimGetSerializedSampleSize(
    const Claim* sample,
    DDS_ULong currentAlignment);

DDS_Long ClaimSerialize(
    const Claim* sample,
    CDRSerializer* cdr);

DDS_Long ClaimDeserialize(
    Claim* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong ClaimGetSerializedKeyMaxSize();

DDS_ULong ClaimGetSerializedKeySize(
    const Claim* sample,
    DDS_ULong currentAlignment);

DDS_Long ClaimSerializeKey(
    const Claim* sample,
    CDRSerializer* cdr);

DDS_Long ClaimDeserializeKey(
    Claim* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long ClaimGetKeyHash(
    const Claim* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean ClaimHasKey();

TypeCodeHeader* ClaimGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean ClaimNoSerializingSupported();

DDS_ULong ClaimFixedHeaderLength();

DDS_Long ClaimOnSiteDeserialize(CDRDeserializer* cdr,
    Claim* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* ClaimLoanSampleBuf(Claim* sample, DDS_Boolean takeBuffer);

void ClaimReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long ClaimLoanDeserialize(Claim* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct Grant
{
    DDS_Char* batch_id; // @ID(0) /* unbounded string */ 
    DDS_Char* winner_worker_id; // @ID(1) /* unbounded string */ 
} Grant; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(GrantSeq, Grant);

// 用户使用接口
DDS_Boolean GrantInitialize(
    Grant* self);

DDS_Boolean GrantInitializeEx(
    Grant* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void GrantFinalize(
    Grant* self);

void GrantFinalizeEx(
    Grant* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean GrantCopy(
    Grant* dst,
    const Grant* src);

DDS_Boolean GrantCopyEx(
    Grant* dst,
    const Grant* src,
    ZRMemPool* pool);

void GrantPrintData(
    const Grant* sample);

DDS::TypeCode* GrantGetTypeCode();

// 底层使用函数
Grant* GrantCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void GrantDestroySample(
    ZRMemPool* pool,
    Grant* sample);

DDS_ULong GrantGetSerializedSampleMaxSize();

DDS_ULong GrantGetSerializedSampleSize(
    const Grant* sample,
    DDS_ULong currentAlignment);

DDS_Long GrantSerialize(
    const Grant* sample,
    CDRSerializer* cdr);

DDS_Long GrantDeserialize(
    Grant* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong GrantGetSerializedKeyMaxSize();

DDS_ULong GrantGetSerializedKeySize(
    const Grant* sample,
    DDS_ULong currentAlignment);

DDS_Long GrantSerializeKey(
    const Grant* sample,
    CDRSerializer* cdr);

DDS_Long GrantDeserializeKey(
    Grant* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long GrantGetKeyHash(
    const Grant* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean GrantHasKey();

TypeCodeHeader* GrantGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean GrantNoSerializingSupported();

DDS_ULong GrantFixedHeaderLength();

DDS_Long GrantOnSiteDeserialize(CDRDeserializer* cdr,
    Grant* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* GrantLoanSampleBuf(Grant* sample, DDS_Boolean takeBuffer);

void GrantReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long GrantLoanDeserialize(Grant* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct TaskList
{
    DDS_Char* batch_id; // @ID(0) /* unbounded string */ 
    DDS_Char* model_id; // @ID(1) /* unbounded string */ 
    DDS_Char* assigned_worker_id; // @ID(2) /* unbounded string */ 
    data_structure::TaskSeq tasks; // @ID(3) /* unbounded sequence */ 
} TaskList; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(TaskListSeq, TaskList);

// 用户使用接口
DDS_Boolean TaskListInitialize(
    TaskList* self);

DDS_Boolean TaskListInitializeEx(
    TaskList* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void TaskListFinalize(
    TaskList* self);

void TaskListFinalizeEx(
    TaskList* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean TaskListCopy(
    TaskList* dst,
    const TaskList* src);

DDS_Boolean TaskListCopyEx(
    TaskList* dst,
    const TaskList* src,
    ZRMemPool* pool);

void TaskListPrintData(
    const TaskList* sample);

DDS::TypeCode* TaskListGetTypeCode();

// 底层使用函数
TaskList* TaskListCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void TaskListDestroySample(
    ZRMemPool* pool,
    TaskList* sample);

DDS_ULong TaskListGetSerializedSampleMaxSize();

DDS_ULong TaskListGetSerializedSampleSize(
    const TaskList* sample,
    DDS_ULong currentAlignment);

DDS_Long TaskListSerialize(
    const TaskList* sample,
    CDRSerializer* cdr);

DDS_Long TaskListDeserialize(
    TaskList* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong TaskListGetSerializedKeyMaxSize();

DDS_ULong TaskListGetSerializedKeySize(
    const TaskList* sample,
    DDS_ULong currentAlignment);

DDS_Long TaskListSerializeKey(
    const TaskList* sample,
    CDRSerializer* cdr);

DDS_Long TaskListDeserializeKey(
    TaskList* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long TaskListGetKeyHash(
    const TaskList* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean TaskListHasKey();

TypeCodeHeader* TaskListGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean TaskListNoSerializingSupported();

DDS_ULong TaskListFixedHeaderLength();

DDS_Long TaskListOnSiteDeserialize(CDRDeserializer* cdr,
    TaskList* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* TaskListLoanSampleBuf(TaskList* sample, DDS_Boolean takeBuffer);

void TaskListReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long TaskListLoanDeserialize(TaskList* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct WorkerTaskResult
{
    DDS_Char* request_id; // @ID(0) /* unbounded string */ 
    DDS_Char* task_id; // @ID(1) /* unbounded string */ 
    DDS_Char* client_id; // @ID(2) /* unbounded string */ 
    DDS_Char* status; // @ID(3) /* unbounded string */ 
    data_structure::Bytes output_blob; // @ID(4)
    DDS_StringSeq texts; // @ID(5) /* unbounded sequence */ 
} WorkerTaskResult; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(WorkerTaskResultSeq, WorkerTaskResult);

// 用户使用接口
DDS_Boolean WorkerTaskResultInitialize(
    WorkerTaskResult* self);

DDS_Boolean WorkerTaskResultInitializeEx(
    WorkerTaskResult* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void WorkerTaskResultFinalize(
    WorkerTaskResult* self);

void WorkerTaskResultFinalizeEx(
    WorkerTaskResult* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean WorkerTaskResultCopy(
    WorkerTaskResult* dst,
    const WorkerTaskResult* src);

DDS_Boolean WorkerTaskResultCopyEx(
    WorkerTaskResult* dst,
    const WorkerTaskResult* src,
    ZRMemPool* pool);

void WorkerTaskResultPrintData(
    const WorkerTaskResult* sample);

DDS::TypeCode* WorkerTaskResultGetTypeCode();

// 底层使用函数
WorkerTaskResult* WorkerTaskResultCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void WorkerTaskResultDestroySample(
    ZRMemPool* pool,
    WorkerTaskResult* sample);

DDS_ULong WorkerTaskResultGetSerializedSampleMaxSize();

DDS_ULong WorkerTaskResultGetSerializedSampleSize(
    const WorkerTaskResult* sample,
    DDS_ULong currentAlignment);

DDS_Long WorkerTaskResultSerialize(
    const WorkerTaskResult* sample,
    CDRSerializer* cdr);

DDS_Long WorkerTaskResultDeserialize(
    WorkerTaskResult* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong WorkerTaskResultGetSerializedKeyMaxSize();

DDS_ULong WorkerTaskResultGetSerializedKeySize(
    const WorkerTaskResult* sample,
    DDS_ULong currentAlignment);

DDS_Long WorkerTaskResultSerializeKey(
    const WorkerTaskResult* sample,
    CDRSerializer* cdr);

DDS_Long WorkerTaskResultDeserializeKey(
    WorkerTaskResult* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long WorkerTaskResultGetKeyHash(
    const WorkerTaskResult* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean WorkerTaskResultHasKey();

TypeCodeHeader* WorkerTaskResultGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean WorkerTaskResultNoSerializingSupported();

DDS_ULong WorkerTaskResultFixedHeaderLength();

DDS_Long WorkerTaskResultOnSiteDeserialize(CDRDeserializer* cdr,
    WorkerTaskResult* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* WorkerTaskResultLoanSampleBuf(WorkerTaskResult* sample, DDS_Boolean takeBuffer);

void WorkerTaskResultReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long WorkerTaskResultLoanDeserialize(WorkerTaskResult* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct WorkerResult
{
    DDS_Char* batch_id; // @ID(0) /* unbounded string */ 
    DDS_Char* model_id; // @ID(1) /* unbounded string */ 
    DDS_Char* worker_id; // @ID(2) /* unbounded string */ 
    data_structure::WorkerTaskResultSeq results; // @ID(3) /* unbounded sequence */ 
} WorkerResult; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(WorkerResultSeq, WorkerResult);

// 用户使用接口
DDS_Boolean WorkerResultInitialize(
    WorkerResult* self);

DDS_Boolean WorkerResultInitializeEx(
    WorkerResult* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void WorkerResultFinalize(
    WorkerResult* self);

void WorkerResultFinalizeEx(
    WorkerResult* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean WorkerResultCopy(
    WorkerResult* dst,
    const WorkerResult* src);

DDS_Boolean WorkerResultCopyEx(
    WorkerResult* dst,
    const WorkerResult* src,
    ZRMemPool* pool);

void WorkerResultPrintData(
    const WorkerResult* sample);

DDS::TypeCode* WorkerResultGetTypeCode();

// 底层使用函数
WorkerResult* WorkerResultCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void WorkerResultDestroySample(
    ZRMemPool* pool,
    WorkerResult* sample);

DDS_ULong WorkerResultGetSerializedSampleMaxSize();

DDS_ULong WorkerResultGetSerializedSampleSize(
    const WorkerResult* sample,
    DDS_ULong currentAlignment);

DDS_Long WorkerResultSerialize(
    const WorkerResult* sample,
    CDRSerializer* cdr);

DDS_Long WorkerResultDeserialize(
    WorkerResult* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong WorkerResultGetSerializedKeyMaxSize();

DDS_ULong WorkerResultGetSerializedKeySize(
    const WorkerResult* sample,
    DDS_ULong currentAlignment);

DDS_Long WorkerResultSerializeKey(
    const WorkerResult* sample,
    CDRSerializer* cdr);

DDS_Long WorkerResultDeserializeKey(
    WorkerResult* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long WorkerResultGetKeyHash(
    const WorkerResult* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean WorkerResultHasKey();

TypeCodeHeader* WorkerResultGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean WorkerResultNoSerializingSupported();

DDS_ULong WorkerResultFixedHeaderLength();

DDS_Long WorkerResultOnSiteDeserialize(CDRDeserializer* cdr,
    WorkerResult* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* WorkerResultLoanSampleBuf(WorkerResult* sample, DDS_Boolean takeBuffer);

void WorkerResultReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long WorkerResultLoanDeserialize(WorkerResult* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct ResultItem
{
    DDS_Char* task_id; // @ID(0) /* unbounded string */ 
    DDS_Char* status; // @ID(1) /* unbounded string */ 
    data_structure::Bytes output_blob; // @ID(2)
    DDS_StringSeq texts; // @ID(3) /* unbounded sequence */ 
} ResultItem; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(ResultItemSeq, ResultItem);

// 用户使用接口
DDS_Boolean ResultItemInitialize(
    ResultItem* self);

DDS_Boolean ResultItemInitializeEx(
    ResultItem* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void ResultItemFinalize(
    ResultItem* self);

void ResultItemFinalizeEx(
    ResultItem* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean ResultItemCopy(
    ResultItem* dst,
    const ResultItem* src);

DDS_Boolean ResultItemCopyEx(
    ResultItem* dst,
    const ResultItem* src,
    ZRMemPool* pool);

void ResultItemPrintData(
    const ResultItem* sample);

DDS::TypeCode* ResultItemGetTypeCode();

// 底层使用函数
ResultItem* ResultItemCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void ResultItemDestroySample(
    ZRMemPool* pool,
    ResultItem* sample);

DDS_ULong ResultItemGetSerializedSampleMaxSize();

DDS_ULong ResultItemGetSerializedSampleSize(
    const ResultItem* sample,
    DDS_ULong currentAlignment);

DDS_Long ResultItemSerialize(
    const ResultItem* sample,
    CDRSerializer* cdr);

DDS_Long ResultItemDeserialize(
    ResultItem* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong ResultItemGetSerializedKeyMaxSize();

DDS_ULong ResultItemGetSerializedKeySize(
    const ResultItem* sample,
    DDS_ULong currentAlignment);

DDS_Long ResultItemSerializeKey(
    const ResultItem* sample,
    CDRSerializer* cdr);

DDS_Long ResultItemDeserializeKey(
    ResultItem* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long ResultItemGetKeyHash(
    const ResultItem* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean ResultItemHasKey();

TypeCodeHeader* ResultItemGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean ResultItemNoSerializingSupported();

DDS_ULong ResultItemFixedHeaderLength();

DDS_Long ResultItemOnSiteDeserialize(CDRDeserializer* cdr,
    ResultItem* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* ResultItemLoanSampleBuf(ResultItem* sample, DDS_Boolean takeBuffer);

void ResultItemReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long ResultItemLoanDeserialize(ResultItem* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
typedef struct ResultUpdate
{
    DDS_Char* request_id; // @ID(0) /* unbounded string */ 
    DDS_Char* client_id; // @ID(1) /* unbounded string */ 
    data_structure::ResultItemSeq items; // @ID(2) /* unbounded sequence */ 
} ResultUpdate; // @Extensibility(EXTENSIBLE)

DDS_USER_SEQUENCE_CPP(ResultUpdateSeq, ResultUpdate);

// 用户使用接口
DDS_Boolean ResultUpdateInitialize(
    ResultUpdate* self);

DDS_Boolean ResultUpdateInitializeEx(
    ResultUpdate* self,
    ZRMemPool* pool,
    DDS_Boolean allocateMemory);

void ResultUpdateFinalize(
    ResultUpdate* self);

void ResultUpdateFinalizeEx(
    ResultUpdate* self,
    ZRMemPool* pool,
    DDS_Boolean deletePointers);

DDS_Boolean ResultUpdateCopy(
    ResultUpdate* dst,
    const ResultUpdate* src);

DDS_Boolean ResultUpdateCopyEx(
    ResultUpdate* dst,
    const ResultUpdate* src,
    ZRMemPool* pool);

void ResultUpdatePrintData(
    const ResultUpdate* sample);

DDS::TypeCode* ResultUpdateGetTypeCode();

// 底层使用函数
ResultUpdate* ResultUpdateCreateSample(
    ZRMemPool* pool,
    DDS_Boolean allocMutable);

void ResultUpdateDestroySample(
    ZRMemPool* pool,
    ResultUpdate* sample);

DDS_ULong ResultUpdateGetSerializedSampleMaxSize();

DDS_ULong ResultUpdateGetSerializedSampleSize(
    const ResultUpdate* sample,
    DDS_ULong currentAlignment);

DDS_Long ResultUpdateSerialize(
    const ResultUpdate* sample,
    CDRSerializer* cdr);

DDS_Long ResultUpdateDeserialize(
    ResultUpdate* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_ULong ResultUpdateGetSerializedKeyMaxSize();

DDS_ULong ResultUpdateGetSerializedKeySize(
    const ResultUpdate* sample,
    DDS_ULong currentAlignment);

DDS_Long ResultUpdateSerializeKey(
    const ResultUpdate* sample,
    CDRSerializer* cdr);

DDS_Long ResultUpdateDeserializeKey(
    ResultUpdate* sample,
    CDRDeserializer* cdr,
    ZRMemPool* pool);

DDS_Long ResultUpdateGetKeyHash(
    const ResultUpdate* sample,
    CDRSerializer* cdr,
    DDS::KeyHash_t* result);

DDS_Boolean ResultUpdateHasKey();

TypeCodeHeader* ResultUpdateGetInnerTypeCode();

#ifdef _ZRDDS_INCLUDE_ONSITE_DESERILIZE
DDS_Boolean ResultUpdateNoSerializingSupported();

DDS_ULong ResultUpdateFixedHeaderLength();

DDS_Long ResultUpdateOnSiteDeserialize(CDRDeserializer* cdr,
    ResultUpdate* sample,
    DDS_ULong offset,
    DDS_ULong totalSize,
    DDS_Char* payload,
    DDS_ULong payloadLen,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_ONSITE_DESERILIZE*/

#ifdef _ZRDDS_INCLUDE_NO_SERIALIZE_MODE
DDS_Char* ResultUpdateLoanSampleBuf(ResultUpdate* sample, DDS_Boolean takeBuffer);

void ResultUpdateReturnSampleBuf(DDS_Char* sampleBuf);

DDS_Long ResultUpdateLoanDeserialize(ResultUpdate* sampleBuf,
    CDRDeserializer* cdr,
    DDS_ULong curIndex,
    DDS_ULong totalNum,
    DDS_Char* base,
    DDS_ULong offset,
    DDS_ULong space,
    DDS_ULong fixedHeaderLen);

#endif/*_ZRDDS_INCLUDE_NO_SERIALIZE_MODE*/
}
#endif
