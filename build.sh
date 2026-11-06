#!/bin/bash

build_type=Debug

if [[ $# -gt 1 ]] then
	echo "error"
	exit
fi
if [[ $# -eq 1 ]] then
	build_type=$1
fi

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE="$build_type"
cmake --build build
./build/main
