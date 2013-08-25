include_directories ("${PROJECT_SOURCE_DIR}/parse")
add_subdirectory(parse)

add_executable(Main main.cpp)
target_link_libraries(Main Parse)

