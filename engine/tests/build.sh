# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=/Users/you/code/electrifying-stunt/engine/lib
# or you can:
# cp ../lib/libengine.so .
g++ -L../lib -I../include -Wall -o main main.cpp -lengine --std=c++11
