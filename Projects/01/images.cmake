
file(GLOB INPUT_FILES ${INPUT_FILE_DIR}/test*.txt )

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMAGE_DIR})

foreach(_d_file ${INPUT_FILES} )
	get_filename_component(_file ${_d_file} NAME)
	string(REGEX REPLACE "\\.txt" ".ppm" _image ${_file})
	execute_process(
		COMMAND ${SCRIPT_NAME} ${INPUT_FILE_DIR}/${_file} ${OUTPUT_IMAGE_DIR}/${_image})
endforeach()
