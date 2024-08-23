import helloworld;

#include <iostream>

int hi();
void test_exception();
void test_struct();
void test_vector();
void test_vector_container();
void test_list_container();
void test_complex_x();
void test_vector_x();
void test_parallel();
void test_vector_t();
void test_limit();
void test_template_args();
void test_pair();
void test_example_vector();
void test_deduction_guide();
void test_template_func_obj();
void test_init_mode();
void test_template_value_ex(); // нельзя одновременно с test_vector_t();
void test_if_time_compile();

import concept_x;
import concept2_x;

int run() {
	hello();
	// test_concept_x();
	test_concept2_x();

	return 0;
}
