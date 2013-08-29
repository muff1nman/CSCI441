set(SRCS
	image_output.cpp
)

add_library(ImageOutput ${SRCS})
target_link_libraries(ImageOutput Domain)

