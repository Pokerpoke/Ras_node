aux_source_directory(. AN_GUI_QT_LIB)

add_library(an_gui_qt 
            SHARED 
            ${AN_GUI_QT_LIB}
            )

target_link_libraries(an_gui_qt
                      an_core
                      Qt4::QtCore 
                      Qt4::QtGui
                      Qt4::QtWebKit
                      )