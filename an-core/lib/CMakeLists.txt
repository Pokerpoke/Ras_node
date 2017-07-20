aux_source_directory(. AN_CORE_LIB)
add_library(an_core_lib SHARED ${AN_CORE_LIB})
target_link_libraries(an_core_lib
	${LOG4CPP_LIBRARIES}
)