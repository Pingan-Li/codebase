cmake_minimum_required(VERSION 3.5)

project("codebase")

add_compile_options("-std=c++20")

# GTest
set(gtest_source_set testing/googletest/src/gtest-all.cc)
add_library(gtest STATIC ${gtest_source_set})
target_include_directories(gtest PUBLIC testing/googletest/include)
target_include_directories(gtest PRIVATE testing/googletest)
# GTestMain
add_library(gtest_main STATIC testing/googletest/src/gtest_main.cc)
target_include_directories(gtest_main PUBLIC testing/googletest/include)
target_link_libraries(gtest_main PRIVATE gtest)
# GMock
set(gmock_source_set testing/googlemock/src/gmock-all.cc)
add_library(gmock STATIC ${gmock_source_set})
target_include_directories(gmock PUBLIC testing/googletest/include)
target_include_directories(gmock PUBLIC testing/googlemock/include)
target_include_directories(gmock PRIVATE testing/googletest)
target_include_directories(gmock PRIVATE testing/googlemock)
# GMockMain
add_library(gmock_main STATIC testing/googlemock/src/gmock_main.cc)
target_include_directories(gmock_main PUBLIC testing/googletest/include)
target_include_directories(gmock_main PUBLIC testing/googlemock/include)
target_link_libraries(gmock_main PRIVATE gmock)

# Monorepo include path
include_directories(".")

# Experiments
add_executable(atomic_exp "experiment/atomic_exp.cc")
target_link_libraries(atomic_exp PRIVATE gtest_main)