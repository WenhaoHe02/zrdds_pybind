#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ai_train.h"
#include "ai_trainDataReader.h"
#include "ai_trainDataWriter.h"
#include "ai_trainTypeSupport.h"
#include <cstring>
#include <iostream>
#include <WaitSet.h>

namespace py = pybind11;

// 自定义删除器，用于安全地管理DDS对象的生命周期
// 注意：对于DDS对象，我们不直接delete，而是依赖DDS运行时管理
struct TrainCmdDataReaderDeleter
{
    void operator()(ai_train::TrainCmdDataReader *ptr) const
    {
        // 对于DDS对象，析构函数是protected的，不能直接delete
        // 我们也不调用特定的释放函数，因为这些对象的生命周期由DDS运行时管理
        // 这里保持为空，实际的对象清理由DDS运行时负责
        // 在Python端，我们使用reference策略来避免尝试销毁这些对象
    }
};

struct ClientUpdateDataReaderDeleter
{
    void operator()(ai_train::ClientUpdateDataReader *ptr) const
    {
    }
};

struct ModelBlobDataReaderDeleter
{
    void operator()(ai_train::ModelBlobDataReader *ptr) const
    {
    }
};

struct TrainCmdDataWriterDeleter
{
    void operator()(ai_train::TrainCmdDataWriter *ptr) const
    {
    }
};

struct ClientUpdateDataWriterDeleter
{
    void operator()(ai_train::ClientUpdateDataWriter *ptr) const
    {
    }
};

struct ModelBlobDataWriterDeleter
{
    void operator()(ai_train::ModelBlobDataWriter *ptr) const
    {
    }
};

// Bytes <-> Python bytes
// 将Python字节转换为DDS字节序列
static void py_to_bytes(const py::bytes &pybytes, ai_train::Bytes &dds_bytes)
{
    std::string temp = pybytes;
    DDS_ULong len = static_cast<DDS_ULong>(temp.size());

    if (len > 0)
    {
        dds_bytes.ensure_length(len, len);
        dds_bytes.from_array(reinterpret_cast<const DDS_Octet *>(temp.data()), len);
    }
    else
    {
        dds_bytes.ensure_length(0, 0);
    }
}

// 将DDS字节序列转换为Python字节
static py::bytes bytes_to_py(const ai_train::Bytes &dds_bytes)
{
    DDS_ULong len = dds_bytes.length();
    if (len == 0)
        return py::bytes();

    const DDS_Octet *buf = dds_bytes.get_contiguous_buffer();
    if (!buf)
        return py::bytes();

    return py::bytes(reinterpret_cast<const char *>(buf), static_cast<size_t>(len));
}

// TrainCmd结构体包装器，用于在Python中使用
struct TrainCmdWrapper : ai_train::TrainCmd
{
    TrainCmdWrapper() { TrainCmdInitialize(this); }
    ~TrainCmdWrapper() { TrainCmdFinalize(this); }
};

// ClientUpdate结构体包装器，用于在Python中使用
struct ClientUpdateWrapper : ai_train::ClientUpdate
{
    ClientUpdateWrapper() { ClientUpdateInitialize(this); }
    ~ClientUpdateWrapper() { ClientUpdateFinalize(this); }
};

// ModelBlob结构体包装器，用于在Python中使用
struct ModelBlobWrapper : ai_train::ModelBlob
{
    ModelBlobWrapper() { ModelBlobInitialize(this); }
    ~ModelBlobWrapper() { ModelBlobFinalize(this); }
};

// Seq类型封装模板（Base -> Wrapper 映射）
// 用于将C++序列类型绑定到Python，提供序列操作功能
template <typename Seq, typename Base, typename Wrapper>
void bind_sequence_mapped(py::module_ &m, const char *name)
{
    py::class_<Seq>(m, name)
        .def(py::init<DDS_ULong>(), py::arg("max") = 16)

        // 获取序列长度
        .def("length", [](const Seq &self)
             { return static_cast<size_t>(self.length()); })

        // 获取指定索引的元素，返回Wrapper的副本而不是尝试转换指针
        .def("get_at", [](Seq &self, size_t i)
             {
            if (i >= self.length()) throw py::index_error();
            const Base& elem = self.get_at(static_cast<DDS_ULong>(i));
            // 创建一个新的Wrapper对象并复制数据
            auto wrapper = new Wrapper();
            *static_cast<Base*>(wrapper) = elem;
            return wrapper; }, py::return_value_policy::take_ownership)

        // 设置指定索引的元素，Wrapper -> Base
        .def("set_at", [](Seq &self, size_t i, const Wrapper &val)
             {
            if (i >= self.length()) throw py::index_error();
            const Base& base_val = val;  // 使用更明确的类型转换
            if (!self.set_at(static_cast<DDS_ULong>(i), base_val))
                throw std::runtime_error("set_at failed"); })

        // 添加元素到序列末尾，Wrapper -> Base
        .def("append", [](Seq &self, const Wrapper &val)
             {
            if (!self.append(static_cast<const Base&>(val)))
                throw std::runtime_error("append failed"); })

        // 清空序列
        .def("clear", [](Seq &self)
             {
            if (!self.clear()) throw std::runtime_error("clear failed"); })

        // 确保序列具有指定长度和最大容量
        .def("ensure_length", [](Seq &self, size_t length, size_t max)
             {
            if (!self.ensure_length(static_cast<DDS_ULong>(length), static_cast<DDS_ULong>(max)))
                throw std::runtime_error("ensure_length failed"); })

        // 转为 Python list，返回Wrapper对象的列表
        .def("to_array", [](Seq &self)
             {
            py::list result;
            DDS_ULong len = self.length();
            for (DDS_ULong i = 0; i < len; ++i) {
                const Base& elem = self.get_at(i);
                // 创建一个新的Wrapper对象并复制数据
                auto wrapper = new Wrapper();
                *static_cast<Base*>(wrapper) = elem;
                result.append(py::cast(wrapper, py::return_value_policy::take_ownership));
            }
            return result; })

        // 从Python列表复制数据到序列中
        .def("from_array", [](Seq &self, const py::list &list)
             {
            DDS_ULong len = static_cast<DDS_ULong>(list.size());
            // 调整序列长度以容纳所有元素
            self.ensure_length(len, len);
            for (DDS_ULong i = 0; i < len; ++i) {
                // 将Python列表中的每个元素转换为Wrapper，然后转换为Base
                const Wrapper& wrapper = list[i].cast<const Wrapper&>();
                self.set_at(i, static_cast<const Base&>(wrapper));
            }
            return true; });
}

// ================================
// DataWriter 绑定模板
// ================================
template <typename DDSWriterType, typename MsgType, typename MsgWrapper, typename Deleter>
void bind_datawriter(py::module_ &m, const char *py_class_name)
{
    py::class_<DDSWriterType, std::unique_ptr<DDSWriterType, Deleter>>(m, py_class_name)
        .def("write", [](DDSWriterType &writer, const MsgWrapper &msg_wrapper)
             {
            const MsgType &msg = static_cast<const MsgType &>(msg_wrapper);
            return writer.write(msg, DDS::HANDLE_NIL_NATIVE); });
}

// DataReader 绑定模板（去掉DDS::DataReader基类）
template <typename DDSReaderType, typename MsgType, typename SeqType, typename MsgWrapper, typename Deleter>
void bind_datareader(py::module_ &m, const char *py_class_name)
{
    py::class_<DDSReaderType, std::unique_ptr<DDSReaderType, Deleter>>(m, py_class_name)
        .def("take", [](DDSReaderType &reader, SeqType &dataSeq, DDS::SampleInfoSeq &infoSeq, py::object max_samples, py::object sampleState, py::object viewState, py::object instanceState)
             {
                // 处理Python中定义的DDS常量和默认值
                DDS::Long max_samples_val = py::cast<DDS::Long>(max_samples);
                DDS::SampleStateMask sample_state = static_cast<DDS::SampleStateMask>(py::cast<DDS::ULong>(sampleState));
                DDS::ViewStateMask view_state = static_cast<DDS::ViewStateMask>(py::cast<DDS::ULong>(viewState));
                DDS::InstanceStateMask instance_state = static_cast<DDS::InstanceStateMask>(py::cast<DDS::ULong>(instanceState));
                return reader.take(dataSeq, infoSeq, max_samples_val, sample_state, view_state, instance_state); }, py::arg("dataSeq"), py::arg("infoSeq"), py::arg("max_samples") = LENGTH_UNLIMITED, py::arg("sampleState") = DDS::ANY_SAMPLE_STATE, py::arg("viewState") = DDS::ANY_VIEW_STATE, py::arg("instanceState") = DDS::ANY_INSTANCE_STATE)
        .def("create_readcondition", [](DDSReaderType &self, py::object sample_mask, py::object view_mask, py::object instance_mask) -> std::shared_ptr<DDS::ReadCondition>
             {
                DDS::ReadCondition* rc = self.create_readcondition(
                    static_cast<DDS::SampleStateMask>(py::cast<DDS::ULong>(sample_mask)),
                    static_cast<DDS::ViewStateMask>(py::cast<DDS::ULong>(view_mask)),
                    static_cast<DDS::InstanceStateMask>(py::cast<DDS::ULong>(instance_mask)));

                if (!rc) {
                    return nullptr;
                }

                // 注意：不要直接用 shared_ptr 管理 DDS 返回的裸指针，否则析构会 double free
                // 推荐用 return_value_policy::reference 或者 aliasing 技巧
                return std::shared_ptr<DDS::ReadCondition>(rc, [](DDS::ReadCondition*) {
                    // 空 deleter，让 DDS 自己管理生命周期
                    }); }, py::arg("sample_mask"), py::arg("view_mask"), py::arg("instance_mask"),
             py::return_value_policy::reference // 确保 Python 端不去释放它
        );
}

// ================================
// narrow 工厂函数（DataWriter）
// ================================
static std::unique_ptr<ai_train::TrainCmdDataWriter, TrainCmdDataWriterDeleter>
as_train_cmd_datawriter(DDS::DataWriter *writer)
{
    ai_train::TrainCmdDataWriter *data_writer = ai_train::TrainCmdDataWriter::createI(writer, ai_train::TrainCmdTypeSupport::get_instance);
    return std::unique_ptr<ai_train::TrainCmdDataWriter, TrainCmdDataWriterDeleter>(data_writer);
}

static std::unique_ptr<ai_train::ClientUpdateDataWriter, ClientUpdateDataWriterDeleter>
as_client_update_datawriter(DDS::DataWriter *writer)
{
    ai_train::ClientUpdateDataWriter *data_writer = ai_train::ClientUpdateDataWriter::createI(writer, ai_train::ClientUpdateTypeSupport::get_instance);
    return std::unique_ptr<ai_train::ClientUpdateDataWriter, ClientUpdateDataWriterDeleter>(data_writer);
}

static std::unique_ptr<ai_train::ModelBlobDataWriter, ModelBlobDataWriterDeleter>
as_model_blob_datawriter(DDS::DataWriter *writer)
{
    ai_train::ModelBlobDataWriter *data_writer = ai_train::ModelBlobDataWriter::createI(writer, ai_train::ModelBlobTypeSupport::get_instance);
    return std::unique_ptr<ai_train::ModelBlobDataWriter, ModelBlobDataWriterDeleter>(data_writer);
}

// ================================
// narrow 工厂函数（DataReader）
// ================================
static std::unique_ptr<ai_train::TrainCmdDataReader, TrainCmdDataReaderDeleter>
as_train_cmd_datareader(DDS::DataReader *reader)
{
    ai_train::TrainCmdDataReader *data_reader = ai_train::TrainCmdDataReader::createI(reader, ai_train::TrainCmdTypeSupport::get_instance);
    return std::unique_ptr<ai_train::TrainCmdDataReader, TrainCmdDataReaderDeleter>(data_reader);
}

static std::unique_ptr<ai_train::ClientUpdateDataReader, ClientUpdateDataReaderDeleter>
as_client_update_datareader(DDS::DataReader *reader)
{
    ai_train::ClientUpdateDataReader *data_reader = ai_train::ClientUpdateDataReader::createI(reader, ai_train::ClientUpdateTypeSupport::get_instance);
    return std::unique_ptr<ai_train::ClientUpdateDataReader, ClientUpdateDataReaderDeleter>(data_reader);
}

static std::unique_ptr<ai_train::ModelBlobDataReader, ModelBlobDataReaderDeleter>
as_model_blob_datareader(DDS::DataReader *reader)
{
    ai_train::ModelBlobDataReader *data_reader = ai_train::ModelBlobDataReader::createI(reader, ai_train::ModelBlobTypeSupport::get_instance);
    return std::unique_ptr<ai_train::ModelBlobDataReader, ModelBlobDataReaderDeleter>(data_reader);
}

// ----------------------
// ReadCondition 绑定
// ----------------------

// trampoline 类，允许 Python 重写虚函数
class PyReadCondition : public DDS::ReadCondition
{
public:
    using ReadCondition::ReadCondition;

    DDS::DataReader *get_datareader() override
    {
        PYBIND11_OVERRIDE_PURE(
            DDS::DataReader *,
            DDS::ReadCondition,
            get_datareader);
    }

    DDS::SampleStateMask get_sample_state_mask() override
    {
        PYBIND11_OVERRIDE_PURE(
            DDS::SampleStateMask,
            DDS::ReadCondition,
            get_sample_state_mask);
    }

    DDS::ViewStateMask get_view_state_mask() override
    {
        PYBIND11_OVERRIDE_PURE(
            DDS::ViewStateMask,
            DDS::ReadCondition,
            get_view_state_mask);
    }

    DDS::InstanceStateMask get_instance_state_mask() override
    {
        PYBIND11_OVERRIDE_PURE(
            DDS::InstanceStateMask,
            DDS::ReadCondition,
            get_instance_state_mask);
    }
};

// 绑定转换
// 将所有类型和功能绑定到Python模块
PYBIND11_MODULE(dds_pybindings, m)
{
    // 先绑定基类，用于继承关系
    py::class_<ai_train::TrainCmd>(m, "TrainCmdBase")
        .def_readwrite("round_id", &ai_train::TrainCmd::round_id)
        .def_readwrite("subset_size", &ai_train::TrainCmd::subset_size)
        .def_readwrite("epochs", &ai_train::TrainCmd::epochs)
        .def_readwrite("lr", &ai_train::TrainCmd::lr)
        .def_readwrite("seed", &ai_train::TrainCmd::seed);

    py::class_<ai_train::ClientUpdate>(m, "ClientUpdateBase")
        .def_readwrite("client_id", &ai_train::ClientUpdate::client_id)
        .def_readwrite("round_id", &ai_train::ClientUpdate::round_id)
        .def_readwrite("num_samples", &ai_train::ClientUpdate::num_samples);

    py::class_<ai_train::ModelBlob>(m, "ModelBlobBase")
        .def_readwrite("round_id", &ai_train::ModelBlob::round_id);

    // 再绑定包装类（不声明继承关系），这些是在Python中实际使用的类
    py::class_<TrainCmdWrapper>(m, "TrainCmd")
        .def(py::init<>())
        .def_readwrite("round_id", &TrainCmdWrapper::round_id)
        .def_readwrite("subset_size", &TrainCmdWrapper::subset_size)
        .def_readwrite("epochs", &TrainCmdWrapper::epochs)
        .def_readwrite("lr", &TrainCmdWrapper::lr)
        .def_readwrite("seed", &TrainCmdWrapper::seed);

    py::class_<ClientUpdateWrapper>(m, "ClientUpdate")
        .def(py::init<>())
        .def_readwrite("client_id", &ClientUpdateWrapper::client_id)
        .def_readwrite("round_id", &ClientUpdateWrapper::round_id)
        .def_readwrite("num_samples", &ClientUpdateWrapper::num_samples)
        // 数据属性使用property方式绑定，支持Python bytes类型
        .def_property(
            "data",
            [](const ClientUpdateWrapper &self)
            { return bytes_to_py(self.data); },
            [](ClientUpdateWrapper &self, const py::bytes &b)
            { py_to_bytes(b, self.data); });

    py::class_<ModelBlobWrapper>(m, "ModelBlob")
        .def(py::init<>())
        .def_readwrite("round_id", &ModelBlobWrapper::round_id)
        // 数据属性使用property方式绑定，支持Python bytes类型
        .def_property(
            "data",
            [](const ModelBlobWrapper &self)
            { return bytes_to_py(self.data); },
            [](ModelBlobWrapper &self, const py::bytes &b)
            { py_to_bytes(b, self.data); });

    // 封装序列类型，提供序列操作功能
    bind_sequence_mapped<ai_train::TrainCmdSeq, ai_train::TrainCmd, TrainCmdWrapper>(m, "TrainCmdSeq");
    bind_sequence_mapped<ai_train::ClientUpdateSeq, ai_train::ClientUpdate, ClientUpdateWrapper>(m, "ClientUpdateSeq");
    bind_sequence_mapped<ai_train::ModelBlobSeq, ai_train::ModelBlob, ModelBlobWrapper>(m, "ModelBlobSeq");

    // 封装读写器，提供数据读写功能
    bind_datawriter<ai_train::TrainCmdDataWriter, ai_train::TrainCmd, TrainCmdWrapper, TrainCmdDataWriterDeleter>(m, "TrainCmdDataWriter");
    bind_datawriter<ai_train::ClientUpdateDataWriter, ai_train::ClientUpdate, ClientUpdateWrapper, ClientUpdateDataWriterDeleter>(m, "ClientUpdateDataWriter");
    bind_datawriter<ai_train::ModelBlobDataWriter, ai_train::ModelBlob, ModelBlobWrapper, ModelBlobDataWriterDeleter>(m, "ModelBlobDataWriter");

    bind_datareader<ai_train::TrainCmdDataReader, ai_train::TrainCmd, ai_train::TrainCmdSeq, TrainCmdWrapper, TrainCmdDataReaderDeleter>(m, "TrainCmdDataReader");
    bind_datareader<ai_train::ClientUpdateDataReader, ai_train::ClientUpdate, ai_train::ClientUpdateSeq, ClientUpdateWrapper, ClientUpdateDataReaderDeleter>(m, "ClientUpdateDataReader");
    bind_datareader<ai_train::ModelBlobDataReader, ai_train::ModelBlob, ai_train::ModelBlobSeq, ModelBlobWrapper, ModelBlobDataReaderDeleter>(m, "ModelBlobDataReader");

    // 绑定转换函数
    m.def("as_train_cmd_datawriter", &as_train_cmd_datawriter);
    m.def("as_client_update_datawriter", &as_client_update_datawriter);
    m.def("as_model_blob_datawriter", &as_model_blob_datawriter);

    m.def("as_train_cmd_datareader", &as_train_cmd_datareader);
    m.def("as_client_update_datareader", &as_client_update_datareader);
    m.def("as_model_blob_datareader", &as_model_blob_datareader);

    // SampleInfo 封装
    py::class_<DDS_SampleInfo>(m, "SampleInfo")
        .def_readonly("sample_state", &DDS_SampleInfo::sample_state)
        .def_readonly("view_state", &DDS_SampleInfo::view_state)
        .def_readonly("instance_state", &DDS_SampleInfo::instance_state)
        .def_readonly("source_timestamp", &DDS_SampleInfo::source_timestamp)
        .def_readonly("write_sequence_number", &DDS_SampleInfo::write_sequence_number)
        .def_readonly("instance_handle", &DDS_SampleInfo::instance_handle)
        .def_readonly("publication_handle", &DDS_SampleInfo::publication_handle)
        .def_readonly("disposed_generation_count", &DDS_SampleInfo::disposed_generation_count)
        .def_readonly("no_writers_generation_count", &DDS_SampleInfo::no_writers_generation_count)
        .def_readonly("sample_rank", &DDS_SampleInfo::sample_rank)
        .def_readonly("generation_rank", &DDS_SampleInfo::generation_rank)
        .def_readonly("absolute_generation_rank", &DDS_SampleInfo::absolute_generation_rank)
        .def_readonly("valid_data", &DDS_SampleInfo::valid_data)
        .def_readonly("recive_locator", &DDS_SampleInfo::recive_locator)
        .def_readonly("recive_order", &DDS_SampleInfo::recive_order)
        .def_readonly("is_batch_end", &DDS_SampleInfo::is_batch_end);

    // SampleInfoSeq封装
    bind_sequence_mapped<DDS_SampleInfoSeq, DDS_SampleInfo, DDS_SampleInfo>(m, "SampleInfoSeq");

    m.attr("ANY_SAMPLE_STATE") = DDS::ANY_SAMPLE_STATE;
    m.attr("READ_SAMPLE_STATE") = DDS::READ_SAMPLE_STATE;
    m.attr("NOT_READ_SAMPLE_STATE") = DDS::NOT_READ_SAMPLE_STATE;

    m.attr("ANY_VIEW_STATE") = DDS::ANY_VIEW_STATE;
    m.attr("NEW_VIEW_STATE") = DDS::NEW_VIEW_STATE;
    m.attr("NOT_NEW_VIEW_STATE") = DDS::NOT_NEW_VIEW_STATE;

    m.attr("ANY_INSTANCE_STATE") = DDS::ANY_INSTANCE_STATE;
    m.attr("ALIVE_INSTANCE_STATE") = DDS::ALIVE_INSTANCE_STATE;
    m.attr("DISPOSED_INSTANCE_STATE") = DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE;
    m.attr("NO_WRITERS_INSTANCE_STATE") = DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE;

    py::class_<DDS::ReadCondition, PyReadCondition, std::shared_ptr<DDS::ReadCondition>>(m, "ReadCondition")
        .def("get_datareader", &DDS::ReadCondition::get_datareader, py::return_value_policy::reference)
        .def("get_sample_state_mask", &DDS::ReadCondition::get_sample_state_mask)
        .def("get_view_state_mask", &DDS::ReadCondition::get_view_state_mask)
        .def("get_instance_state_mask", &DDS::ReadCondition::get_instance_state_mask);

    py::class_<DDS::WaitSet>(m, "WaitSet")
        .def(py::init<>()) // 构造函数
        // attach_condition
        .def("attach_condition", [](DDS::WaitSet &self, DDS::Condition *cond)
             { return self.attach_condition(cond); }, py::arg("condition"))
        // detach_condition
        .def("detach_condition", [](DDS::WaitSet &self, DDS::Condition *cond)
             { return self.detach_condition(cond); }, py::arg("condition"))
        // wait
        .def("wait", [](DDS::WaitSet &self, DDS::ConditionSeq &seq, const DDS::Duration_t &timeout)
             { return self.wait(seq, timeout); }, py::arg("active_conditions"), py::arg("timeout"))
        // get_conditions
        .def("get_conditions", [](DDS::WaitSet &self, DDS::ConditionSeq &seq)
             { return self.get_conditions(seq); }, py::arg("attached_conditions"));
}