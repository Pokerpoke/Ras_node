include_directories(include)

add_subdirectory(lib)
add_subdirectory(include/aeronode)

if(ENABLE_EXAMPLE)
    add_subdirectory(example)
endif(ENABLE_EXAMPLE)

if(ENABLE_TEST)
    add_subdirectory(test)
endif(ENABLE_TEST)
# add_subdirectory(swig)