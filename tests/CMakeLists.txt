set(TASK_TEST_LIST
  echo/runner.sh
  exit_code_argv/runner.sh
  rv32i/test_add
  rv32i/test_sub
  rv32im/test_mul
  rv32im/test_div
)

set(INTERPRETER $<TARGET_FILE:rv32sim>)

add_test(
  NAME task_tests_setup
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/riscv-interpreter-task/
  make -j
)

set_tests_properties(task_tests_setup PROPERTIES
  FIXTURES_SETUP "${TASK_TEST_LIST}"
)

set(TASK_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/riscv-interpreter-task/bin)

foreach(test IN LISTS TASK_TEST_LIST)
  get_filename_component(exec_name ${test} NAME)

  if(exec_name STREQUAL "runner.sh")
    get_filename_component(runner_dir ${TASK_TEST_DIR}/${test} DIRECTORY)

    add_test(NAME task_test_${test} COMMAND ${CMAKE_COMMAND} -E chdir ${runner_dir}
      ./runner.sh ${INTERPRETER}
    )
  else()
    add_test(NAME task_test_${test} COMMAND ${CMAKE_COMMAND} -E chdir ${TASK_TEST_DIR}
      ${INTERPRETER} ${TASK_TEST_DIR}/${test}
    )
  endif()
endforeach()
