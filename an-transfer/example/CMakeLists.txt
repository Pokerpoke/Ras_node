add_executable(qa_udp_send_file_client qa_udp_send_file_client.cc)
target_link_libraries(qa_udp_send_file_client
	an_transfer_lib
	)

file(COPY test.txt
	DESTINATION ${EXECUTABLE_OUTPUT_PATH})
