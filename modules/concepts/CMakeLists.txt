# теперь буду использовать только modules c++ 20

add_library(concept_x)
target_sources(concept_x
    PUBLIC
        FILE_SET cxx_modules_concept TYPE CXX_MODULES FILES
        concept_x.cpp
)
add_library(concept2_x)
target_sources(concept2_x
    PUBLIC
        FILE_SET cxx_modules_concept2 TYPE CXX_MODULES FILES
        concept2_x.cpp
)
