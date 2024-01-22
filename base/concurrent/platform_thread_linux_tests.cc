/**
 * @file platform_thread_linux_tests.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "base/concurrent/platform_thread_linux.h"

#include <syscall.h>
#include <unistd.h>

#include <chrono>
#include <future>
#include <ostream>
#include <thread>

#include "base/concurrent/task.h"
#include "testing/googletest/include/gtest/gtest.h"

void TestThreadName(std::string const &name) {
  base::platform_thread::ThreadHandle handle =
      base::platform_thread::current::GetThreadHandle();

  ASSERT_TRUE(base::platform_thread::SetName(handle, name));

  std::string thread_name = base::platform_thread::GetName(handle);

  ASSERT_EQ(thread_name, name);
}

void TestThreadHandle() {
  base::platform_thread::ThreadHandle pthread_id =
      base::platform_thread::current::GetThreadHandle();

  base::platform_thread::KernelThreadHandle lwp_id =
      base::platform_thread::current::GetKernelThreadHandle();

  ASSERT_EQ(pthread_id, pthread_self());
  ASSERT_EQ(lwp_id, syscall(SYS_gettid));
}

TEST(PlatformThreadLinux, ThreadName) {
  TestThreadName("Main");
  std::thread thread(TestThreadName, "Child");
  thread.join();
}

TEST(PlatformThreadLinux, Handle) {
  TestThreadHandle();
  std::thread thread(TestThreadHandle);
  thread.join();
}

TEST(PlatformThreadLinux, IsMain) {
  ASSERT_TRUE(base::platform_thread::current::IsMainThread());
  std::thread thread([]() -> void {
    ASSERT_FALSE(base::platform_thread::current::IsMainThread());
  });
  thread.join();
}

int add(int a, int b) { return a + b; }

TEST(PlatformThreadLinux, Start) {
  base::platform_thread::ThreadHandle thread_handle;
  auto future = base::platform_thread::Start(thread_handle, &add, 1, 2);
  std::cout << future.get() << std::endl;
  base::platform_thread::Join(thread_handle);
}

TEST(PlatformThreadLinux, Start_2) {
  base::platform_thread::ThreadHandle thread_handle;
  int result = 0;
  auto packaged_task =
      base::MakeTask([](int a, int b, int *result) -> void { *result = a + b; },
                     1, 2, &result);

  auto future = packaged_task.get_future();
  base::platform_thread::Start(thread_handle, std::move(packaged_task));
  future.get();
  std::cout << "result = " << result;
  base::platform_thread::Join(thread_handle);
}