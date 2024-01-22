/**
 * @file platform_thread_linux.h
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BASE_CONCURRENT_PLATFORM_THREAD_LINUX_H_
#define BASE_CONCURRENT_PLATFORM_THREAD_LINUX_H_

#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace base {
namespace platform_thread {

using ThreadHandle = uint64_t;
using KernelThreadHandle = int32_t;

inline static void *StartInternal(void *args) {
  auto *task = static_cast<std::function<void()> *>(args);
  task->operator()();
  delete task;
  return nullptr;
}

template <typename Callable, typename... Args,
          typename std::enable_if<std::is_trivially_copyable<Callable>::value,
                                  bool>::type = true>
std::future<typename std::invoke_result<Callable, Args...>::type>
Start(ThreadHandle &thread_handle, Callable &&callable, Args &&...args) {
  auto promise = std::make_shared<
      std::promise<typename std::invoke_result<Callable, Args...>::type>>();
  auto future = promise->get_future();
  auto closure = new std::function<void()>(
      [callable_(callable),
       arguments_(std::make_tuple<Args...>(std::forward<Args>(args)...)),
       promise_(promise)]() -> void {
        promise_->set_value(std::apply(callable_, arguments_));
      });

  int rv = pthread_create(&thread_handle, nullptr, StartInternal, closure);
  switch (rv) {
  case EAGAIN:
  case EINVAL:
  case EPERM:
    return {};
  }
  return future;
}

using Closure = std::packaged_task<void()>;

inline static void *StartRoutine(void *args) {
  if (args) {
    auto *closure = static_cast<Closure *>(args);
    closure->operator()();
    delete closure;
  }
  return nullptr;
}

inline void Start(base::platform_thread::ThreadHandle &thread_handle,
                  Closure &&packaged_task) {
  auto *closure = new Closure{std::move(packaged_task)};
  int rv = pthread_create(&thread_handle, nullptr, &StartRoutine, closure);
  switch (rv) {
  case EAGAIN:
  case EINVAL:
  case EPERM:
    std::cerr << std::strerror(rv) << std::endl;
  }
  return;
}

bool SetName(ThreadHandle thread_handle, std::string const &name) noexcept;

std::string GetName(ThreadHandle thread_handle) noexcept;

bool Join(ThreadHandle thread_handle) noexcept;

namespace current {

bool IsMainThread() noexcept;

template <typename Rep, typename Period>
static void SleepFor(std::chrono::duration<Rep, Period> const &sleep_duration) {
  if (sleep_duration <= sleep_duration.zero()) {
    return;
  }
  auto seconds =
      std::chrono::duration_cast<std::chrono::seconds>(sleep_duration);
  auto nano_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(
      sleep_duration - seconds);
  timespec time_spec = {static_cast<std::time_t>(seconds.count()),
                        static_cast<long>(nano_seconds.count())};
  while (::nanosleep(&time_spec, &time_spec) == -1 && errno == EINTR) {
  }
}

template <typename Clock, typename Duration>
static void
SleepUntil(std::chrono::time_point<Clock, Duration> const &wakeup_time_point) {
  auto now = Clock::now();
  if (Clock::is_steady) {
    if (now < wakeup_time_point)
      SleepFor(wakeup_time_point - now);
    return;
  }
  // using while-loop to deal with the unsteady clock.
  while (now < wakeup_time_point) {
    SleepFor(wakeup_time_point - now);
    now = Clock::now();
  }
}

void Yeild() noexcept;

platform_thread::ThreadHandle GetThreadHandle() noexcept;

platform_thread::KernelThreadHandle GetKernelThreadHandle() noexcept;

} // namespace current
} // namespace platform_thread
} // namespace base

#endif // BASE_CONCURRENT_PLATFORM_THREAD_LINUX_H_