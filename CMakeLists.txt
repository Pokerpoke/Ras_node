project(Aero-Node)

cmake_minimum_required(VERSION 2.8.0)

# 使用C++11编译
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif() 

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	add_definitions(-DENABLE_DEBUG)
endif()

set(CMAKE_MODULE_PATH 
	APPEND "${CMAKE_SOURCE_DIR}/cmake/Modules/"
	)

# 添加Swig库
# find_package(SWIG)
# 	if(SWIG_FOUND)
# 		include(${SWIG_USE_FILE})
# 	endif(SWIG_FOUND)

# find_package(PythonLibs 3)
# include_directories(${PYTHON_INCLUDE_PATH})

# 添加Boost库
# find_package(Boost
# 	COMPONENTS system
# 	REQUIRED
# 	)
# 	if(Boost_FOUND)
# 		include_directories(${Boost_INCLUDE_DIRS})
# 	endif(Boost_FOUND)

# # 添加pthread
# find_package(Threads REQUIRED)

# 添加glog库
# find_package(glog)
# 	if(glog_FOUND)
# 		include_directories(${glog_INCLUDE_DIRS})
# 	endif(glog_FOUND)
	

# 添加log4cpp库
find_package(log4cpp REQUIRED)
include_directories(${LOG_4_CPP_INCLUDE_DIR})

# 添加alsa库
find_package(ALSA REQUIRED)
include_directories(${ALSA_INCLUDE_DIR})

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
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include_directories(
	# ${ALSA_INCLUDE_DIR}
	# ${LOG_4_CPP_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/an-core/include
	${CMAKE_CURRENT_SOURCE_DIR}/an-transfer/include
)

add_subdirectory(an-core)
add_subdirectory(an-transfer)


# 显示include directories
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "Include dir='${dir}'")
endforeach()