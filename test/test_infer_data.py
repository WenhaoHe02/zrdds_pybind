import os, sys
zrdds_bin = r"C:\Program Files (x86)\ZRDDS\ZRDDS-2.4.4\bin"
os.add_dll_directory(zrdds_bin)  # Python 3.8+ 支持
import DDS_All
import dds_infer_pybindings as dds
import DDS_All 
import dds_infer_pybindings as dds
# === 你原来的对象构造与打印 ===
task = dds.Task()
task.request_id = "req_123"
task.task_id = "task_abc"
task.client_id = "client_xyz"
task.payload = b"hello_infer_payload"

print("Task 对象：")
print("  request_id:", task.request_id)
print("  task_id:", task.task_id)
print("  client_id:", task.client_id)
print("  payload (bytes):", task.payload)

task_seq = dds.TaskSeq()
task_seq.append(task)

print("\nTaskSeq 长度：", task_seq.length())
print("第一个 task_id：", task_seq.get_at(0).task_id)

task_list = dds.TaskList()
task_list.batch_id = "batch_001"
task_list.model_id = "model_alpha"
task_list.assigned_worker_id = "worker_777"
task_list.tasks = [task]

print("\nTaskList：")
print("  batch_id:", task_list.batch_id)
print("  model_id:", task_list.model_id)
print("  assigned_worker_id:", task_list.assigned_worker_id)
print("  task_count:", len(task_list.tasks))
print("  第一个 task.request_id:", task_list.tasks[0].request_id)

result = dds.WorkerTaskResult()
result.request_id = "req_123"
result.task_id = "task_abc"
result.client_id = "client_xyz"
result.status = "done"
result.output_blob = b"infer result bytes"

worker_result = dds.WorkerResult()
worker_result.batch_id = "batch_001"
worker_result.model_id = "model_alpha"
worker_result.worker_id = "worker_777"
worker_result.results = [result]

print("\nWorkerResult：")
print("  result count:", len(worker_result.results))
print("  第一个 result.status:", worker_result.results[0].status)
print("  output_blob:", worker_result.results[0].output_blob)

# === 补充：DataWriter / DataReader 最小用法 ===
# 假设你已经通过 DDS 创建好了以下实例（此处仅占位）：
# task_writer: dds.TaskDataWriter
# task_reader: dds.TaskDataReader
# task_list_writer: dds.TaskListDataWriter
# worker_result_writer: dds.WorkerResultDataWriter
# worker_result_reader: dds.WorkerResultDataReader
# claim_writer: dds.ClaimDataWriter
# openbatch_writer: dds.OpenBatchDataWriter
# grant_writer: dds.GrantDataWriter

# 1) 写入样例
def publish_samples(task_writer, task_list_writer, worker_result_writer,
                    claim_writer, openbatch_writer, grant_writer):
    # 写单条 Task
    rc1 = task_writer.write(task)
    print("\n写入 Task rc:", rc1)

    # 写 TaskList（内部有 tasks）
    rc2 = task_list_writer.write(task_list)
    print("写入 TaskList rc:", rc2)

    # 写 WorkerResult（包含若干 WorkerTaskResult）
    rc3 = worker_result_writer.write(worker_result)
    print("写入 WorkerResult rc:", rc3)

    # （可选）写 Claim/OpenBatch/Grant
    claim = dds.Claim()
    claim.batch_id = "batch_001"
    claim.worker_id = "worker_777"
    claim.queue_length = 0
    print("写入 Claim rc:", claim_writer.write(claim))

    ob = dds.OpenBatch()
    ob.batch_id = "batch_001"
    ob.model_id = "model_alpha"
    ob.size = 1
    ob.create_ts_ms = 1234567890
    print("写入 OpenBatch rc:", openbatch_writer.write(ob))

    grant = dds.Grant()
    grant.batch_id = "batch_001"
    grant.winner_worker_id = "worker_777"
    print("写入 Grant rc:", grant_writer.write(grant))

# 2) 读取样例（take_list/read_list）
def consume_samples(task_reader, worker_result_reader):
    # 从 Task 主题抓取（take 会消费样本；read 不消费）
    tasks = task_reader.take_list()  # max_samples 默认 -1 == LENGTH_UNLIMITED
    print("\n接收到 Task 条数:", len(tasks))
    for i, t in enumerate(tasks):
        print(f"  Task[{i}]: req={t.request_id}, task_id={t.task_id}, client={t.client_id}, payload_len={len(t.payload)}")

    # 从 WorkerResult 主题抓取结果
    wr_list = worker_result_reader.take_list()
    print("接收到 WorkerResult 条数:", len(wr_list))
    for i, wr in enumerate(wr_list):
        print(f"  WorkerResult[{i}]: batch={wr.batch_id}, model={wr.model_id}, worker={wr.worker_id}, n_results={len(wr.results)}")
        for j, r in enumerate(wr.results):
            print(f"    Result[{j}]: req={r.request_id}, task_id={r.task_id}, status={r.status}, out_len={len(r.output_blob)}")

# —— 实际调用时，把真实的 reader/writer 实例传进去即可：
# publish_samples(task_writer, task_list_writer, worker_result_writer,
#                 claim_writer, openbatch_writer, grant_writer)
# consume_samples(task_reader, worker_result_reader)
