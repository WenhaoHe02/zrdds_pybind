import ctypes
from typing import Any
try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")

class Py_PublisherListener(DDS_Listeners.PublisherListener):
    def __init__(self, name: str = "MyPublisherListener"):
        super().__init__()
        self.name = name
        self.matched_writers = []

    def on_publication_matched(self, writer: ctypes.c_void_p, status: Any) -> None:
        """重写发布匹配回调"""
        print(f"[{self.name}] 发布者匹配: writer={writer}, 当前匹配数={status.current_count}")
        self.matched_writers.append(writer)

    def on_offered_deadline_missed(self, writer: ctypes.c_void_p, status: Any) -> None:
        """重写期限错过回调"""
        print(f"[{self.name}] 数据未及时发布: writer={writer}, 总错过次数={status.total_count}")

    def __repr__(self) -> str:
        return f"<MyPublisherListener name={self.name}, matched_writers={len(self.matched_writers)}>"
    

    
    ### 测试函数 ###
def test_publisher_listener():
    # 创建监听器实例
    listener = Py_PublisherListener("TestPubListener")

    # 模拟DDS回调事件
    mock_writer = ctypes.c_void_p(0x1234)
    mock_status = type("Status", (), {"current_count": 2, "total_count": 1})()  # 动态创建状态对象

    # 触发回调
    print("--- 模拟发布者事件 ---")
    listener.on_publication_matched(mock_writer, mock_status)
    listener.on_offered_deadline_missed(mock_writer, mock_status)

    # 验证内部状态
    print("\n--- 检查监听器状态 ---")
    print(listener)
    assert len(listener.matched_writers) == 1

if __name__ == "__main__":
    test_publisher_listener()