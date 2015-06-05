# NOTE:  to run app on OSX you will need:
# export DYLD_FALLBACK_LIBRARY_PATH=<absolute path to...>/electrify/engine/lib
# or you can:
# cp ../engine/lib/libengine.so .
g++ -L../engine/lib -I../engine/src/ -Wall -o app app.cpp -lengine --std=c++11
