################################################################################
# 
# Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
# 
# @file
# @author   姜阳 (j824544269@gmail.com)
# @date     2018-01
# @brief    
# @version  0.0.1
# 
# Last Modified:  2018-01-08
# Modified By:    姜阳 (j824544269@gmail.com)
# 
################################################################################

aux_source_directory(. AN_CODEC_LIB)
add_library(an-codec SHARED
            ${AN_CODEC_LIB}
            )

target_link_libraries(an-codec
                      an-core
                      ${BCG729_LIBRARIES})