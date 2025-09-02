try:

    import DDS_TypeSupports as dds_typesupport
    print("[SUCCESS] DDS_TypeSupport module imported successfully")

except ImportError as e:
    print(f"[FAILED] Failed to import DDS_DataReaderListener module: {e}")
    exit(1)

# import ctypes

# def test_listener_base():
#     """测试基类 Listener 的实例化"""
#     listener = dds_listener.Listener()
#     print(f"[PASS] Listener base class created: {listener}")

# def test_data_writer_listener():
#     """测试 DataWriterListener 回调"""
#     class MyDataWriterListener(dds_listener.DataWriterListener):
#         def on_publication_matched(self, writer, status):
#             print(f"  [CALLBACK] on_publication_matched - Writer: {writer}, Status: {status}")

#     listener = MyDataWriterListener()
#     # 模拟回调（实际由DDS触发）
#     listener.on_publication_matched(ctypes.c_void_p(0x1234), type("Status", (), {"current_count": 1}))
#     print("[PASS] DataWriterListener test")

# def test_data_reader_listener():
#     """测试 DataReaderListener 回调"""
#     class MyDataReaderListener(dds_listener.DataReaderListener):
#         def on_data_available(self, reader):
#             print(f"  [CALLBACK] on_data_available - Reader: {reader}")

#     listener = MyDataReaderListener()
#     listener.on_data_available(ctypes.c_void_p(0x5678))
#     print("[PASS] DataReaderListener test")

# def test_topic_listener():
#     """测试 TopicListener 回调"""
#     class MyTopicListener(dds_listener.TopicListener):
#         def on_inconsistent_topic(self, topic, status):
#             print(f"  [CALLBACK] on_inconsistent_topic - Topic: {topic}, Status: {status}")

#     listener = MyTopicListener()
#     listener.on_inconsistent_topic(ctypes.c_void_p(0xABCD), type("Status", (), {"total_count": 2}))
#     print("[PASS] TopicListener test")

# def test_publisher_listener():
#     """测试 PublisherListener 继承链"""
#     class MyPublisherListener(dds_listener.PublisherListener):
#         def on_publication_matched(self, writer, status):
#             print(f"  [CALLBACK] PublisherListener::on_publication_matched - Writer: {writer}")

#     listener = MyPublisherListener()
#     listener.on_publication_matched(ctypes.c_void_p(0x1111), None)
#     print("[PASS] PublisherListener test")

# def test_subscriber_listener():
#     """测试 SubscriberListener 回调"""
#     class MySubscriberListener(dds_listener.SubscriberListener):
#         def on_data_on_readers(self, subscriber):
#             print(f"  [CALLBACK] on_data_on_readers - Subscriber: {subscriber}")

#     listener = MySubscriberListener()
#     listener.on_data_on_readers(ctypes.c_void_p(0x2222))
#     print("[PASS] SubscriberListener test")

# def test_domain_participant_listener():
#     """测试 DomainParticipantListener 多继承"""
#     class MyDomainListener(dds_listener.DomainParticipantListener):
#         def on_domain_received(self, domain_id):
#             print(f"  [CALLBACK] on_domain_received - Domain ID: {domain_id}")
#         def on_data_available(self, reader):  # 继承自 SubscriberListener
#             print(f"  [CALLBACK] DomainParticipantListener::on_data_available - Reader: {reader}")

#     listener = MyDomainListener()
#     listener.on_domain_received(123)
#     listener.on_data_available(ctypes.c_void_p(0x3333))
#     print("[PASS] DomainParticipantListener test")

# if __name__ == "__main__":
#     test_listener_base()
#     test_data_writer_listener()
#     test_data_reader_listener()
#     test_topic_listener()
#     test_publisher_listener()
#     test_subscriber_listener()
#     test_domain_participant_listener()
#     print("All tests passed!")