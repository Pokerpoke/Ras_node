aux_source_directory(. AN_CORE_LIB)
add_library(an_core SHARED ${AN_CORE_LIB})
target_link_libraries(an_core
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	${JRTPLIB_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)