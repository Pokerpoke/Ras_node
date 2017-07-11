include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(an_core_swig.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(an_core_swig.i PROPERTIES SWIG_FLAGS "-includeall")
swig_add_module(an_core python an_core_swig.i ../lib/an_core.cc)
swig_link_libraries(an_core ${PYTHON_LIBRARIES})