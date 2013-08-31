
set(LINK_LIBRARIES Domain )

set(SRCS
	simple_environment.cpp
)

add_library(Environment ${SRCS})
target_link_libraries(Environment ${LINK_LIBRARIES})
