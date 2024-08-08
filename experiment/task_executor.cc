/**
 * @file task_executor.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace concurrent {

using Task = std::function<void()>;
using TaskQueue = std::queue<Task>;
using TaskWorker = std::thread;

class TaskScheduler {
 public:
  virtual void Submit(Task task) = 0;
};

class SequentialTaskScheduler : public TaskScheduler {
 public:
  void Submit(Task task) override;
};

class ConcurrentTaskScheduler : public TaskScheduler {
 public:
  void Submit(Task task) override;
};

class TaskExecutor {
 public:
  virtual void Submit(Task task) = 0;

  virtual void Start() = 0;

  virtual void Stop() = 0;
};

class SequentialTaskExecutor : public TaskExecutor {
 public:
  void Submit(Task task) override;

  void Start() override;

  void Stop() override;

 private:
  std::mutex mutex_;
  std::condition_variable condition_variable_;
  TaskWorker task_worker;
  TaskQueue task_queue_;
};

void SequentialTaskExecutor::Submit(Task task) {
  (void)task;
}

void SequentialTaskExecutor::Start() {}

void SequentialTaskExecutor::Stop() {}

class ConcurrnetTaskExecutor : public TaskExecutor {
 public:
 private:
};

class TaskExecutionService {
 public:
};
class TaskExecutionServiceImpl : public TaskExecutionService {};

}  // namespace concurrent