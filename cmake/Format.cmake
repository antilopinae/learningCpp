function(Format target directory)
	find_program(CLANG-FORMAT_PATH clang-format REQUIRED)
	set(EXPRESSION h hpp hh cc c cxx cpp)
	list(TRANSFORM EXPRESSION PREPEND "{directory}/*.")
	file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
		LIST_DIRECTORIES false ${EXPRESSION}
	)
	add_custom_command(TARGET ${target} PRE_BUILD COMMAND
		${CLANG-FORMAT_PATH} -style=file -i ${ALL_SOURCE_FILES}
	)
endfunction()
