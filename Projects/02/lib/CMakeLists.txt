add_subdirectory(gl)

set( SHADER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

set(destDir ${SHADER_OUTPUT_DIR})
set(srcDir "${CMAKE_CURRENT_SOURCE_DIR}/shaders")

make_directory(${destDir})

file(GLOB templateFiles RELATIVE ${srcDir} shaders/*)
message(STATUS "Files to be copied: ${templateFiles}")
foreach(templateFile ${templateFiles})
	set(srcTemplatePath ${srcDir}/${templateFile})
	if(NOT IS_DIRECTORY ${srcTemplatePath})
		message(STATUS "Copying ${templateFile}")
		configure_file(
			${srcTemplatePath}
			${destDir}/${templateFile}
			COPYONLY)
	endif(NOT IS_DIRECTORY ${srcTemplatePath})
endforeach(templateFile)
