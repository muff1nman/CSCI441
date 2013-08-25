include_directories ("../parse")
#add_subdirectory(../parse)

add_executable(Main main.cpp)
target_link_libraries(Main Parse)

