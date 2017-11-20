# - Find V4L2 library
# Find the native V4L2 includes and library
# This module defines
#  V4L2_INCLUDE_DIR, where to find libv4l2.h, etc.
#  V4L2_LIBRARIES, libraries to link against to use V4L2.
#  V4L2_FOUND, If false, do not try to use V4L2. also defined, but not for general use are
#  V4L2_LIBRARY, where to find the V4L2 library.
#
#=============================================================================
# Copyright 2012 Juergen Heinemann (Undefined) http://www.hjcms.de
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#
#=============================================================================

if (V4L2_INCLUDE_DIR)
    # Already in cache, be silent
    set(V4L2_FIND_QUIETLY TRUE)
endif ()
# SET (V4L2_FOUND 0)

find_path (V4L2_INCLUDE_DIR
    NAMES libv4l2.h libv4lconvert.h
    PATH_SUFFIXES v4l2 video4linux
    DOC "The Video4Linux Version 2 (v4l2) include directory"
)

find_path (_videodev2
    NAMES videodev2.h
    PATH_SUFFIXES linux
    DOC "Video for Linux Two header file include directory"
)

find_library (V4L2_LIBRARY
    NAMES v4l2 v4lconvert
    DOC "The Video4Linux Version 2 (v4l2) library"
)

# handle the QUIETLY and REQUIRED arguments and set V4L2_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(V4L2
                                  REQUIRED_VARS V4L2_LIBRARY V4L2_INCLUDE_DIR
                                  VERSION_VAR V4L2_VERSION_STRING)

if (V4L2_FOUND)
    set (V4L2_LIBRARIES ${V4L2_LIBRARY})
    set (V4L2_INCLUDE_DIRS ${V4L2_INCLUDE_DIR})
else (V4L2_FOUND)
    message (WARNING "libv4l2 or libv4lconvert libraries from http://linuxtv.org not found!")
endif (V4L2_FOUND)

if (NOT _videodev2)
    message (WARNING "videodev2.h kernel header not found!")
    set (V4L2_FOUND 0)
endif(NOT _videodev2)

mark_as_advanced (V4L2_INCLUDE_DIR V4L2_LIBRARY)

##EOF