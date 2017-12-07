# find at libraries
find_package(Qt4 4.8 REQUIRED
             QtCore 
             QtGui 
             QtWebKit
             )
include_directories(${QT_INCLUDES})

# qt flags
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(lib)

add_executable(main main.cc)
target_link_libraries(main an_gui_qt)

# copy qss files
file(COPY themes
     DESTINATION ${EXECUTABLE_OUTPUT_PATH})