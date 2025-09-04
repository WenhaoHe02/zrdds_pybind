

import DDS_Listeners
import DDS_Train_DataStructure as dds
import DDS_Core
import struct
import time
import Project1


# 自定义 Python listener
class MyListener(DDS_Listeners.DataReaderListener):
    def __init__(self):
        super().__init__()
    def on_data_available(self, reader):
        print("接收到数据！")
        # 这里 reader 已经是绑定过的 DataReader 指针
        trainCmdSeq = dds.TrainCmdSeq()     # 假设已经通过 pybind 暴露 ShapeTypeSeq
        sampleInfoSeq = dds.SampleInfoSeq()


        # 调用 take
        rtn = reader.take(
            trainCmdSeq,
            sampleInfoSeq,
            10,
            dds.ANY_SAMPLE_STATE,
            dds.ANY_VIEW_STATE,
            dds.ANY_INSTANCE_STATE
        )

        if rtn != dds.OK:
            print("take 函数失败")
            return

        # 遍历数据
        for i in range(trainCmdSeq.length()):
            received_cmd = trainCmdSeq.get_at(i)
            if not sampleInfoSeq.get_at(i).valid_data:
                continue
            print("Received:")
            print("  cmd_id:", received_cmd.round_id)
            print("  subset_size:", received_cmd.subset_size)

        # 返还 loan
        try:
            rtn = reader.return_loan(trainCmdSeq, sampleInfoSeq)
            if rtn != dds.OK:
                print("return loan failed")
            else:
                print("返还 loan 成功")
        except Exception as e:
            print("return loan failed", e)

def init():
        # 从工厂创建DomainParticipant
    factory = DDS_Core.DomainParticipantFactory.get_instance()
    participant = factory.create_participant(0, DDS_Core.DOMAINPARTICIPANT_QOS_DEFAULT, None, 0)
    if participant is None:
        print("创建DomainParticipant失败")
        return
    
    print("成功创建DomainParticipant")
    Project1.register_all_types(participant)
    
    # 创建Publisher和Subscriber
    publisher = participant.create_publisher(DDS_Core.PUBLISHER_QOS_DEFAULT, None, 0)
    if publisher is None:
        print("创建Publisher失败")
        return
        
    subscriber = participant.create_subscriber(DDS_Core.SUBSCRIBER_QOS_DEFAULT, None, 0)
    if subscriber is None:
        print("创建Subscriber失败")
        return
    
    print("成功创建Publisher和Subscriber")
    
    # 使用base_bindings中已定义的类型进行测试
    # 创建Topic (使用WorkerResult类型，该类型在base_bindings中已定义)
    topic = participant.create_topic("TrainCmd", "TrainCmd", DDS_Core.TOPIC_QOS_DEFAULT, None, 0)
    if topic is None:
        print("创建Topic失败 - TrainCmd类型可能未在DDS中注册")
    else:
        print("成功创建Topic")
    # # 使用Subscriber创建DataReader
    # reader = subscriber.create_datareader(topic, DDS_Core.DATAREADER_QOS_DEFAULT, None, 0)
    # if reader is None:
    #     print("创建DataReader失败")
    # else:
    #     print("成功创建DataReader")
    #     print("Reader类型:", type(reader))

    # 创建监听器
    listener = MyListener()
    # 创建带监听器的reader
    reader_with_listener = subscriber.create_datareader(topic, DDS_Core.DATAREADER_QOS_DEFAULT, listener, 1024)
    if reader_with_listener is None:
        print("创建带监听器的DataReader失败")
    else:
        print("成功创建带监听器的DataReader")

    while True:
        time.sleep(5)
        print("正在监听数据...")




if __name__ == "__main__":
    init()