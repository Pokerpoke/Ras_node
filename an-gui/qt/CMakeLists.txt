# find_package(Qt5Core REQUIRED)
# find_package(Qt5Widgets REQUIRED)
# find_package(Qt5Gui REQUIRED)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(an_gui_qt SHARED developer_tools.cc developer_tools.h)
# target_link_libraries(an_gui_qt Qt5::Widgets)
target_link_libraries(an_gui_qt Qt4::QtCore Qt4::QtGui)

add_executable(main main.cc)
# target_link_libraries(main an_gui_qt Qt5::Widgets)
target_link_libraries(main an_gui_qt Qt4::QtCore Qt4::QtGui)