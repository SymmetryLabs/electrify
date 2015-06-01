pushd build
g++ -I../include -c -fpic ../src/*
g++ -shared -o ../lib/libengine.so *.o
popd
