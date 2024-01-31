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

#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>
#include <vector>

#include "base/concurrent/thread_group.h"
#include "base/macro.h"

namespace base {

class TaskExecutorImpl : public TaskExecutor, public ThreadGroup {
public:
  TaskExecutorImpl();

  DISABLE_COPY(TaskExecutorImpl);
  DISABLE_MOVE(TaskExecutorImpl);

  bool Start(Configuration const &configuration) override;

  bool Submit(Task task, TaskTraits const &task_traits = {}) override;

  int GetThreads() const noexcept override;

  int GetIdleThreads() const noexcept override;

  bool IsRuning() const noexcept override;

  bool Stop(Task callback = {}) override;

  ~TaskExecutorImpl() override;

private:
  std::deque<Task> task_queue_;
  std::mutex mutex_;
  std::condition_variable condtion_varibale_;
  std::vector<std::thread> worker_threads_;
  bool is_running_{false};
  // size_t number_of_busy_threads_{};
  // size_t number_of_idle_threads_{};
  // size_t number_of_total_threads_{};
  // std::condition_variable notify_on_stop_;
  Configuration configuration_;
};

} // namespace base
#endif // BASE_CONCURRENT_TASK_EXECUTOR_IMPL_H_