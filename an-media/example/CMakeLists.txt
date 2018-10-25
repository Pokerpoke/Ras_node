################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-06
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-06-20
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################
aux_source_directory(. EXAMPLE_EXECUTABLE)
foreach(T_FILE_NAME ${EXAMPLE_EXECUTABLE})
	get_filename_component(EXECUTABLE_NAME ${T_FILE_NAME} NAME_WE)
	# message(${EXECUTABLE_NAME})
	add_executable(${EXECUTABLE_NAME} ${T_FILE_NAME})
	target_link_libraries(${EXECUTABLE_NAME}
		an-core
		an-media
		${LOG4CPP_LIBRARIES}
		${JRTPLIB_LIBRARIES}
        ${ALSA_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
	)
endforeach()