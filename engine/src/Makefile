CC=g++
CPPFLAGS= -Wall --std=c++11 -fpic
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(objects)

%.o: %.cpp ../include/%.h
	$(CC) $(CPPFLAGS) $< -o $@
clean:
	rm -f *.o