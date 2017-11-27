# cross compile settings
if(CMAKE_BUILD_TARGET STREQUAL Tiny4412)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolschain/Tiny4412.cmake)
endif()

# project name
project(Aero-Node)
# set version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_DEBUG 3)

cmake_minimum_required(VERSION 2.8.6)

# 使用C++11编译
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	add_definitions(-DENABLE_DEBUG)
endif()

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

# 添加jrtp库
find_package(JRTPLIB REQUIRED)
include_directories(${JRTPLIB_INCLUDE_DIR})

# 添加jthread库
find_package(JTHREAD REQUIRED)
include_directories(${JTHREAD_INCLUDE_DIR})

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

# 设置可执行文件输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

include_directories(
    ${CMAKE_SOURCE_DIR}/an-core/include
    ${CMAKE_SOURCE_DIR}/an-transfer/include
)

add_subdirectory(an-core)
add_subdirectory(an-gui)
# add_subdirectory(an-transfer)