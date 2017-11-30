aux_source_directory(. EXAMPLE_EXECUTABLE)
foreach(T_FILE_NAME ${EXAMPLE_EXECUTABLE})
	get_filename_component(EXECUTABLE_NAME ${T_FILE_NAME} NAME_WE)
	# message(${EXECUTABLE_NAME})
	add_executable(${EXECUTABLE_NAME} ${T_FILE_NAME})
	target_link_libraries(${EXECUTABLE_NAME}
		an_core
		# ${LOG4CPP_LIBRARIES}
		# ${JRTPLIB_LIBRARIES}
		# ${ALSA_LIBRARIES}
	)
endforeach()