#!/bin/bash
# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=<absolute path to...>/electrify/engine/lib
# or you can:
# cp ../lib/libengine.so .
cd "$( dirname "$0" )"
g++ -L../build -I../build/include -o main main.cpp -lSymmetryEngine --std=c++11
