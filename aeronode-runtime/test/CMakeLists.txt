aux_source_directory(. TESTS)
foreach(TEST_NAME ${TESTS})
	get_filename_component(TEST ${TEST_NAME} NAME_WE)
    add_executable(${TEST} ${TEST_NAME})
    target_link_libraries(${TEST}
                          gtest
                          gtest_main
                          pthread
                          an-core)
    gtest_discover_tests(${TEST})
endforeach()
