import helloworld;

#include <iostream>

int hi();
void test_exception();
void test_struct();
void test_vector();
void test_vector_container();
void test_list_container();

int run() {
	std::cout<<hello()<<std::endl;
	test_vector_container();
	test_list_container();

	return 0;
}
