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

// 注释掉不存在的头文件，因为我们没有这些IDL生成的文件
// #include "ai_trainTypeSupport.h"
#include "../datastruct_cpp/ai_trainTypeSupport.h"

namespace py = pybind11;

// WorkerResult和Claim类型的声明（与bindings.cpp中保持一致）
struct WorkerResult
{
    std::string batch_id;
    std::string model_id;
    std::string worker_id;
};

struct Claim
{
    std::string batch_id;
    git rm - r-- cached.std::string worker_id;
    int queue_length;
};

// 这里实现批量注册
// 由于我们没有实际的IDL生成类型，我们创建一个示例函数
void register_all_types(DDS::DomainParticipant *dp)
{
    if (!dp)
        return;

    // 注释掉不存在的类型注册
    ai_train::TrainCmdTypeSupport::get_instance()->register_type(dp, "TrainCmd");

    // my_msgs::FooTypeSupport::register_type(dp, "Foo");
    // my_msgs::BarTypeSupport::register_type(dp, "Bar");

    // 这里可以添加实际的类型注册逻辑
    // 但由于我们没有具体的TypeSupport类，暂时留空
}

PYBIND11_MODULE(Project1, m)
{
    // 假设你已经在别的文件里绑定了 DomainParticipantFactory / DomainParticipant
    py::class_<DDS::DomainParticipant, DDS::Entity, std::unique_ptr<DDS::DomainParticipant, py::nodelete>>(m, "DomainParticipant");

    // 绑定 register_all_types
    m.def("register_all_types", &register_all_types,
          py::arg("participant"),
          "Register all known DDS types with the given DomainParticipant");

    // 如果需要的话，也可以把 QoS 常量一起导出
    m.attr("DOMAINPARTICIPANT_QOS_DEFAULT") = py::cast(DDS::DOMAINPARTICIPANT_QOS_DEFAULT);
}