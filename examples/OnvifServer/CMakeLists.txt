###
project(OnvifTestServer)
cmake_minimum_required(VERSION 2.8)

# SIGRLOG_CURRLEVEL:
# level of verboseness of the logger range [0..4]
add_definitions(-DSIGRLOG_CURRLEVEL=2)
# SIGRLOG_OUTPUT:
# destinations of the logger output
# 0 - none, 1 - console only, 2 - file only, 3 - console and file
add_definitions(-DSIGRLOG_OUTPUT=1)
# SIGRLOG_FILENAME
# output filename for logger
add_definitions(-DSIGRLOG_FILENAME=\"oxxServerLog.ini\")

find_library(SDKLIB OnvifSDK ${SDK})
message(STATUS ${SDKLIB})
link_directories(${SDK})

include_directories(${PROJECT_SOURCE_DIR}/../../common
                    ${PROJECT_SOURCE_DIR}/../../OnvifSDK/include
                    ${PROJECT_SOURCE_DIR})


set(HEADERS ${PROJECT_SOURCE_DIR}/../../OnvifSDK/include/OnvifSDK.h
        ${PROJECT_SOURCE_DIR}/../../common/sigrlog.h)	

set(SOURCES		${PROJECT_SOURCE_DIR}/mainServ.cpp
			${PROJECT_SOURCE_DIR}/OnvifTestServer.h
		        ${PROJECT_SOURCE_DIR}/OnvifTestServer.cpp)

add_executable(OnvifTestServer  ${HEADERS} ${SOURCES})

target_link_libraries(OnvifTestServer ${SDKLIB} pthread)
