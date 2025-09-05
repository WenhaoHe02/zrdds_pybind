/*************************************************************/
/*           此文件由编译器生成，请勿随意修改                */
/*************************************************************/
#include <stdlib.h>
#include "ZRDDSTypePlugin.h"
#include "ai_infer.h"
#include "ai_inferTypeSupport.h"
#include "ai_inferDataReader.h"
#include "ai_inferDataWriter.h"
#include "ZRDDSTypeSupport.cpp"

namespace data_structure
{

const DDS_Char* Bytes_TYPENAME = "Bytes";
DDSTypeSupportImpl(BytesTypeSupport, Bytes, Bytes_TYPENAME);


const DDS_Char* SingleTask_TYPENAME = "SingleTask";
DDSTypeSupportImpl(SingleTaskTypeSupport, SingleTask, SingleTask_TYPENAME);


const DDS_Char* InferenceRequest_TYPENAME = "InferenceRequest";
DDSTypeSupportImpl(InferenceRequestTypeSupport, InferenceRequest, InferenceRequest_TYPENAME);


const DDS_Char* Task_TYPENAME = "Task";
DDSTypeSupportImpl(TaskTypeSupport, Task, Task_TYPENAME);


const DDS_Char* OpenBatch_TYPENAME = "OpenBatch";
DDSTypeSupportImpl(OpenBatchTypeSupport, OpenBatch, OpenBatch_TYPENAME);


const DDS_Char* Claim_TYPENAME = "Claim";
DDSTypeSupportImpl(ClaimTypeSupport, Claim, Claim_TYPENAME);


const DDS_Char* Grant_TYPENAME = "Grant";
DDSTypeSupportImpl(GrantTypeSupport, Grant, Grant_TYPENAME);


const DDS_Char* TaskList_TYPENAME = "TaskList";
DDSTypeSupportImpl(TaskListTypeSupport, TaskList, TaskList_TYPENAME);


const DDS_Char* WorkerTaskResult_TYPENAME = "WorkerTaskResult";
DDSTypeSupportImpl(WorkerTaskResultTypeSupport, WorkerTaskResult, WorkerTaskResult_TYPENAME);


const DDS_Char* WorkerResult_TYPENAME = "WorkerResult";
DDSTypeSupportImpl(WorkerResultTypeSupport, WorkerResult, WorkerResult_TYPENAME);


const DDS_Char* ResultItem_TYPENAME = "ResultItem";
DDSTypeSupportImpl(ResultItemTypeSupport, ResultItem, ResultItem_TYPENAME);


const DDS_Char* ResultUpdate_TYPENAME = "ResultUpdate";
DDSTypeSupportImpl(ResultUpdateTypeSupport, ResultUpdate, ResultUpdate_TYPENAME);

}
