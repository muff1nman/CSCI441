
#set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.54 COMPONENTS thread date_time program_options filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(Threads REQUIRED)

set(LINK_LIBRARIES Domain ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
if(${LOGGING})
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif(${LOGGING})

set(SRCS
	simple_environment.cpp
	screen_iterator.cpp
	screen.cpp
	simple_worker.cpp
)

add_library(Environment ${SRCS})
target_link_libraries(Environment ${LINK_LIBRARIES})
