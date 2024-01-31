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

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <tuple>
#include <utility>

#include "base/log.h"

namespace base {

TaskExecutorImpl::TaskExecutorImpl()
    : task_queue_{}, mutex_{}, condtion_varibale_{}, worker_threads_{},
      is_running_{false}, configuration_{} {}

TaskExecutorImpl::~TaskExecutorImpl() {
  if (is_running_) {
    Stop();
  }
}

bool TaskExecutorImpl::Start(Configuration const &configuration) {
  std::lock_guard<std::mutex> lock_guard{mutex_};

  configuration_ = std::move(configuration);

  for (auto i = 0; i < configuration_.max_threads(); ++i) {
    worker_threads_.emplace_back([this]() -> void {
      while (true) {
        Task task;
        {
          std::unique_lock<std::mutex> unique_lock{this->mutex_};

          while (!this->is_running_) {
            LOG(INFO) << "lipinga: is_running_ = " << this->is_running_;
            return;
          }

          while (this->task_queue_.empty()) {
            this->condtion_varibale_.wait(unique_lock);
          }

          task = std::move(this->task_queue_.front());
          this->task_queue_.pop_front();
        }
        task.operator()();
      }
    });
  }

  is_running_ = true;
  return true;
}

bool TaskExecutorImpl::Submit(Task task, TaskTraits const &task_traits) {
  {
    std::lock_guard<std::mutex> lock_guard{mutex_};
    task_queue_.emplace_back(std::move(task));
  }

  condtion_varibale_.notify_one();
  std::ignore = task_traits;
  return true;
}

int TaskExecutorImpl::GetThreads() const noexcept { return 0; }

int TaskExecutorImpl::GetIdleThreads() const noexcept { return 0; }

bool TaskExecutorImpl::Stop(Task callback) {
  {
    std::lock_guard<std::mutex> lock_guard{mutex_};
    is_running_ = false;
    condtion_varibale_.notify_all();
  }

  for (auto &&thread : worker_threads_) {
    if (thread.joinable()) {
      LOG(INFO) << "thread.join() called!";
      thread.join();
    } else {
      LOG(INFO) << "thread.join() called!";
      thread.detach();
    }
  }

  if (callback)
    callback();
  // callback();
  return true;
}

bool TaskExecutorImpl::IsRuning() const noexcept { return is_running_; }

} // namespace base