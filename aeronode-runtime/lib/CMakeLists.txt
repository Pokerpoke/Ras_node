aux_source_directory(. AN_CORE_LIB)

# remove json parser for cannot build on Tiny4412
if(CMAKE_BUILD_TARGET STREQUAL Tiny4412)
    list(REMOVE_ITEM AN_CORE_LIB
         "./json.hpp"
         "./config_json.h"
         "./config_json.cc")
endif()

add_library(an-core SHARED ${AN_CORE_LIB})
target_link_libraries(an-core
	${LOG4CPP_LIBRARIES}
	${ALSA_LIBRARIES}
	${JRTPLIB_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

################################################################################
# install files
################################################################################
install(TARGETS
        an-core
        DESTINATION ${AN_LIBRARIES_DIR}
        COMPONENT "an_core_libraries"
        )