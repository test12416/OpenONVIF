project(WsDiscovery)
cmake_minimum_required(VERSION 2.6)

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

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-Bsymbolic-functions -Wl,-Bsymbolic")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(GSOAP 2.8.15 REQUIRED)
message(STATUS "The GSOAP version: ${GSOAP_VERSION}")
message(STATUS "The GSOAP include directory: ${GSOAP_INCLUDE_DIR}")
message(STATUS "The GSOAP libraries: ${GSOAP_LIBRARIES}")
message(STATUS "The GSOAP import directory: ${GSOAP_IMPORT_DIR}")
if( GSOAP_IMPORT_DIR STREQUAL "GSOAP_IMPORT_DIR-NOTFOUND" )
	set(GSOAP_IMPORT_DIR "/usr/local/share/gsoap/import")
endif()

set(WSDD_SOURCE_DIR ${PROJECT_BINARY_DIR}/src)

add_subdirectory(xml)

aux_source_directory(${WSDD_SOURCE_DIR} WSDD_SOURCES)
if(NOT IS_DIRECTORY ${WSDD_SOURCE_DIR})
	file(MAKE_DIRECTORY ${WSDD_SOURCE_DIR})

	execute_process(
		COMMAND ${GSOAP_WSDL2H} -gxP -oh -t${PROJECT_SOURCE_DIR}/typemap.dat ${XML_WSDL_DIR}/remotediscovery.wsdl
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

	file(APPEND ${PROJECT_BINARY_DIR}/h
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
                COMMAND ${GSOAP_SOAPCPP2} -abjnxL -dsrc -pWsdd h -I/usr/share/gsoap/import/stlvector.h
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	)

	foreach(NAME "WsddRemoteDiscoveryBindingProxy" "WsddRemoteDiscoveryBindingService" "WsddC")
		execute_process(
			COMMAND sed -i s/dn:/wsd:/g ${PROJECT_BINARY_DIR}/src/${NAME}.cpp
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		)
	endforeach()

	aux_source_directory(${WSDD_SOURCE_DIR} WSDD_SOURCES)
endif()


include_directories(
    ${PROJECT_SOURCE_DIR}/include
	${WSDD_SOURCE_DIR}
	${GSOAP_INCLUDE_DIR}
	${GSOAP_IMPORT_DIR}/../plugin
    ${PROJECT_SOURCE_DIR}/../common
	${PROJECT_SOURCE_DIR}/../OnvifSDK/gen/include
)

set (STDSOAP2 ${PROJECT_SOURCE_DIR}/../OnvifSDK/gen/include/stdsoap2.h
        ${PROJECT_SOURCE_DIR}/../OnvifSDK/gen/source/stdsoap2.cpp)

set (COMMON_HEADERS ${PROJECT_SOURCE_DIR}/../common/sigrlog.h)

file(GLOB WSDD_HEADERS ${WSDD_SOURCE_DIR}/*.h)
if(ONLY_SERVER)
	file(GLOB WSDD_SOURCES ${PROJECT_SOURCE_DIR}/*_service.cpp)
elseif(ONLY_CLIENT)
        file(GLOB WSDD_SOURCES ${PROJECT_SOURCE_DIR}/*_proxy.cpp)
else(ONLY_SERVER)
	aux_source_directory(${PROJECT_SOURCE_DIR} WSDD_SOURCES)
endif(ONLY_SERVER)

add_definitions(-DWITH_PURE_VIRTUAL)

add_library(${PROJECT_NAME} SHARED
                                    ${STDSOAP2}
                                    ${COMMON_HEADERS}
                                    typemap.dat
                                    ${WSDD_HEADERS} ${WSDD_SOURCES}
)

target_link_libraries(${PROJECT_NAME} pthread)

