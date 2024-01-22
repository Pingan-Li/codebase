/**
 * @file task_executor_impl.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "base/concurrent/task_executor_impl.h"

#include <atomic>
#include <iostream>
#include <mutex>
#include <tuple>
#include <utility>

namespace base {

TaskExecutorImpl::TaskExecutorImpl()
    : task_queue_(), mtx_(), cv_(), config_(), idle_threads_(), threads_() {}

bool TaskExecutorImpl::Start(Configuration const &configuration) {
  config_ = std::move(configuration);

  idle_threads_.store(config_.max_threads, std::memory_order_relaxed);

  for (auto i = 0; i < config_.max_threads; ++i) {
    threads_.emplace_back([this]() -> void {
      while (true) {
        Task task;
        {
          std::unique_lock<std::mutex> unique_lock{this->mtx_};
          std::cout << "AC";
          while (this->task_queue_.empty()) {
            this->cv_.wait(unique_lock);
          }
          this->idle_threads_.fetch_add(-1);
          task = std::move(this->task_queue_.front());
          this->task_queue_.pop_front();
        }
        task();
        this->idle_threads_.fetch_add(1);
      }
    });
  }

  return true;
}

bool TaskExecutorImpl::Submit(Task task, TaskTraits const &task_traits) {
  //
  {
    std::lock_guard<std::mutex> lock_guard{mtx_};
    task_queue_.emplace_back(std::move(task));
    cv_.notify_one();
  }

  std::ignore = task_traits;
  return true;
}

bool TaskExecutorImpl::Stop() {}
} // namespace base