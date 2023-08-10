#include "base/concurrent/thread_group.h"

#include "base/concurrent/mutex.h"
#include "base/concurrent/mutex_guard.h"
#include "base/concurrent/thread.h"

namespace base {
// static
std::unique_ptr<ThreadGroup> ThreadGroup::Create(CreationParams const &args) {
  // std::make_unique doesn't work with a private constructor.
  auto thread_group = std::unique_ptr<ThreadGroup>(new ThreadGroup);

  // two-phase initialization.
  thread_group->name_ = args.name;
  thread_group->thread_limit_ = args.thread_limit;
  thread_group->task_queue_limit = args.task_queue_limit;
  return thread_group;
}

ThreadGroup::~ThreadGroup(){

};

// private
// static
void ThreadGroup::ThreadWorkRoutine(ThreadGroup *thread_group) {
  while (true) {
    Task task;
    thread_group->mtx_.Acquire();
    while (thread_group->task_queue_.empty()) {
      thread_group->cv_.Wait(thread_group->mtx_);
    }
    task = thread_group->task_queue_.front();
  }
}

// private
void ThreadGroup::SpawnNewThread() {
  {
    MutexGuard<Mutex> mutex_guard{mtx_};
    worker_threads_.emplace_back();
  }
  worker_threads_.back().Start(&ThreadGroup::ThreadWorkRoutine, this);
}

ThreadGroup::ThreadGroup() = default;

} // namespace base