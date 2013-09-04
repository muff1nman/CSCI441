set(SRCS
	image_2D.cpp
	RGB.cpp
	ray.cpp
	vector_3D.cpp
	screen_iterator.cpp
	screen.cpp
)


add_library(Domain ${SRCS})
if(${LOGGING})
	target_link_libraries(Domain glog)
endif(${LOGGING})

add_subdirectory(shapes)

