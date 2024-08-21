add_library(vector_t vector_t.cpp
)
# add_library(limit limit.cpp
# )
add_library(template_args template_args.cpp
)
add_library(pair pair.cpp
)
add_library(example_vector example_vector.cpp
)
add_library(deduction_guide deduction_guide.cpp
)
add_library(template_func_obj template_func_obj.cpp
vector_t.cpp
)
target_link_libraries(template_func_obj PUBLIC vector_t)
