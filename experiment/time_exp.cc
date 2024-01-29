/**
 * @file time_exp.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-01-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <sys/time.h>

#include "testing/googletest/include/gtest/gtest.h"

TEST(Calendar, Time) {
  time_t t0;
  auto t1 = time(&t0);
  ASSERT_EQ(t1, t0);
  std::cout << ctime(&t1);
  tm *ptm = localtime(&t1);
  std::cout << "tm_sec " << ptm->tm_sec << std::endl;
  std::cout << "tm_min " << ptm->tm_min << std::endl;
  std::cout << "tm_hour " << ptm->tm_hour << std::endl;
  std::cout << "tm_wday " << ptm->tm_wday << std::endl;
  std::cout << "tm_mday " << ptm->tm_mday << std::endl;
  std::cout << "tm_yday " << ptm->tm_yday << std::endl;
  std::cout << "tm_year " << ptm->tm_year << std::endl;
  std::cout << "tm_zone " << ptm->tm_zone << std::endl;
}

// gettimeofday is deprecated.
TEST(Calendar, gettimeofday) {
  timeval tv;
  gettimeofday(&tv, nullptr);
  std::cout << tv.tv_sec << std::endl;
  std::cout << tv.tv_usec << std::endl;
}

TEST(Clock, GetResolution) {
  timespec ts;
  clock_getres(CLOCK_REALTIME, &ts);
  std::cout << ts.tv_sec << std::endl;
  std::cout << ts.tv_nsec << std::endl;
  clock_getres(CLOCK_BOOTTIME, &ts);
  std::cout << ts.tv_sec << std::endl;
  std::cout << ts.tv_nsec << std::endl;
  clock_getres(CLOCK_MONOTONIC, &ts);
  std::cout << ts.tv_sec << std::endl;
  std::cout << ts.tv_nsec << std::endl;
}

#if defined(CLOCK_REALTIME)
TEST(Clock, GetRealTime) {
  timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  std::cout << "real time seconds: " << ts.tv_sec
            << ", nanoseconds = " << ts.tv_nsec << std::endl;
  std::cout << ctime(&ts.tv_sec);
  static char buffer[1024];
  std::string time_fmt = "[%04d-%02d-%02d %02d:%02d:%02d.%d]";
  tm *ptm = localtime(&ts.tv_sec);
  std::sprintf(buffer, time_fmt.c_str(), ptm->tm_year + 1900, ptm->tm_mon + 1,
               ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
               ts.tv_nsec);
  std::cout << buffer << std::endl;
}
#endif

#if defined(CLOCK_MONOTONIC)
TEST(Clock, GetMonotonicTime) {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  std::cout << "monotonic time seconds: " << ts.tv_sec
            << ", nanoseconds = " << ts.tv_nsec << std::endl;
}
#endif

#if defined(CLOCK_BOOTTIME)
TEST(Clock, GetBootTime) {
  timespec ts;
  clock_gettime(CLOCK_BOOTTIME, &ts);
  std::cout << "boot time seconds: " << ts.tv_sec
            << ", nanoseconds = " << ts.tv_nsec << std::endl;
}
#endif
