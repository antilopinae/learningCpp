# теперь буду использовать только modules c++ 20

add_library(concept_x)
target_sources(concept_x
    PUBLIC
        FILE_SET cxx_modules_concept TYPE CXX_MODULES FILES
        concept_x.cpp
)
