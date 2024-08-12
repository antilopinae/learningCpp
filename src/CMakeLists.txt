add_library(sut STATIC run.cpp)
target_include_directories(sut PUBLIC .)

target_link_libraries(sut PRIVATE my_lib)

target_compile_options(sut
	PUBLIC -O3
	PUBLIC -finline-functions
	PUBLIC -ftree-vectorize
)

target_compile_options(sut PRIVATE -save-temps=obj)

include(Format)
Format(sut .)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	target_compile_options(sut PRIVATE --coverage)
	target_link_options(sut PUBLIC --coverage)
	add_custom_command(TARGET sut PRE_BUILD COMMAND
		find ${CMAKE_BINARY_DIR} -type f
		-name '*.gcda' -exec rm {} +)
endif()

#[=[
target_compile_options(sut
	PRIVATE -std=c++20
	PRIVATE -fmodules-ts
)
#target_precompile_headers(sut PRIVATE <iostream>)
#target_compile_options(sut PRIVATE -H)
#]=]

add_executable(bootstrap bootstrap.cpp)
target_link_libraries(bootstrap PRIVATE sut)
