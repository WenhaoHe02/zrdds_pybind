// listener_bindings.cpp

#include <pybind11/pybind11.h>
#include "Listener.h"

#include <pybind11/stl.h>
#include "DataReaderListener.h"
#include "ZRDDSDataReader.h"

#include <pybind11/functional.h>
#include "DataWriterListener.h"

#include "PublisherListener.h"

#include "SubscriberListener.h"

#include "TopicListener.h"

#include "DomainParticipantListener.h"

#include <iostream>

namespace py = pybind11;

// 不透明指针声明（无需绑定 DataReader 完整定义）
namespace DDS {
    struct DataReader; // 前向声明
    struct DataWriter; // 前向声明
    struct Subscriber;
    struct DataReader;
    struct Topic; // 前向声明

}

namespace py = pybind11;

// 绑定基类 Listener
void bind_Listener(py::module& m)
{
    py::class_<DDS::Listener>(m, "Listener")
        .def(py::init<>()) // 默认构造函数
        .def("__repr__", [](const DDS::Listener&) { return "<DDS.Listener>"; });
}

//// 绑定基础 DataReaderListener
// void bind_DataReaderListener(py::module& m) {
//     py::class_<DDS::DataReaderListener, DDS::Listener>(m, "DataReaderListener")
//         .def(py::init<>())
//         .def("__repr__", [](const DDS::DataReaderListener&) {
//         return "<DDS.DataReaderListener>";
//             })
// #ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
//         .def("on_requested_deadline_missed", [](DDS::DataReaderListener& self, void* reader, const DDS::RequestedDeadlineMissedStatus& status) {
//         self.on_requested_deadline_missed(static_cast<DDS::DataReader*>(reader), status);
//             }, py::arg("reader"), py::arg("status"))
// #endif
//         .def("on_data_available", [](DDS::DataReaderListener& self, void* reader) {
//         self.on_data_available(static_cast<DDS::DataReader*>(reader));
//             }, py::arg("reader"))
//         .def("on_data_arrived", [](DDS::DataReaderListener& self, void* reader, void* sample, const DDS::SampleInfo& info) {
//         self.on_data_arrived(static_cast<DDS::DataReader*>(reader), sample, info);
//             }, py::arg("reader"), py::arg("sample"), py::arg("info"))
//         .def("on_sample_rejected", [](DDS::DataReaderListener& self, void* reader, const DDS::SampleRejectedStatus& status) {
//         self.on_sample_rejected(static_cast<DDS::DataReader*>(reader), status);
//             }, py::arg("reader"), py::arg("status"))
// #ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
//         .def("on_liveliness_changed", [](DDS::DataReaderListener& self, void* reader, const DDS::LivelinessChangedStatus& status) {
//         self.on_liveliness_changed(static_cast<DDS::DataReader*>(reader), status);
//             }, py::arg("reader"), py::arg("status"))
// #endif
//         .def("on_requested_incompatible_qos", [](DDS::DataReaderListener& self, void* reader, const DDS::RequestedIncompatibleQosStatus& status) {
//         self.on_requested_incompatible_qos(static_cast<DDS::DataReader*>(reader), status);
//             }, py::arg("reader"), py::arg("status"))
//         .def("on_subscription_matched", [](DDS::DataReaderListener& self, void* reader, const DDS::SubscriptionMatchedStatus& status) {
//         self.on_subscription_matched(static_cast<DDS::DataReader*>(reader), status);
//             }, py::arg("reader"), py::arg("status"))
//         .def("on_sample_lost", [](DDS::DataReaderListener& self, void* reader, const DDS::SampleLostStatus& status) {
//         self.on_sample_lost(static_cast<DDS::DataReader*>(reader), status);
//             }, py::arg("reader"), py::arg("status"));
// }

// 绑定模板类 SimpleDataReaderListener（需用户指定模板参数）
template <typename T, typename TSeq, typename TDataReader>
void bind_SimpleDataReaderListener(py::module& m, const std::string& name)
{
    py::class_<DDS::SimpleDataReaderListener<T, TSeq, TDataReader>, DDS::DataReaderListener>(m, name.c_str())
        .def(py::init<>())
        .def("on_process_sample", [](DDS::SimpleDataReaderListener<T, TSeq, TDataReader>& self, void* reader, const T& sample, const DDS::SampleInfo& info) { self.on_process_sample(static_cast<DDS::DataReader*>(reader), sample, info); }, py::arg("reader"), py::arg("sample"), py::arg("info"));
}

// 绑定 DataWriterListener（继承自已绑定的 Listener）
void bind_DataWriterListener(py::module& m)
{
    py::class_<DDS::DataWriterListener, DDS::Listener>(m, "DataWriterListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DataWriterListener&) { return "<DDS.DataWriterListener>"; })
#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
        // 将 DataWriter* 转换为 void* 传递
        .def("on_liveliness_lost", [](DDS::DataWriterListener& self, void* the_writer, const DDS::LivelinessLostStatus& status) { self.on_liveliness_lost(static_cast<DDS::DataWriter*>(the_writer), status); }, py::arg("the_writer"), py::arg("status"))
#endif
#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
        .def("on_offered_deadline_missed", [](DDS::DataWriterListener& self, void* the_writer, const DDS::OfferedDeadlineMissedStatus& status) { self.on_offered_deadline_missed(static_cast<DDS::DataWriter*>(the_writer), status); }, py::arg("the_writer"), py::arg("status"))
#endif
        .def("on_offered_incompatible_qos", [](DDS::DataWriterListener& self, void* the_writer, const DDS::OfferedIncompatibleQosStatus& status) { self.on_offered_incompatible_qos(static_cast<DDS::DataWriter*>(the_writer), status); }, py::arg("the_writer"), py::arg("status"))
        .def("on_publication_matched", [](DDS::DataWriterListener& self, void* the_writer, const DDS::PublicationMatchedStatus& status) { self.on_publication_matched(static_cast<DDS::DataWriter*>(the_writer), status); }, py::arg("the_writer"), py::arg("status"));
}

// 绑定 PublisherListener（继承自 DataWriterListener）
void bind_PublisherListener(py::module& m)
{
    py::class_<DDS::PublisherListener, DDS::DataWriterListener>(m, "PublisherListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::PublisherListener&) { return "<DDS.PublisherListener>"; });
}

// 绑定 SubscriberListener（继承自 DataReaderListener）
void bind_SubscriberListener(py::module& m)
{
    py::class_<DDS::SubscriberListener, DDS::DataReaderListener>(m, "SubscriberListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::SubscriberListener&) { return "<DDS.SubscriberListener>"; })
        // 将 Subscriber* 转换为 void* 传递
        .def("on_data_on_readers", [](DDS::SubscriberListener& self, void* the_subscriber) { self.on_data_on_readers(static_cast<DDS::Subscriber*>(the_subscriber)); }, py::arg("the_subscriber"));
}

// 绑定 TopicListener（继承自已绑定的 Listener）
void bind_TopicListener(py::module& m)
{
    py::class_<DDS::TopicListener, DDS::Listener>(m, "TopicListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::TopicListener&) { return "<DDS.TopicListener>"; })
        // 将 Topic* 转换为 void* 传递
        .def("on_inconsistent_topic", [](DDS::TopicListener& self, void* the_topic, const DDS::InconsistentTopicStatus& status) { self.on_inconsistent_topic(static_cast<DDS::Topic*>(the_topic), status); }, py::arg("the_topic"), py::arg("status"));
}

// 绑定 DomainParticipantListener（多继承）
void bind_DomainParticipantListener(py::module& m)
{
    py::class_<DDS::DomainParticipantListener,
        DDS::PublisherListener,
        DDS::TopicListener,
        DDS::SubscriberListener>(m, "DomainParticipantListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DomainParticipantListener&) { return "<DDS.DomainParticipantListener>"; })
        .def("on_domain_received", &DDS::DomainParticipantListener::on_domain_received);
}

// 1) Trampoline：把 C++ 虚函数安全地“转发”到 Python
class PyDataReaderListener : public DDS::DataReaderListener {
public:
    using DDS::DataReaderListener::DataReaderListener;

    void on_data_available(DDS::DataReader* reader) override
    {
        std::cerr << "[C++] trampoline:on_data_available enter, reader=" << reader << std::endl;
        py::gil_scoped_acquire gil;
        try {
            PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_data_available, reader);
        } catch (const py::error_already_set& e) {
            std::cerr << "[C++] Python exception in on_data_available: " << e.what() << std::endl;
            PyErr_Print(); // 打印 Python traceback 到 stderr
        }
        std::cerr << "[C++] trampoline:on_data_available exit" << std::endl;
    }

    void on_data_arrived(DDS::DataReader* reader, void* sample, const DDS::SampleInfo& info) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_data_arrived, reader, sample, info);
    }

#ifdef _ZRDDS_INCLUDE_DEADLINE_QOS
    void on_requested_deadline_missed(DDS::DataReader* reader, const DDS::RequestedDeadlineMissedStatus& status) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_requested_deadline_missed, reader, status);
    }
#endif

#ifdef _ZRDDS_INCLUDE_LIVELINESS_QOS
    void on_liveliness_changed(DDS::DataReader* reader, const DDS::LivelinessChangedStatus& status) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_liveliness_changed, reader, status);
    }
#endif

    void on_sample_rejected(DDS::DataReader* reader, const DDS::SampleRejectedStatus& status) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_sample_rejected, reader, status);
    }

    void on_requested_incompatible_qos(DDS::DataReader* reader, const DDS::RequestedIncompatibleQosStatus& status) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_requested_incompatible_qos, reader, status);
    }

    void on_subscription_matched(DDS::DataReader* reader, const DDS::SubscriptionMatchedStatus& status) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_subscription_matched, reader, status);
    }

    void on_sample_lost(DDS::DataReader* reader, const DDS::SampleLostStatus& status) override
    {
        py::gil_scoped_acquire gil;
        PYBIND11_OVERLOAD(void, DDS::DataReaderListener, on_sample_lost, reader, status);
    }
};

// 2) 绑定：注意第二个模板参数是 PyDataReaderListener（trampoline）
void bind_DataReaderListener(py::module& m)
{
    py::class_<DDS::DataReaderListener, PyDataReaderListener, DDS::Listener>(m, "DataReaderListener")
        .def(py::init<>())
        .def("__repr__", [](const DDS::DataReaderListener&) { return "<DDS.DataReaderListener>"; });

    // 这里**不再**用 lambda 去 .def("on_data_available", []{ self.on_data_available(...) })，
    // 因为真正的回调由 DDS 触发时，会走到上面的 trampoline。
    // 如需从 Python 主动调用基类实现，可再按需补充 .def(...) 绑定到非虚接口。
}

void bind_listeners(py::module& m)
{
    // 模块文档字符串
    m.doc() = "Python bindings for DDS Listener class using pybind11";

    // 绑定 Listener 类
    bind_Listener(m);

    // 绑定基础监听器
    bind_DataReaderListener(m);

    // 示例：绑定特定类型的 SimpleDataReaderListener（需用户根据实际类型替换）

    bind_SimpleDataReaderListener<DDS_Octet, DDS_OctetSeq, DDS::ZRDDSDataReader<DDS_Octet, DDS_OctetSeq>>(m, "SimpleIntDataReaderListener");

    bind_DataWriterListener(m);
    bind_PublisherListener(m);

    bind_SubscriberListener(m);
    bind_TopicListener(m);
    bind_DomainParticipantListener(m);
}
