# ZRDDS Python Bindings

Python bindings for ZRDDS (Zero-Runtime DDS) using pybind11.

## 默认参数调用说明

在创建DDS实体时，可以使用以下三种方式传递QoS参数：

### 1. 使用None（默认QoS）
```python
participant = factory.create_participant(domain_id, None, None, 0)
```

### 2. 使用-1（特殊标记值）
```python
participant = factory.create_participant(domain_id, -1, None, 0)
```

### 3. 使用预定义常量
```python
participant = factory.create_participant(
    domain_id, 
    Project1.DOMAINPARTICIPANT_QOS_DEFAULT, 
    None, 
    0
)
```

支持的预定义常量包括：
- `DOMAINPARTICIPANT_QOS_DEFAULT`
- `PUBLISHER_QOS_DEFAULT`
- `SUBSCRIBER_QOS_DEFAULT`
- `DATAWRITER_QOS_DEFAULT`
- `DATAREADER_QOS_DEFAULT`
- `TOPIC_QOS_DEFAULT`
- `DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT`

以上三种方式在功能上是等价的，都会使用DDS实体的默认QoS配置。