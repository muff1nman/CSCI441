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

