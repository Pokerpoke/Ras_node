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

add_executable(qa_cam_capture qa_cam_capture.cc)
target_link_libraries(qa_cam_capture
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_cam_capture_to_file qa_cam_capture_to_file.cc)
target_link_libraries(qa_cam_capture_to_file
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)

# add_executable(qa_cam_capture_video qa_cam_capture_video.cc)
# target_link_libraries(qa_cam_capture_video
# 	an_core_lib
# 	${LOG4CPP_LIBRARIES}
# 	)

add_executable(qa_cam_capture_stream_to_file qa_cam_capture_stream_to_file.cc)
target_link_libraries(qa_cam_capture_stream_to_file
	an_core_lib
	${LOG4CPP_LIBRARIES}
	)

add_executable(qa_voice_capture qa_voice_capture.cc)
target_link_libraries(qa_voice_capture
	an_core_lib
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	)

add_executable(qa_voice_playback qa_voice_playback.cc)
target_link_libraries(qa_voice_playback
	an_core_lib
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	)

add_executable(qa_voice_test qa_voice_test.cc)
target_link_libraries(qa_voice_test
	an_core_lib
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	)