include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_SWIG_FLAGS "")

set_source_files_properties(system_info_swig.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(system_info_swig.i PROPERTIES SWIG_FLAGS "-includeall")
swig_add_module(system_info python system_info_swig.i ../lib/system_info.cc)
swig_link_libraries(system_info ${PYTHON_LIBRARIES})