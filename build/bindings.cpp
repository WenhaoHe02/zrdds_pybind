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

namespace py = pybind11;

PYBIND11_MODULE(Project1, m)
{
    m.doc() = "Python bindings for DDS Subscriber and related classes";

    // 绑定相关类型
    py::class_<DDS::StatusCondition>(m, "StatusCondition");
    py::class_<DDS::StatusKindMask>(m, "StatusKindMask")
        .def(py::init<>());
    py::class_<DDS::InstanceHandle_t>(m, "InstanceHandle_t")
        .def(py::init<>()); // 添加默认构造函数
    py::class_<DDS::ReturnCode_t>(m, "ReturnCode_t");
    py::class_<DDS::DataReaderListener>(m, "DataReaderListener");
    py::class_<DDS::DataReaderQos>(m, "DataReaderQos")
        .def(py::init<>()); // 添加默认构造函数
    py::class_<DDS::TopicDescription, std::unique_ptr<DDS::TopicDescription, py::nodelete>>(m, "TopicDescription");

    py::class_<DDS::SubscriberListener>(m, "SubscriberListener");
    py::class_<DDS::SubscriberQos>(m, "SubscriberQos");
    py::class_<DDS::DomainParticipantListener>(m, "DomainParticipantListener");
    py::class_<DDS::DomainParticipantQos>(m, "DomainParticipantQos")
        .def(py::init<>());
    // 添加DomainParticipantFactoryQos的绑定
    py::class_<DDS_DomainParticipantFactoryQos>(m, "DomainParticipantFactoryQos")
        .def(py::init<>());
    py::class_<DDS::DataWriterListener>(m, "DataWriterListener");
    py::class_<DDS::DataWriterQos>(m, "DataWriterQos")
        .def(py::init<>());
    py::class_<DDS::PublisherListener>(m, "PublisherListener")
        .def(py::init<>());
    py::class_<DDS::PublisherQos>(m, "PublisherQos")
        .def(py::init<>());
    py::class_<DDS::TopicListener>(m, "TopicListener");
    py::class_<DDS_TopicQos>(m, "TopicQos")
        .def(py::init<>());

    // 绑定Entity基类
    py::class_<DDS::Entity>(m, "Entity")
        .def("get_statuscondition", &DDS::Entity::get_statuscondition,
             py::return_value_policy::reference)
        .def("get_status_changes", &DDS::Entity::get_status_changes)
        .def("enable", &DDS::Entity::enable)
        .def("get_instance_handle", &DDS::Entity::get_instance_handle);

    // 绑定Topic基类
    py::class_<DDS::Topic, DDS::Entity, std::unique_ptr<DDS::Topic, py::nodelete>>(m, "Topic");

    // 绑定默认QoS常量
    // 替换原来的常量绑定代码
    // 直接导出 sentinel，不做 py::cast

    m.attr("DOMAINPARTICIPANT_QOS_DEFAULT") = py::int_(-1);
    m.attr("DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT") = DDS::DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT;
    // m.attr("DOMAINPARTICIPANT_QOS_DEFAULT") = DDS::DOMAINPARTICIPANT_QOS_DEFAULT;
    m.attr("PUBLISHER_QOS_DEFAULT") = DDS::PUBLISHER_QOS_DEFAULT;
    m.attr("SUBSCRIBER_QOS_DEFAULT") = DDS::SUBSCRIBER_QOS_DEFAULT;
    m.attr("DATAWRITER_QOS_DEFAULT") = DDS::DATAWRITER_QOS_DEFAULT;
    m.attr("DATAREADER_QOS_DEFAULT") = DDS::DATAREADER_QOS_DEFAULT;
    m.attr("TOPIC_QOS_DEFAULT") = DDS::TOPIC_QOS_DEFAULT;
    m.attr("DATAWRITER_QOS_USE_TOPIC_QOS") = DDS::DATAWRITER_QOS_USE_TOPIC_QOS;
    m.attr("DATAREADER_QOS_USE_TOPIC_QOS") = DDS::DATAREADER_QOS_USE_TOPIC_QOS;

    // 绑定DataReader类
    py::class_<DDS::DataReader, DDS::Entity>(m, "DataReader")
        .def("enable", &DDS::DataReader::enable)
        .def("set_listener", &DDS::DataReader::set_listener,
             py::arg("listener") = py::none(), py::arg("mask") = 0);

    py::class_<DDS::DataWriter, DDS::Entity, std::unique_ptr<DDS::DataWriter, py::nodelete>>(m, "DataWriter");
    // WorkerResult Writer
    // 首先需要声明WorkerResult和Claim类型 - 这里简化处理，实际应该在其他地方定义完整的类
    struct WorkerResult
    {
        std::string batch_id;
        std::string model_id;
        std::string worker_id;
        // WorkerTaskResultSeq results; // 简化处理，省略复杂成员
    };

    struct Claim
    {
        std::string batch_id;
        std::string worker_id;
        int queue_length;
    };

    // 为WorkerResult类型创建专门的DataWriter绑定
    py::class_<DDS::ZRDDSDataWriter<WorkerResult>, DDS::DataWriter>(m, "WorkerResultDataWriter")
        .def("write", &DDS::ZRDDSDataWriter<WorkerResult>::write,
             py::arg("data"),
             py::arg("handle") = DDS::HANDLE_NIL_NATIVE,
             py::call_guard<py::gil_scoped_release>(),
             "发布 WorkerResult 数据样本");

    // Claim Writer
    py::class_<DDS::ZRDDSDataWriter<Claim>, DDS::DataWriter>(m, "ClaimDataWriter")
        .def("write", &DDS::ZRDDSDataWriter<Claim>::write,
             py::arg("data"),
             py::arg("handle") = DDS::HANDLE_NIL_NATIVE,
             py::call_guard<py::gil_scoped_release>());

    // 绑定Publisher类
    py::class_<DDS::Publisher, DDS::Entity, std::unique_ptr<DDS::Publisher, py::nodelete>>(m, "Publisher")
        .def("create_datawriter", &DDS::Publisher::create_datawriter,
             py::return_value_policy::reference,
             py::arg("the_topic"),
             py::arg("qoslist"),
             py::arg("a_listener") = py::none(),
             py::arg("mask") = DDS::StatusKindMask());

    // 绑定Subscriber类
    py::class_<DDS::Subscriber, DDS::Entity, std::unique_ptr<DDS::Subscriber, py::nodelete>>(m, "Subscriber")
        .def("create_datareader", &DDS::Subscriber::create_datareader,
             py::return_value_policy::reference,
             py::arg("a_topic"),
             py::arg("qoslist"),
             py::arg("a_listener") = py::none(),
             py::arg("mask") = DDS::StatusKindMask());

    // 工厂
    // 绑定DomainParticipant类
    py::class_<DDS::DomainParticipant, DDS::Entity, std::unique_ptr<DDS::DomainParticipant, py::nodelete>>(m, "DomainParticipant")
        .def("create_subscriber", &DDS::DomainParticipant::create_subscriber,
             py::return_value_policy::reference,
             py::arg("qos"),
             py::arg("listener") = py::none(),
             py::arg("mask") = DDS::StatusKindMask())
        .def("create_publisher", &DDS::DomainParticipant::create_publisher,
             py::return_value_policy::reference,
             py::arg("qoslist"),
             py::arg("a_listener") = py::none(),
             py::arg("mask") = DDS::StatusKindMask())
        .def("create_topic", &DDS::DomainParticipant::create_topic,
             py::return_value_policy::reference,
             py::arg("topic_name"),
             py::arg("type_name"),
             py::arg("qoslist"),
             py::arg("a_listener") = py::none(),
             py::arg("mask") = DDS::StatusKindMask());

    // 绑定DomainParticipantFactory类
    py::class_<DDS::DomainParticipantFactory, std::unique_ptr<DDS::DomainParticipantFactory, py::nodelete>>(m, "DomainParticipantFactory")
        .def_static("get_instance", &DDS::DomainParticipantFactory::get_instance,
                    py::return_value_policy::reference)
        // .def("create_participant", &DDS::DomainParticipantFactory::create_participant,
        //      py::return_value_policy::reference,
        //      py::arg("domainId"),
        //      py::arg("qos"),
        //      py::arg("listener") = py::none(),
        //      py::arg("mask") = DDS::StatusKindMask())
        .def("create_participant",
             [](DDS::DomainParticipantFactory *factory,
                int domain_id,
                py::object qos_obj,
                DDS::DomainParticipantListener *listener,
                int mask)
             {
                 // 如果 Python 传的是 sentinel，就走这里
                 if (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1)
                 {
                     return factory->create_participant(domain_id,
                                                        DDS::DOMAINPARTICIPANT_QOS_DEFAULT,
                                                        listener,
                                                        mask);
                 }
                 // 否则，把它当作一个真实的 QoS 对象
                 DDS::DomainParticipantQos qos = qos_obj.cast<DDS::DomainParticipantQos>();
                 return factory->create_participant(domain_id, qos, listener, mask);
             })

        .def("get_default_participant_qos", [](DDS::DomainParticipantFactory &self, DDS::DomainParticipantQos &qoslist)
             { return self.get_default_participant_qos(qoslist); }, "获取该工厂为域参与者保存的默认QoS配置", py::arg("qoslist"))
        .def("get_qos", [](DDS::DomainParticipantFactory &self, DDS_DomainParticipantFactoryQos &qoslist)
             { return self.get_qos(qoslist); }, "获取DomainParticipantFactory的QoS设置", py::arg("qoslist"));
}