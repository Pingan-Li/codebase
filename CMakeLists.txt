cmake_minimum_required(VERSION 3.5)

project("codebase")

# Monorepo configurations
include_directories(".")
add_compile_options("-std=c++17")
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
  link_libraries("pthread")
endif()

# GTest
set(gtest_source_set testing/googletest/src/gtest-all.cc)
add_library(gtest STATIC ${gtest_source_set})
target_include_directories(gtest PUBLIC testing/googletest/include)
target_include_directories(gtest PRIVATE testing/googletest)

# GTestMain
add_library(gtest_main STATIC testing/googletest/src/gtest_main.cc)
target_include_directories(gtest_main PUBLIC testing/googletest/include)

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

# base library 
set(base_source_set 
  "base/concurrent/mutex.cc"
  "base/concurrent/spin_lock.cc"
  "base/concurrent/condition_variable.cc"
  "base/concurrent/count_down_latch.cc"
  "base/memory/atomic_reference_counting.cc"
  "base/memory/reference_counting.cc")
add_library(base SHARED ${base_source_set})

# concurrent tests
add_executable(count_down_latch_tests base/concurrent/count_down_latch_tests.cc)
target_link_libraries(count_down_latch_tests PRIVATE base gtest_main gtest)
add_executable(spin_lock base/concurrent/spin_lock_tests.cc)
target_link_libraries(spin_lock PRIVATE base gtest_main gtest)
# Experiments
add_executable(atomic_exp "experiment/atomic_exp.cc")
target_link_libraries(atomic_exp PRIVATE gtest_main gtest)

add_executable(store_load_reordering_exp "experiment/store_load_reordering_exp.cc")
add_executable(store_load_reordering_preshing "experiment/store_load_reordering_preshing.cc")
add_executable(store_sotre_reordering_exp "experiment/store_store_reordering_exp.cc")

add_executable(weak_observer "experiment/weak_observer.cc")