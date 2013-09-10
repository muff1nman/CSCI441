
#set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.54 COMPONENTS thread date_time program_options filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(Threads REQUIRED)


set(LINK_LIBRARIES ImageOutput Domain Parse Environment ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
if(${LOGGING})
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif(${LOGGING})

add_executable(Main main.cpp)
target_link_libraries(Main ${LINK_LIBRARIES})

add_executable(intersect find_intersections.cpp)
target_link_libraries(intersect ${LINK_LIBRARIES})

add_executable(ParseTest parse_test.cpp)
target_link_libraries(ParseTest ${LINK_LIBRARIES})

add_executable(Simple simple_image.cpp)
target_link_libraries(Simple ${LINK_LIBRARIES})

add_executable(Test single_test.cpp)
target_link_libraries(Test ${LINK_LIBRARIES})
