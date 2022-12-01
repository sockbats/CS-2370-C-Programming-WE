cmake_minimum_required(VERSION 3.23)
project(Project_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Vector main.cpp Vector.cpp)
add_executable(VectorTest testVector.cpp Vector.cpp)

