add_executable(path_parser_test path_parser_test.cc)

target_link_libraries(path_parser_test 
                      gtest
                      gtest_main
                    #   pthread
                      an-core)

gtest_discover_tests(path_parser_test)