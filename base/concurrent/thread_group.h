#ifndef BASE_CONCURRENT_THREAD_GROUP_H_
#define BASE_CONCURRENT_THREAD_GROUP_H_

#include "base/concurrent/condition_variable.h"
#include "base/concurrent/mutex.h"
#include "base/concurrent/mutex_guard.h"
#include "base/concurrent/thread.h"
#include "base/macro.h"

#include <functional>
#include <future>
#include <memory>
#include <queue>
#include <type_traits>
#include <vector>

namespace base {
class ThreadGroup {
public:
  using Task = std::function<void()>;

  struct CreationParams {
    //  Thread group name.
    std::string name = "Anonymous";
    // 0 means no limit.
    std::size_t thread_limit = 0;
    // 0 means no limit.
    std::size_t task_queue_limit = 0;
  };

  static std::unique_ptr<ThreadGroup> Create(CreationParams const &args);

  DISABLE_COPY(ThreadGroup);
  DISABLE_MOVE(ThreadGroup);

  virtual ~ThreadGroup();

  template <typename Callable, typename... Args>
  std::future<typename std::invoke_result<Callable, Args...>::type>
  Submit(Callable &&callable, Args &&...args) {
    // Allocated.
    auto packaged_task = std::make_shared<std::packaged_task<
        typename std::invoke_result<Callable, Args...>::type()>>(
        std::bind(std::forward<Callable>(callable),
                  std::forward<Args>(args)...));

    // future.
    auto future = packaged_task->get_future();
    { MutexGuard<Mutex> mutex_guard{mtx_}; }
  }

private:
  friend Thread;

  ThreadGroup();

  static void ThreadWorkRoutine(ThreadGroup *thread_group);

  void SpawnNewThread();

  std::string name_;
  base::Mutex mtx_;
  base::ConditionVariable cv_;
  std::vector<base::Thread> worker_threads_;
  std::queue<Task> task_queue_;
  std::size_t thread_limit_;
  std::size_t task_queue_limit;
};

} // namespace base
#endif