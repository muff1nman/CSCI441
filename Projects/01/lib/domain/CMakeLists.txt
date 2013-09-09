set(SRCS
	image_2D.cpp
	RGB.cpp
	vector_3D.cpp
	ray.cpp
	material.cpp
)


add_library(Domain ${SRCS})
if(${LOGGING})
	target_link_libraries(Domain glog)
endif(${LOGGING})

add_subdirectory(shapes)

