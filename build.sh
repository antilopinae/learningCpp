#!/bin/bash
rm -R build
#cmake -G "Ninja" -D CMAKE_C_COMPILER="usr/bin/gcc" -D CMAKE_CXX_COMPILER="/usr/bin/clang-18" -B build -S .
cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -D CMAKE_C_COMPILER="/usr/bin/clang" -D CMAKE_CXX_COMPILER="/usr/bin/clang++" -G Ninja -B build -S .  # note, the ninja build tool is faster than the make tool referenced in the docs.
cmake --build build
./build/bin/bootstrap
