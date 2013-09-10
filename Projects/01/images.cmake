
file(GLOB INPUT_FILES ${INPUT_FILE_DIR}/test*.txt )

if( NOT INPUT_FILES )
	message(STATUS "test data not extracted... attempting extraction")
	execute_process(COMMAND tar -C ../instructions_and_provided_resources/ -xvf ../instructions_and_provided_resources/testdata.tar )
	file(GLOB INPUT_FILES ${INPUT_FILE_DIR}/test*.txt )
endif()


execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMAGE_DIR})

foreach(_d_file ${INPUT_FILES} )
	get_filename_component(_file ${_d_file} NAME)
	string(REGEX REPLACE "\\.txt" ".ppm" _image ${_file})
	execute_process(
		COMMAND ${SCRIPT_NAME} ${INPUT_FILE_DIR}/${_file} ${OUTPUT_IMAGE_DIR}/${_image})
endforeach()
