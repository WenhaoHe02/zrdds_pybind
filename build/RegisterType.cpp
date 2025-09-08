#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../CPlusPlusInterface/Subscriber.h"
#include "../CPlusPlusInterface/Entity.h"
#include "../CPlusPlusInterface/DataReader.h"
#include "../CPlusPlusInterface/TopicDescription.h"
#include "../CPlusPlusInterface/DataReaderListener.h"
#include "../CPlusPlusInterface/ZRDDSDataWriter.h"
#include "../CPlusPlusInterface/DomainParticipant.h"
#include "../CPlusPlusInterface/SubscriberListener.h"
#include "../CPlusPlusInterface/DomainParticipantFactory.h"
#include "../CPlusPlusInterface/DomainParticipantListener.h"
#include "../CPlusPlusInterface/DataWriter.h"
#include "../CPlusPlusInterface/Publisher.h"
#include "../ZRDDSCoreInterface/DataReaderQos.h"
#include "../ZRDDSCoreInterface/InstanceHandle_t.h"
#include "../ZRDDSCoreInterface/PublisherQos.h"
#include "../ZRDDSCoreInterface/DomainParticipantFactoryQos.h"
#include "../ZRDDSCoreInterface/DefaultQos.h"
#include "../datastruct_cpp/ai_trainTypeSupport.h"
#include "../datastruct_cpp/ai_inferTypeSupport.h"

namespace py = pybind11;

void register_all_types(DDS::DomainParticipant *dp)
{
    if (!dp)
        return;

    // 训练相关
    ai_train::TrainCmdTypeSupport::get_instance()->register_type(dp, "TrainCmd");
    ai_train::ClientUpdateTypeSupport::get_instance()->register_type(dp, "ClientUpdate");
    ai_train::ModelBlobTypeSupport::get_instance()->register_type(dp, "ModelBlob");

    // 推理相关
    data_structure::TaskTypeSupport::get_instance()->register_type(dp, "Task");
    data_structure::ClaimTypeSupport::get_instance()->register_type(dp, "Claim");
    data_structure::OpenBatchTypeSupport::get_instance()->register_type(dp, "OpenBatch");
    data_structure::GrantTypeSupport::get_instance()->register_type(dp, "Grant");
    data_structure::TaskListTypeSupport::get_instance()->register_type(dp, "TaskList");
    data_structure::WorkerTaskResultTypeSupport::get_instance()->register_type(dp, "WorkerTaskResult");
    data_structure::WorkerResultTypeSupport::get_instance()->register_type(dp, "WorkerResult");
}

void bind_type(py::module &m)
{

    m.def("register_all_types", &register_all_types,
          py::arg("participant"),
          "Register all known DDS types with the given DomainParticipant");
}