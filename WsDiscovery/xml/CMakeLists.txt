project(${CMAKE_PROJECT_NAME}_xml)
cmake_minimum_required(VERSION 2.6)

find_program(XSLTPROC
	NAMES xsltproc
	HINTS /usr/bin
	DOC "The xsltproc bin directory"
)
if(NOT XSLTPROC)
	message(FATAL_ERROR "Could not find xsltproc")
endif()

file(GLOB XML_FILES *.*)


foreach(XML ${XML_FILES})
	get_filename_component(XML_EXT ${XML} EXT)
	if(XML_EXT STREQUAL ".wsdl" OR XML_EXT STREQUAL ".xsd")
		get_filename_component(XML_NAME ${XML} NAME)
		execute_process(
			COMMAND ${XSLTPROC} -o ${XML_NAME} ${PROJECT_SOURCE_DIR}/patch.xslt ${PROJECT_SOURCE_DIR}/${XML_NAME}
			WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		)
	endif()
endforeach()



file(GLOB WSDL_FILES ${PROJECT_BINARY_DIR}/*.wsdl)
list(REMOVE_ITEM WSDL_FILES ${PROJECT_BINARY_DIR}/bw-2.wsdl)
list(REMOVE_ITEM WSDL_FILES ${PROJECT_BINARY_DIR}/rw-2.wsdl)

#foreach(WSDL ${WSDL_FILES})
#    get_filename_component(WSDL_NAME ${WSDL} NAME)
#    if(WSDL_NAME STREQUAL "bw-2.wsdl" OR WSDL_NAME STREQUAL "rw-2.wsdl")
#        list(REMOVE_ITEM WSDL_FILES ${WSDL})
#    endif()
#endforeach()

set(XML_WSDL_DIR ${PROJECT_BINARY_DIR} PARENT_SCOPE)
set(XML_WSDL_LIST ${WSDL_FILES} PARENT_SCOPE)

add_custom_target(${PROJECT_NAME} SOURCES ${XML_FILES})
