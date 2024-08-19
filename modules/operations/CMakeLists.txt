add_library(x x.cpp)
add_library(complex_x complex.cpp)
add_library(vector_x vector_x.cpp
vector_x.h
)
add_library(parallel
parallel.cpp
vector_x.cpp
vector_x.h
)

