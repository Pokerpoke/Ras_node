# - Find BCG729 library
# Once done this will define
# BCG729_FOUND - system has BCG729
# BCG729_INCLUDE_DIR - BCG729 include directories
# BCG729_LIBRARY - where to find the BCG729 library

if(BCG729_INCLUDE_DIR)
    # Already in cache, be silent
    set(BCG729_FIND_QUIETLY TRUE)
endif()

find_path(BCG729_INCLUDE_DIR
    NAMES rtpsession.h
    PATH_SUFFIXES bcg729
    DOC "BCG729 include directories"
    )

find_library(BCG729_LIBRARY
    NAMES jrtp
    DOC "BCG729 library"
    )

# handle the QUIETLY and REQUIRED arguments and set BCG729_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BCG729
                                  REQUIRED_VARS BCG729_LIBRARY BCG729_INCLUDE_DIR
                                  VERSION_VAR BCG729_VERSION_STRING)

if(BCG729_INCLUDE_DIR AND BCG729_LIBRARY)
    set(BCG729_FOUND TRUE)
    set(BCG729_LIBRARIES ${BCG729_LIBRARY})
    set(BCG729_INCLUDE_DIRS ${BCG729_INCLUDE_DIR})
else()
    set (BCG729_FOUND FALSE)
    message(FATAL_ERROR "BCG729 not found")
endif()

mark_as_advanced(
    BCG729_INCLUDE_DIR
    BCG729_LIBRARY)