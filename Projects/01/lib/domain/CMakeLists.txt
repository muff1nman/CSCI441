set(SRCS
	image_2D.cpp
	config.cpp
	RGB.cpp
	ray.cpp
	vector_3D.cpp
	screen_iterator.cpp
	screen.cpp
)

add_library(Domain ${SRCS})

add_subdirectory(shapes)

