project(Aero-Node)

cmake_minimum_required(VERSION 2.6)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(PythonLibs 3)
include_directories(${PYTHON_INCLUDE_PATH})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(an-core)
