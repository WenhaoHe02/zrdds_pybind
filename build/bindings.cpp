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

    // --------------------------
    // 基本类型绑定（保留你已有的绑定）
    // --------------------------
    py::class_<DDS::StatusCondition>(m, "StatusCondition");
    py::class_<DDS::StatusKindMask>(m, "StatusKindMask")
        .def(py::init<>());
    py::class_<DDS::InstanceHandle_t>(m, "InstanceHandle_t")
        .def(py::init<>());
    py::class_<DDS::ReturnCode_t>(m, "ReturnCode_t");
    py::class_<DDS::DataReaderListener>(m, "DataReaderListener");
    py::class_<DDS::DataReaderQos>(m, "DataReaderQos")
        .def(py::init<>());
    py::class_<DDS::TopicDescription, std::unique_ptr<DDS::TopicDescription, py::nodelete>>(m, "TopicDescription");

    py::class_<DDS::SubscriberListener>(m, "SubscriberListener");
    py::class_<DDS::SubscriberQos>(m, "SubscriberQos");
    py::class_<DDS::DomainParticipantListener>(m, "DomainParticipantListener");
    py::class_<DDS::DomainParticipantQos>(m, "DomainParticipantQos")
        .def(py::init<>());
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

    // --------------------------
    // Entity / Topic / DataReader / DataWriter / Publisher / Subscriber / Participant 绑定
    // --------------------------
    py::class_<DDS::Entity>(m, "Entity")
        .def("get_statuscondition", &DDS::Entity::get_statuscondition,
             py::return_value_policy::reference)
        .def("get_status_changes", &DDS::Entity::get_status_changes)
        .def("enable", &DDS::Entity::enable)
        .def("get_instance_handle", &DDS::Entity::get_instance_handle);

    py::class_<DDS::Topic, DDS::Entity, std::unique_ptr<DDS::Topic, py::nodelete>>(m, "Topic");

    // 绑定默认 QoS 常量：全部导出为 -1（Python sentinel）
    // 你可以根据需要仅导出部分，但这里一并导出常见的 default 常量为 -1
    m.attr("DOMAINPARTICIPANT_QOS_DEFAULT") = py::int_(-1);
    m.attr("DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT") = py::int_(-1);
    m.attr("PUBLISHER_QOS_DEFAULT") = py::int_(-1);
    m.attr("SUBSCRIBER_QOS_DEFAULT") = py::int_(-1);
    m.attr("DATAWRITER_QOS_DEFAULT") = py::int_(-1);
    m.attr("DATAREADER_QOS_DEFAULT") = py::int_(-1);
    m.attr("TOPIC_QOS_DEFAULT") = py::int_(-1);
    m.attr("DATAWRITER_QOS_USE_TOPIC_QOS") = py::int_(-2); // 可自定义特殊值
    m.attr("DATAREADER_QOS_USE_TOPIC_QOS") = py::int_(-2);

    // --------------------------
    // DataReader 绑定（create / set_listener）
    // --------------------------
    py::class_<DDS::DataReader, DDS::Entity>(m, "DataReader")
        .def("enable", &DDS::DataReader::enable)
        .def("set_listener", &DDS::DataReader::set_listener,
             py::arg("listener") = py::none(), py::arg("mask") = 0);

    // DataWriter 抽象绑定（用于继承）
    py::class_<DDS::DataWriter, DDS::Entity, std::unique_ptr<DDS::DataWriter, py::nodelete>>(m, "DataWriter");

    // WorkerResult / Claim 举例 DataWriter 绑定（保留你原有实现）
    struct WorkerResult
    {
        std::string batch_id;
        std::string model_id;
        std::string worker_id;
    };
    struct Claim
    {
        std::string batch_id;
        std::string worker_id;
        int queue_length;
    };

    py::class_<DDS::ZRDDSDataWriter<WorkerResult>, DDS::DataWriter>(m, "WorkerResultDataWriter")
        .def("write", &DDS::ZRDDSDataWriter<WorkerResult>::write,
             py::arg("data"),
             py::arg("handle") = DDS::HANDLE_NIL_NATIVE,
             py::call_guard<py::gil_scoped_release>());

    py::class_<DDS::ZRDDSDataWriter<Claim>, DDS::DataWriter>(m, "ClaimDataWriter")
        .def("write", &DDS::ZRDDSDataWriter<Claim>::write,
             py::arg("data"),
             py::arg("handle") = DDS::HANDLE_NIL_NATIVE,
             py::call_guard<py::gil_scoped_release>());

    // --------------------------
    // Publisher 绑定（create_datawriter wrapper）
    // --------------------------
    py::class_<DDS::Publisher, DDS::Entity, std::unique_ptr<DDS::Publisher, py::nodelete>>(m, "Publisher")
        // create_datawriter wrapper: 支持 qos 为 None / -1 / PublisherQos 对象
        .def("create_datawriter", [](DDS::Publisher *pub, py::object topic_obj, py::object qos_obj, py::object listener_obj, int mask) -> DDS::DataWriter *
             {
                DDS::DataWriterListener* listener = nullptr;
                if (!listener_obj.is_none()) {
                    listener = listener_obj.cast<DDS::DataWriterListener*>();
                }

                // 处理 qos: None 或 -1 -> use sentinel DDS::DATAWRITER_QOS_DEFAULT
                if (qos_obj.is_none() || (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1)) {
                    return pub->create_datawriter(topic_obj.cast<DDS::Topic*>(),
                        DDS::DATAWRITER_QOS_DEFAULT,
                        listener,
                        mask);
                }

                // 否则期望是 DataWriterQos
                DDS::DataWriterQos qos = qos_obj.cast<DDS::DataWriterQos>();
                return pub->create_datawriter(topic_obj.cast<DDS::Topic*>(), qos, listener, mask); }, py::return_value_policy::reference, py::arg("the_topic"), py::arg("qoslist") = py::none(), py::arg("a_listener") = py::none(), py::arg("mask") = 0);

    // --------------------------
    // Subscriber 绑定（create_datareader wrapper）
    // --------------------------
    py::class_<DDS::Subscriber, DDS::Entity, std::unique_ptr<DDS::Subscriber, py::nodelete>>(m, "Subscriber")
        .def("create_datareader", [](DDS::Subscriber *sub, py::object topic_obj, py::object qos_obj, py::object listener_obj, int mask) -> DDS::DataReader *
             {
                DDS::DataReaderListener* listener = nullptr;
                if (!listener_obj.is_none()) {
                    listener = listener_obj.cast<DDS::DataReaderListener*>();
                }

                if (qos_obj.is_none() || (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1)) {
                    return sub->create_datareader(topic_obj.cast<DDS::Topic*>(),
                        DDS::DATAREADER_QOS_DEFAULT,
                        listener,
                        mask);
                }

                DDS::DataReaderQos qos = qos_obj.cast<DDS::DataReaderQos>();
                return sub->create_datareader(topic_obj.cast<DDS::Topic*>(), qos, listener, mask); }, py::return_value_policy::reference, py::arg("a_topic"), py::arg("qoslist") = py::none(), py::arg("a_listener") = py::none(), py::arg("mask") = 0);

    // --------------------------
    // DomainParticipant 绑定（create_subscriber / create_publisher / create_topic wrappers）
    // --------------------------
    py::class_<DDS::DomainParticipant, DDS::Entity, std::unique_ptr<DDS::DomainParticipant, py::nodelete>>(m, "DomainParticipant")
        .def("create_subscriber", [](DDS::DomainParticipant *part, py::object qos_obj, py::object listener_obj, int mask) -> DDS::Subscriber *
             {
                DDS::SubscriberListener* listener = nullptr;
                if (!listener_obj.is_none()) listener = listener_obj.cast<DDS::SubscriberListener*>();

                if (qos_obj.is_none() || (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1)) {
                    return part->create_subscriber(DDS::SUBSCRIBER_QOS_DEFAULT, listener, mask);
                }
                DDS::SubscriberQos qos = qos_obj.cast<DDS::SubscriberQos>();
                return part->create_subscriber(qos, listener, mask); }, py::return_value_policy::reference, py::arg("qos") = py::none(), py::arg("listener") = py::none(), py::arg("mask") = 0)

        .def("create_publisher", [](DDS::DomainParticipant *part, py::object qos_obj, py::object listener_obj, int mask) -> DDS::Publisher *
             {
                DDS::PublisherListener* listener = nullptr;
                if (!listener_obj.is_none()) listener = listener_obj.cast<DDS::PublisherListener*>();

                if (qos_obj.is_none() || (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1)) {
                    return part->create_publisher(DDS::PUBLISHER_QOS_DEFAULT, listener, mask);
                }
                DDS::PublisherQos qos = qos_obj.cast<DDS::PublisherQos>();
                return part->create_publisher(qos, listener, mask); }, py::return_value_policy::reference, py::arg("qoslist") = py::none(), py::arg("a_listener") = py::none(), py::arg("mask") = 0)

        .def("create_topic", [](DDS::DomainParticipant *part, const std::string &topic_name, const std::string &type_name, py::object qos_obj, py::object listener_obj, int mask) -> DDS::Topic *
             {
                DDS::TopicListener* listener = nullptr;
                if (!listener_obj.is_none()) listener = listener_obj.cast<DDS::TopicListener*>();

                if (qos_obj.is_none() || (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1)) {
                    return part->create_topic(topic_name.c_str(),
                        type_name.c_str(),
                        DDS::TOPIC_QOS_DEFAULT,
                        listener,
                        mask);
                }
                DDS_TopicQos qos = qos_obj.cast<DDS_TopicQos>();
                return part->create_topic(topic_name.c_str(), type_name.c_str(), qos, listener, mask); }, py::return_value_policy::reference, py::arg("topic_name"), py::arg("type_name"), py::arg("qoslist") = py::none(), py::arg("a_listener") = py::none(), py::arg("mask") = 0);

    // --------------------------
    // DomainParticipantFactory 绑定（get_instance / create_participant wrapper / get_default_participant_qos / get_qos）
    // --------------------------
    py::class_<DDS::DomainParticipantFactory, std::unique_ptr<DDS::DomainParticipantFactory, py::nodelete>>(m, "DomainParticipantFactory")
        .def_static("get_instance", &DDS::DomainParticipantFactory::get_instance,
                    py::return_value_policy::reference)

        .def("create_participant", [](DDS::DomainParticipantFactory *factory, int domain_id, py::object qos_obj, DDS::DomainParticipantListener *listener, int mask) -> DDS::DomainParticipant *
             {
                if (qos_obj.is_none() || (py::isinstance<py::int_>(qos_obj) && qos_obj.cast<int>() == -1))
                {
                    return factory->create_participant(domain_id,
                        DDS::DOMAINPARTICIPANT_QOS_DEFAULT,
                        listener,
                        mask);
                }
                DDS::DomainParticipantQos qos = qos_obj.cast<DDS::DomainParticipantQos>();
                return factory->create_participant(domain_id, qos, listener, mask); }, py::arg("domainId"), py::arg("qos") = py::none(), py::arg("listener") = py::none(), py::arg("mask") = 0, py::return_value_policy::reference)

        .def("get_default_participant_qos", [](DDS::DomainParticipantFactory &self, DDS::DomainParticipantQos &qoslist)
             { return self.get_default_participant_qos(qoslist); }, "获取该工厂为域参与者保存的默认QoS配置", py::arg("qoslist"))

        .def("get_qos", [](DDS::DomainParticipantFactory &self, DDS_DomainParticipantFactoryQos &qoslist)
             { return self.get_qos(qoslist); }, "获取DomainParticipantFactory的QoS设置", py::arg("qoslist"));

    // --------------------------
    // 结束模块
    // --------------------------
}
