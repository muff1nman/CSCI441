cmake_minimum_required(VERSION 2.8)
project(SimpleParser)

 
set(PARSE_SRCS
	parser.cpp
)

set(LINK_LIBRARIES Environment Shapes)
if(${LOGGING})
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif(${LOGGING})

add_library(Parse ${PARSE_SRCS})
target_link_libraries(Parse ${LINK_LIBRARIES})

add_executable(simple_parser main.cpp)
target_link_libraries(simple_parser Parse)
