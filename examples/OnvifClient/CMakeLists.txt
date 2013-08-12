###
project(OnvifTestClient)
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
add_definitions(-DSIGRLOG_FILENAME=\"clientLog.ini\")

find_library(SDKLIB OnvifSDK ${SDK})
if( SDKLIB STREQUAL "SDKLIB-NOTFOUND" )
    message(FATAL_ERROR "OnvifSDK library wasn't provided")
endif()
message(STATUS "OSDK Library : ${SDKLIB}")

include_directories(${PROJECT_SOURCE_DIR}/../../common
                    ${PROJECT_SOURCE_DIR}/../../OnvifSDK/include)

set(${HEADERS} ${PROJECT_SOURCE_DIR}/../../OnvifSDK/include/OnvifSDK.h)

set(SOURCES 
	${PROJECT_SOURCE_DIR}/mainClient.cpp)
							
add_executable(OnvifTestClient  ${SOURCES} 			${HEADERS})
target_link_libraries(OnvifTestClient ${SDKLIB} pthread)

