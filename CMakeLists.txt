cmake_minimum_required(VERSION 3.10)
project(TemplateMatrix)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(test)

add_executable(TemplateMatrix main.cpp Matrix.h)