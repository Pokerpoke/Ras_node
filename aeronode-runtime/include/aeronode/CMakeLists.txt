aux_source_directory(. AN_HEADERS)

install(FILES
        cam_capture.h
        logger.h
        DESTINATION ${AN_INCLUDE_DIR}/aeronode/
        COMPONENT "runtime_devel"
        )
