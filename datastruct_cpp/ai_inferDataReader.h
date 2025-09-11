#ifndef ai_inferDataReader_h__
#define ai_inferDataReader_h__
/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/

#include "ai_infer.h"
#include "ZRDDSDataReader.h"

namespace data_structure
{
typedef struct BytesSeq BytesSeq;

typedef DDS::ZRDDSDataReader<Bytes, BytesSeq> BytesDataReader;

typedef struct SingleTaskSeq SingleTaskSeq;

typedef DDS::ZRDDSDataReader<SingleTask, SingleTaskSeq> SingleTaskDataReader;

typedef struct InferenceRequestSeq InferenceRequestSeq;

typedef DDS::ZRDDSDataReader<InferenceRequest, InferenceRequestSeq> InferenceRequestDataReader;

typedef struct TaskSeq TaskSeq;

typedef DDS::ZRDDSDataReader<Task, TaskSeq> TaskDataReader;

typedef struct OpenBatchSeq OpenBatchSeq;

typedef DDS::ZRDDSDataReader<OpenBatch, OpenBatchSeq> OpenBatchDataReader;

typedef struct ClaimSeq ClaimSeq;

typedef DDS::ZRDDSDataReader<Claim, ClaimSeq> ClaimDataReader;

typedef struct GrantSeq GrantSeq;

typedef DDS::ZRDDSDataReader<Grant, GrantSeq> GrantDataReader;

typedef struct TaskListSeq TaskListSeq;

typedef DDS::ZRDDSDataReader<TaskList, TaskListSeq> TaskListDataReader;

typedef struct WorkerTaskResultSeq WorkerTaskResultSeq;

typedef DDS::ZRDDSDataReader<WorkerTaskResult, WorkerTaskResultSeq> WorkerTaskResultDataReader;

typedef struct WorkerResultSeq WorkerResultSeq;

typedef DDS::ZRDDSDataReader<WorkerResult, WorkerResultSeq> WorkerResultDataReader;

typedef struct ResultItemSeq ResultItemSeq;

typedef DDS::ZRDDSDataReader<ResultItem, ResultItemSeq> ResultItemDataReader;

typedef struct ResultUpdateSeq ResultUpdateSeq;

typedef DDS::ZRDDSDataReader<ResultUpdate, ResultUpdateSeq> ResultUpdateDataReader;

}
#endif

