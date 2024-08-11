cmake_minimum_required(VERSION 3.26.0)
project(Test CXX)
#enable_testing()

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDER 1)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  include(gcc_modules.cmake)
endif()


#[=[
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  include(gcc_modules.cmake)
endif()
]=]


#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#add_compile_options(-fmodules-ts)
add_subdirectory(modules)
add_subdirectory(src bin)
#add_subdirectory(test)
#configure_file(.clang-format .clang-format COPYONLY)
