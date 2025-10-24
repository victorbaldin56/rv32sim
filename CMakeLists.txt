cmake_minimum_required(VERSION 3.14)
project(rv32sim)

find_package(Boost REQUIRED)
find_package(elfutils REQUIRED)

add_subdirectory(base)
add_subdirectory(sim)
add_subdirectory(main)
