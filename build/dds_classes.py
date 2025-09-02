class WorkerResult:
    """
    WorkerResult类表示一个工作结果，包含批次ID、模型ID和工作ID。
    这是C++中WorkerResult结构体的Python版本。
    """
    
    def __init__(self, batch_id="", model_id="", worker_id=""):
        """
        初始化WorkerResult实例
        
        Args:
            batch_id (str): 批次ID
            model_id (str): 模型ID
            worker_id (str): 工作ID
        """
        self.batch_id = batch_id
        self.model_id = model_id
        self.worker_id = worker_id
        # self.results = []  # 对应C++中的WorkerTaskResultSeq，可根据需要启用
    
    def __repr__(self):
        return f"WorkerResult(batch_id='{self.batch_id}', model_id='{self.model_id}', worker_id='{self.worker_id}')"
    
    def __str__(self):
        return f"WorkerResult(batch_id={self.batch_id}, model_id={self.model_id}, worker_id={self.worker_id})"


class Claim:
    """
    Claim类表示一个声明，包含批次ID、工作ID和队列长度。
    这是C++中Claim结构体的Python版本。
    """
    
    def __init__(self, batch_id="", worker_id="", queue_length=0):
        """
        初始化Claim实例
        
        Args:
            batch_id (str): 批次ID
            worker_id (str): 工作ID
            queue_length (int): 队列长度
        """
        self.batch_id = batch_id
        self.worker_id = worker_id
        self.queue_length = queue_length
    
    def __repr__(self):
        return f"Claim(batch_id='{self.batch_id}', worker_id='{self.worker_id}', queue_length={self.queue_length})"
    
    def __str__(self):
        return f"Claim(batch_id={self.batch_id}, worker_id={self.worker_id}, queue_length={self.queue_length})"