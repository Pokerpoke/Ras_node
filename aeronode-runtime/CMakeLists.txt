include_directories(include)

add_subdirectory(lib)
add_subdirectory(include/aeronode)
add_subdirectory(example)

if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
# add_subdirectory(swig)