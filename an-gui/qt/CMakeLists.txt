# find at libraries
find_package(Qt4 4.8 REQUIRED
             QtCore 
             QtGui 
             QtWebKit
			 )

include_directories(${QT_INCLUDES})
include_directories(include)

# qt flags
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(lib)

add_executable(aero-node aero-node.cc)
target_link_libraries(aero-node an_gui_qt)

# copy qss files
file(COPY themes
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})