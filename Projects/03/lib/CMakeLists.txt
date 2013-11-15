add_subdirectory(gl)
add_subdirectory(parse)


# for opengl stuff
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set( GLM_INCLUDE_DIRS "/usr/include/glm")
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}) 


#include shaders file
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

set(LINK_LIBRARIES glviewer_gl glviewer_parse ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GLEW )

IF(Boost_FOUND)
	set(LINK_LIBRARIES ${LINK_LIBRARIES} ${Boost_LIBRARIES})
ENDIF()

add_executable(glviewer glviewer.cpp)

target_link_libraries(glviewer ${LINK_LIBRARIES})

###########################################################################
# COPY SHADERS 
###########################################################################
set( SHADER_DIR_NAME "shaders")
set( SHADER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR_NAME}")

# shaders file
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/shader_locations.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/shader_locations.h )

set(destDir ${SHADER_OUTPUT_DIR})
set(srcDir "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_DIR_NAME}/")

make_directory(${destDir})

file(GLOB templateFiles RELATIVE ${srcDir} ${SHADER_DIR_NAME}/*)
message(STATUS "Files to be copied: ${templateFiles}")
foreach(templateFile ${templateFiles})
	set(srcTemplatePath ${srcDir}/${templateFile})
	if(NOT IS_DIRECTORY ${srcTemplatePath})
		message(STATUS "Copying ${templateFile}")
		configure_file(
			${srcTemplatePath}
			${destDir}/${templateFile}
			COPYONLY)
	endif(NOT IS_DIRECTORY ${srcTemplatePath})
endforeach(templateFile)

###########################################################################
# COPY TEXTURES
###########################################################################
set( TEXTURE_DIR_NAME "textures")
set( TEXTURE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${TEXTURE_DIR_NAME}")

# config file for location paths.
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/texture_locations.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/texture_locations.h )

set(destDir ${TEXTURE_OUTPUT_DIR})
set(srcDir "${CMAKE_CURRENT_SOURCE_DIR}/${TEXTURE_DIR_NAME}/")

make_directory(${destDir})

file(GLOB_RECURSE templateFiles RELATIVE ${srcDir} ${TEXTURE_DIR_NAME}/*)
message(STATUS "Files to be copied: ${templateFiles}")
foreach(templateFile ${templateFiles})
	set(srcTemplatePath ${srcDir}/${templateFile})
	if(NOT IS_DIRECTORY ${srcTemplatePath})
		message(STATUS "Copying ${templateFile}")
		configure_file(
			${srcTemplatePath}
			${destDir}/${templateFile}
			COPYONLY)
	endif(NOT IS_DIRECTORY ${srcTemplatePath})
endforeach(templateFile)
