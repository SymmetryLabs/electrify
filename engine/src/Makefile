CC=g++
CPPFLAGS= -Wall --std=c++11 -fpic
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
LFLAGS=-shared -Wall --std=c++11
LIBRARY=../lib/libengine.so

$(LIBRARY): $(objects)
	$(CC) $(LFLAGS) -o $(LIBRARY) $(objects)

%.o: %.cpp %.h
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o