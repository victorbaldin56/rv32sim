cmake_minimum_required(VERSION 3.14)
project(rv32sim)

find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)
find_package(magic_enum REQUIRED)

include(CTest)

add_subdirectory(base)
add_subdirectory(sim)
add_subdirectory(main)

option(ENABLE_TESTING "Enable testing" ON)
if (ENABLE_TESTING)
  enable_testing()

  add_subdirectory(tests)
endif()
