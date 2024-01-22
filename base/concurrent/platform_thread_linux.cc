/**
 * @file platform_thread_linux.cc
 * @author lipingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "base/concurrent/platform_thread_linux.h"

#include <pthread.h>
#include <sched.h>
#include <syscall.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>

namespace base {
namespace platform_thread {

#if not defined(SYS_gettid)
#error "SYS_gettid unavailable on this system"
#endif
#define gettid() ((pid_t)syscall(SYS_gettid))

bool SetName(ThreadHandle thread_handle, std::string const &name) noexcept {
  int rv = pthread_setname_np(thread_handle, name.c_str()) != 0;
  switch (rv) {
  case ERANGE: {
    std::cerr << std::strerror(rv) << std::endl;
    return false;
  }
  }
  return true;
}

std::string GetName(ThreadHandle thread_handle) noexcept {
  thread_local char buffer[1024];
  int rv = pthread_getname_np(thread_handle, buffer, sizeof(buffer));
  switch (rv) {
  case ERANGE: {
    std::cerr << std::strerror(rv) << std::endl;
    return {};
  }
  }
  return std::string{buffer};
}

bool Join(ThreadHandle thread_handle) noexcept {
  int rv = pthread_join(thread_handle, nullptr);
  switch (rv) {
  case EDEADLK:
  case ESRCH:
  case EINVAL: {
    std::cerr << std::strerror(rv) << std::endl;
    return false;
  }
  }
  return true;
}

namespace current {

thread_local pid_t t_thread_group_handle = 0;
thread_local platform_thread::ThreadHandle t_thread_handle = 0;
thread_local platform_thread::KernelThreadHandle t_kernel_thread_handle = 0;

bool IsMainThread() noexcept {
  if (t_thread_group_handle == 0) {
    t_thread_group_handle = getpid();
  }

  if (t_kernel_thread_handle == 0) {
    t_kernel_thread_handle = gettid();
  }

  return t_thread_group_handle == t_kernel_thread_handle;
}

void Yeild() noexcept {
  if (sched_yield() == -1) {
    std::cerr << std::strerror(errno) << std::endl;
  }
}

platform_thread::ThreadHandle GetThreadHandle() noexcept {
  if (t_thread_handle == 0) {
    t_thread_handle = pthread_self();
  }
  return t_thread_handle;
}

platform_thread::KernelThreadHandle GetKernelThreadHandle() noexcept {
  if (t_kernel_thread_handle == 0) {
    t_kernel_thread_handle = gettid();
  }
  return t_kernel_thread_handle;
}

} // namespace current
} // namespace platform_thread
} // namespace base