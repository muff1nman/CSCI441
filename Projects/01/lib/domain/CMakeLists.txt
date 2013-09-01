set(SRCS
	image_2D.cpp
	config.cpp
	RGB.cpp
	ray.cpp
)

add_library(Domain ${SRCS})

add_subdirectory(shapes)

