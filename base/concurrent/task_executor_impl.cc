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
#include <pthread.h>
#include <tuple>
#include <utility>

namespace base {

TaskExecutorImpl::TaskExecutorImpl()
    : task_queue_(), mtx_(), cv_(), config_(), idle_threads_(),
      is_running_(false), threads_() {}

TaskExecutorImpl::~TaskExecutorImpl() {
  for (auto &&thread : threads_) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

bool TaskExecutorImpl::Start(Configuration const &configuration) {
  config_ = std::move(configuration);
  idle_threads_.store(config_.max_threads(), std::memory_order_release);
  for (auto i = 0; i < config_.max_threads(); ++i) {
    threads_.emplace_back([this]() -> void {
      while (this->is_running_.load()) {
        Task task;
        {
          std::unique_lock<std::mutex> unique_lock{this->mtx_};
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
  is_running_.store(true, std::memory_order_release);
  return true;
}

bool TaskExecutorImpl::Submit(Task task, TaskTraits const &task_traits) {
  {
    std::lock_guard<std::mutex> lock_guard{mtx_};
    task_queue_.emplace_back(std::move(task));
  }
  cv_.notify_all();
  std::ignore = task_traits;
  return true;
}

int TaskExecutorImpl::GetThreads() const noexcept { return task_queue_.size(); }

int TaskExecutorImpl::GetIdleThreads() const noexcept {
  return idle_threads_.load(std::memory_order_acquire);
}

bool TaskExecutorImpl::Stop(Task callback) {
  {
    std::lock_guard<std::mutex> lock_guard{mtx_};
    is_running_ = false;
    cv_.notify_all();
  }
  std::cerr << "Heck" << std::endl;

  callback();
  
  return true;
}

bool TaskExecutorImpl::IsRuning() const noexcept {
  return is_running_.load(std::memory_order_acquire);
}

} // namespace base