add_executable(qa_system_info qa_system_info.cc)
target_link_libraries(qa_system_info 
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_udp_client qa_udp_client.cc)
target_link_libraries(qa_udp_client 
	an_core_lib 
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_udp_server qa_udp_server.cc)
target_link_libraries(qa_udp_server 
	an_core_lib 
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_tcp_client qa_tcp_client.cc)
target_link_libraries(qa_tcp_client 
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_tcp_server qa_tcp_server.cc)
target_link_libraries(qa_tcp_server 
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)