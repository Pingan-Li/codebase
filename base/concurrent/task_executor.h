/**
 * @file task_executor.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BASE_CONCURRENT_TASK_EXECUTOR_H_
#define BASE_CONCURRENT_TASK_EXECUTOR_H_

#include "base/concurrent/task.h"

namespace base {

class TaskExecutor {
public:
  struct Configuration {
    int max_threads = 8;
  };

  struct TaskTraits {};

  virtual bool Start(Configuration const &config) = 0;
  virtual bool Submit(Task task, TaskTraits const &task_traits = {}) = 0;
};

} // namespace base
#endif