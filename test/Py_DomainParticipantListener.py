try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")


import ctypes

class Py_DomainParticipantListener(DDS_Listeners.DomainParticipantListener):
    """具体Listener类，继承自DomainParticipantListener"""
    def __init__(self, name="MyListener"):
        super().__init__()
        self.name = name
        self.received_domains = []

    def on_domain_received(self, domain_id):
        """重写域接收回调"""
        print(f"[{self.name}] Received data from domain: {domain_id}")
        self.received_domains.append(domain_id)

    def on_data_available(self, reader):
        """重写数据到达回调（继承自SubscriberListener）"""
        print(f"[{self.name}] New data available from reader: {reader}")
        # 模拟从reader读取数据
        self._read_samples(reader)

    def _read_samples(self, reader):
        """模拟读取数据的内部方法"""
        print(f"  Processing data from reader {reader}...")
        # 实际应用中这里会调用take()/read()等DDS API

    def __repr__(self):
        return f"<MyConcreteListener name='{self.name}'>"
    


    
    ### 测试函数 ###
def test_concrete_listener():
    # 创建实例
    listener = Py_DomainParticipantListener("TestListener")

    # 模拟DDS回调触发
    print("--- Simulating DDS callbacks ---")
    listener.on_domain_received(123)  # 来自DomainParticipantListener
    listener.on_data_available(ctypes.c_void_p(0x1234))  # 来自SubscriberListener

    # 验证数据存储
    print("\n--- Checking internal state ---")
    print(f"Received domains: {listener.received_domains}")
    assert listener.received_domains == [123]

if __name__ == "__main__":
    test_concrete_listener()