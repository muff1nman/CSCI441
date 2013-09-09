cmake_minimum_required( VERSION 2.8 )
project( RayTracer )

# General variables
set( RAYTRACER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Configuration Stuff
option(DEBUG "Turn debuggin on or off" ON)
option(LOGGING "Turn loggin on or off" ON)

# Not needed if using the options above
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOG=1 -DDEBUG=1")

# c++ 11 stuff
if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS "enabling c++ 11")
	add_definitions(-std=gnu++0x)
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

# Add custom target for transforming all the files

add_custom_target(images)
add_dependencies(images Simple)

#configure_file(
	#${CMAKE_CURRENT_SOURCE_DIR}/images.cmake.in


add_custom_command(TARGET images
	COMMAND ${CMAKE_COMMAND} 
	-DINPUT_FILE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/instructions_and_provided_resources/testdata
	-DOUTPUT_IMAGE_DIR=${CMAKE_CURRENT_BINARY_DIR}/images
	-DSCRIPT_NAME=$<TARGET_FILE:Simple>
	-P ${CMAKE_CURRENT_SOURCE_DIR}/images.cmake)

