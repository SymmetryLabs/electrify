# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=<absolute path to...>/electrify/engine/lib
# or you can:
# cp ../lib/libengine.so .
g++ -L../lib -I../src/*.h -Wall -o main main.cpp -lengine --std=c++11
