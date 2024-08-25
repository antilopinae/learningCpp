add_library(A)
target_sources(A
    PUBLIC
        FILE_SET cxx_modules_a TYPE CXX_MODULES FILES
        A.cpp
        A-B.cpp
        A-C.cpp
)
