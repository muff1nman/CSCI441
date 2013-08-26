cmake_minimum_required(VERSION 2.8)
project(SimpleParser)

set (PARSE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PARSE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
set(PARSE_SRCS
	${PARSE_SOURCE_DIR}/helper.cpp
)

include_directories(${PARSE_INCLUDE_DIR})

add_library(Parse ${PARSE_SRCS})

add_executable(simple_parser ${PARSE_SOURCE_DIR}/main.cpp)
target_link_libraries(simple_parser Parse)
