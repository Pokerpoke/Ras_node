################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-06
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-06-20
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################
include_directories(include)

# find at libraries
find_package(Qt4 4.8 REQUIRED
             QtCore 
             QtGui 
            #  QtWebKit
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
target_link_libraries(aero-node an_qt)

# copy qss files
# file(COPY themes
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

################################################################################
# install files
################################################################################
install(DIRECTORY themes
        DESTINATION ${AN_ETC_DIR}
        COMPONENT "aero-node/themes")

install(TARGETS
        aero-node
        DESTINATION ${AN_BINARIES_DIR}
        COMPONENT "binaries"
        )