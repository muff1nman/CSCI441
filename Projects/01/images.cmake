
#message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
#set( INPUT_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/instructions_and_provided_resources/testdata )
file(GLOB INPUT_FILES ${INPUT_FILE_DIR}/test*.txt )
#set( INPUT_FILES test1.txt )

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMAGE_DIR})

message(STATUS $<TARGET_FILE:Simple> )

foreach(_d_file ${INPUT_FILES} )
	get_filename_component(_file ${_d_file} NAME)
	string(REGEX REPLACE "\\.txt" ".ppm" _image ${_file})
	execute_process(
		COMMAND ${SCRIPT_NAME} ${INPUT_FILE_DIR}/${_file} ${OUTPUT_IMAGE_DIR}/${_image}
		ERROR_QUIET)
endforeach()
