import ctypes
try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")
from typing import Any

class Py_DataWriter(DDS_Listeners.DataWriterListener):
    def __init__(self, name: str = "MyWriterListener"):
        super().__init__()
        self.name = name
        self.matched_readers = set()
        self.deadline_misses = 0

    def on_publication_matched(self, writer: ctypes.c_void_p, status: Any) -> None:
        """当DataWriter与远端DataReader匹配时触发"""
        reader_id = status.last_subscription_handle  # 假设status包含读者ID
        if status.current_count_change > 0:
            self.matched_readers.add(reader_id)
            print(f"[{self.name}] 匹配新Reader: ID={reader_id}, 当前匹配数={status.current_count}")
        else:
            self.matched_readers.discard(reader_id)
            print(f"[{self.name}] Reader断开: ID={reader_id}, 剩余匹配数={status.current_count}")

    def on_offered_deadline_missed(self, writer: ctypes.c_void_p, status: Any) -> None:
        """未能按时发布数据时触发"""
        self.deadline_misses += 1
        print(f"[{self.name}] 期限错过! writer={writer}, 总次数={self.deadline_misses}")

    def on_offered_incompatible_qos(self, writer: ctypes.c_void_p, status: Any) -> None:
        """QoS不兼容时触发"""
        print(f"[{self.name}] QoS不兼容! 策略ID={status.policy_id}, 冲突数={status.count}")

    def __repr__(self) -> str:
        return f"<MyDataWriterListener name={self.name}, 匹配读者数={len(self.matched_readers)}>"
    

    
    ### 测试函数 ###
def test_datawriter_listener():
    # 创建监听器实例
    listener = Py_DataWriter("TestWriterListener")

    # 模拟DDS回调事件
    mock_writer = ctypes.c_void_p(0x1234)
    mock_status = type("Status", (), {
        "current_count": 2,
        "current_count_change": 1,
        "last_subscription_handle": 1001,
        "policy_id": 1,
        "count": 3
    })()

    print("--- 模拟DataWriter事件 ---")
    listener.on_publication_matched(mock_writer, mock_status)  # 匹配事件
    listener.on_offered_deadline_missed(mock_writer, None)     # 期限错过
    listener.on_offered_incompatible_qos(mock_writer, mock_status)  # QoS冲突

    # 验证内部状态
    print("\n--- 检查监听器状态 ---")
    print(listener)
    assert len(listener.matched_readers) == 1
    assert listener.deadline_misses == 1

if __name__ == "__main__":
    test_datawriter_listener()