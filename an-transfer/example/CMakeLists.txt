add_executable(qa_udp_send_file_client qa_udp_send_file_client.cc)
target_link_libraries(qa_udp_send_file_client
	an_transfer_lib
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_tcp_send_file_client qa_tcp_send_file_client.cc)
target_link_libraries(qa_tcp_send_file_client
	an_transfer_lib
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)


file(COPY test.txt
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY test.txt
	DESTINATION ${EXECUTABLE_OUTPUT_PATH})