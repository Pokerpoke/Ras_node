aux_source_directory(. AN_MEDIA_LIB)

add_library(an-media SHARED ${AN_MEDIA_LIB})
target_link_libraries(an-media
    an-core
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	${JRTPLIB_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

################################################################################
# install files
################################################################################
install(TARGETS
        an-media
        DESTINATION ${AN_LIBRARIES_DIR}
        COMPONENT "an_media_libraries"
        )