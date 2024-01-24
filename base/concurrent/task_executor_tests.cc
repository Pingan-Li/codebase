/**
 * @file task_executor_tests.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <chrono>
#include <future>
#include <iostream>
#include <vector>

#include "base/concurrent/platform_thread_linux.h"
#include "base/concurrent/task.h"
#include "base/concurrent/task_executor.h"
#include "base/concurrent/task_executor_impl.h"

#include "testing/googletest/include/gtest/gtest.h"

TEST(TaskExecutorImpl, Submit) {
  base::TaskExecutorImpl task_executor_impl;
  base::ThreadGroup::Configuration config{"Main", 8, 0};
  task_executor_impl.Start(config);
  ASSERT_EQ(task_executor_impl.GetIdleThreads(), config.max_threads());

  std::cerr.sync_with_stdio(true);
  std::vector<std::future<void>> futures;
  for (auto i = 0; i < 100; ++i) {
    auto task = base::MakeTask(
        [](int k) -> void { std::cerr << "i = " << k << std::endl; }, i);
    futures.emplace_back(task.get_future());
    task_executor_impl.Submit(std::move(task));
  }

  auto stop_task = base::MakeTask(
      [&task_executor_impl]() -> void { task_executor_impl.Stop(); });

  task_executor_impl.Submit(std::move(stop_task));

  // base::platform_thread::current::SleepFor(std::chrono::seconds{1});
}