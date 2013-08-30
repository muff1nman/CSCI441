add_executable(Main main.cpp)
target_link_libraries(Main ImageOutput Domain Parse)

add_executable(intersect find_intersections.cpp)
target_link_libraries(intersect ImageOutput Domain Parse)

add_executable(ParseTest parse_test.cpp)
target_link_libraries(ParseTest ImageOutput Domain Parse)
