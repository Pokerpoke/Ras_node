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

# - Find Log4cpp
# Find the native LOG4CPP includes and library
#
#  LOG4CPP_INCLUDE_DIR - where to find LOG4CPP.h, etc.
#  LOG4CPP_LIBRARIES   - List of libraries when using LOG4CPP.
#  LOG4CPP_FOUND       - True if LOG4CPP found.


if (LOG4CPP_INCLUDE_DIR)
    # Already in cache, be silent
    set(LOG4CPP_FIND_QUIETLY TRUE)
endif ()

find_path(LOG4CPP_INCLUDE_DIR
    NAMES Category.hh
    PATH_SUFFIXES log4cpp
    DOC "Log4cpp include directories"
)

find_library(LOG4CPP_LIBRARY
    NAMES log4cpp
    DOC "Log4cpp library"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LOG4CPP
                                  REQUIRED_VARS LOG4CPP_LIBRARY LOG4CPP_INCLUDE_DIR
                                  VERSION_VAR VERSION)

if(LOG4CPP_INCLUDE_DIR AND LOG4CPP_LIBRARY)
    set(LOG4CPP_FOUND TRUE)
    set(LOG4CPP_LIBRARIES ${LOG4CPP_LIBRARY})
    set(LOG4CPP_INCLUDE_DIRS ${LOG4CPP_INCLUDE_DIR})
else()
    set (LOG4CPP_FOUND FALSE)
    message(FATAL_ERROR "LOG4CPP not found")
endif()

mark_as_advanced(
    LOG4CPP_LIBRARIES
    LOG4CPP_INCLUDE_DIRS
)