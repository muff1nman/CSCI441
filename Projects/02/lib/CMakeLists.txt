add_subdirectory(gl)
add_subdirectory(parse)


# for opengl stuff
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set( GLM_INCLUDE_DIRS "/usr/include/glm")
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}) 

set(LINK_LIBRARIES glviewer_gl glviewer_parse ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GLEW)

add_executable(glviewer glviewer.cpp)

target_link_libraries(glviewer ${LINK_LIBRARIES})

# COPY SHADERS

set( SHADER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

set(destDir ${SHADER_OUTPUT_DIR})
set(srcDir "${CMAKE_CURRENT_SOURCE_DIR}/shaders")

make_directory(${destDir})

file(GLOB templateFiles RELATIVE ${srcDir} shaders/*)
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
