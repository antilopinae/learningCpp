#!/bin/bash
rm -R build
cmake -G "Ninja" -B build -S .
cmake --build build

