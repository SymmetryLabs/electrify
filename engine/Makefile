CC=g++
LFLAGS=-shared -o -Wall --std=c++11
LIBRARY=lib/libengine.so
VPATH = ./src:./include
INCLUDE=include
SRC=src
objects := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
headers := $(patsubst %.cpp,%.o,$(wildcard include/*.h))

$(LIBRARY): $(objects) $(headers)
	$(CC) $(LFLAGS) $(LIBRARY) $(objects)

%.o: %.cpp %.h
	make -C $(SRC) $@

clean:
	make -C $(SRC) clean