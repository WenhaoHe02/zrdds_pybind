import ctypes
try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")
    
from typing import Any

class Py_SubscriberListener(DDS_Listeners.SubscriberListener):
    def __init__(self, name: str = "MySubListener"):
        super().__init__()
        self.name = name
        self.data_count = 0
        self.sample_storage = []

    def on_data_available(self, reader: ctypes.c_void_p) -> None:
        """数据到达时的回调（必须重写）"""
        self.data_count += 1
        print(f"[{self.name}] 数据到达事件 #{self.data_count} (reader={reader})")
        
        # 模拟从reader读取数据（实际需调用take()/read()）
        sample = self._mock_read_sample(reader)
        self.sample_storage.append(sample)

    def on_requested_deadline_missed(self, reader: ctypes.c_void_p, status: Any) -> None:
        """订阅期限错过回调"""
        print(f"[{self.name}] 数据未及时到达! reader={reader}, 总错过次数={status.total_count}")

    def _mock_read_sample(self, reader: ctypes.c_void_p) -> str:
        """模拟读取数据（实际项目需对接DDS API）"""
        return f"Sample from reader_{hex(reader.value)}"

    def __repr__(self) -> str:
        return f"<MySubscriberListener name={self.name}, received={self.data_count} samples>"
    

    
    ### 测试函数 ###
def test_subscriber_listener():
    # 创建监听器实例
    listener = Py_SubscriberListener("TestSubListener")

    # 模拟DDS回调事件
    mock_reader = ctypes.c_void_p(0x5678)
    mock_status = type("Status", (), {"total_count": 3})()  # 动态创建状态对象

    print("--- 模拟订阅者事件 ---")
    listener.on_data_available(mock_reader)  # 第一次数据到达
    listener.on_data_available(ctypes.c_void_p(0x9ABC))  # 第二次不同reader
    listener.on_requested_deadline_missed(mock_reader, mock_status)

    # 验证数据存储
    print("\n--- 检查监听器状态 ---")
    print(listener)
    print("存储的样本:", listener.sample_storage)
    assert listener.data_count == 2

if __name__ == "__main__":
    test_subscriber_listener()