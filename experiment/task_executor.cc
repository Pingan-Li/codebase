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

#include <cstddef>
#include <memory>
#include "testing/googletest/include/gtest/gtest.h"

class TaskExecutor : public std::enable_shared_from_this<TaskExecutor> {
 public:
 private:
};

class Pipeline {
 public:
 private:
 
};

class TaskExecutionService {
 public:
  struct ServiceAttributes {
    std::size_t concurrnet_pipeline_size = 2;
    std::size_t sequential_pipeline_size = 2;
    std::size_t threads_per_concurrnet_pipeline = 4;
  };

  constexpr TaskExecutionService() noexcept = default;

  TaskExecutionService(TaskExecutionService const&) = delete;
  TaskExecutionService& operator=(TaskExecutionService const&) = delete;

  TaskExecutionService(TaskExecutionService&&) = delete;
  TaskExecutionService& operator=(TaskExecutionService&&) = delete;

  virtual ~TaskExecutionService();

  std::unique_ptr<TaskExecutor> CreateSequentialTaskExecutor();

  std::unique_ptr<TaskExecutor> CreateConcurrentTaskExecutor();

  void Init();

  void Stop();

 private:
};

TEST(TaskExecutor, Case0) {}