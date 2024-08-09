#!/bin/bash

echo "Setupping your project.."
echo "Are you agree?"

read answer

if [ $answer == "yes" ] ;then

rm -R src
rm -R build
rm -R CMakeLists.txt
rm -R test
rm -R cmake


mkdir src
mkdir test
mkdir cmake

printf 'cmake_minimum_required(VERSION 3.20.0)
project(Formatting CXX)
enable_testing()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
add_subdirectory(src bin)
add_subdirectory(test)
#configure_file(.clang-format .clang-format COPYONLY)' >> CMakeLists.txt

printf 'add_library(sut STATIC run.cpp)
target_include_directories(sut PUBLIC .)

#include(Format)
#Format(sut .)

add_executable(bootstrap bootstrap.cpp)
target_link_libraries(bootstrap PRIVATE sut)' >> src/CMakeLists.txt

printf 'int run();
int main() {
	run();
}' >> src/bootstrap.cpp

printf '#include <iostream>
using namespace std;

int run() {
	return 0;
}' >> src/run.cpp

printf '' >> test/CMakeLists.txt

else
	echo "Ok, see you next time!"
fi
