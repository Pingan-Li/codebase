#!/bin/bash
cmake -S ./ -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B out/Debug -DCMAKE_BUILD_TYPE=Debug
cmake -S ./ -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B out/Release -DCMAKE_BUILD_TYPE=Release
cmake -S ./ -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B out/RelWithDebInfo -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake -S ./ -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B out/MinSizeRel -DCMAKE_BUILD_TYPE=MinSizeRel