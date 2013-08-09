###
project(OnvifSDK)
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

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(GSOAP 2.8.15 REQUIRED)
message(STATUS "The GSOAP version: ${GSOAP_VERSION}")
message(STATUS "The GSOAP include directory: ${GSOAP_INCLUDE_DIR}")
message(STATUS "The GSOAP libraries: ${GSOAP_LIBRARIES}")
message(STATUS "The GSOAP import directory: ${GSOAP_IMPORT_DIR}")

if( GSOAP_IMPORT_DIR STREQUAL "GSOAP_IMPORT_DIR-NOTFOUND" )
    set(GSOAP_IMPORT_DIR "/usr/local/share/gsoap/import")
endif()


### find dependency
find_library(WSDDLIB WsDiscovery ${WSDD})
link_directories(${WSDD})
message(STATUS "WSDDLIB = ${WSDDLIB}")
add_definitions(-DWITH_PURE_VIRTUAL)

### generate stubs
set(OSDK_GEN_SOURCE_DIR ${PROJECT_BINARY_DIR}/src)
add_subdirectory(xml)

if(NOT IS_DIRECTORY ${OSDK_GEN_SOURCE_DIR})
    file(MAKE_DIRECTORY ${OSDK_GEN_SOURCE_DIR})

    execute_process(
        COMMAND ${GSOAP_WSDL2H} -gxP -oh -t/usr/local/share/gsoap/WS/typemap.dat
        ${XML_WSDL_DIR}/devicemgmt.wsdl ${XML_WSDL_DIR}/deviceio.wsdl
        ${XML_WSDL_DIR}/display.wsdl ${XML_WSDL_DIR}/recording.wsdl 
        ${XML_WSDL_DIR}/replay.wsdl ${XML_WSDL_DIR}/search.wsdl
        ${XML_WSDL_DIR}/receiver.wsdl
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

    execute_process(
        COMMAND ln -s ${GSOAP_IMPORT_DIR}/stlvector.h stlvector.h
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

    execute_process(
        COMMAND ln -s ${GSOAP_IMPORT_DIR}/soap12.h soap12.h
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

    execute_process(
        COMMAND ${GSOAP_SOAPCPP2} -abjnxL h -dsrc -I${GSOAP_IMPORT_DIR} -I${GSOAP_IMPORT_DIR}/..
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

    aux_source_directory(${OSDK_GEN_SOURCE_DIR} OSDK_GEN_FILES)
endif()

# list project files
include_directories(${PROJECT_SOURCE_DIR}/../common
                    ${PROJECT_SOURCE_DIR}/gen/include
                    ${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/../WsDiscovery
                    ${OSDK_GEN_SOURCE_DIR})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/../common/sigrlog.h
    ${PROJECT_SOURCE_DIR}/gen/include/stdsoap2.h
    ${PROJECT_SOURCE_DIR}/gen/include/duration.h
    ${PROJECT_SOURCE_DIR}/include/stringGenerator.h
    ${PROJECT_SOURCE_DIR}/include/BaseServer.h
    ${PROJECT_SOURCE_DIR}/include/BaseClient.h
    ${PROJECT_SOURCE_DIR}/include/OnvifSDK.h
    ${PROJECT_SOURCE_DIR}/../WsDiscovery/WsddLib.h)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/gen/source/stdsoap2.cpp
    ${PROJECT_SOURCE_DIR}/gen/source/duration.cpp
    ${PROJECT_SOURCE_DIR}/source/BaseServer.cpp
    ${PROJECT_SOURCE_DIR}/source/BaseClient.cpp)

file(GLOB OSDK_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB OSDK_SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(OnvifSDK SHARED     ${SOURCES} ${HEADERS}
                                ${OSDK_GEN_FILES}
                                ${OSDK_HEADERS}
                                ${OSDK_SOURCES})

target_link_libraries(OnvifSDK ${WSDDLIB})
