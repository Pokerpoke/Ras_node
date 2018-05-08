################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-01
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-01-15
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

aux_source_directory(. AN_G729_LIB)
add_library(an-g729 SHARED
            ${AN_G729_LIB}
            )

target_link_libraries(an-g729
                      an-core
                      ${BCG729_LIBRARIES})

################################################################################
# install files
################################################################################
install(TARGETS
        an-g729
        DESTINATION ${AN_LIBRARIES_DIR}
        COMPONENT "an_g729_libraries"
        )