#!/bin/bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Debug .
(cd build; make -j12)
./build/Qomodoro
