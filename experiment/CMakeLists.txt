cmake_minimum_required(VERSION 3.5)

project("experiment")

add_executable(ls "file_system/ls.cc")
target_link_libraries(ls gtest gtest_main)

add_executable(fcntl_exp "file_system/fcntl_exp.cc")
target_link_libraries(fcntl_exp gtest gtest_main)

add_executable(bio "io/bio.cc")
target_link_libraries(bio gtest gtest_main)

add_executable(pipe "ipc/pipe.cc")

add_executable(fifo "ipc/fifo.cc")

add_executable(posix_mq "ipc/posix_mq.cc")

add_executable(posix_sem "ipc/posix_sem.cc")
target_link_libraries(posix_sem gtest gtest_main)

add_executable(posix_shm "ipc/posix_shm.cc")
target_link_libraries(posix_shm gtest gtest_main)

add_executable(sysv_mq "ipc/sysv_mq.cc")
target_link_libraries(sysv_mq gtest gtest_main)

add_executable(sysv_sem "ipc/sysv_sem.cc")
target_link_libraries(sysv_sem gtest gtest_main)

add_executable(sysv_shm "ipc/sysv_shm.cc")
target_link_libraries(sysv_shm gtest gtest_main)