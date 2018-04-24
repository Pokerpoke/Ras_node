include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(an_core.i PROPERTIES CPLUSPLUS ON)
# set_source_files_properties(system_infoe.i PROPERTIES SWIG_FLAGS "-includeall")
swig_add_module(an_core python an_core.i ${AN_CORE_LIB})
swig_link_libraries(an_core an-core ${PYTHON_LIBRARIES})