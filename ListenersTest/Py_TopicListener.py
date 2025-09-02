import ctypes
try:    
    import DDS_Listeners
except ImportError:
    print("DDS_Listeners 模块未找到，请确保 pyds 已正确安装。")
    
from typing import Any
from dataclasses import dataclass

@dataclass
class InconsistentTopicStatus:
    total_count: int
    last_reason: str

class Py_TopicListener(DDS_Listeners.TopicListener):
    def __init__(self, name: str = "MyTopicListener"):
        super().__init__()
        self.name = name
        self.inconsistent_events = []
        self.qos_conflicts = 0

    def on_inconsistent_topic(self, topic: ctypes.c_void_p, status: Any) -> None:
        """当检测到主题不一致时触发（必须重写）"""
        reason = self._parse_reason(status.last_reason_code)
        event = InconsistentTopicStatus(
            total_count=status.total_count,
            last_reason=reason
        )
        self.inconsistent_events.append(event)
        print(f"[{self.name}] 主题不一致! 原因: {reason}, 累计次数: {status.total_count}")

    def on_qos_alert(self, topic: ctypes.c_void_p, status: Any) -> None:
        """自定义QoS告警处理（示例方法）"""
        self.qos_conflicts += 1
        print(f"[{self.name}] QoS告警 #{self.qos_conflicts} (topic={topic})")

    def _parse_reason(self, code: int) -> str:
        """将错误码转换为可读信息"""
        reasons = {
            0: "TOPIC_TYPE_MISMATCH",
            1: "TOPIC_NAME_MISMATCH",
            2: "QOS_INCOMPATIBLE"
        }
        return reasons.get(code, f"UNKNOWN_CODE_{code}")

    def __repr__(self) -> str:
        return f"<MyTopicListener name={self.name}, 不一致事件数={len(self.inconsistent_events)}>"


### 测试函数 ###
def test_topic_listener():
    # 创建监听器实例
    listener = Py_TopicListener("TestTopicListener")

    # 模拟DDS回调事件
    mock_topic = ctypes.c_void_p(0xABCD)
    mock_status = type("Status", (), {
        "total_count": 2,
        "last_reason_code": 0  # 假设0表示类型不匹配
    })()

    print("--- 模拟Topic事件 ---")
    listener.on_inconsistent_topic(mock_topic, mock_status)  # 主题不一致
    listener.on_qos_alert(mock_topic, None)  # 自定义QoS告警

    # 验证内部状态
    print("\n--- 检查监听器状态 ---")
    print(listener)
    print("最近不一致原因:", listener.inconsistent_events[-1].last_reason)
    assert len(listener.inconsistent_events) == 1
    assert listener.qos_conflicts == 1

if __name__ == "__main__":
    test_topic_listener()