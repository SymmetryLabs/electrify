pushd build
g++ --std=c++11 -I../include -c -fpic ../src/*
g++ --std=c++11 -shared -o ../lib/libengine.so *.o
popd
