cmake_minimum_required(VERSION 3.0)

add_library(whereami include/whereami.h src/whereami.c)
target_include_directories(whereami PUBLIC include)
