/**
 * @file task.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-07-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>

#include "base/base_exports.h"

namespace base {
using Task = std::function<void()>;
}