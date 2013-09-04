
set(LINK_LIBRARIES Domain )
if(${LOGGING})
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif(${LOGGING})

set(SRCS
	simple_environment.cpp
)

add_library(Environment ${SRCS})
target_link_libraries(Environment ${LINK_LIBRARIES})
