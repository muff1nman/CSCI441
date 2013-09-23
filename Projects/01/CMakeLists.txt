cmake_minimum_required( VERSION 2.6 )
project( RayTracer )

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# General variables
set( RAYTRACER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Configuration Stuff
option(DEBUG "Turn debuggin on or off" ON)
option(LOGGING "Turn loggin on or off" ON)
set( LOG_LEVEL 1 )
if(DEBUG)
	set( LOG_LEVEL 0 )
endif(DEBUG)

# Not needed if using the options above
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOG=1 -DDEBUG=1")

# profiling stuff
if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS "enabling c++ 11")
	#add_definitions(-std=gnu++0x)
	if(DEBUG)
		message(STATUS "enabling gprof")
		add_definitions(-Wall)
		add_definitions(-pg)
		set( CMAKE_EXE_LINKER_FLAGS -pg )
	endif(DEBUG)
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	message(STATUS "enabling c++ 11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

configure_file( 
	${RAYTRACER_INCLUDE_DIR}/raytracer/config/config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/include/raytracer/config/config.h )

# For a vim plugin (not necessary for the project)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


# Project includes 
include_directories( ${RAYTRACER_INCLUDE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}/include )

# For the optional types
find_package(Boost 1.54)
include_directories(${Boost_INCLUDE_DIR})

# not needed unless the optional types goes away
#if(LOGGING)
	##set(Boost_USE_STATIC_LIBS ON)
	#find_package(Boost 1.54)
	#include_directories(${Boost_INCLUDE_DIR})
	#message(STATUS "boost include dir: " ${Boost_INCLUDE_DIR} )
#endif(LOGGING)

# Go do work CMake!
add_subdirectory( lib )

# Add custom target for transforming all the files in the inputs folder

add_custom_target(images)
add_dependencies(images inputs testdata)

add_custom_target(inputs)
add_dependencies(inputs Simple)

add_custom_command(TARGET inputs
	COMMAND ${CMAKE_COMMAND} 
	-DINPUT_FILE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/instructions_and_provided_resources/inputs
	-DOUTPUT_IMAGE_DIR=${CMAKE_CURRENT_BINARY_DIR}/inputs
	-DSCRIPT_NAME=${CMAKE_CURRENT_BINARY_DIR}/lib/drivers/Simple
	-DBASE_NAME=input
	-P ${CMAKE_CURRENT_SOURCE_DIR}/images.cmake)

add_custom_target(testdata)
add_dependencies(testdata Simple)

add_custom_command(TARGET testdata
	COMMAND ${CMAKE_COMMAND} 
	-DINPUT_FILE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/instructions_and_provided_resources/testdata
	-DOUTPUT_IMAGE_DIR=${CMAKE_CURRENT_BINARY_DIR}/testdata
	-DBASE_NAME=test
	-DSCRIPT_NAME=${CMAKE_CURRENT_BINARY_DIR}/lib/drivers/Simple
	-P ${CMAKE_CURRENT_SOURCE_DIR}/images.cmake)

