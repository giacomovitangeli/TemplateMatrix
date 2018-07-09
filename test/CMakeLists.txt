cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES MatrixTest.cpp)
add_executable(runGameCharacterTests ${SOURCE_FILES})
target_link_libraries(runGameCharacterTests ${GTEST_BOTH_LIBRARIES} core)