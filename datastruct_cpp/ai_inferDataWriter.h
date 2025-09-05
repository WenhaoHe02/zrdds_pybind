#ifndef ai_inferDataWriter_h__
#define ai_inferDataWriter_h__
/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/

#include "ai_infer.h"
#include "ZRDDSDataWriter.h"

namespace data_structure
{

typedef DDS::ZRDDSDataWriter<Bytes> BytesDataWriter;


typedef DDS::ZRDDSDataWriter<SingleTask> SingleTaskDataWriter;


typedef DDS::ZRDDSDataWriter<InferenceRequest> InferenceRequestDataWriter;


typedef DDS::ZRDDSDataWriter<Task> TaskDataWriter;


typedef DDS::ZRDDSDataWriter<OpenBatch> OpenBatchDataWriter;


typedef DDS::ZRDDSDataWriter<Claim> ClaimDataWriter;


typedef DDS::ZRDDSDataWriter<Grant> GrantDataWriter;


typedef DDS::ZRDDSDataWriter<TaskList> TaskListDataWriter;


typedef DDS::ZRDDSDataWriter<WorkerTaskResult> WorkerTaskResultDataWriter;


typedef DDS::ZRDDSDataWriter<WorkerResult> WorkerResultDataWriter;


typedef DDS::ZRDDSDataWriter<ResultItem> ResultItemDataWriter;


typedef DDS::ZRDDSDataWriter<ResultUpdate> ResultUpdateDataWriter;

}
#endif

