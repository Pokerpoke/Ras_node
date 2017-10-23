aux_source_directory(. AN_TRANSFER_LIB)
add_library(an_transfer SHARED ${AN_TRANSFER_LIB})
target_link_libraries(an_transfer 
	an_core
	${LOG4CPP_LIBRARIES}
	)