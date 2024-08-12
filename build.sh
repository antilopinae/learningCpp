#!/bin/bash
#rm -R build
#cmake -G "Ninja" -D CMAKE_C_COMPILER="usr/bin/gcc" -D CMAKE_CXX_COMPILER="/usr/bin/clang-18" -B build -S .
echo "Generating"
cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug -D CMAKE_C_COMPILER="/usr/bin/clang" -D CMAKE_CXX_COMPILER="/usr/bin/clang++" -G Ninja -B build -S .  # note, the ninja build tool is faster than the make tool referenced in the docs.

echo "Building"
cmake --build build -t coverage

echo "Testing"
cd build
ctest
cd ..

echo "Graphviz"
cd build
mkdir graph
cmake --graphviz=graph/test.dot .
dot -Tpdf graph/test.dot >> deps.pdf
dot -Tpdf graph/test.dot.sut >> sut.pdf
cd ..

echo "Running"
./build/bin/bootstrap
