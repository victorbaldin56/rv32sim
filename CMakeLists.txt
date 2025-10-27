cmake_minimum_required(VERSION 3.14)
project(rv32sim)

find_package(Boost REQUIRED)
find_package(elfutils REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(base)
add_subdirectory(sim)
add_subdirectory(main)

include(CTest)

set(TESTS_PATH ${CMAKE_SOURCE_DIR}/riscv-interpreter-task)

add_custom_target(tests ALL
  COMMAND make -j
  COMMENT "Building external tests"
  WORKING_DIRECTORY ${TESTS_PATH}
)

# Add test that runs the tests with your interpreter
add_test(
  NAME run_tests
  COMMAND make test INTERPRETER=$<TARGET_FILE:rv32sim> -j
  WORKING_DIRECTORY ${TESTS_PATH}
)
