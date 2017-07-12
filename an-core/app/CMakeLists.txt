add_executable(qa_system_info qa_system_info.cc)
target_link_libraries(qa_system_info an_core_lib)

add_executable(qa_udp_client qa_udp_client.cc)
target_link_libraries(qa_udp_client 
	an_core_lib 
	${Boost_LIBRARIES}
	pthread
)

add_executable(qa_tcp_client_c qa_tcp_client_c.cc)
target_link_libraries(qa_tcp_client_c an_core_lib)