aux_source_directory(. AN_TRANSFER_LIB)
add_library(an_transfer_lib SHARED ${AN_TRANSFER_LIB})
target_link_libraries(an_transfer_lib an_core_lib)