###
project(OnvifSDK)
cmake_minimum_required(VERSION 2.8)

# SIGRLOG_CURRLEVEL:
# level of verboseness of the logger range [0..4]
add_definitions(-DSIGRLOG_CURRLEVEL=4)
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

add_definitions(-DWITH_PURE_VIRTUAL)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

### generate stubs
set(OSDK_GEN_SOURCE_DIR ${PROJECT_BINARY_DIR}/src)
add_subdirectory(xml)

if(NOT IS_DIRECTORY ${OSDK_GEN_SOURCE_DIR})
    file(MAKE_DIRECTORY ${OSDK_GEN_SOURCE_DIR})

    execute_process(
        COMMAND ${GSOAP_WSDL2H} -jgxP -oweb.h  -t${PROJECT_SOURCE_DIR}/typemapWeb.dat
        ${XML_WSDL_DIR}/devicemgmt.wsdl ${XML_WSDL_DIR}/deviceio.wsdl
        ${XML_WSDL_DIR}/display.wsdl ${XML_WSDL_DIR}/recording.wsdl
        ${XML_WSDL_DIR}/replay.wsdl ${XML_WSDL_DIR}/search.wsdl
        ${XML_WSDL_DIR}/receiver.wsdl
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
### remove optional fault element
    execute_process(
        COMMAND sed "s/struct\\sSOAP_ENV__Fault/\\/\\/struct SOAP_ENV__Fault/" web.h
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        OUTPUT_FILE web1.h
    )

    execute_process(
        COMMAND ${GSOAP_WSDL2H} -gxP -ord.h  -t${PROJECT_SOURCE_DIR}/typemapWsdd.dat
        ${XML_WSDL_DIR}/remotediscovery.wsdl
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

    file(APPEND ${PROJECT_BINARY_DIR}/rd.h
            "struct SOAP_ENV__Header {\n"
                    "std::string wsa__MessageID;\n"
                    "wsa__Relationship *wsa__RelatesTo;\n"
                    "wsa__EndpointReferenceType *wsa__From;\n"
                    "wsa__EndpointReferenceType *wsa__ReplyTo;\n"
                    "wsa__EndpointReferenceType *wsa__FaultTo;\n"
                    "std::string  wsa__To;\n"
                    "std::string  wsa__Action;\n"
                    "wsd__AppSequenceType *wsd__AppSequence;\n"
            "};"
    )

    execute_process(
        COMMAND ${GSOAP_SOAPCPP2} -abjnxLw web1.h -dsrc -qWeb -I${GSOAP_IMPORT_DIR} -I${GSOAP_IMPORT_DIR}/..
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
    execute_process(
        COMMAND ${GSOAP_SOAPCPP2} -abjnxLw rd.h -dsrc -pWsdd -I${GSOAP_IMPORT_DIR} -I${GSOAP_IMPORT_DIR}/..
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

    aux_source_directory(${OSDK_GEN_SOURCE_DIR} OSDK_GEN_FILES)
endif()

# list project files
include_directories(${PROJECT_SOURCE_DIR}/../common
                    ${PROJECT_SOURCE_DIR}/gen/include
                    ${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/WsDiscovery
                    ${OSDK_GEN_SOURCE_DIR})

set(HEADERS
    ${PROJECT_SOURCE_DIR}/../common/sigrlog.h
    ${PROJECT_SOURCE_DIR}/gen/include/stdsoap2.h
    ${PROJECT_SOURCE_DIR}/include/stringGenerator.h
    ${PROJECT_SOURCE_DIR}/include/BaseServer.h
    ${PROJECT_SOURCE_DIR}/include/BaseClient.h
    ${PROJECT_SOURCE_DIR}/include/OnvifSDK.h
    ${PROJECT_SOURCE_DIR}/../WsDiscovery/WsddLib.h)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/gen/source/stdsoap2.cpp
    ${PROJECT_SOURCE_DIR}/source/BaseServer.cpp
    ${PROJECT_SOURCE_DIR}/source/BaseClient.cpp)

file(GLOB WSD_FILES ${PROJECT_SOURCE_DIR}/WsDiscovery/*)

file(GLOB OSDK_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB OSDK_SOURCES ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_library(OnvifSDK STATIC     ${SOURCES} ${HEADERS}
                                ${OSDK_GEN_FILES}
                                ${WSD_FILES}
                                ${OSDK_HEADERS}
                                ${OSDK_SOURCES})

target_link_libraries(OnvifSDK pthread)
