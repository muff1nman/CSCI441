#include_directories (${PARSE_INCLUDE_DIR})
message(STATUS ${PARSE_INCLUDE_DIR})
#include_directories (../parse/include)

add_executable(Main main.cpp)
target_link_libraries(Main Parse)

