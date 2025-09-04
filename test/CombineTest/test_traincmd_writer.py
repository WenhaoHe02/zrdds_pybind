# 测试应用层 write
from DDS_Core import DomainParticipantFactory
from DDS_Train_DataStructure import TrainCmd, TrainCmdDataWriter

# 1. 获取工厂 & 创建 DomainParticipant
factory = DomainParticipantFactory.get_instance()
participant = factory.create_participant(
    0,  # domain id
    -1, # DOMAINPARTICIPANT_QOS_DEFAULT
    None, 0
)

# 2. 创建 Publisher
publisher = participant.create_publisher(-1, None, 0)

# 3. 注册类型 & 创建 Topic
# 通常需要调用类型支持类（由 IDL 生成），比如：
#   ai_train.TrainCmdTypeSupport.register_type(participant, "TrainCmd")
# 这里我用伪代码，具体取决于你生成的 TypeSupport 名称
from RegisterType import register_all_types

register_all_types(participant)  

topic = participant.create_topic(
    "TrainCmdTopic",
    "TrainCmd",
    -1, None, 0
)

# 4. 创建 DataWriter（注意：返回的是 TrainCmdDataWriter 而不是裸 DataWriter）
# writer = publisher.create_datawriter(topic, -1, None, 0)


# print(type(writer))  # 应该是 <class 'dds_pybindings.TrainCmdDataWriter'>
# writer = TrainCmdDataWriter.__cast__(writer)  # 这里需要把基类 DataWriter 转为具体类型

# 5. 构造 TrainCmd 消息
cmd = TrainCmd()
cmd.round_id = 1
cmd.subset_size = 128
cmd.epochs = 10
cmd.lr = 0.01
cmd.seed = 1234

print(participant.delete_topic(topic))
