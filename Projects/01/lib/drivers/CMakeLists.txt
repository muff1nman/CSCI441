set(LINK_LIBRARIES ImageOutput Domain Parse Environment)
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
