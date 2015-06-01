# NOTE:  to run app you will need
# export DYLD_FALLBACK_LIBRARY_PATH=/Users/ben/code/electrifying-stunt/engine/lib
# or you can copy the engine/lib/libengine.so to .
g++ -L../engine/lib -I../engine/include -Wall -o app app.cpp -lengine --std=c++11
