cmake_minimum_required(VERSION 3.20)
project(analisis_mu)

set(CMAKE_CXX_STANDARD 17)
set(TARGET draw_graph makehist decayhist decayhist_nogui)

find_package(ROOT REQUIRED)

add_library(func func.cpp)
set(ROOT_LINK ROOT::Core ${ROOT_LIBRARIES})
target_link_libraries(func ${ROOT_LINK})

foreach(EXE IN LISTS TARGET)
	add_executable(${EXE} ${EXE}.cpp)
	target_link_libraries(${EXE} func ${ROOT_LINK})
endforeach()
