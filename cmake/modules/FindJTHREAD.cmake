################################################################################
 # 
 # Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 # 
 # @file
 # @author   姜阳 (j824544269@gmail.com)
 # @date     2017-11
 # @brief    
 # @version  0.0.1
 # 
 # Last Modified:  2017-12-25
 # Modified By:    姜阳 (j824544269@gmail.com)
 # 
################################################################################

# - Find JTHREAD library
# Once done this will define
# JTHREAD_FOUND - system has JTHREAD
# JTHREAD_INCLUDE_DIR - JTHREAD include directories
# JTHREAD_LIBRARY - where to find the JTHREAD library

if(JTHREAD_INCLUDE_DIR)
    # Already in cache, be silent
    set(JTHREAD_FIND_QUIETLY TRUE)
endif()

find_path(JTHREAD_INCLUDE_DIR
    NAMES jthread.h
    PATH_SUFFIXES jthread jthread3
    DOC "JTHREAD include directories"
    )

find_library(JTHREAD_LIBRARY
    NAMES jthread
    DOC "JTHREAD library"
    )

# handle the QUIETLY and REQUIRED arguments and set JTHREAD_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JTHREAD
                                  REQUIRED_VARS JTHREAD_LIBRARY JTHREAD_INCLUDE_DIR
                                  VERSION_VAR JTHREAD_VERSION_STRING)

if(JTHREAD_INCLUDE_DIR AND JTHREAD_LIBRARY)
    set(JTHREAD_FOUND TRUE)
    set(JTHREAD_LIBRARIES ${JTHREAD_LIBRARY})
    set(JTHREAD_INCLUDE_DIRS ${JTHREAD_INCLUDE_DIR})
else()
    set (JTHREAD_FOUND FALSE)
    message(FATAL_ERROR "JTHREAD not found")
endif()

mark_as_advanced(
    JTHREAD_INCLUDE_DIR
    JTHREAD_LIBRARY)