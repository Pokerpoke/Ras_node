aux_source_directory(. AN_CORE_LIB)
add_library(an-core SHARED ${AN_CORE_LIB})
target_link_libraries(an-core
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	${JRTPLIB_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)

################################################################################
# install files
################################################################################
install(TARGETS
        an-core
        DESTINATION ${CMAKE_BINARY_DIR}/lib
        COMPONENT "an_core_libraries"
        )