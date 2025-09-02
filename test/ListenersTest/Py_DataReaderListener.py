import ctypes
try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")
from typing import Any
from dataclasses import dataclass

@dataclass
class SampleInfo:
    source_timestamp: float
    valid_data: bool

class Py_DataReaderListener(DDS_Listeners.DataReaderListener):
    def __init__(self, name: str = "MyReaderListener"):
        super().__init__()
        self.name = name
        self.sample_count = 0
        self.matched_writers = set()

    def on_data_available(self, reader: ctypes.c_void_p) -> None:
        """数据到达时的回调（必须重写）"""
        self.sample_count += 1
        print(f"[{self.name}] 数据到达事件 #{self.sample_count} (reader={reader})")
        
        # 模拟读取数据（实际项目需调用take()/read()）
        samples = self._mock_read_samples(reader)
        self._process_samples(samples)

    def on_subscription_matched(self, reader: ctypes.c_void_p, status: Any) -> None:
        """当与DataWriter匹配状态变化时触发"""
        writer_id = status.last_publication_handle
        if status.current_count_change > 0:
            self.matched_writers.add(writer_id)
            print(f"[{self.name}] 匹配新Writer: ID={writer_id}, 总数={status.current_count}")
        else:
            self.matched_writers.discard(writer_id)
            print(f"[{self.name}] Writer断开: ID={writer_id}, 剩余={status.current_count}")

    def on_requested_deadline_missed(self, reader: ctypes.c_void_p, status: Any) -> None:
        """数据未在截止时间内到达"""
        print(f"[{self.name}] 数据延迟! reader={reader}, 总延迟次数={status.total_count}")

    def _mock_read_samples(self, reader: ctypes.c_void_p) -> list[tuple[str, SampleInfo]]:
        """模拟读取数据样本（返回样本数据+元信息）"""
        return [
            (f"Data_{hex(reader.value)[-4:]}_1", SampleInfo(16777216.0, True)),
            (f"Data_{hex(reader.value)[-4:]}_2", SampleInfo(16777217.0, False))
        ]

    def _process_samples(self, samples: list[tuple[str, SampleInfo]]) -> None:
        """处理读取到的样本"""
        for data, info in samples:
            status = "有效" if info.valid_data else "无效"
            print(f"  处理样本: {data} (时间戳={info.source_timestamp}, 状态={status})")

    def __repr__(self) -> str:
        return f"<MyDataReaderListener name={self.name}, 接收样本={self.sample_count}>"
    


    
    ### 测试函数 ###
def test_datareader_listener():
    # 创建监听器实例
    listener = Py_DataReaderListener("TestReaderListener")

    # 模拟DDS回调事件
    mock_reader = ctypes.c_void_p(0x5678)
    mock_status = type("Status", (), {
        "current_count": 3,
        "current_count_change": 1,
        "last_publication_handle": 2001,
        "total_count": 2
    })()

    print("--- 模拟DataReader事件 ---")
    listener.on_data_available(mock_reader)  # 数据到达
    listener.on_subscription_matched(mock_reader, mock_status)  # 匹配事件
    listener.on_requested_deadline_missed(mock_reader, mock_status)  # 延迟事件

    # 验证内部状态
    print("\n--- 检查监听器状态 ---")
    print(listener)
    assert listener.sample_count == 1
    assert len(listener.matched_writers) == 1

if __name__ == "__main__":
    test_datareader_listener()