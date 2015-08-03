#!/bin/bash
# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=<absolute path to...>/electrify/engine/lib
# or you can:
# cp ../lib/libengine.so .
cd "$( dirname "$0" )"
g++ --std=c++11                             \
-I../src                                    \
-I../src/core                               \
-I../src/blueprint                          \
-I../src/blueprint_ui                       \
-I../src/nodes                              \
-I../src/nodes/oscillators                  \
-I../src/nodes/transforms                   \
-I../src/utils                              \
-isystem ../../build/engine/ext_include     \
-isystem /usr/local/include                 \
-o main *.cpp                               \
-Wl,-rpath,@loader_path/../../build/engine  \
-L../../build/engine -lSymmetryEngine       \
