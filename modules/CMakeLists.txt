add_library(my_lib)
target_sources(my_lib
    PRIVATE
        my_lib.cpp
)
target_sources(my_lib
    PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        my_lib.cppm
)
target_compile_options(my_lib
	PRIVATE -std=c++20
	PRIVATE -fmodules-ts
)
