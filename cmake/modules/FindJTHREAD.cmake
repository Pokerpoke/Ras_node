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