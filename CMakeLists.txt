cmake_minimum_required(VERSION 3.20)

add_library(FixedWidthInts INTERFACE)
target_include_directories(FixedWidthInts INTERFACE inc)
target_sources(FixedWidthInts INTERFACE inc/FWILiterals.hpp inc/FWIConcepts.hpp)
