cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)

add_library(FixedWidthInts INTERFACE)
target_include_directories(FixedWidthInts INTERFACE inc)
target_sources(FixedWidthInts INTERFACE inc/FWILiterals.hpp inc/FWIConcepts.hpp)

#project(FWI)
#add_executable(FWI main.cpp)
#target_link_libraries(FWI PUBLIC FixedWidthInts)
