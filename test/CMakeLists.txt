cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES runAllTests.cpp MatrixTest.cpp)
add_executable(runAllTests ${SOURCE_FILES})
target_link_libraries(runAllTests ${GTEST_BOTH_LIBRARIES})