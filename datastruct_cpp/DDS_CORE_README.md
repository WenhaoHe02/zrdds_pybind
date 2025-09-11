# DDS_Core 模块接口文档

本模块通过 **pybind11** 封装 DDS C++ 接口，提供 Python 调用。

---

## 1. 基础类型 / 数据结构

### `DDS::StatusCondition`

- **说明**：状态条件对象（类型声明）

### `DDS::StatusKindMask`

- `__init__()`：默认构造

### `DDS_InstanceHandle_t`

- `__init__()`：默认构造
- `valid`：布尔值，可读写属性
- `value`：长度为 16 的字节数组

  - getter：返回 `list[int] (len=16)`
  - setter：传入 `list[int] (len=16)`，否则抛异常

### `DDS::ReturnCode_t`

- **说明**：返回码（类型声明）

### `DDS::DataReaderListener`

- **说明**：数据读取器监听器（类型声明）

### `DDS::DataReaderQos`

- `__init__()`：默认构造

### `DDS::SubscriptionMatchedStatus`

- `__init__()`：默认构造
- 属性：

  - `total_count: int`
  - `total_count_change: int`
  - `current_count: int`
  - `current_count_change: int`
  - `last_publication_handle: InstanceHandle_t`

### `DDS::SubscriberListener`

- **说明**：订阅者监听器（类型声明）

### `DDS::SubscriberQos`

- **说明**：订阅者 QoS（类型声明）

### `DDS::DomainParticipantListener`

- **说明**：参与者监听器（类型声明）

### `DDS::DomainParticipantQos`

- `__init__()`：默认构造

### `DDS::DomainParticipantFactoryQos`

- `__init__()`：默认构造

### `DDS::DataWriterListener`

- **说明**：数据写入器监听器（类型声明）

### `DDS::DataWriterQos`

- `__init__()`：默认构造

### `DDS::PublisherListener`

- `__init__()`：默认构造

### `DDS::PublisherQos`

- `__init__()`：默认构造

### `DDS::TopicListener`

- **说明**：主题监听器（类型声明）

### `DDS::TopicQos`

- `__init__()`：默认构造

---

## 2. 实体类（Entity）

### `DDS::Entity`

- `get_statuscondition() -> StatusCondition`
  获取状态条件
- `get_status_changes() -> int`
  获取状态变化标志
- `enable() -> ReturnCode_t`
  启用实体
- `get_instance_handle() -> InstanceHandle_t`
  获取实例句柄

### `DDS::Topic (Entity 继承)`

- **说明**：主题实体类型（无额外方法）

---

## 3. DataReader

### `DDS::DataReader (Entity 继承)`

- `enable() -> ReturnCode_t`
- `set_listener(listener=None, mask=0) -> ReturnCode_t`

  - `listener`: `DataReaderListener` 或 None
  - `mask`: int

- `get_subscription_matched_status() -> SubscriptionMatchedStatus`

  - 返回订阅匹配状态
  - 如果失败抛出异常

---

## 4. DataWriter

### `DDS::PublicationMatchedStatus`

- `__init__()`：默认构造
- 属性：

  - `total_count: int`
  - `total_count_change: int`
  - `current_count: int`
  - `current_count_change: int`
  - `last_subscription_handle: InstanceHandle_t`

### `DDS::DataWriter (Entity 继承)`

- `get_publication_matched_status() -> PublicationMatchedStatus`

  - 返回发布匹配状态
  - 如果失败抛出异常

---

## 5. Publisher

### `DDS::Publisher (Entity 继承)`

- `create_datawriter(the_topic, qoslist=None, a_listener=None, mask=0) -> DataWriter`

  - `the_topic`: `Topic*`
  - `qoslist`: `DataWriterQos` 或 None 或 -1 (默认 QoS)
  - `a_listener`: `DataWriterListener*` 或 None
  - `mask`: int

---

## 6. Subscriber

### `DDS::Subscriber (Entity 继承)`

- `create_datareader(a_topic, qoslist=None, a_listener=None, mask=0) -> DataReader`

  - `a_topic`: `Topic*`
  - `qoslist`: `DataReaderQos` 或 None 或 -1 (默认 QoS)
  - `a_listener`: `DataReaderListener*` 或 None
  - `mask`: int

---

## 7. DomainParticipant

### `DDS::DomainParticipant (Entity 继承)`

- `create_subscriber(qos=None, listener=None, mask=0) -> Subscriber`

  - `qos`: `SubscriberQos` 或 None 或 -1
  - `listener`: `SubscriberListener*` 或 None
  - `mask`: int

- `create_publisher(qoslist=None, a_listener=None, mask=0) -> Publisher`

  - `qoslist`: `PublisherQos` 或 None 或 -1
  - `a_listener`: `PublisherListener*` 或 None
  - `mask`: int

- `create_topic(topic_name: str, type_name: str, qoslist=None, a_listener=None, mask=0) -> Topic`

  - `topic_name`: string
  - `type_name`: string
  - `qoslist`: `TopicQos` 或 None 或 -1
  - `a_listener`: `TopicListener*` 或 None
  - `mask`: int

- `delete_topic(a_topic: Topic) -> ReturnCode_t`

---

## 8. DomainParticipantFactory

### `DDS::DomainParticipantFactory`

- `get_instance() -> DomainParticipantFactory` (静态方法)

- `get_instance_w_qos(qoslist: DomainParticipantFactoryQos) -> DomainParticipantFactory` (静态方法)

- `create_participant(domainId: int, qos=None, listener=None, mask=0) -> DomainParticipant`

  - `domainId`: int
  - `qos`: `DomainParticipantQos` 或 None 或 -1
  - `listener`: `DomainParticipantListener*` 或 None
  - `mask`: int

- `delete_participant(a_dp: DomainParticipant) -> ReturnCode_t`

- `get_default_participant_qos(qoslist: DomainParticipantQos) -> ReturnCode_t`

- `get_qos(qoslist: DomainParticipantFactoryQos) -> ReturnCode_t`

---

## 9. 常量绑定 (Python 层 sentinel 值)

- 可以传默认值，也可以填以下赋值
- `DOMAINPARTICIPANT_QOS_DEFAULT = -1`
- `DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT = -1`
- `PUBLISHER_QOS_DEFAULT = -1`
- `SUBSCRIBER_QOS_DEFAULT = -1`
- `DATAWRITER_QOS_DEFAULT = -1`
- `DATAREADER_QOS_DEFAULT = -1`
- `TOPIC_QOS_DEFAULT = -1`
- `DATAWRITER_QOS_USE_TOPIC_QOS = -2`
- `DATAREADER_QOS_USE_TOPIC_QOS = -2`

---
