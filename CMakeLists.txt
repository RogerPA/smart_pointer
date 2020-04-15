cmake_minimum_required(VERSION 3.15)

project("Garbage Collector")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(googletest)

# Include Sources
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

enable_testing()

add_subdirectory(source/smart_pointer)

add_executable(garbage_collector
  source/main.cpp
  source/smart_pointer/smart_pointer.hpp
  )
