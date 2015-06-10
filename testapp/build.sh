#!/bin/bash
# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=<absolute path to...>/electrify/engine/build
# or you can:
# cp ../engine/lib/libengine.so .
cd "$( dirname "$0" )"
g++ -L../engine/build -I../engine/src/ -I../engine/libs/jsoncpp -Wall -o app app.cpp -lSymmetryEngine --std=c++11
