project("Garbage Collector")
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include Sources
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

add_executable(garbage_collector
  source/main.cpp
  source/smart_pointer/smart_pointer.hpp
  )
