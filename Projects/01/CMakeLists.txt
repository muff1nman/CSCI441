cmake_minimum_required( VERSION 2.8 )
project( RayTracer )

# General variables
set( RAYTRACER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Configuration Stuff
option(DEBUG "Turn debuggin on or off" ON)
option(LOGGING "Turn loggin on or off" ON)

# Not needed if using the options above
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOG=1 -DDEBUG=1")

configure_file( 
	${RAYTRACER_INCLUDE_DIR}/raytracer/config/config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/include/raytracer/config/config.h )

# For a vim plugin (not necessary for the project)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


# Project includes 
include_directories( ${RAYTRACER_INCLUDE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}/include )

# Go do work CMake!
add_subdirectory( lib )




