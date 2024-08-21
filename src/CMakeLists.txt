add_library(sut STATIC run.cpp)
target_include_directories(sut PUBLIC .)

target_link_libraries(sut PRIVATE my_lib)
target_link_libraries(sut PRIVATE canvas)
target_link_libraries(sut PRIVATE try_catch)
target_link_libraries(sut PRIVATE struct)
target_link_libraries(sut PRIVATE complex)
target_link_libraries(sut PRIVATE container)
target_link_libraries(sut PRIVATE
complex_x
vector_x
)
target_link_libraries(sut PRIVATE
parallel
)
target_link_libraries(sut PRIVATE
vector_t
# limit
template_args
pair
example_vector
deduction_guide
template_func_obj
)


#target_compile_options(sut PRIVATE -save-temps=obj)
#include(Format REQUIRED)
#Format(sut .)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	target_compile_options(sut PRIVATE --coverage)
	target_link_options(sut PUBLIC --coverage)
	add_custom_command(TARGET sut PRE_BUILD COMMAND
		find ${CMAKE_BINARY_DIR} -type f
		-name '*.gcda' -exec rm {} +
	)
endif()

if (CMAKE_BUILD_TYPE STREQUAL Release)
	target_compile_options(sut
		PUBLIC -O3
		PUBLIC -finline-functions
		PUBLIC -ftree-vectorize
	)

	include(CheckIPOSupported)
	check_ipo_supported(RESULT ipo_supported)
	if(ipo_supported)
		set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
	endif()
endif()

#[=[
#target_precompile_headers(sut PRIVATE <iostream>)
#target_compile_options(sut PRIVATE -H)
#]=]

add_executable(bootstrap bootstrap.cpp)
target_link_libraries(bootstrap PRIVATE sut)
