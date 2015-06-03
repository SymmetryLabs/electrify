CC=g++
CFLAGS=-c -Wall --std=c++11 -fpic
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(objects)

%.o: %.cpp ../include/%.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o