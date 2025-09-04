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
#include "../ZRDDSCoreInterface/SubscriptionMatchedStatus.h"
#include "../datastruct_cpp/ai_train.h"

namespace py = pybind11;

void bind_core(py::module &m)
{
    m.doc() = "Python bindings for DDS Subscriber and related classes";

    // --------------------------
    // 基本类型绑定（保留你已有的绑定）
    // --------------------------
    py::class_<DDS::StatusCondition>(m, "StatusCondition");
    py::class_<DDS::StatusKindMask>(m, "StatusKindMask")
        .def(py::init<>());
    py::class_<DDS_InstanceHandle_t>(m, "InstanceHandle_t")
        .def(py::init<>())
        // 绑定 valid 字段
        .def_readwrite("valid", &DDS_InstanceHandle_t::valid)
        // 用 property 手动绑定 value[16]
        .def_property(
            "value",
            [](const DDS_InstanceHandle_t &h)
            {
                return std::vector<uint8_t>(h.value, h.value + 16); // 复制成 Python list
            },
            [](DDS_InstanceHandle_t &h, const std::vector<uint8_t> &vec)
            {
                if (vec.size() != 16)
                    throw std::runtime_error("value must be length 16");
                std::copy(vec.begin(), vec.end(), h.value);
            });
    // py::class_<DDS::DataReaderListener>(m, "DataReaderListener");
    py::class_<DDS::DataReaderQos>(m, "DataReaderQos")
        .def(py::init<>());

    py::class_<DDS::SubscriptionMatchedStatus>(m, "SubscriptionMatchedStatus")
        .def(py::init<>())
        .def_readwrite("total_count", &DDS::SubscriptionMatchedStatus::total_count)
        .def_readwrite("total_count_change", &DDS::SubscriptionMatchedStatus::total_count_change)
        .def_readwrite("current_count", &DDS::SubscriptionMatchedStatus::current_count)
        .def_readwrite("current_count_change", &DDS::SubscriptionMatchedStatus::current_count_change)
        .def_readwrite("last_publication_handle", &DDS::SubscriptionMatchedStatus::last_publication_handle);

    // py::class_<DDS::SubscriberListener>(m, "SubscriberListener");
    py::class_<DDS::SubscriberQos>(m, "SubscriberQos");
    // py::class_<DDS::DomainParticipantListener>(m, "DomainParticipantListener");
    py::class_<DDS::DomainParticipantQos>(m, "DomainParticipantQos")
        .def(py::init<>());
    py::class_<DDS::DomainParticipantFactoryQos>(m, "DomainParticipantFactoryQos")
        .def(py::init<>());
    // py::class_<DDS::DataWriterListener>(m, "DataWriterListener");
    py::class_<DDS::DataWriterQos>(m, "DataWriterQos")
        .def(py::init<>());
    // py::class_<DDS::PublisherListener>(m, "PublisherListener")
    //     .def(py::init<>());
    py::class_<DDS::PublisherQos>(m, "PublisherQos")
        .def(py::init<>());
    // py::class_<DDS::TopicListener>(m, "TopicListener");
    py::class_<DDS::TopicQos>(m, "TopicQos")
        .def(py::init<>());

    // --------------------------
    // TypeSupport 绑定
    // --------------------------
    // py::class_<DDS::TypeSupport>(m, "TypeSupport")
    //     .def("get_type_name", &DDS::TypeSupport::get_type_name)

    //     .def("register_type", &DDS::TypeSupport::register_type, py::arg("participant"), py::arg("type_name"))

    //     .def("unregister_type", &DDS::TypeSupport::unregister_type, py::arg("participant"), py::arg("type_name"));

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
    // StatusKind 枚举绑定
    // --------------------------

    py::enum_<DDS::StatusKind>(m, "StatusKind", py::arithmetic())
        .value("INCONSISTENT_TOPIC_STATUS", DDS_INCONSISTENT_TOPIC_STATUS)
        .value("OFFERED_DEADLINE_MISSED_STATUS", DDS_OFFERED_DEADLINE_MISSED_STATUS)
        .value("REQUESTED_DEADLINE_MISSED_STATUS", DDS_REQUESTED_DEADLINE_MISSED_STATUS)
        .value("OFFERED_INCOMPATIBLE_QOS_STATUS", DDS_OFFERED_INCOMPATIBLE_QOS_STATUS)
        .value("REQUESTED_INCOMPATIBLE_QOS_STATUS", DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS)
        .value("SAMPLE_LOST_STATUS", DDS_SAMPLE_LOST_STATUS)
        .value("SAMPLE_REJECTED_STATUS", DDS_SAMPLE_REJECTED_STATUS)
        .value("DATA_ON_READERS_STATUS", DDS_DATA_ON_READERS_STATUS)
        .value("DATA_AVAILABLE_STATUS", DDS_DATA_AVAILABLE_STATUS)
        .value("LIVELINESS_LOST_STATUS", DDS_LIVELINESS_LOST_STATUS)
        .value("LIVELINESS_CHANGED_STATUS", DDS_LIVELINESS_CHANGED_STATUS)
        .value("PUBLICATION_MATCHED_STATUS", DDS_PUBLICATION_MATCHED_STATUS)
        .value("SUBSCRIPTION_MATCHED_STATUS", DDS_SUBSCRIPTION_MATCHED_STATUS)
        .export_values();

    // --------------------------
    // DataReader 绑定（create / set_listener）
    // --------------------------
    py::class_<DDS::DataReader, DDS::Entity>(m, "DataReader")
        .def("enable", &DDS::DataReader::enable)
        .def("set_listener", &DDS::DataReader::set_listener,
             py::arg("listener") = py::none(), py::arg("mask") = 0)
        .def("get_subscription_matched_status", [](DDS::DataReader &self)
             {
                 DDS::SubscriptionMatchedStatus status;
                 DDS::ReturnCode_t ret = self.get_subscription_matched_status(status);
                 if (ret != DDS::RETCODE_OK)
                 {
                     throw std::runtime_error("get_subscription_matched_status failed");
                 }
                 return status; // 返回 status 给 Python
             });

    // DataWriter 抽象绑定（用于继承）
    // PublicationMatchedStatus 绑定
    py::class_<DDS::PublicationMatchedStatus>(m, "PublicationMatchedStatus")
        .def(py::init<>())
        .def_readwrite("total_count", &DDS::PublicationMatchedStatus::total_count)
        .def_readwrite("total_count_change", &DDS::PublicationMatchedStatus::total_count_change)
        .def_readwrite("current_count", &DDS::PublicationMatchedStatus::current_count)
        .def_readwrite("current_count_change", &DDS::PublicationMatchedStatus::current_count_change)
        .def_readwrite("last_subscription_handle", &DDS::PublicationMatchedStatus::last_subscription_handle);

    py::class_<DDS::DataWriter, DDS::Entity, std::unique_ptr<DDS::DataWriter, py::nodelete>>(m, "DataWriter")
        .def("get_publication_matched_status", [](DDS::DataWriter &self)
             {
                 DDS::PublicationMatchedStatus status;
                 DDS::ReturnCode_t ret = self.get_publication_matched_status(status);
                 if (ret != DDS::RETCODE_OK)
                 {
                     throw std::runtime_error("get_publication_matched_status failed");
                 }
                 return status; // 直接返回 Python 可用的 PublicationMatchedStatus 对象
             });

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
                            return part->create_topic(topic_name.c_str(), type_name.c_str(), qos, listener, mask); }, py::return_value_policy::reference, py::arg("topic_name"), py::arg("type_name"), py::arg("qoslist") = py::none(), py::arg("a_listener") = py::none(), py::arg("mask") = 0)

        .def("delete_topic", &DDS::DomainParticipant::delete_topic, py::arg("a_topic"));

    // --------------------------
    // DomainParticipantFactory 绑定（get_instance / create_participant wrapper / get_default_participant_qos / get_qos）
    // --------------------------
    py::class_<DDS::DomainParticipantFactory, std::unique_ptr<DDS::DomainParticipantFactory, py::nodelete>>(m, "DomainParticipantFactory")
        .def_static("get_instance", &DDS::DomainParticipantFactory::get_instance,
                    py::return_value_policy::reference)

        .def_static("get_instance_w_qos", &DDS::DomainParticipantFactory::get_instance_w_qos,
                    py::arg("qoslist"),
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

        .def("delete_participant", &DDS::DomainParticipantFactory::delete_participant, py::arg("a_dp"))

        .def("get_default_participant_qos", [](DDS::DomainParticipantFactory &self, DDS::DomainParticipantQos &qoslist)
             { return self.get_default_participant_qos(qoslist); }, "获取该工厂为域参与者保存的默认QoS配置", py::arg("qoslist"))

        .def("get_qos", [](DDS::DomainParticipantFactory &self, DDS_DomainParticipantFactoryQos &qoslist)
             { return self.get_qos(qoslist); }, "获取DomainParticipantFactory的QoS设置", py::arg("qoslist"));

    // --------------------------
    // 结束模块s
    // --------------------------
}
