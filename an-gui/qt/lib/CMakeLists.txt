aux_source_directory(. AN_GUI_QT_LIB)

add_library(an_gui_qt 
            SHARED 
            ${AN_GUI_QT_LIB}
            )

target_link_libraries(an_gui_qt
                      an-core
                      Qt4::QtCore 
                      Qt4::QtGui
                      Qt4::QtWebKit
                      )

################################################################################
# install files
################################################################################
install(TARGETS
        an_gui_qt
        DESTINATION ${CMAKE_BINARY_DIR}/lib
        COMPONENT "an_gui_qt_libraries"
        )