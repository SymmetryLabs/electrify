# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=<absolute path to...>/electrify/engine/lib
# or you can:
# cp ../lib/libengine.so .
cd "$( dirname "$0" )"
g++ -L../lib -I../src/ -Wall -o main main.cpp -lengine --std=c++11
