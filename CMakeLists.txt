project(Aero-Node)

cmake_minimum_required(VERSION 2.6)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(PythonLibs 3)
include_directories(${PYTHON_INCLUDE_PATH})


# 使用doxygen来生成文档
find_package(Doxygen)
	if(DOXYGEN_FOUND)
		# 设置doxygen.in
		set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
		set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
		# 生成配置文件
		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

		message("Doxygen build started.")
		# 生成文档
		add_custom_target(doc
		${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	else (DOXYGEN_FOUND)
		message("Doxygen need to be installed to generate the doxygen documentation")
	endif(DOXYGEN_FOUND)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(an-core)
