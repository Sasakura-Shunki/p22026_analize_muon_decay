cmake_minimum_required(VERSION 3.20)
project(decayhist)

set(CMAKE_CXX_STANDARD 17)

find_package(ROOT REQUIRED)

add_library(func func.cpp)
target_link_libraries(func ROOT::Core ${ROOT_LIBRARIES})

add_executable(Main decayhist_nogui.cpp)
target_link_libraries(Main func ROOT::Core ${ROOT_LIBRARIES})
