/**
 * @file thread.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/concurrent/thread.h"

namespace base {

Thread::Thread(std::string const &thread_name)
    : thread_(), joined_(false), name_(thread_name), state_{kCreated} {}

Thread::Thread(Thread &&other) noexcept
    : thread_(std::move_if_noexcept(other.thread_)),
      joined_(std::move_if_noexcept(other.joined_)),
      name_(std::move_if_noexcept(other.name_)),
      state_(std::move_if_noexcept(other.state_)) {}

Thread &Thread::operator=(Thread &&other) noexcept {
  thread_ = std::move_if_noexcept(other.thread_);
  joined_ = std::move_if_noexcept(other.joined_);
  name_ = std::move_if_noexcept(other.name_);
  return *this;
}

Thread::~Thread() {
  if (!joined_) {
    pthread_detach(thread_);
  }
}

// NAIVE!
void Thread::Join() noexcept {
  if (!joined_) {
    pthread_join(thread_, nullptr);
    joined_ = true;
  }
}

std::string Thread::GetName() const noexcept { return name_; }

// NAIVE!
Thread::State Thread::GetSate() const noexcept { return state_; }

// private
// static
void *Thread::StartInternal(void *args) {
  auto data = static_cast<InternalData *>(args);
  if (data && data->start_routine) {
    data->start_routine->operator()();
  }
  if (data->thread) {
    data->thread->SwitchState(kFinished);
  }
  delete data->start_routine;
  delete data;
  return nullptr;
}

// private

void Thread::SwitchState(State next_state) {
  // TODO: add state check.
  state_ = next_state;
}

} // namespace base