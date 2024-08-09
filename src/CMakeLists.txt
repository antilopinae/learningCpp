set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(modules)

target_compile_options(modules
	PUBLIC -fmodules-ts
)

add_library(sut STATIC run.cpp)
target_include_directories(sut PUBLIC .)

target_link_libraries(sut PRIVATE modules)

target_compile_options(sut
	PUBLIC -O3
	PUBLIC -finline-functions
	#PUBLIC -ftree-vectorize
)

target_compile_options(sut
	PUBLIC -std=c++20
	PUBLIC -fmodules-ts
)

#target_precompile_headers(sut PRIVATE <iostream>)

target_compile_options(sut PRIVATE -save-temps=obj)
#target_compile_options(sut PRIVATE -H)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	target_compile_options(sut PRIVATE --coverage)
	target_link_options(sut PUBLIC --coverage)
	add_custom_command(TARGET sut PRE_BUILD COMMAND
		find ${CMAKE_BINARY_DIR} -type f
		-name '*.gcda' -exec rm {} +)
endif()


include(Format)
Format(sut .)

add_executable(bootstrap bootstrap.cpp)
target_link_libraries(bootstrap PRIVATE sut)
