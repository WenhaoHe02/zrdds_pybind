import Project1
import traceback

def log_success(msg):
    print(f"[SUCCESS] {msg}")

def log_fail(msg, e=None):
    print(f"[FAILED] {msg}")
    if e:
        print("    -> Exception:", e)
        traceback.print_exc()


# Mock 数据类型
class WorkerResult:
    def __init__(self, batch_id="b1", model_id="m1", worker_id="w1"):
        self.batch_id = batch_id
        self.model_id = model_id
        self.worker_id = worker_id
        self.results = []


class Claim:
    def __init__(self, batch_id="b1", worker_id="w1", queue_length=5):
        self.batch_id = batch_id
        self.worker_id = worker_id
        self.queue_length = queue_length


if __name__ == "__main__":
    print("====== Project1 DDS Python 绑定流程测试 ======")


    print("===== QoS 默认常量检查 =====")
    print("DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT:", Project1.DOMAINPARTICIPANT_FACTORY_QOS_DEFAULT)
    print("DOMAINPARTICIPANT_QOS_DEFAULT:", Project1.DOMAINPARTICIPANT_QOS_DEFAULT)
    print("PUBLISHER_QOS_DEFAULT:", Project1.PUBLISHER_QOS_DEFAULT)
    print("SUBSCRIBER_QOS_DEFAULT:", Project1.SUBSCRIBER_QOS_DEFAULT)
    print("DATAWRITER_QOS_DEFAULT:", Project1.DATAWRITER_QOS_DEFAULT)
    print("DATAREADER_QOS_DEFAULT:", Project1.DATAREADER_QOS_DEFAULT)
    print("TOPIC_QOS_DEFAULT:", Project1.TOPIC_QOS_DEFAULT)
    print("DATAWRITER_QOS_USE_TOPIC_QOS:", Project1.DATAWRITER_QOS_USE_TOPIC_QOS)
    print("DATAREADER_QOS_USE_TOPIC_QOS:", Project1.DATAREADER_QOS_USE_TOPIC_QOS)

    try:
        # 1. 获取工厂
        factory = Project1.DomainParticipantFactory.get_instance()
        log_success("获取 DomainParticipantFactory 成功")
    except Exception as e:
        log_fail("获取 DomainParticipantFactory 失败", e)

    try:
        # 2. 创建 Participant
        # qos = Project1.DomainParticipantQos()
        qos=Project1.DOMAINPARTICIPANT_QOS_DEFAULT
        
        # result = factory.get_default_participant_qos(qos)
        participant = factory.create_participant(0, Project1.DOMAINPARTICIPANT_QOS_DEFAULT, None, 0)
        log_success("DomainParticipant 创建成功")
        print(type(participant))
    except Exception as e:
        log_fail("DomainParticipant 创建失败", e)

    try:
        # 3. 创建 Topic (成功)
        topic = participant.create_topic(
            "TestTopic", "WorkerResult", Project1.TOPIC_QOS_DEFAULT, None, 0
        )
        log_success("Topic 创建成功")
    except Exception as e:
        log_fail("Topic 创建失败", e)

    try:
        # 4. 创建 Topic (失败 - 传入非法参数)
        participant.create_topic(None, None, Project1.TopicQos())
        log_fail("Topic 创建失败用例未触发异常")
    except Exception:
        log_success("Topic 创建失败用例触发异常 ✔")

    try:
        # 5. 创建 Publisher / Subscriber
        publisher = participant.create_publisher(Project1.PUBLISHER_QOS_DEFAULT, None, 0)
        subscriber = participant.create_subscriber(Project1.SUBSCRIBER_QOS_DEFAULT, None, 0)
        log_success("Publisher / Subscriber 创建成功")
    except Exception as e:
        log_fail("Publisher / Subscriber 创建失败", e)
    try:
        # 6. 创建 DataWriter / DataReader
        writer = publisher.create_datawriter(topic, Project1.DATAWRITER_QOS_DEFAULT, None, 0)
        print(writer)
        reader = subscriber.create_datareader(topic, Project1.DATAREADER_QOS_DEFAULT, None, 0)
        log_success("DataWriter / DataReader 创建成功")
    except Exception as e:
        log_fail("DataWriter / DataReader 创建失败", e)

    try:
        # 7. Writer 写 WorkerResult (成功)
        wr_writer = publisher.create_datawriter(topic, Project1.DATAWRITER_QOS_DEFAULT, None, 0)
        data = WorkerResult("b1", "m1", "w1")
        handle = Project1.InstanceHandle_t()
        result = wr_writer.write(data, handle)
        if result == Project1.ReturnCode_t.DDS_RETCODE_OK:
            log_success("WorkerResultWriter 写入成功")
        else:
            log_fail(f"WorkerResultWriter 返回错误码 {result}")
    except Exception as e:
        log_fail("WorkerResultWriter 写入失败", e)

    # try:
    #     # 8. Writer 写 Claim (成功)
    #     cl_writer = Project1.ClaimWriter()
    #     data = Claim()
    #     handle = Project1.InstanceHandle_t()
    #     result = cl_writer.write(data, handle)
    #     if result == Project1.ReturnCode_t.DDS_RETCODE_OK:
    #         log_success("ClaimWriter 写入成功")
    #     else:
    #         log_fail(f"ClaimWriter 返回错误码 {result}")
    # except Exception as e:
    #     log_fail("ClaimWriter 写入失败", e)

    # try:
    #     # 9. Writer 写非法数据 (失败)
    #     cl_writer = Project1.ClaimWriter()
    #     result = cl_writer.write(None, None)
    #     if result != Project1.ReturnCode_t.DDS_RETCODE_OK:
    #         log_success("ClaimWriter 写入失败用例触发 ✔")
    #     else:
    #         log_fail("ClaimWriter 写入失败用例未触发异常")
    # except Exception:
    #     log_success("ClaimWriter 写入失败用例触发异常 ✔")

    # print("====== 测试完成 ======")
