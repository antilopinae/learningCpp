add_library(my_lib)
target_sources(my_lib
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        my_lib.cpp
)

add_library(canvas STATIC canvas.cpp)
add_library(try_catch STATIC try_catch.cpp)
add_library(struct STATIC struct.cpp)

add_subdirectory(classes)
add_subdirectory(operations)
