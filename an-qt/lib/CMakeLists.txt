aux_source_directory(. AN_QT_LIB)

add_library(an_qt 
            SHARED 
            ${AN_QT_LIB}
            )

target_link_libraries(an_qt
                      an-core
                      Qt4::QtCore 
                      Qt4::QtGui
                    #   Qt4::QtWebKit
                      )

################################################################################
# install files
################################################################################
install(TARGETS
        an_qt
        DESTINATION ${AN_LIBRARIES_DIR}
        COMPONENT "an_qt_libraries"
        )