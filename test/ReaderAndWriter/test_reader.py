import DDS_All as dds
import RegisterType as Project1

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
    # 使用Subscriber创建DataReader
    reader = subscriber.create_datareader(topic, dds.DATAREADER_QOS_DEFAULT, None, 0)
    if reader is None:
        print("创建DataReader失败")
    else:
        print("成功创建DataReader")
        print("Reader类型:", type(reader))

    try:
        readcondition=reader.create_readcondition(dds.ANY_SAMPLE_STATE,dds.ANY_VIEW_STATE,dds.ANY_INSTANCE_STATE)
    except Exception as e:
        print("创建ReadCondition失败，原因：",e)
    if readcondition is not None:
        print("成功创建ReadCondition")


    # 创建WaitSet
    waitset = dds.WaitSet()
    if waitset is not None:
        print("成功创建WaitSet")
    try:
        waitset.attach_condition(readcondition)
        print("成功将ReadCondition添加到WaitSet")
    except Exception as e:
        print("将ReadCondition添加到WaitSet失败，原因：",e)

    while True:
        conditionSeq=dds.ConditionSeq()
        if(conditionSeq is not None):
            print("成功创建ConditionSeq")
        else:
            print("创建ConditionSeq失败")

        duration = dds.DDS_Duration_t(10, 0)  # 10秒
        try:
            code=waitset.wait(conditionSeq, duration)
            print("WaitSet等待成功")
            if(code==dds.OK):
                print("WaitSet等待成功，有数据到达")
                readData(reader)
        except Exception as e:
            print("WaitSet等待失败，原因：",e)

def readData(reader: dds.TrainCmdDataReader):
    trainCmdSeq=dds.TrainCmdSeq()
    if(trainCmdSeq is not None):
        print("成功创建TrainCmdSeq")

    sampleInfoSeq=dds.SampleInfoSeq()
    if(sampleInfoSeq is not None):
        print("成功创建SampleInfoSeq")

    try:
        reader.take(trainCmdSeq, sampleInfoSeq, 10, dds.ANY_VIEW_STATE, dds.ANY_INSTANCE_STATE)
        print("成功调用take方法")
        for i in range(trainCmdSeq.length()):
            received_cmd = trainCmdSeq.get_at(i)
            if not sampleInfoSeq.get_at(i).valid_data:
                continue
            print("Received:")
            print("  cmd_id:", received_cmd.round_id)
            print("  subset_size:", received_cmd.subset_size)
    except Exception as e:
        print("take失败，原因：",e)

    # 返还 loan
    try:
        rtn = reader.return_loan(trainCmdSeq, sampleInfoSeq)
        if rtn != dds.OK:
            print("return loan failed")
        else:
            print("返还 loan 成功")
    except Exception as e:
        print("return loan failed", e)



if __name__ == "__main__":
    init()