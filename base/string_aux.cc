/**
 * @file string_auxiliary.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "base/string_aux.h"

namespace base {
std::vector<std::string> Split(const std::string &text, char delimiter) {
  std::vector<std::string> strings;
  auto slow = text.begin();
  auto fast = text.begin();
  while (fast != text.end()) {
    if (*fast == delimiter) {
      strings.emplace_back(slow, fast);
      slow = ++fast;
    } else {
      ++fast;
    }
  }
  strings.emplace_back(slow, fast);
  return strings;
}

std::vector<std::string> Split(const std::string &text, char delimiter,
                               int degree) {
  std::vector<std::string> strings;
  auto slow = text.begin();
  auto fast = text.begin();
  while (fast != text.end()) {
    if (*fast == delimiter) {
      if (--degree < 0)
        break;
      strings.emplace_back(slow, fast);
      slow = ++fast;
    } else {
      ++fast;
    }
  }
  strings.emplace_back(slow, text.end());
  return strings;
}

std::vector<std::string> ReverseSplit(const std::string &text, char delimiter) {
  std::vector<std::string> strings;
  auto fast = text.end();
  auto slow = text.end();
  while (fast != text.begin()) {
    --fast;
    if (*fast == delimiter) {
      strings.emplace_back(fast + 1, slow);
      slow = fast;
    }
  }
  strings.emplace_back(fast, slow);
  return strings;
}

std::vector<std::string> ReverseSplit(const std::string &text, char delimiter,
                                      int degree) {
  std::vector<std::string> strings;
  auto fast = text.end();
  auto slow = text.end();
  while (fast != text.begin()) {
    --fast;
    if (*fast == delimiter) {
      if (--degree < 0)
        break;
      strings.emplace_back(fast + 1, slow);
      slow = fast;
    }
  }
  strings.emplace_back(text.begin(), slow);
  return strings;
}

void LeftTrim(std::string &text) {
  auto iter = text.begin();
  while (iter != text.end() && std::isspace(*iter)) {
    ++iter;
  }
  text.erase(text.begin(), iter);
}

void RightTrim(std::string &text) {
  auto iter = text.rbegin();
  while (iter != text.rend() && std::isspace(*iter)) {
    ++iter;
  }
  iter.base();
  text.erase(iter.base(), text.rbegin().base());
}

void Trim(std::string &text) {
  LeftTrim(text);
  RightTrim(text);
}

std::string LeftTrim(const std::string &text) {
  auto iter = text.begin();
  while (iter != text.end() && std::isspace(*iter)) {
    ++iter;
  }
  return std::string{iter, text.end()};
}

std::string RightTrim(const std::string &text) {
  auto iter = text.rbegin();
  while (iter != text.rend() && std::isspace(*iter)) {
    ++iter;
  }
  return std::string{text.begin(), iter.base()};
}

std::string Trim(const std::string &text) {
  auto left = text.begin();
  while (left != text.end() && std::isspace(*left)) {
    ++left;
  }
  auto right = text.rbegin();
  while (right != text.rend() && std::isspace(*right)) {
    ++right;
  }
  return std::string{left, right.base()};
}

bool StartsWith(const std::string &text, const std::string &prefix) {
  if (text.size() < prefix.size() || text.empty() || prefix.empty()) {
    return false;
  } else {
    auto iterText = text.begin();
    auto iterPrefix = prefix.begin();
    while (iterPrefix != prefix.end()) {
      if (*iterPrefix != *iterText) {
        return false;
      }
      iterPrefix++;
      iterText++;
    }
    return true;
  }
}

bool EndsWith(const std::string &text, const std::string &suffix) {
  if (text.size() < suffix.size() || text.empty() || suffix.empty()) {
    return false;
  } else {
    auto iterText = text.rbegin();
    auto iterSuffix = suffix.rbegin();
    while (iterSuffix != suffix.rend()) {
      if (*iterSuffix != *iterText) {
        return false;
      }
      ++iterSuffix;
      ++iterText;
    }
    return true;
  }
}

void SetBit(size_t &bits, size_t index) {
  bits |= (static_cast<size_t>(1) << index);
}

void ResetBit(size_t &bits, size_t index) {
  bits &= ~(static_cast<size_t>(1) << index);
}

void FlipBit(size_t &bits, size_t index) {
  bits ^= (static_cast<size_t>(1) << index);
}
} // namespace base