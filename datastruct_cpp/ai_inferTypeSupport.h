#ifndef ai_inferTypeSupport_h__
#define ai_inferTypeSupport_h__
/*************************************************************/
/*           ���ļ��ɱ��������ɣ����������޸�                */
/*************************************************************/

#include "ZRDDSTypeSupport.h"

namespace data_structure {
    DDSTypeSupport(BytesTypeSupport, Bytes);
    DDSTypeSupport(SingleTaskTypeSupport, SingleTask);
    DDSTypeSupport(InferenceRequestTypeSupport, InferenceRequest);
    DDSTypeSupport(TaskTypeSupport, Task);
    DDSTypeSupport(OpenBatchTypeSupport, OpenBatch);
    DDSTypeSupport(ClaimTypeSupport, Claim);
    DDSTypeSupport(GrantTypeSupport, Grant);
    DDSTypeSupport(TaskListTypeSupport, TaskList);
    DDSTypeSupport(WorkerTaskResultTypeSupport, WorkerTaskResult);
    DDSTypeSupport(WorkerResultTypeSupport, WorkerResult);
    DDSTypeSupport(ResultItemTypeSupport, ResultItem);
    DDSTypeSupport(ResultUpdateTypeSupport, ResultUpdate);
}
#endif

