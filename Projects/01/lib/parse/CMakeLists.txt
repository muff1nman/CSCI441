cmake_minimum_required(VERSION 2.8)
project(SimpleParser)

 
set(PARSE_SRCS
	helper.cpp
)

add_library(Parse ${PARSE_SRCS})

add_executable(simple_parser main.cpp)
target_link_libraries(simple_parser Parse)
