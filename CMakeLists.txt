################################################################################
# 
# Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
# 
# @file
# @author   姜阳 (j824544269@gmail.com)
# @date     2017-12
# @brief    
# @version  0.0.1
# 
# Last Modified:  2017-12-25
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

# cross compile settings
if(CMAKE_BUILD_TARGET STREQUAL Tiny4412)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolschain/Tiny4412.cmake)
    set(AN_BUILD_TARGET "#define AN_TARGET_TINY4412")
else()
    set(AN_BUILD_TARGET "#define AN_TARGET_X86")
endif()

# project name
project(Aero-Node)
# set version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_DEBUG 4)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_DEBUG}")

cmake_minimum_required(VERSION 2.8.6)

# Enable test or not
option(ENABLE_TEST "Enable test or not" OFF)

# Check debug flag
# #define confilt with log4cpp, so use ENABLE_DEBUG to enable debug
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DENABLE_DEBUG)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
    set(ENABLE_TEST ON)
endif()

# 使用C++11编译
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# include some modules
include(CheckIncludeFile)
include(CheckIncludeFileCXX)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in 
               ${CMAKE_CURRENT_BINARY_DIR}/aeronode-runtime/include/aeronode/config.h
               )

# add module path
set(CMAKE_MODULE_PATH 
    APPEND "${CMAKE_SOURCE_DIR}/cmake/modules/"
    )

# 添加log4cpp库
find_package(LOG4CPP REQUIRED)
include_directories(${LOG4CPP_INCLUDE_DIR})

# 添加alsa库
find_package(ALSA REQUIRED)
include_directories(${ALSA_INCLUDE_DIR})

# 添加jthread库
find_package(JTHREAD REQUIRED)
include_directories(${JTHREAD_INCLUDE_DIR})

# 添加jrtp库
find_package(JRTPLIB REQUIRED)
include_directories(${JRTPLIB_INCLUDE_DIR})

# 添加bcg729库
find_package(BCG729 REQUIRED)
include_directories(${BCG729_INCLUDE_DIR})

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_PATH})

# 添加线程相关的库
find_package(Threads REQUIRED)

# 使用doxygen来生成文档
find_package(Doxygen)
    if(DOXYGEN_FOUND)
        # 设置doxygen.in
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        # 生成配置文件
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        message(STATUS "Doxygen build started.")
        # 生成文档
        add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
    else (DOXYGEN_FOUND)
        message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
    endif(DOXYGEN_FOUND)

# install paths
set(AN_INCLUDE_DIR usr/include CACHE PATH "Path to install header files")
set(AN_LIBRARIES_DIR usr/lib CACHE PATH "Path to install libraries")
set(AN_BINARIES_DIR usr/bin CACHE PATH "Path to install binaries")
set(AN_ETC_DIR usr/share/aero-node CACHE PATH "Path to install etc directories")

include_directories(aeronode-runtime/include
                    ${CMAKE_BINARY_DIR}/aeronode-runtime/include
                    an-g729/include
                    )

################################################################################
# unit test
################################################################################
if(ENABLE_TEST)
    find_package(GTest REQUIRED)
        if(GTEST_FOUND)
            include(GoogleTest)
            include_directories(${GTEST_INCLUDE_DIR})
            enable_testing()
            message(STATUS "Enable test")
        else (GTEST_FOUND)
            message(STATUS "Google test libraries is needed when enable test")
        endif(GTEST_FOUND)
endif(ENABLE_TEST)

add_subdirectory(aeronode-runtime)
add_subdirectory(an-qt)
add_subdirectory(an-g729)

# build executable program
add_subdirectory(binary)

################################################################################
# install files
################################################################################
install(FILES
        ${CMAKE_BINARY_DIR}/aeronode-runtime/include/aeronode/config.h
        DESTINATION ${AN_INCLUDE_DIR}/aeronode
        COMPONENT "runtime_devel"
        )
