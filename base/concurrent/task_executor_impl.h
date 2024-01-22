/**
 * @file task_executor_impl.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BASE_CONCURRENT_TASK_EXECUTOR_IMPL_H_
#define BASE_CONCURRENT_TASK_EXECUTOR_IMPL_H_

#include "base/concurrent/task_executor.h"

#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <vector>

#include "base/macro.h"

namespace base {

class TaskExecutorImpl : public TaskExecutor {
public:
  TaskExecutorImpl();

  DISABLE_COPY(TaskExecutorImpl);
  DISABLE_MOVE(TaskExecutorImpl);

  bool Start(Configuration const &configuration) override;

  bool Submit(Task task, TaskTraits const &task_traits = {}) override;

  inline int GetIdleThreads() {
    return idle_threads_.load(std::memory_order_acquire);
  }

  bool Stop(); // FASONG RENWU CHUQU.

  ~TaskExecutorImpl() {
    // for (auto &&t : threads_) {
    //   t.detach();
    // }
  }

private:
  std::deque<Task> task_queue_;
  std::mutex mtx_;
  std::condition_variable cv_;
  Configuration config_;
  std::atomic_int idle_threads_;
  std::vector<std::thread> threads_;
};

} // namespace base
#endif // BASE_CONCURRENT_TASK_EXECUTOR_IMPL_H_