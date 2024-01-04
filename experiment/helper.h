/**
 * @file helper.h
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstring>
#include <iostream>

#ifndef EXPERIMENT_HELPER_H_
#define EXPERIMENT_HELPER_H_

#define LOG_ERR_MSG()                                                          \
  std::cerr << "[" << __FILE__ << "(" << __LINE__ << ")@" << __func__          \
            << "()] "                                                          \
            << "Error " << errno << " Occured: " << std::strerror(errno)       \
            << std::endl

#endif // EXPERIMENT_HELPER_H_