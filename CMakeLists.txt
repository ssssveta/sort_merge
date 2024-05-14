cmake_minimum_required(VERSION 3.5)

project(untitled1 LANGUAGES CXX)
set (CMAKE_PREFIX_PATH "/home/svetlana/allegro5" ${CMAKE_PREFIX_PATH})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ALLEGRO_FLAGS} ")
set(CMAKE_CXX_COMPILER mpic++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5Core)
find_package(Allegro REQUIRED)
find_package(MPI REQUIRED)

add_executable(untitled1
  main.cpp
  draw_merge.h
  parallel_merge.h
  draw.h
)

include_directories(/home/svetlana/allegro5/include/allegro5)
include_directories(/home/svetlana/allegro5/addons/primitives/allegro5)
#include_directories(/home/svetlana/openmpi-5.0.3)
include_directories(${MPI_INCLUDE_PATH})
link_directories(/home/svetlana/allegro5/build/lib)
target_link_libraries(untitled1 Qt5::Core)
target_link_libraries(untitled1 Allegro::allegro Allegro::allegro_primitives )
target_link_libraries(untitled1 ${MPI_CXX_LIBRARIES})
