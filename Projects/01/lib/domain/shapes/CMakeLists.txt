set(SRCS
	sphere.cpp
	triangle.cpp
)

set(LINK_LIBRARIES Domain)

add_library(Shapes ${SRCS})

target_link_libraries(Shapes ${LINK_LIBRARIES})
