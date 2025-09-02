import ctypes
try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")
from typing import Any

class Py_Listener(DDS_Listeners.Listener):
    """通用监听器基类，提供公共日志和状态跟踪"""
    def __init__(self, name: str = "BaseListener"):
        super().__init__()
        self.name = name
        self.event_count = 0

    def _log_event(self, event_type: str, source: ctypes.c_void_p) -> None:
        """通用事件日志方法"""
        self.event_count += 1
        print(f"[{self.name}] 事件#{self.event_count}: {event_type} (source={source})")

    def __repr__(self) -> str:
        return f"<Py_Listener name={self.name}, 事件总数={self.event_count}>"
    

class MyCompositeListener(Py_Listener, DDS_Listeners.DataReaderListener):
    """组合监听器：同时继承基类功能和具体监听器"""
    def on_data_available(self, reader: ctypes.c_void_p) -> None:
        self._log_event("DATA_AVAILABLE", reader)
        print("  处理数据...")

    def on_requested_deadline_missed(self, reader: ctypes.c_void_p, status: Any) -> None:
        self._log_event("DEADLINE_MISSED", reader)
        print(f"  错过截止时间! 总次数={status.total_count}")

class DebugListener(Py_Listener):
    """仅用于调试的基础监听器"""
    def on_all(self, event_type: str, source: ctypes.c_void_p, *args) -> None:
        """捕获所有未处理的回调（需C++绑定支持）"""
        self._log_event(f"UNHANDLED_{event_type}", source)
        print(f"  未处理参数: {args}")

### 测试函数 ###
def test_base_listener():
    # 测试组合监听器
    composite = MyCompositeListener("CompositeDemo")
    mock_reader = ctypes.c_void_p(0x1234)
    mock_status = type("Status", (), {"total_count": 3})()

    print("--- 测试组合监听器 ---")
    composite.on_data_available(mock_reader)
    composite.on_requested_deadline_missed(mock_reader, mock_status)
    print(composite)

    # 测试调试监听器（需绑定支持）
    if hasattr(DebugListener, 'on_all'):
        debug = DebugListener("DebugDemo")
        print("\n--- 测试调试监听器 ---")
        debug.on_all("CUSTOM_EVENT", ctypes.c_void_p(0x5678), "extra_arg")
        print(debug)

if __name__ == "__main__":
    test_base_listener()