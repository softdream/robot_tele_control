CMAKE_MINIMUM_REQUIRED( VERSION 3.5.1 )

ADD_DEFINITIONS( -std=c++11 )

FIND_PACKAGE( Threads )

SET( EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin" )

AUX_SOURCE_DIRECTORY( ${PROJECT_SOURCE_DIR}/src source_file )

INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}/include" )

LINK_DIRECTORIES( "${PROJECT_SOURCE_DIR}/libs" )

ADD_EXECUTABLE( robot_control ${source_file} )

TARGET_LINK_LIBRARIES( robot_control libpcs.a ${CMAKE_THREAD_LIBS_INIT} )
