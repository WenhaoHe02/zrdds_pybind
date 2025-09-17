# test_project1_basic.py
import PyddsCore as Project1
from RegisterType import register_all_types
def main():
    # 1. 获取工厂实例
    factory = Project1.DomainParticipantFactory.get_instance()
    print("✅ Got DomainParticipantFactory:", factory)

    # 2. 创建 DomainParticipant
    participant = factory.create_participant(
        0,  # domain id
        Project1.DOMAINPARTICIPANT_QOS_DEFAULT,  # 使用默认 QoS
        None,
        0
    )
    print("✅ Created DomainParticipant:", participant)

    # 3. 创建 Publisher
    publisher = participant.create_publisher(
        Project1.PUBLISHER_QOS_DEFAULT,
        None,
        0
    )
    print("✅ Created Publisher:", publisher)

    # 4. 创建 Subscriber
    subscriber = participant.create_subscriber(
        Project1.SUBSCRIBER_QOS_DEFAULT,
        None,
        0
    )
    print("✅ Created Subscriber:", subscriber)



    register_all_types(participant)

    # 5. 创建 Topic
    topic = participant.create_topic(
        "TrainTopic",
        "TrainCmd",  
        Project1.TOPIC_QOS_DEFAULT,
        None,
        0
    )
    print("✅ Created Topic:", topic)

if __name__ == "__main__":
    main()
