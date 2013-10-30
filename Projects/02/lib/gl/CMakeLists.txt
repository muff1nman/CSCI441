set( SRCS
	buffer.cpp
	program.cpp
	shader.cpp
	vertexarray.cpp
	)

add_library(glviewer_gl ${SRCS})

# for opengl stuff
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
set( GLM_INCLUDE_DIRS "/usr/include/glm")
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}) 

set(LINK_LIBRARIES glviewer_gl ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GLEW)

add_executable(viewer viewer.cpp)

target_link_libraries(viewer ${LINK_LIBRARIES})
