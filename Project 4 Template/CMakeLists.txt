cmake_minimum_required(VERSION 3.23)
project(Project_4_Template)

set(CMAKE_CXX_STANDARD 14)

add_executable(VectorTemplate main.cpp)
add_executable(VectorTemplateTest testVector.cpp)
enable_testing()
add_test(NAME test COMMAND VectorTemplateTest.exe --output-on-failure)