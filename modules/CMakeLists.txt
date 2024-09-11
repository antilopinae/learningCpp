add_library(my_lib)
target_sources(my_lib
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        my_lib.cpp
)

add_library(casts)
target_sources(casts
    PUBLIC
        FILE_SET cxx_modules_casts TYPE CXX_MODULES FILES
        casts.cpp
)

add_library(namespaces)
target_sources(namespaces
    PUBLIC
        FILE_SET cxx_modules_namespaces TYPE CXX_MODULES FILES
        namespaces.cpp
)

add_library(modules)
target_sources(modules
    PUBLIC
        FILE_SET cxx_modules_modules TYPE CXX_MODULES FILES
        modules.cpp
)
target_link_libraries(modules PRIVATE
A
)

add_library(noexcepts)
target_sources(noexcepts
    PUBLIC
        FILE_SET cxx_modules_noexcepts TYPE CXX_MODULES FILES
        noexcepts.cpp
)

add_library(move_semantic)
target_sources(move_semantic
    PUBLIC
        FILE_SET cxx_modules_move_semantic TYPE CXX_MODULES FILES
        move_semantic.cpp
)

add_library(move_semantic2)
target_sources(move_semantic2
    PUBLIC
        FILE_SET cxx_modules_move_semantic2 TYPE CXX_MODULES FILES
        move_semantic2.cpp
)

add_library(canvas STATIC canvas.cpp)
add_library(try_catch STATIC try_catch.cpp)
add_library(struct STATIC struct.cpp)

add_subdirectory(classes)
add_subdirectory(operations)
add_subdirectory(templates)
add_subdirectory(concepts)
add_subdirectory(modules)
add_subdirectory(threads)
