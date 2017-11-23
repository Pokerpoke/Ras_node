find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# qt5_wrap_ui(Ui_FILES widget.ui)

add_library(an_widget SHARED widget.cpp widget.h)
target_link_libraries(an_widget Qt5::Widgets)

add_executable(main main.cpp)
target_link_libraries(main an_widget Qt5::Widgets)