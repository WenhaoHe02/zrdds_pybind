import DDS_All as dds
import RegisterType as Project1
import time


def init():
        # 从工厂创建DomainParticipant
    factory = dds.DomainParticipantFactory.get_instance()
    participant = factory.create_participant(0, dds.DOMAINPARTICIPANT_QOS_DEFAULT, None, 0)
    if participant is None:
        print("创建DomainParticipant失败")
        return
    
    print("成功创建DomainParticipant")
    Project1.register_all_types(participant)
    
    # 创建Publisher和Subscriber
    publisher = participant.create_publisher(dds.PUBLISHER_QOS_DEFAULT, None, 0)
    if publisher is None:
        print("创建Publisher失败")
        return
        
    subscriber = participant.create_subscriber(dds.SUBSCRIBER_QOS_DEFAULT, None, 0)
    if subscriber is None:
        print("创建Subscriber失败")
        return
    
    print("成功创建Publisher和Subscriber")
    
    # 使用base_bindings中已定义的类型进行测试
    # 创建Topic (使用WorkerResult类型，该类型在base_bindings中已定义)
    topic = participant.create_topic("TrainCmd", "TrainCmd", dds.TOPIC_QOS_DEFAULT, None, 0)
    if topic is None:
        print("创建Topic失败 - TrainCmd类型可能未在DDS中注册")
    else:
        print("成功创建Topic")

        # 使用Publisher创建DataWriter
    writer = publisher.create_datawriter(topic, dds.DATAWRITER_QOS_DEFAULT, None, 0)
    if writer is None:
        print("创建DataWriter失败")
    else:
        print("成功创建DataWriter")
        print("Writer类型:", type(writer))

        # 测试get_publication_matched_status
        status= writer.get_publication_matched_status()
        print("DataWriter的匹配状态:", status)
        print("当前匹配的订阅者数量:", status.current_count)
        
        # 创建 TrainCmd 对象
        train_cmd = dds.TrainCmd()
        train_cmd.round_id = 1
        train_cmd.subset_size = 100

        while True:
            time.sleep(2)
            # 发送消息
            writer.write(train_cmd)
            try:
                writer.write(train_cmd)
                print("成功发送WorkerResult消息")
            except Exception as e:
                print(f"发送WorkerResult消息失败: {e}")


if __name__ == "__main__":
    
    init()