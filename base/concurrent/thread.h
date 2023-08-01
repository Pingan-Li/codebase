/**
 * @file thread.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-07-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_CONCURRENT_THREAD_H_
#define BASE_CONCURRENT_THREAD_H_

#include "base/macro.h"

#include <chrono>
#include <functional>
#include <string>

#include <pthread.h>

namespace base {

// template <typename T>
// concept Task = requires(T t) { t.operator()(); };

/**
 * @brief
 *
 */
// TODO
struct API CurrentThread {
  static void SleepFor(std::chrono::microseconds const &us);

  static void SleepUntil(std::chrono::microseconds const &us);

  static bool IsMainThread() noexcept;
};

/**
 * @brief A portable ThreadId class.
 *
 */
// TODO
class ThreadId {};

/**
 * @brief A naive wrapper of platform thread.
 *
 */

class API Thread {
public:
  // For now, only POSIX pthread is supported.
  using PlatformThread = pthread_t;
  using StartRoutine = std::function<void()>;

  // TODO
  enum State {
    // Create but not started yet.
    kCreated,
    // After Thread::Start() called.
    kStarted,
    // Block
    // kBlocked,
    // Sleeping.
    kSleeping,
    // StartRoutine execution finished.
    kFinished,
  };

  explicit Thread(std::string const &thread_name = "Anonymous");

  // Disbale copy.
  DISABLE_COPY(Thread);
  // Support move.
  Thread(Thread &&) noexcept;
  Thread &operator=(Thread &&) noexcept;

  virtual ~Thread();

  template <typename Callable, typename... Args>
  void Start(Callable &&callable, Args &&...args) {
    // Heap allocated.
    InternalData *data = new InternalData;
    data->thread = this;
    data->start_routine = new StartRoutine(std::bind(
        std::forward<Callable>(callable), std::forward<Args>(args)...));

    pthread_create(&thread_, nullptr, &StartInternal, data);
    // Pthread created.
    SwitchState(kStarted);
    // Set pthread name.
    // TODO: consider using prctl. pthread_setname_np is also non-protbale.
    pthread_setname_np(thread_, name_.c_str());
  }

  void Join() noexcept;

  std::string GetName() const noexcept;

  State GetSate() const noexcept;

private:
  // Test helper function.
  friend class ThreadTestHelper;

  static void *StartInternal(void *args);

  struct InternalData {
    Thread *thread;
    StartRoutine *start_routine;
  };
  /**
   * @brief Switch thread state.
   *
   * @param next_state - the next state of base::Thread.
   */
  void SwitchState(State next_state);

  /**
   * @brief check if the state transition is ok.
   *
   * @param currnet_state
   * @param next_state
   */
  void CheckState(State currnet_state, State next_state);

  // Must not exposed.
  PlatformThread thread_;
  // State
  State state_;
  // joined
  bool joined_;
  // Unmutable.
  std::string name_;
};

} // namespace base
#endif