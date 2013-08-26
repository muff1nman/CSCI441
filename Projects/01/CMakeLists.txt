cmake_minimum_required( VERSION 2.8 )
project( RayTracer )

# For a vim plugin (not necessary for the project)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( RAYTRACER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

include_directories( ${RAYTRACER_INCLUDE_DIR} )

add_subdirectory( lib )



