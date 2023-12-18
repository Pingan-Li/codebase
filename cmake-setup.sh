#!/bin/bash
cmake -S ./ -G Ninja -B out/Debug -DCMAKE_BUILD_TYPE=Debug
cmake -S ./ -G Ninja -B out/Release -DCMAKE_BUILD_TYPE=Release
cmake -S ./ -G Ninja -B out/RelWithDebInfo -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake -S ./ -G Ninja -B out/MinSizeRel -DCMAKE_BUILD_TYPE=MinSizeRel